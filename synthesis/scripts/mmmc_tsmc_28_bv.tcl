#################################################################################
# tsmc 28 nm
#################################################################################

set LIB_PATH /pdk/tsmc/PDK28/PDK_TSMC28_bv/tcbn28hpcplusbwp30p140_190a/TSMCHOME/digital/Front_End
set TECH_PATH /pdk/tsmc/PDK28/PDK_TSMC28_bv/tcbn28hpcplusbwp30p140_190a/TSMCHOME/digital/Back_End
set CONSTRAINTS_PATH ./scripts

#################################################################
## library_sets (lib from library)
#################################################################

# ssg0p81v125c
create_library_set -name libset_0p81v_125c \
    -timing  "${LIB_PATH}/timing_power_noise/NLDM/tcbn28hpcplusbwp30p140_180a/tcbn28hpcplusbwp30p140ssg0p81v125c.lib"

# tt0p9v25c
create_library_set -name libset_0p90v_25c \
    -timing  "${LIB_PATH}/timing_power_noise/NLDM/tcbn28hpcplusbwp30p140_180a/tcbn28hpcplusbwp30p140tt0p9v25c.lib"

# ffg0p99vm40c
create_library_set -name libset_0p99v_m40c \
    -timing  "${LIB_PATH}/timing_power_noise/NLDM/tcbn28hpcplusbwp30p140_180a/tcbn28hpcplusbwp30p140ffg0p99vm40c.lib"


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
     -qrc_tech ${TECH_PATH}/qrc/RC_QRC_crn28hpc+_1p09m+ut-alrdl_5x1y1z1u_rcworst/qrcTechFile

 create_rc_corner -name rc_corner_25c_captyp \
     -temperature 25.0 \
    -qrc_tech ${TECH_PATH}/qrc/RC_QRC_crn28hpc+_1p09m+ut-alrdl_5x1y1z1u_typical/qrcTechFile

 create_rc_corner -name rc_corner_m40c_capbst \
     -temperature -40.0 \
     -qrc_tech ${TECH_PATH}/qrc/RC_QRC_crn28hpc+_1p09m+ut-alrdl_5x1y1z1u_rcbest/qrcTechFile


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
read_physical -lefs "${TECH_PATH}/lef/tsmcn28_9lm5X1Y1Z1UUTRDL.tlef  ${TECH_PATH}/lef/tcbn28hpcplusbwp30p140_110a/lef/tcbn28hpcplusbwp30p140.lef"
