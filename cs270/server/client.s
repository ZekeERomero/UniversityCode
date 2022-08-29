	.file	"client.c"
	.text
	.globl	error
	.type	error, @function
error:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	perror
	movl	$0, %edi
	call	exit
	.cfi_endproc
.LFE2:
	.size	error, .-error
	.section	.rodata
.LC0:
	.string	"usage %s hostname port\n"
.LC1:
	.string	"ERROR opening socket"
.LC2:
	.string	"ERROR, no such host\n"
.LC3:
	.string	"ERROR connecting"
	.align 8
.LC4:
	.string	"Please enter a prefix expression: "
.LC5:
	.string	"ERROR writing to socket"
.LC6:
	.string	"ERROR reading from socket"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$320, %rsp
	movl	%edi, -308(%rbp)
	movq	%rsi, -320(%rbp)
	cmpl	$2, -308(%rbp)
	jg	.L3
	movq	-320(%rbp), %rax
	movq	(%rax), %rdx
	movq	stderr(%rip), %rax
	movl	$.LC0, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$0, %edi
	call	exit
.L3:
	movq	-320(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, -4(%rbp)
	movl	$0, %edx
	movl	$1, %esi
	movl	$2, %edi
	call	socket
	movl	%eax, -8(%rbp)
	cmpl	$0, -8(%rbp)
	jns	.L4
	movl	$.LC1, %edi
	call	error
.L4:
	movq	-320(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	gethostbyname
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L5
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$20, %edx
	movl	$1, %esi
	movl	$.LC2, %edi
	call	fwrite
	movl	$0, %edi
	call	exit
.L5:
	leaq	-48(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	bzero
	movw	$2, -48(%rbp)
	movq	-16(%rbp), %rax
	movl	20(%rax), %eax
	movslq	%eax, %rdx
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movq	(%rax), %rax
	leaq	-48(%rbp), %rcx
	addq	$4, %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	bcopy
	movl	-4(%rbp), %eax
	movzwl	%ax, %eax
	movl	%eax, %edi
	call	htons
	movw	%ax, -46(%rbp)
	leaq	-48(%rbp), %rcx
	movl	-8(%rbp), %eax
	movl	$16, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	connect
	testl	%eax, %eax
	jns	.L6
	movl	$.LC3, %edi
	call	error
.L6:
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	leaq	-304(%rbp), %rax
	movl	$256, %esi
	movq	%rax, %rdi
	call	bzero
	movq	stdin(%rip), %rdx
	leaq	-304(%rbp), %rax
	movl	$255, %esi
	movq	%rax, %rdi
	call	fgets
	leaq	-304(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	movq	%rax, %rdx
	leaq	-304(%rbp), %rcx
	movl	-8(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write
	movl	%eax, -20(%rbp)
	cmpl	$0, -20(%rbp)
	jns	.L7
	movl	$.LC5, %edi
	call	error
.L7:
	leaq	-304(%rbp), %rax
	movl	$256, %esi
	movq	%rax, %rdi
	call	bzero
	leaq	-304(%rbp), %rcx
	movl	-8(%rbp), %eax
	movl	$255, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read
	movl	%eax, -20(%rbp)
	cmpl	$0, -20(%rbp)
	jns	.L8
	movl	$.LC6, %edi
	call	error
.L8:
	leaq	-304(%rbp), %rax
	movq	%rax, %rdi
	call	puts
	movl	-8(%rbp), %eax
	movl	%eax, %edi
	call	close
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-36)"
	.section	.note.GNU-stack,"",@progbits
