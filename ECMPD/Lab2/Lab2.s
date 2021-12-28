	.file	"lab1.cpp"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	_Z10razlojeniey
	.type	_Z10razlojeniey, @function
_Z10razlojeniey:
.LFB75:
	testq	%rdi, %rdi
	je	.L8
	pushq	%rbp
.LCFI0:
	pushq	%rbx
.LCFI1:
	movq	%rdi, %rbp
	xorl	%ebx, %ebx
	pxor	%xmm2, %xmm2
	subq	$24, %rsp
.LCFI2:
	jmp	.L7
	.p2align 4,,10
	.p2align 3
.L14:
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rbx, %xmm1
.L4:
	movsd	.LC1(%rip), %xmm0
	movsd	%xmm2, 8(%rsp)
	call	pow
	leaq	1(%rbx,%rbx), %rax
	movsd	8(%rsp), %xmm2
	testq	%rax, %rax
	js	.L5
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm1
.L6:
	divsd	%xmm1, %xmm0
	addq	$1, %rbx
	cmpq	%rbx, %rbp
	addsd	%xmm0, %xmm2
	je	.L13
.L7:
	testq	%rbx, %rbx
	jns	.L14
	movq	%rbx, %rax
	movq	%rbx, %rdx
	pxor	%xmm1, %xmm1
	shrq	%rax
	andl	$1, %edx
	orq	%rdx, %rax
	cvtsi2sdq	%rax, %xmm1
	addsd	%xmm1, %xmm1
	jmp	.L4
	.p2align 4,,10
	.p2align 3
.L5:
	movq	%rax, %rdx
	pxor	%xmm1, %xmm1
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm1
	addsd	%xmm1, %xmm1
	jmp	.L6
	.p2align 4,,10
	.p2align 3
.L13:
	mulsd	.LC2(%rip), %xmm2
	addq	$24, %rsp
.LCFI3:
	popq	%rbx
.LCFI4:
	popq	%rbp
.LCFI5:
	movapd	%xmm2, %xmm0
	ret
.L8:
	pxor	%xmm0, %xmm0
	ret
.LFE75:
	.size	_Z10razlojeniey, .-_Z10razlojeniey
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC6:
	.string	"%f\n"
.LC8:
	.string	"Time taken: %lf sec.\n"
	.section	.text.unlikely
.LCOLDB9:
	.section	.text.startup,"ax",@progbits
.LHOTB9:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB76:
	pushq	%r15 
.LCFI6:
	pushq	%r14
.LCFI7:
	movl	$4, %edi
	pushq	%r13
.LCFI8:
	pushq	%r12
.LCFI9:
	movq	%rsi, %r12
	pushq	%rbp
.LCFI10:
	pushq	%rbx
.LCFI11:
	subq	$72, %rsp 
.LCFI12:
	leaq	16(%rsp), %rsi 
	movq	%fs:40, %rax 
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax 
	call	clock_gettime
	movq	8(%r12), %r15
	movq	%r15, %rdi
	call	strlen 
	testl	%eax, %eax 
	jle	.L23
	leal	-1(%rax), %ebp 
	xorl	%r14d, %r14d 
	xorl	%ebx, %ebx 
	movabsq	$-9223372036854775808, %r13
	jmp	.L21 
	.p2align 4,,10
	.p2align 3
.L28:
	subl	$1, %ebp
	addq	$1, %r14
	cmpl	$-1, %ebp 
	cvttsd2siq	%xmm0, %rbx
	je	.L16
.L29:
	movq	8(%r12), %r15
.L21:
	movsbl	(%r15,%r14), %eax 
	pxor	%xmm2, %xmm2 
	pxor	%xmm1, %xmm1 
	movsd	.LC4(%rip), %xmm0
	subl	$48, %eax
	cvtsi2sd	%ebp, %xmm1 /
	cvtsi2sd	%eax, %xmm2
	movsd	%xmm2, 8(%rsp) 
	call	pow 
	testq	%rbx, %rbx 
	mulsd	8(%rsp), %xmm0
	js	.L17 
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rbx, %xmm1
.L18:
	addsd	%xmm1, %xmm0
	ucomisd	.LC5(%rip), %xmm0
	jb	.L28 
	subsd	.LC5(%rip), %xmm0
	subl	$1, %ebp
	addq	$1, %r14
	cvttsd2siq	%xmm0, %rbx
	xorq	%r13, %rbx
	cmpl	$-1, %ebp
	jne	.L29 
