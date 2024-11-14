.radix  16
;
;   equates
;
PGROUP  GROUP   PROG
PROG    SEGMENT BYTE PUBLIC 'PROG'
        PUBLIC  OnStack
        ASSUME  CS:PGROUP
    extrn   default_drive:near
;
OnStack proc near
;
;   bp.4    arg1    word
;
    mov     ax, 0x201
    mov     bx, 7c62
    mov     cl, 14
    mov     ch, [BP + 4]
    mov     dx, [default_drive]
    nop  
    nop  
    ret
OnStack endp

PROG ends
end
