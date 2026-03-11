	.file	"6.Proc.c"
	.text
	.globl	compute
	.type	compute, @function
compute:
.LFB11:
	.cfi_startproc
	imull	%edi, %esi
	addl	%edi, %esi
	movl	%esi, (%rdx)
	ret
	.cfi_endproc
.LFE11:
	.size	compute, .-compute
	.globl	double_val
	.type	double_val, @function
double_val:
.LFB12:
	.cfi_startproc
	movl	(%rdi), %eax
	addl	%eax, %eax
	ret
	.cfi_endproc
.LFE12:
	.size	double_val, .-double_val
	.globl	main
	.type	main, @function
main:
.LFB13:
	.cfi_startproc
	subq	$16, %rsp
	.cfi_def_cfa_offset 24
	movl	$0, 12(%rsp)
	leaq	12(%rsp), %rdx
	movl	$3, %esi
	movl	$5, %edi
	call	compute
	leaq	12(%rsp), %rdi
	call	double_val
	addq	$16, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE13:
	.size	main, .-main
	.ident	"GCC: (GNU) 11.5.0 20240719 (Red Hat 11.5.0-11)"
	.section	.note.GNU-stack,"",@progbits
