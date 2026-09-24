proc fail {message} {
    puts stderr ""
    puts stderr "ERROR: $message"
    catch {close_project}
    exit 1
}

proc strip_quotes {value} {
    set value [string trim $value]

    if {[string length $value] >= 2} {
        set first [string index $value 0]
        set last  [string index $value end]

        if {($first eq "\"" && $last eq "\"") ||
            ($first eq "\{" && $last eq "\}")} {
            return [string range $value 1 end-1]
        }
    }

    return $value
}

proc append_unique {var_name value} {
    upvar 1 $var_name values

    if {[lsearch -exact $values $value] < 0} {
        lappend values $value
    }
}

proc read_ip_manifest {manifest_file} {
    set manifest_file [file normalize $manifest_file]

    if {![file exists $manifest_file]} {
        error "IP manifest not found: $manifest_file"
    }

    set ips {}
    set fd [open $manifest_file r]
    set line_number 0

    while {[gets $fd line] >= 0} {
        incr line_number
        set line [string trim $line]

        if {$line eq ""} {
            continue
        }

        if {[string match "#*" $line] || [string match "//*" $line]} {
            continue
        }

        set name [strip_quotes $line]

        if {![regexp {^[A-Za-z0-9_.-]+$} $name]} {
            close $fd
            error "$manifest_file:$line_number: invalid IP name '$name'"
        }

        append_unique ips $name
    }

    close $fd

    if {[llength $ips] == 0} {
        error "IP manifest is empty: $manifest_file"
    }

    return $ips
}

proc ip_recipe_path {recipe_dir ip_name} {
    return [file join $recipe_dir "${ip_name}.tcl"]
}

proc get_ip_exact {name} {
    return [get_ips -quiet $name]
}

proc get_xci_for_ip {name} {
    set matches [get_files -quiet "*${name}.xci"]

    if {[llength $matches] == 0} {
        set matches [get_files -quiet "${name}.xci"]
    }

    return $matches
}

proc reset_bad_ooc_run {name {force_reset 0}} {
    set run_name "${name}_synth_1"
    set run [get_runs -quiet $run_name]

    if {[llength $run] == 0} {
        return
    }

    set status [get_property STATUS $run]
    set status_lc [string tolower $status]

    set bad_status [expr {
        [string match "*error*" $status_lc] ||
        [string match "*fail*"  $status_lc]
    }]

    if {$force_reset || $bad_status} {
        puts "Resetting OOC synthesis run '$run_name' (status: $status)"
        if {[catch {reset_run $run} err]} {
            fail "Could not reset OOC run '$run_name': $err"
        }
    }
}

proc export_recipe {ip_name recipe_dir {force_write 0}} {
    file mkdir $recipe_dir

    set ip [get_ip_exact $ip_name]
    if {[llength $ip] == 0} {
        fail "Cannot export recipe for missing IP '$ip_name'."
    }

    set output [ip_recipe_path $recipe_dir $ip_name]

    if {!$force_write && [file exists $output]} {
        puts "Recipe already exists: $output"
        return
    }

    puts "Writing IP recipe: $ip_name -> $output"

    # Keep the IP version in the recipe. On a future Vivado release the
    # recreated IP can then follow the normal upgrade_ip flow.
    if {[catch {write_ip_tcl -force $ip $output} err]} {
        fail "Could not export recipe for IP '$ip_name': $err"
    }
}

proc recreate_ip_from_recipe {ip_name recipe_dir} {
    set recipe [ip_recipe_path $recipe_dir $ip_name]

    if {![file exists $recipe]} {
        fail "IP '$ip_name' must be recreated, but no recipe exists: $recipe"
    }

    set old_ip [get_ip_exact $ip_name]

    if {[llength $old_ip] > 0} {
        puts "Removing existing IP '$ip_name' before recreation..."

        catch {delete_ip_run -force $old_ip}

        set xci_files [get_xci_for_ip $ip_name]

        foreach xci $xci_files {
            set xci_path [get_property NAME $xci]
            puts "Removing XCI from project: $xci_path"

            if {[catch {remove_files $xci} err]} {
                fail "Could not remove XCI for IP '$ip_name': $err"
            }
        }
    }

    puts "Recreating IP '$ip_name' from:"
    puts "  $recipe"

    if {[catch {source $recipe} err]} {
        fail "Could not recreate IP '$ip_name' from recipe: $err"
    }

    set new_ip [get_ip_exact $ip_name]
    if {[llength $new_ip] == 0} {
        fail "Recipe completed but IP '$ip_name' was not created."
    }

    return $new_ip
}

proc ensure_ip_exists {ip_name recipe_dir} {
    set ip [get_ip_exact $ip_name]

    if {[llength $ip] > 0} {
        return $ip
    }

    puts ""
    puts "IP '$ip_name' is missing from the project."

    return [recreate_ip_from_recipe $ip_name $recipe_dir]
}

proc upgrade_if_needed {ip_name ip} {
    set locked   [get_property IS_LOCKED $ip]
    set upgrades [get_property UPGRADE_VERSIONS $ip]
    set modified 0

    puts "Locked           : $locked"
    puts "Upgrade versions : $upgrades"

    if {$upgrades ne ""} {
        puts "Upgrading IP '$ip_name' to the catalog version..."

        if {[catch {upgrade_ip $ip} err]} {
            fail "Could not upgrade IP '$ip_name': $err"
        }

        set ip [get_ip_exact $ip_name]
        set modified 1

        puts "Upgrade complete."
    }

    set locked_after [get_property IS_LOCKED $ip]

    if {$locked_after} {
        fail "IP '$ip_name' is still locked and Vivado offers no usable automatic upgrade. A project-specific recreation recipe or manual migration is required."
    }

    return [list $ip $modified]
}

