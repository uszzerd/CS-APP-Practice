	.file	"7.Array.c"
	.text
	.globl	get
	.type	get, @function
get:
.LFB11:
	.cfi_startproc
	movslq	%esi, %rsi
	movl	(%rdi,%rsi,4), %eax
	ret
	.cfi_endproc
.LFE11:
	.size	get, .-get
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