.L16:
	movq	%rbx, %rdi
	call	_Z10razlojeniey
	movl	$.LC6, %esi
	movl	$1, %edi
	movl	$1, %eax
	call	__printf_chk
	leaq	32(%rsp), %rsi
	movl	$4, %edi
	call	clock_gettime
	movq	40(%rsp), %rax
	subq	24(%rsp), %rax
	movl	$.LC8, %esi
	pxor	%xmm0, %xmm0
	movl	$1, %edi
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm0
	movq	32(%rsp), %rax
	subq	16(%rsp), %rax
	cvtsi2sdq	%rax, %xmm1
	movl	$1, %eax
	mulsd	.LC7(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	__printf_chk
	xorl	%eax, %eax
	movq	56(%rsp), %rdx
	xorq	%fs:40, %rdx
	jne	.L30
	addq	$72, %rsp
.LCFI13:
	popq	%rbx
.LCFI14:
	popq	%rbp
.LCFI15:
	popq	%r12
.LCFI16:
	popq	%r13
.LCFI17:
	popq	%r14
.LCFI18:
	popq	%r15
.LCFI19:
	ret
	.p2align 4,,10
	.p2align 3
.L17:
.LCFI20:
	movq	%rbx, %rax
	pxor	%xmm1, %xmm1
	shrq	%rax
	andl	$1, %ebx
	orq	%rbx, %rax
	cvtsi2sdq	%rax, %xmm1
	addsd	%xmm1, %xmm1
	jmp	.L18
.L23:
	xorl	%ebx, %ebx
	jmp	.L16
.L30:
	call	__stack_chk_fail
.LFE76:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE9:
	.section	.text.startup
.LHOTE9:
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	-1074790400
	.align 8
.LC2:
	.long	0
	.long	1074790400
	.align 8
.LC4:
	.long	0
	.long	1076101120
	.align 8
.LC5:
	.long	0
	.long	1138753536
	.align 8
.LC7:
	.long	3894859413
	.long	1041313291
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0
	.byte	0x3
	.string	"zR"
	.uleb128 0x1
	.sleb128 -8
	.uleb128 0x10
	.uleb128 0x1
	.byte	0x3
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 8
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.long	.LFB76
	.long	.LFE76-.LFB76
	.uleb128 0
	.byte	0x4
	.long	.LCFI6-.LFB76
	.byte	0xe
	.uleb128 0x10
	.byte	0x8f
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI7-.LCFI6
	.byte	0xe
	.uleb128 0x18
	.byte	0x8e
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI8-.LCFI7
	.byte	0xe
	.uleb128 0x20
	.byte	0x8d
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI9-.LCFI8
	.byte	0xe
	.uleb128 0x28
	.byte	0x8c
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI10-.LCFI9
	.byte	0xe
	.uleb128 0x30
	.byte	0x86
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI11-.LCFI10
	.byte	0xe
	.uleb128 0x38
	.byte	0x83
	.uleb128 0x7
	.byte	0x4
	.long	.LCFI12-.LCFI11
	.byte	0xe
	.uleb128 0x80
	.byte	0x4
	.long	.LCFI13-.LCFI12
	.byte	0xa
	.byte	0xe
	.uleb128 0x38
	.byte	0x4
	.long	.LCFI14-.LCFI13
	.byte	0xe
	.uleb128 0x30
	.byte	0x4
	.long	.LCFI15-.LCFI14
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.long	.LCFI16-.LCFI15
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.long	.LCFI17-.LCFI16
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.long	.LCFI18-.LCFI17
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.long	.LCFI19-.LCFI18
	.byte	0xe
	.uleb128 0x8
	.byte	0x4
	.long	.LCFI20-.LCFI19
	.byte	0xb
	.align 8
.LEFDE1:
	.ident	"GCC: (Ubuntu 5.5.0-12ubuntu1~16.04) 5.5.0 20171010"
	.section	.note.GNU-stack,"",@progbits