proc generate_ip_products {ip_name ip force_reset_run} {
    puts "Generating output products for '$ip_name'..."

    if {[catch {generate_target all $ip} err]} {
        fail "Could not generate output products for IP '$ip_name': $err"
    }

    reset_bad_ooc_run $ip_name $force_reset_run

    catch {validate_ip $ip}
}

proc warn_unexpected_ips {expected_ips} {
    set project_ips [get_ips -quiet]
    set unexpected {}

    foreach ip $project_ips {
        set name [get_property NAME $ip]

        if {[lsearch -exact $expected_ips $name] < 0} {
            lappend unexpected $name
        }
    }

    if {[llength $unexpected] > 0} {
        puts ""
        puts "WARNING: The project contains IPs not listed in the selected manifest:"
        foreach name $unexpected {
            puts "  $name"
        }
        puts "They will not be modified by this script."
        puts ""
    }
}

proc report_status {report_dir suffix} {
    file mkdir $report_dir
    set report_file [file join $report_dir "ip_status_${suffix}.rpt"]

    if {[catch {report_ip_status -file $report_file} err]} {
        puts "WARNING: Could not write IP status report: $err"
        return
    }

    puts "IP status report: [file normalize $report_file]"
}

proc check_expected_ips {expected_ips recipe_dir report_dir} {
    update_ip_catalog

    report_status $report_dir before
    warn_unexpected_ips $expected_ips

    foreach ip_name $expected_ips {
        puts ""
        puts "============================================================"
        puts "IP: $ip_name"
        puts "============================================================"

        set ip [ensure_ip_exists $ip_name $recipe_dir]

        lassign [upgrade_if_needed $ip_name $ip] ip modified

        generate_ip_products $ip_name $ip $modified

        # On the first successful run, create a reproducible recipe without
        # changing already-versioned recipes during every build.
        export_recipe $ip_name $recipe_dir 0

        puts "Status: OK"
    }

    report_status $report_dir after

    set locked_names {}

    foreach ip_name $expected_ips {
        set ip [get_ip_exact $ip_name]

        if {[llength $ip] == 0} {
            fail "Expected IP '$ip_name' disappeared from the project."
        }

        if {[get_property IS_LOCKED $ip]} {
            lappend locked_names $ip_name
        }
    }

    if {[llength $locked_names] > 0} {
        fail "Locked IPs remain after preparation: [join $locked_names {, }]"
    }
}

proc export_expected_recipes {expected_ips recipe_dir report_dir} {
    update_ip_catalog

    # Export only after bringing the expected IPs to a usable state.
    foreach ip_name $expected_ips {
        puts ""
        puts "Preparing '$ip_name' before exporting its recipe..."

        set ip [ensure_ip_exists $ip_name $recipe_dir]
        lassign [upgrade_if_needed $ip_name $ip] ip modified
        generate_ip_products $ip_name $ip $modified
        export_recipe $ip_name $recipe_dir 1
    }

    report_status $report_dir exported
}

proc recreate_expected_ips {expected_ips recipe_dir report_dir} {
    update_ip_catalog

    foreach ip_name $expected_ips {
        puts ""
        puts "============================================================"
        puts "FORCE RECREATE: $ip_name"
        puts "============================================================"

        set ip [recreate_ip_from_recipe $ip_name $recipe_dir]
        lassign [upgrade_if_needed $ip_name $ip] ip modified

        generate_ip_products $ip_name $ip 1
    }

    report_status $report_dir recreated
}

if {$argc < 4} {
    fail "Usage: ip_manage.tcl <project.xpr> <check|export|recreate> <ips.f> <recipe_dir>"
}

set project_xpr [file normalize [lindex $argv 0]]
set mode        [lindex $argv 1]
set manifest    [file normalize [lindex $argv 2]]
set recipe_dir  [file normalize [lindex $argv 3]]

if {![file exists $project_xpr]} {
    fail "Project file not found: $project_xpr"
}

if {![file exists $manifest]} {
    fail "IP manifest not found: $manifest"
}

if {[catch {set expected_ips [read_ip_manifest $manifest]} err]} {
    fail $err
}

set project_dir [file dirname $project_xpr]
set report_dir  [file join $project_dir reports]

puts "============================================================"
puts "RS5 IP MANAGEMENT"
puts "Project  : $project_xpr"
puts "Mode     : $mode"
puts "Manifest : $manifest"
puts "Recipes  : $recipe_dir"
puts "Expected : [join $expected_ips {, }]"
puts "============================================================"

open_project $project_xpr

puts "Vivado project part: [get_property PART [current_project]]"

switch -- $mode {
    check {
        check_expected_ips $expected_ips $recipe_dir $report_dir
    }

    export {
        export_expected_recipes $expected_ips $recipe_dir $report_dir
    }

    recreate {
        recreate_expected_ips $expected_ips $recipe_dir $report_dir
    }

    default {
        fail "Unknown mode '$mode'. Use check, export or recreate."
    }
}

puts ""
puts "============================================================"
puts "IP MANAGEMENT COMPLETE"
puts "============================================================"

close_project
exit 0
