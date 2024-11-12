.radix  16
;
;   equates
;
PGROUP  GROUP   PROG
PROG    SEGMENT BYTE PUBLIC 'PROG'
        PUBLIC  DelInst5ff9_ Goober_
        ASSUME  CS:PGROUP
    extrn   _default_drive:near
;
DelInst5ff9_ proc near
;
    mov     bl, 90
    mov     byte ptr CS:[Goober_::dest_write], BL
    mov     bl, 90
    mov     byte ptr CS:[Goober_::dest_write + 1], BL
    Ret
DelInst5ff9_ endp
;
Goober_ proc near
;
;   bp.4    p1      void
;   bp.6    dest    &void
;
    push    bp
    mov     bp, sp
    mov     cx, word ptr [BP + 4]
    mov     ch, cl
    mov     ch, 14
    mov     al, 1
    mov     ah, 2
    mov     bx, word ptr [bp + 6]
    push    CS
    pop     ds
    mov     word ptr [bx_load + 1], bx
    push    ES
    pop     DS
bx_load:
    mov     bx, 0
    push    bx
    mov     dl, byte ptr [_default_drive]
    mov     dh, 0
dest_write:
    add     byte ptr [bx + si], dl
    mov     al, 0
    mov     cs:[dest_write], ax
    mov     cx, 28
    XOR     ax, ax
    pop     bx
    mov     si, 10
or_loop:
    or      ax, word ptr [bx + si]
    add     si, 2
    loop    or_loop
    mov     ax, 1000
    mov     cs:[dest_write], ax
    mov     ax, 0a5a5
    or      ax, ax
    jz      jmp_return_zero
    pop     bp
    ret
jmp_return_zero:
    mov     ax, -1
    jmp     isDos210_::return_zero
Goober_ endp
end