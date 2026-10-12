#################################################################################
# MMMC views of the Genus flow (RS5 synthesis/scripts MMMC file; library files from
# scripts/config/pdk.env: LIB_SS/TT/FF, QRC_WORST/TYP/BEST, LEF_TECH, LEF_CELLS)
#################################################################################

set CONSTRAINTS_PATH ./scripts ;# replaced at run time by synth.tcl

#################################################################
## library_sets (lib from library)
#################################################################

# worst case, 0.81 V / 125 C
create_library_set -name libset_0p81v_125c \
    -timing  "$::env(LIB_SS)"

# typical, 0.90 V / 25 C
create_library_set -name libset_0p90v_25c \
    -timing  "$::env(LIB_TT)"

# best case, 0.99 V / -40 C
create_library_set -name libset_0p99v_m40c \
    -timing  "$::env(LIB_FF)"


#################################################################
## Operation condition (opcond)
#################################################################

create_opcond -name opcond_0p81v_125c -voltage 0.81 -temperature 125.0
create_opcond -name opcond_0p90v_25c  -voltage 0.90 -temperature  25.0
create_opcond -name opcond_0p99v_m40c -voltage 0.99 -temperature -40.0


#################################################################
## timing_condition
#################################################################

create_timing_condition -name timing_cond_0p81v_125c \
    -opcond         opcond_0p81v_125c \
    -library_sets { libset_0p81v_125c }

create_timing_condition -name timing_cond_0p90v_25c \
    -opcond         opcond_0p90v_25c \
    -library_sets { libset_0p90v_25c }

create_timing_condition -name timing_cond_0p99v_m40c \
    -opcond         opcond_0p99v_m40c \
    -library_sets { libset_0p99v_m40c }


#################################################################
## rc_corner
#################################################################

 create_rc_corner -name rc_corner_125c_capwst \
    -temperature 125.0 \
     -qrc_tech $::env(QRC_WORST)

 create_rc_corner -name rc_corner_25c_captyp \
     -temperature 25.0 \
    -qrc_tech $::env(QRC_TYP)

 create_rc_corner -name rc_corner_m40c_capbst \
     -temperature -40.0 \
     -qrc_tech $::env(QRC_BEST)


#################################################################
## delay_corner
#################################################################

create_delay_corner -name delay_corner_0p81v_125c_capwst \
    -timing_condition timing_cond_0p81v_125c \
     -rc_corner rc_corner_125c_capwst

create_delay_corner -name delay_corner_0p90v_25c_captyp \
    -timing_condition timing_cond_0p90v_25c \
     -rc_corner rc_corner_25c_captyp

create_delay_corner -name delay_corner_0p99v_m40c_capbst \
    -timing_condition timing_cond_0p99v_m40c \
     -rc_corner rc_corner_m40c_capbst


#################################################################
## constraint_mode
#################################################################
create_constraint_mode -name constraints_default \
    -sdc_files "${CONSTRAINTS_PATH}/constraints.sdc"


#################################################################
## analysis_view
#################################################################

create_analysis_view -name analysis_view_0p81v_125c_capwst_slowest \
    -constraint_mode constraints_default \
    -delay_corner delay_corner_0p81v_125c_capwst

create_analysis_view -name analysis_view_0p90v_25c_captyp_nominal \
    -constraint_mode constraints_default \
    -delay_corner delay_corner_0p90v_25c_captyp

create_analysis_view -name analysis_view_0p99v_m40c_capbst_fastest \
    -constraint_mode constraints_default \
    -delay_corner delay_corner_0p99v_m40c_capbst


#################################################################
## set_analysis_view
#################################################################
set_analysis_view -setup { analysis_view_0p81v_125c_capwst_slowest } \
                  -hold  { analysis_view_0p99v_m40c_capbst_fastest }


#################################################################
## read LEF files
#################################################################
read_physical -lefs "$::env(LEF_TECH) $::env(LEF_CELLS)"
