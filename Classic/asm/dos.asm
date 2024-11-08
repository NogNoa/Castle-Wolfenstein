.radix  16
;
;   equates
    gt_default_drv      equ 1900
    gt_oem_os_version  equ 3000
;
PGROUP  GROUP   PROG
PROG    SEGMENT BYTE PUBLIC 'PROG'
        PUBLIC  isDos210_
        ASSUME  CS:PGROUP
    extrn   del_inst_5ff9:near
    extrn   default_drive:near
isDos210_ proc near
;
;   ret 1- success 0- fail  bool
;
    push    bp
    mov     ax,gt_default_drv   ;get current default drive
    int     21
    mov     byte ptr [default_drive], AL
    CALL    del_inst_5ff9
    mov     ax, gt_oem_os_version
    int     21
    CMP     AL, 2               ;is dos 2.?
    jnz     return_zero
    CMP     AH, 0a              ; is dos ?.10?
    jnz     return_zero
    mov     ax, 1
    pop     BP
    ret
return_zero:
    mov     ax, 0
    POP     BP
    RET
isDos210_ endp
PROG ends
end
