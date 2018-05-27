#This is demo project for arm926ej-s kernel
.section .data
.equ GPKCON0,     0x7F008800
.equ GPKCON1,     0x7F008804
.equ GPKDAT,      0x7F008808
.equ GPKPUD,      0x7F00880C

.section .text
.globl _start
_start:
	@set svc32 mode 
	mrs r0, cpsr
	bic r0, r0, #0x3f
	orr r0, r0, #0xd3
	msr cpsr, r0 

#if 0	
	ldr r0, =GPKCON0	
	ldr r1, =0x11112222
	str r1, [r0]

	ldr r0, =GPKDAT
	ldr r1, [r0]
	orr r1, r1, #0x0f0
	bic r1, r1, #0x0A0
	str r1, [r0]
#endif

	bl init_stack @because we will jump to C running enviroment

	@bl clean_bss

	bl main

halt_loop:
	b halt_loop
	
init_stack:
	ldr sp, =0x0C000FFC
	mov pc, lr

clean_bss:
	ldr r0, =__start_bss
	ldr r1, =__end_bss
	cmp r0, r1
	moveq pc, lr

