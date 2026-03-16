	.file	"4._while.c"
	.text
	.globl	loop_wile
	.type	loop_wile, @function
loop_wile:
.LFB11:
	.cfi_startproc
	movl	%edi, %eax
	movl	%esi, %ecx // cx = counter
	cmpw	%si, %di
	jle	.L4 // di < si 면 return
	movl	%esi, %r8d
	imull	%edi, %esi // esi = x * y
	movl	$0, %edx
.L3:
	addl	%esi, %edx // edx += esi
	subl	$1, %eax // count --
	subl	%r8d, %esi // esi -= y -> a * b를 계속 하는거보다 이게 더 효율적이라 판단
	cmpw	%ax, %cx 
	jne	.L3 // cx != ax, counter로 저장해 놓은 횟수가 아니라면
.L1:
	movl	%edx, %eax
	ret
.L4:
	movl	$0, %edx
	jmp	.L1
	.cfi_endproc
.LFE11:
	.size	loop_wile, .-loop_wile
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
