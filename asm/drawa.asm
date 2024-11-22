.radix  16
;
;   equates
    FIELD_SZ       equ  2000
    DISPLAY_BUFFER equ 0b800
;
PGROUP  GROUP   PROG
PROG    SEGMENT BYTE PUBLIC 'PROG'
        PUBLIC  DrawFld0
        ASSUME  CS:PGROUP
DrawFld0 proc near
;   
;   bp.4    src     &word
    push  bp
    mov   bp, sp
    mov   si, word ptr [bp + 4]
    push  es
    mov   di, 0
    cld   
    mov   ax, DISPLAY_BUFFER
    mov   es, ax
    mov   cx, FIELD_SZ
pixel_loop:
    movsw es:[di], [si]
    loop  pixel_loop
    pop   es
    pop   bp
    ret   
DrawFld0 endp
PROG ends
end