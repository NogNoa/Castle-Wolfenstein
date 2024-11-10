.radix  16
;
;   equates
;
PGROUP  GROUP   PROG
PROG    SEGMENT BYTE PUBLIC 'PROG'
        PUBLIC  OnStack_
        ASSUME  CS:PGROUP
    extrn   _default_drive:near
;
OnStack_ proc near
;
;   bp.4    arg1    word
;
    mov     ax, 0x201
    mov     bx, 7c62
    mov     cl, 14
    mov     ch, [BP + 4]
    mov     dx, [_default_drive]
    nop  
    nop  
    ret
OnStack_ endp

PROG ends
end
