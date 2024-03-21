	.file	"main.c"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	foo
	.type	foo, @function
foo:
.LFB0:
	.cfi_startproc
	endbr64
	mov	eax, edi
	imul	eax, edi
	imul	eax, edi
	test	eax, eax
	js	.L4
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	imul	esi, esi
	add	edi, edi
	mov	edx, 17
	sub	edx, edi
	sub	edx, esi
	add	eax, edx
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
