	.arch i686

	.set STACKSIZE, 4096
	.lcomm stack, STACKSIZE


//	.section .mbheader
//	.align 8
// multiboot_header:
//	.long 0xe85250d6
//	.long 0
//	.long multiboot_header_end - multiboot_header
//	.long -(0xe85250d6 + (multiboot_header_end - multiboot_header))

//	.short 0
//	.short 0
//	.long 8
// multiboot_header_end:


	.section .startup
	.align 16
	.globl start
start:
	cli
	mov	$(stack + STACKSIZE), %esp

	/* Reset the flags.  */
	pushl	$0
	popf

	// Push the pointer to the Multiboot information structure.
	push	%ebx
	// Push the magic value
	push	%eax

	call	kmain

	hlt
