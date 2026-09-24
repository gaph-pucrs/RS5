proc fail {message} {
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

proc parse_filelist {filelist result_var incdir_var stack_var} {
    upvar 1 $result_var result
    upvar 1 $incdir_var incdirs
    upvar 1 $stack_var stack

    set filelist [file normalize $filelist]

    if {![file exists $filelist]} {
        error "Filelist not found: $filelist"
    }

    if {[lsearch -exact $stack $filelist] >= 0} {
        set chain [concat $stack [list $filelist]]
        error "Circular -f inclusion detected:\n  [join $chain "\n  -> "]"
    }

    lappend stack $filelist
    set list_dir [file dirname $filelist]

    puts "Reading filelist: $filelist"

    set fd [open $filelist r]
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

        if {[regexp {^-f[ \t]+(.+)$} $line -> included]} {
            set included [strip_quotes $included]

            if {[file pathtype $included] eq "relative"} {
                set included [file join $list_dir $included]
            }

            if {[catch {
                parse_filelist $included result incdirs stack
            } err]} {
                close $fd
                error "$filelist:$line_number: $err"
            }

            continue
        }

        if {[regexp {^\+incdir\+(.+)$} $line -> incdir] ||
            [regexp {^-incdir(?:[ \t]+|=)(.+)$} $line -> incdir] ||
            [regexp {^-I[ \t]*(.+)$} $line -> incdir]} {

            set incdir [strip_quotes $incdir]

            if {[file pathtype $incdir] eq "relative"} {
                set incdir [file join $list_dir $incdir]
            }

            set incdir [file normalize $incdir]

            if {![file isdirectory $incdir]} {
                close $fd
                error "$filelist:$line_number: include directory not found: $incdir"
            }

            append_unique incdirs $incdir
            continue
        }

        set source [strip_quotes $line]

        if {[file pathtype $source] eq "relative"} {
            set source [file join $list_dir $source]
        }

        set source [file normalize $source]

        if {![file exists $source]} {
            close $fd
            error "$filelist:$line_number: source file not found: $source"
        }

        append_unique result $source
    }

    close $fd
    set stack [lrange $stack 0 end-1]
}

proc add_sources_to_fileset {fileset sources} {
    foreach source $sources {
        set existing [get_files -quiet $source]

        if {[llength $existing] == 0} {
            puts "Adding source: $source"
            add_files -norecurse -fileset $fileset $source
        } else {
            puts "Source already present: $source"
        }
    }
}

if {$argc < 5} {
    fail "Usage: prepare_project.tcl <project.xpr> <rtl.f> <constraints.f> <expected_part> <expected_top>"
}

set project_xpr          [file normalize [lindex $argv 0]]
set rtl_filelist         [file normalize [lindex $argv 1]]
set constraints_filelist [file normalize [lindex $argv 2]]
set expected_part        [lindex $argv 3]
set expected_top         [lindex $argv 4]

foreach required [list $project_xpr $rtl_filelist $constraints_filelist] {
    if {![file exists $required]} {
        fail "Required file not found: $required"
    }
}

puts "============================================================"
puts "RS5 PROJECT PREPARATION"
puts "Project     : $project_xpr"
puts "RTL list    : $rtl_filelist"
puts "Constraints : $constraints_filelist"
puts "Part        : $expected_part"
puts "Top         : $expected_top"
puts "============================================================"

open_project $project_xpr

set actual_part [get_property PART [current_project]]

if {$actual_part ne $expected_part} {
    fail "FPGA part mismatch. Project='$actual_part', expected='$expected_part'."
}

set rtl_sources {}
set rtl_incdirs {}
set rtl_stack {}

if {[catch {
    parse_filelist $rtl_filelist rtl_sources rtl_incdirs rtl_stack
} err]} {
    fail $err
}

set constraints {}
set constraint_incdirs {}
set constraint_stack {}

if {[catch {
    parse_filelist $constraints_filelist constraints constraint_incdirs constraint_stack
} err]} {
    fail $err
}

puts ""
puts "Resolved RTL sources: [llength $rtl_sources]"
puts "Resolved constraints: [llength $constraints]"
puts "Resolved include dirs: [llength $rtl_incdirs]"
puts ""

add_sources_to_fileset sources_1 $rtl_sources

foreach constraint $constraints {
    set ext [string tolower [file extension $constraint]]

    if {$ext ne ".xdc"} {
        fail "Non-XDC file listed in constraints filelist: $constraint"
    }

    set existing [get_files -quiet $constraint]

    if {[llength $existing] == 0} {
        puts "Adding constraint: $constraint"
        add_files -norecurse -fileset constrs_1 $constraint
    } else {
        puts "Constraint already present: $constraint"
    }
}

if {[llength $rtl_incdirs] > 0} {
    set_property include_dirs $rtl_incdirs [get_filesets sources_1]
}

set_property top $expected_top [get_filesets sources_1]

update_compile_order -fileset sources_1

set final_top [get_property TOP [get_filesets sources_1]]

if {$final_top ne $expected_top} {
    fail "Could not set synthesis top to '$expected_top'. Current top: '$final_top'."
}

puts ""
puts "============================================================"
puts "PROJECT PREPARATION COMPLETE"
puts "Part        : [get_property PART [current_project]]"
puts "Top         : $final_top"
puts "RTL files   : [llength $rtl_sources]"
puts "Constraints : [llength $constraints]"
puts "============================================================"

close_project
exit 0
