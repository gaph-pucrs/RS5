// DESCRIPTION: Verilator: Verilog example module
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2017 by Wilson Snyder.
// SPDX-License-Identifier: CC0-1.0
//======================================================================

// For std::unique_ptr
#include <memory>
#include <iostream>

// Include common routines
#include <verilated.h>
#include <verilated_vcd_c.h>

// Include model header, generated from Verilating "top.v"
#include "Vtestbench.h"

int main(int argc, char** argv, char** env) {
    // Construct a VerilatedContext to hold simulation time, etc.
    const auto contextp = std::make_unique<VerilatedContext>();

    // Set debug level, 0 is off, 9 is highest presently used
    // May be overridden by commandArgs argument parsing
    contextp->debug(0);

    // Pass arguments so Verilated code can see them, e.g. $value$plusargs
    // This needs to be called before you create any model
    contextp->commandArgs(argc, argv);

    // Construct the Verilated model, from Vtestbench.h generated from Verilating "testbench.sv".
    const auto top = std::make_unique<Vtestbench>(contextp.get());

    top->IRQ = 0;

    // Simulate until $finish
    while (!contextp->gotFinish()) {
        contextp->timeInc(5);  // 5 timeprecision period passes...

        // Toggle clock
        top->clk_i = !top->clk_i;

        // Toggle control signals on an edge that doesn't correspond
        // to where the controls are sampled; in this example we do
        // this only on a negedge of clk, because we know
        // reset is not sampled there.
        if(!top->clk_i){
            if (contextp->time() > 100)
                top->rst_i = 0;
        }

        // Evaluate model
        top->eval();
    }

    return 0;
}
