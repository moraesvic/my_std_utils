	.file	"primo.s"
	.text
    .globl  primoAsm
    .type   primoAsm, @function

primoAsm:
    # v[] em RDI, n em ESI
    # R8D  = i
    # R9D  = j
    # R10D = k
    # R11D = auxiliar
    cmp $0, %esi
    je primoLoop1Fim
    
    movq $2, (%rdi)
    cmp $1, %esi
    je primoLoop1Fim

    movq $3, 4(%rdi)
    mov $2, %r8d
    primoLoop1:
        cmp %r8d, %esi
        je  primoLoop1Fim
        mov %r8d, %r11d
        sub $1, %r11d
        mov (%rdi,%r11,4), %r9d
        add $2, %r9d
        xor %r10d, %r10d
        primoLoop2:
            cmp %r10d, %r8d
            je  primoLoop2Fim

            # se v[k]*v[k] >= j, interrompe precocemente
            mov (%rdi,%r10,4), %ecx
            mov %ecx, %eax
            mul %ecx
            cmp %r9d, %eax
            jge primoLoop2Fim
            
            # divisão
            # DX:AX tem o dividendo
            # AX fica com o quociente
            # DX com o resto
            mov %r9d, %r11d
            mov %r11d, %eax
            xor %edx, %edx
            div %ecx

            test %edx, %edx
            jne primoLoop2a
            add $2, %r9d
            mov $1, %r10d
            jmp primoLoop2
        primoLoop2a:
            add $1, %r10d
            jmp primoLoop2
    primoLoop2Fim:
        mov %r9d, (%rdi,%r8,4)
        add $1, %r8d
        jmp primoLoop1
primoLoop1Fim:
    ret
