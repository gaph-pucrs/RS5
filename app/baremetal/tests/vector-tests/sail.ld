ENTRY(_entry)

/* Memory layout for the Sail RISC-V model: RAM starts at 0x80000000. */
/* Same sections as rs5.ld, plus the tohost/fromhost words of the     */
/* host-target interface, which the model finds through their symbols. */

SECTIONS {
	. = 0x80000000;

	.text : {
			_text = .;
			*(.text.init)
			*(.text)
			*(.text.*)
			_etext = .;
	}

	. = ALIGN(64);
	.tohost : {
			*(.tohost)
	}

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
	}

	_end = .;
}
