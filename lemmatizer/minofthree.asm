; adapted from
; https://cs.lmu.edu/~ray/notes/nasmtutorial/
; -----------------------------------------------------------------------------
; A 32-bit function that returns the maximum value of its three 64-bit integer
; arguments.  The function has signature:
;
;   uint32_t minofthree(uint32_t x, uint32_t y, uint32_t z)
;
; -----------------------------------------------------------------------------

        global  minofthree
        section .text
minofthree:
        mov     eax, edi                ; result (eax) initially holds x
        cmp     eax, esi                ; is x greater than y?
        cmovg   eax, esi                ; if so, set result to y
        cmp     eax, edx                ; is min(x,y) greater than z?
        cmovg   eax, edx                ; if so, set result to z
        ret                             ; the min will be in rax