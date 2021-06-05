	.file	"select.s"
	.text
    .globl  selectAsm
    .type   selectAsm, @function

smallest:
    # v[] em R11 e n em ESI
    # "add 4 %RDI" para o próximo int
    # EAX guarda o maior
    # EBX guarda o valor atual v[i]
    # ECX guarda o índice do maior valor
    # EDX guarda o contador i
    cmp $0, %esi
    je  smallestFim
    xor %edx, %edx
    xor %ecx, %ecx
    mov (%r11), %eax
smallestLoop:
    mov (%r11), %ebx
    cmp %eax, %ebx
    jge smallestNext
    mov %edx,   %ecx
    mov (%r11), %eax
smallestNext:
    add $4, %r11
    add $1, %edx
    cmp %edx, %esi
    jne smallestLoop
smallestFim:
    ret


selectAsm:
    # v[] em RDI, n em ESI
    # fazemos um bkp de v[] em r11, é isso que usaremos em smallest

    cmp $0, %esi
    je selectEnd
    mov %rdi, %r11
    call smallest

    # agora o menor está em %eax, e seu índice, em %ecx
    # usaremos o GPR r9 como temporária
    # e GPR r10 para calcular o índice

    mov (%rdi), %r9d
    mov %eax, (%rdi)
    xor %r10, %r10
    mov %ecx, %r10d
    mov %r9d, (%rdi,%r10,4)
    add $4, %rdi
    sub $1, %esi 
    call selectAsm
selectEnd:
    ret
