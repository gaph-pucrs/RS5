/*!\file CSRs.sv
 * PUCRS-RV VERSION - 1.0 - Public Release
 *
 * Distribution:  September 2021
 *
 * Willian Nunes   <willian.nunes@edu.pucrs.br>
 * Marcos Sartori  <marcos.sartori@acad.pucrs.br>
 * Ney calazans    <ney.calazans@pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 * Package definition.
 *
 * \detailed
 * Defines the package used in the CSRs implementation.
 */


package CSRs_pkg;

import my_pkg::*;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
    virtual class CSRBASE;
        logic [31:0] value;
        logic [31:0] wmask;

        task reset();
            this.value <= '0;
        endtask

        function logic[31:0] read();
            return this.value;
        endfunction

        task write(logic[31:0] data, csr_ops op);
            if(op==WRITE)
                this.value <= data & this.wmask;
            
            else if(op==SET)
                this.value <= (this.value | data) & this.wmask;
            
            else if(op==CLEAR)
                this.value <= (this.value & (~data)) & this.wmask;
            
            else
                this.value <= value;

        endtask
    endclass

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
    class IMISA extends CSRBASE;
        function new();
            this.value <= '0;
            this.wmask <= 32'h3C000000;
        endfunction
        
        task reset();
            this.value <= 32'h40000100;   // 32 - I
        endtask
    endclass

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
    class IMIE extends CSRBASE;
        function new();
            this.value <= '0;
            this.wmask <= 32'h00000888;
        endfunction

        function logic MEIE;
            return this.value[11];
        endfunction

        function logic MSIE;
            return this.value[3];
        endfunction

        function logic MTIE;
            return this.value[7];
        endfunction
    endclass

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
    class IMTVEC extends CSRBASE;
        function new();
            this.value <= '0;
            this.wmask <= 32'hFFFFFFFC;
        endfunction

        function logic[31:0] BASE;
            return this.value & this.wmask;
        endfunction

        function TRAP_MODE MODE;
            return TRAP_MODE'(this.value[1:0]);
        endfunction
    endclass

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

    class IMSCRATCH extends CSRBASE;
        function new();
            this.value <= '0;
            this.wmask <= 32'hFFFFFFFF;
        endfunction
    endclass

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
    class IMEPC extends CSRBASE;
        function new();
            this.value <= '0;
            this.wmask <= 32'hFFFFFFFC;
        endfunction
    endclass

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
    class IMIP extends CSRBASE;
        function new();
            this.value <= '0;
            this.wmask <= 32'h00000888;
        endfunction

        function logic MEIP;
            return this.value[11];
        endfunction

        function logic MSIP;
            return this.value[3];
        endfunction

        function logic MTIP;
            return this.value[7];
        endfunction
    endclass

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
    class IMCAUSE extends CSRBASE;
        function new();
            this.value <= '0;
            this.wmask <= 32'hFFFFFFFF;
        endfunction
        
        task SET_EXCEPTION();
            this.value[31] <= 0;
        endtask

        task SET_INTERRUPT();
            this.value[31] <= 1;
        endtask

        task SET_CODE(logic[31:0] code);
            this.value[30:0] <= code;
        endtask
    endclass
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
    class IMTVAL extends CSRBASE;
        function new();
            this.value <= '0;
            this.wmask <= 32'hFFFFFFFF;
        endfunction
    endclass

endpackage