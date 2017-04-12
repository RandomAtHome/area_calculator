section .rodata
    fourteen dd 14
    two dd 2
section .text
global f2
f2:
    finit
    fild dword[fourteen]
    fild dword[two]
    fchs
    fld qword[esp+4]
    fmul
    fadd
    ret