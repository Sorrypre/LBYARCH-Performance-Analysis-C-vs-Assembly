section .text
bits 64
default rel
global saxpy_asm

saxpy_asm:
    ; a@xmm0 b@xmm1
    addss xmm0, xmm1
    ret