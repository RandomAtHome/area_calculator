section .rodata
    const1 dd 14
    const2 dd 2
    const3 dd 6
    
section .text
global f1
f1:
    finit
    fldln2
    fld qword[esp+4]
    fyl2x
    ret

global f2
f2:
    finit
    fild dword[const1]
    fild dword[const2]
    fchs
    fld qword[esp+4]
    fmul
    fadd
    ret

global f3
f3:
    finit
    fild dword[const3]
    fld1
    fild dword[const2]
    fld qword[esp+4]
    fchs
    fadd
    fdiv
    fadd
    ret
