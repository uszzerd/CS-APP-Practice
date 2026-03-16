	.file	"5._switch.c"
	.text
	.globl	switch_eg
	.type	switch_eg, @function
switch_eg:
.LFB11:
	.cfi_startproc
	subq	$100, %rsi
	cmpq	$6, %rsi
	ja	.L8
	jmp	*.L4(,%rsi,8)
	.section	.rodata
	.align 8
	.align 4
.L4:
	.quad	.L7
	.quad	.L8
	.quad	.L6
	.quad	.L5
	.quad	.L3
	.quad	.L8
	.quad	.L3
	.text
.L7:
	leaq	(%rdi,%rdi,2), %rax
	leaq	(%rdi,%rax,4), %rdi
	jmp	.L2
.L6:
	addq	$10, %rdi
.L5:
	addq	$11, %rdi
.L2:
	movq	%rdi, (%rdx)
	ret
.L3:
	imulq	%rdi, %rdi
	jmp	.L2
.L8:
	movl	$0, %edi
	jmp	.L2
	.cfi_endproc
.LFE11:
	.size	switch_eg, .-switch_eg
	.globl	main
	.type	main, @function
main:
.LFB12:
	.cfi_startproc
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE12:
	.size	main, .-main
	.ident	"GCC: (GNU) 11.5.0 20240719 (Red Hat 11.5.0-11)"
	.section	.note.GNU-stack,"",@progbits
