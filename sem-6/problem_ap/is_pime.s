.file	"is_prime.c"
.intel_syntax noprefix

.globl is_prime    

// SOLUTION
// --- on entry edi = x (unsigned) ---
// --- returns 1 if prime, 0 if composite ---
is_prime:
        mov     esi, 1
        cmp     edi, 3
        jle     .L1
        mov     esi, edi
        and     esi, 1
        je      .L1
        mov     ecx, 2
.L3:
        add     ecx, 1
        mov     eax, ecx
        imul    eax, ecx
        cmp     eax, edi
        jg      .L1
        mov     eax, edi
        cdq
        idiv    ecx
        test    edx, edx
        jne     .L3
        mov     esi, edx
.L1:
        mov     eax, esi
        ret
// END SOLUTION
