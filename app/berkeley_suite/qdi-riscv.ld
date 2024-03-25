ENTRY(_entry)

/* specify HF-RISC memory areas */
MEMORY
{
    INST (rx) : ORIGIN = 0x00000000, LENGTH = 0x00080000
    DATA (rwx) : ORIGIN = 0x10000000, LENGTH = 0x00008000
}

/* define a global symbol _stack  */

/* now define the output sections  */

SECTIONS {
	. = 0;

	.text : {
			_text = .;
			*(.text.init)
			*(.text)
			*(.text.*)
			_etext = .;
	} > INST

	.data : {
			_rodata = .;
			*(.rdata)
			*(.rodata)
			*(.rodata.*)
			_erodata = .;
			_data = .;
			*(.data)
			*(.data.*)
			_gp = . + 0x800;
			*(.sdata)
			*(.sdata.*)
			. = ALIGN(16); 
			_edata = .;
			_bss_start = .;
			*(.sbss) 
			*(.sbss.*) 
			*(.bss) 
			*(.bss.*)
			. = ALIGN(4);
			_bss_end = . ;
			. += 0x2000;
			_stack = .;
	} > DATA

	_end = .;
}

