.radix  16
;
;   equates
    gt_default_drv     equ 1900
    gt_oem_os_version  equ 3000
;
PGROUP  GROUP   PROG
PROG    SEGMENT BYTE PUBLIC 'PROG'
        PUBLIC  Goober, isDos210
        ASSUME  CS:PGROUP
        extrn   default_:near
;
DelInst5ff9 proc near
;
    mov     bl, 90
    mov     byte ptr CS:[dest_write], BL
    mov     bl, 90
    mov     byte ptr CS:[dest_write + 1], BL
    Ret
DelInst5ff9 endp
;
Goober proc near
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
    mov     dl, byte ptr [default_]
    mov     dh, 0
dest_write label word
    add     byte ptr [bx + si], dl
    mov     al, 0
    mov     word ptr cs:[dest_write], ax
    mov     cx, 28
    XOR     ax, ax
    pop     bx
    mov     si, 10
or_loop:
    or      ax, word ptr [bx + si]
    add     si, 2
    loop    or_loop
    mov     ax, 1000
    mov     word ptr cs:[dest_write], ax
    mov     ax, 0a5a5
    or      ax, ax
    jz      jmp_return_zero
    pop     bp
    ret
jmp_return_zero:
    mov     ax, -1
    jmp     return_zero
Goober endp
;
isDos210 proc near
;
;   ret 1- success 0- fail  bool
;
    push    bp
    mov     ax,gt_default_drv   ;get current default drive
    int     21
    mov     byte ptr [default_], AL
    CALL    DelInst5ff9
    mov     ax, gt_oem_os_version
    int     21
    CMP     AL, 2               ;is dos 2.?
    jnz     return_zero_near
    CMP     AH, 0a              ; is dos ?.10?
    jnz     return_zero_near
    mov     ax, 1
    pop     BP
    ret
return_zero label word
return_zero_near:
    mov     ax, 0
    POP     BP
    RET
isDos210 endp
PROG ends
end
