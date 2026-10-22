/*!
 * \file HPMProfiler.sv
 *
 * \brief
 * Hardware Performance Monitoring profiler.
 *
 * \author
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * GAPH - Hardware Design Support Group <https://nsesd.pucrs.br/en/pages/groups/gaph.html>
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
*/

module HPMProfiler;
    string file_name;
    int fd;

    initial begin
        file_name = $sformatf("./results/%m.txt");
        fd = $fopen(file_name, "w");
    end


    final begin
        $fwrite(fd,"Clock Cycles:             %0d\n", CSRBank.mcycle);
        $fwrite(fd,"Instructions Retired:     %0d\n", CSRBank.minstret);
        $fwrite(fd,"Instructions Compressed:  %0d\n", CSRBank.cntr_compressed);
        $fwrite(fd,"Instructions Killed:      %0d\n", CSRBank.cntr_killed);
        $fwrite(fd,"Context Switches:         %0d\n", CSRBank.cntr_context);
        $fwrite(fd,"Exceptions Raised:        %0d\n", CSRBank.cntr_exception);
        $fwrite(fd,"Interrupts Acked:         %0d\n", CSRBank.cntr_irq);
        $fwrite(fd,"Misaligned Jumps:         %0d\n", CSRBank.cntr_misaligned);
        $fwrite(fd,"Cycles Scalar Instruct:   %0d\n", CSRBank.cntr_scalar);

        $fwrite(fd,"\nCYCLES WITH::\n");
        $fwrite(fd,"HAZARDS:                  %0d\n", CSRBank.cntr_hazard);
        $fwrite(fd,"STALL:                    %0d\n", CSRBank.cntr_stall);
        $fwrite(fd,"BUBBLES (INC. HAZARDS):   %0d\n", CSRBank.cntr_nop);

        $fwrite(fd,"\nINSTRUCTION COUNTERS:\n");
        $fwrite(fd,"LUI_SLT:                  %0d\n", CSRBank.cntr_luislt);
        $fwrite(fd,"LOGIC:                    %0d\n", CSRBank.cntr_logic);
        $fwrite(fd,"ADDSUB:                   %0d\n", CSRBank.cntr_addsub);
        $fwrite(fd,"SHIFT:                    %0d\n", CSRBank.cntr_shift);
        $fwrite(fd,"BRANCH:                   %0d\n", CSRBank.cntr_branch);
        $fwrite(fd,"JUMP:                     %0d\n", CSRBank.cntr_jump);
        $fwrite(fd,"LOAD:                     %0d\n", CSRBank.cntr_load);
        $fwrite(fd,"STORE:                    %0d\n", CSRBank.cntr_store);
        $fwrite(fd,"SYS:                      %0d\n", CSRBank.cntr_sys);
        $fwrite(fd,"CSR:                      %0d\n", CSRBank.cntr_csr);
        $fwrite(fd,"MUL:                      %0d\n", CSRBank.cntr_mul);
        $fwrite(fd,"DIV:                      %0d\n", CSRBank.cntr_div);

        $fwrite(fd, "\nVECTOR EXTENSION:\n");
        $fwrite(fd, "Vector Instructions:     %0d\n", CSRBank.cntr_vinst);
        // $fwrite(fd, "Vector Cycles Total:     %0d\n", CSRBank.cntr_vcycles + cntr_vlscycles);
        $fwrite(fd, "Vector Cycles Arith/Cfg: %0d\n", CSRBank.cntr_vcycles);
        $fwrite(fd, "Vector Cycles Load/Stor: %0d\n", CSRBank.cntr_vlscycles);
        $fwrite(fd, "VADDSUB:                 %0d\n", CSRBank.cntr_vaddsub);
        $fwrite(fd, "VMUL:                    %0d\n", CSRBank.cntr_vmul);
        $fwrite(fd, "VDIV:                    %0d\n", CSRBank.cntr_vdiv);
        $fwrite(fd, "VMAC:                    %0d\n", CSRBank.cntr_vmac);
        $fwrite(fd, "VRED:                    %0d\n", CSRBank.cntr_vred);
        $fwrite(fd, "VLOAD/VSTORE:            %0d\n", CSRBank.cntr_vloadstore);
        $fwrite(fd, "VOTHERS:                 %0d\n", CSRBank.cntr_vothers);
    end

endmodule
