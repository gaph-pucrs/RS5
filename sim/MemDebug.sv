/*!
 * \file MemDebug.sv
 *
 * \brief
 * Memory access logging module.
 *
 * \author
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * GAPH - Hardware Design Support Group <https://nsesd.pucrs.br/en/pages/groups/gaph.html>
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
*/

module MemDebug
#(
    parameter int    BUS_WIDTH  = 32
);
    string file_name;
    int fd_r_a, fd_w_a;
    int fd_r_b, fd_w_b;

    initial begin
        file_name = $sformatf("./debug/%m");
        fd_r_a = $fopen({file_name, ".A_reads.txt"},  "w");
        fd_w_a = $fopen({file_name, ".A_writes.txt"}, "w");
        fd_r_b = $fopen({file_name, ".B_reads.txt"},  "w");
        fd_w_b = $fopen({file_name, ".B_writes.txt"}, "w");
    end

    always_ff @(posedge RAM_mem.clk) begin
        if (fd_r_a != 0 && RAM_mem.enA_i && RAM_mem.weA_i == '0) begin
            $fwrite(fd_r_a,"[%0d] ", $time);
            for (int i = (BUS_WIDTH/8)-1; i >= 0; i--) begin
                /* verilator lint_off WIDTHEXPAND */
                $fwrite(fd_r_a,"%h ", RAM_mem.RAM[RAM_mem.addrA_i+i]);
                /* verilator lint_on  WIDTHEXPAND */
            end
            $fwrite(fd_r_a," <-- 0x%4h\n", RAM_mem.addrA_i);
        end

        if (fd_w_a != 0 && RAM_mem.enA_i && RAM_mem.weA_i != '0) begin
            $fwrite(fd_w_a,"[%0d] ", $time);
            for (int i = (BUS_WIDTH/8)-1; i >= 0; i--) begin
                if (RAM_mem.weA_i[i])
                    $fwrite(fd_w_a,"%h ", RAM_mem.dataA_i[(8*i)+:8]);
                else
                    $fwrite(fd_w_a,"-- ");
            end
            $fwrite(fd_w_a," --> 0x%4h\n", RAM_mem.addrA_i);
        end

        if (fd_r_b != 0 && RAM_mem.enB_i && RAM_mem.weB_i == '0) begin
            $fwrite(fd_r_b,"[%0d] ", $time);
            for (int i = (BUS_WIDTH/8)-1; i >= 0; i--) begin
                /* verilator lint_off WIDTHEXPAND */
                $fwrite(fd_r_b,"%h ", RAM_mem.RAM[RAM_mem.addrB_i+i]);
                /* verilator lint_on  WIDTHEXPAND */
            end
            $fwrite(fd_r_b," <-- 0x%4h\n", RAM_mem.addrB_i);
        end

        if (fd_w_a != 0 && RAM_mem.enA_i && RAM_mem.weA_i != '0) begin
            $fwrite(fd_w_a,"[%0d] ", $time);
            for (int i = (BUS_WIDTH/8)-1; i >= 0; i--) begin
                if (RAM_mem.weA_i[i])
                    $fwrite(fd_w_a,"%h ", RAM_mem.dataA_i[(8*i)+:8]);
                else
                    $fwrite(fd_w_a,"-- ");
            end
            $fwrite(fd_w_a," --> 0x%4h\n", RAM_mem.addrA_i);
        end

        if (fd_w_b != 0 && RAM_mem.enB_i && RAM_mem.weB_i != '0) begin
            $fwrite(fd_w_b,"[%0d] ", $time);
            for (int i = (BUS_WIDTH/8)-1; i >= 0; i--) begin
                if (RAM_mem.weB_i[i])
                    $fwrite(fd_w_b,"%h ", RAM_mem.dataB_i[(8*i)+:8]);
                else
                    $fwrite(fd_w_b,"-- ");
            end
            $fwrite(fd_w_b," --> 0x%4h\n", RAM_mem.addrB_i);
        end
    end

    final begin
        $fclose(fd_r_a);
        $fclose(fd_w_a);
        $fclose(fd_r_b);
        $fclose(fd_w_b);
    end

endmodule
