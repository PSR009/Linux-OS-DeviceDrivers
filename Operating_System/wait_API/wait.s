	.file	"wait.c"
	.text
	.section	.rodata
.LC0:
	.string	"CHILD: PID: %d PPID: %d\n"
.LC1:
	.string	"PARENT: PID: %d PPID: %d\n"
	.align 8
.LC2:
	.string	"After wait: Child has terminated"
.LC3:
	.string	"Bye"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	call	fork@PLT
	movl	%eax, -20(%rbp)
	cmpl	$0, -20(%rbp)
	jne	.L2
	call	getppid@PLT
	movl	%eax, %ebx
	call	getpid@PLT
	movl	%ebx, %edx
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L3
.L2:
	call	getppid@PLT
	movl	%eax, %ebx
	call	getpid@PLT
	movl	%ebx, %edx
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %edi
	call	wait@PLT
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
.L3:
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
