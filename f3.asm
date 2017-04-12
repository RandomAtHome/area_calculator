section .rodata
    six dd 6
    two dd 2
section .text
global f3
f3:
    finit
    fild dword[six]
    fld1
    fild dword[two]
    fld qword[esp+4]
    fchs
    fadd
    fdiv
    fadd
    ret