OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	. = 0x0C000000;
	. = ALIGN(4);
	.text :
	{
		start.o (.text)
		*(.text)	
	}

	. = ALIGN(4);
	.data :{*(.data)}
	
	. = ALIGN(4);
	__start_bss = .;
	.bss :{*(.bss)}
	__end_bss = .;
}	

