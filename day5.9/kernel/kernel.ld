/* Simple linker script for the JOS kernel. this file is for main.c
   See the GNU ld 'info' manual ("info ld") to learn the syntax. */

OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)

SECTIONS
{
	/* Link the kernel at this address: "." means the current address */
	. = 0x280000;
	.text :  {
		*(.text)
	}
	.rodata : {
		*(.rodata)
	}

	.data : {
		*(.data)
	}

	.bss : {
		*(.bss)
	}

	
}
