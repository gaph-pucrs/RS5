/*!
 * \file RegbankDebug.sv
 *
 * \brief
 * Regbank access logging module.
 *
 * \author
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * GAPH - Hardware Design Support Group <https://nsesd.pucrs.br/en/pages/groups/gaph.html>
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
*/


module RegbankDebug;
    string file_name;
    int fd;

    initial begin
        file_name = $sformatf("./debug/%m.txt");
        fd = $fopen(file_name, "w");
    end

    always_ff @(posedge regbank.clk or negedge regbank.reset_n) begin
        if (fd != 0 && regbank.reset_n && regbank.enable && regbank.rd != '0)
            $fwrite(fd,"[%10d] %02d <- %8h\n", $time, regbank.rd, regbank.data_i);
    end

    final begin
        $fclose(fd);
    end

endmodule
