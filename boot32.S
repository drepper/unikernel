# This is an -*- asm -*- file
	.arch i686

	.set STACKSIZE, 4096
	.lcomm stack, STACKSIZE

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
