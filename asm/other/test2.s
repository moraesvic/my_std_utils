	.file	"test.c"
	.text
	.globl	biggest
	.type	biggest, @function
biggest:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rax
	addq	$4, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L2
	cmpl	$1, -12(%rbp)
	jne	.L2
	movl	$6, %eax
	jmp	.L3
.L2:
	movl	$7, %eax
.L3:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	biggest, .-biggest
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
