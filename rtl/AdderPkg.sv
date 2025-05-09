`ifndef ADDER_PKG
`define ADDER_PKG

package AdderPkg;

    typedef enum { 
        CARRY_BYPASS,
        CARRY_SELECT,
        CARRY_INCREMENT
    } add_type_t;

endpackage

`endif
