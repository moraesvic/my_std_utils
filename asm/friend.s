	.file	"friend.c"
	.text
	.globl	friend
	.type	friend, @function
friend:
    # está no EDI, devolve no EAX
    xor     %eax, %eax
    inc     %eax
    xor     %ebx, %ebx
    inc     %ebx
    xor     %edx, %edx
LOOP:
    mov     %eax, %ecx
    add     %ebx, %ecx
    mov     %eax, %ebx
    mov     %ecx, %eax
    inc     %edx
    cmp     %edx, %edi
    jne     LOOP
	ret
