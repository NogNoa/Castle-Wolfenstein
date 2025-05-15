.radix  16
;
data	segment	byte public 'data'
;
data ENDS
PROG    SEGMENT BYTE PUBLIC 'PROG'
        PUBLIC  Sum
        ASSUME  CS:PROG, DS:data
Sum proc near
;
;   bp.4    list    &int
;   bp.6    len     int
;
    push    BP
    mov     bp, sp
    mov     si, word ptr [bp + 4]
    push    CS
    mov     cx, word ptr [bp + 6]
    pop     DS                  ; load DS with program segment
for_cx:
    add     ax, word ptr [si]
    add     si, 2
    loop    for_cx
    push    ES
    pop     DS                  ; return DS to data segment
    pop     BP
    ret
Sum endp
prog ends
;
end