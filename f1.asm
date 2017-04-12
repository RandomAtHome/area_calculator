section .text
global f1
f1:
    finit
    fldln2
    fld qword[esp+4]
    fyl2x
    ret