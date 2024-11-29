.radix  16
;
;   equates
    FIELD_SZ       equ  2000
    DISPLAY_BUFFER equ 0b800
    control_break_handler equ 6c
    print_screen_handler  equ 14
;
DGROUP  GROUP   DATA
;
data	segment	byte public 'data'
        int_frust_p dd 0000000d
data ENDS
PGROUP  GROUP   PROG
PROG    SEGMENT BYTE PUBLIC 'PROG'
        PUBLIC  DrawFld0, IhbtIntr
        ASSUME  CS:PGROUP
IhbtIntr proc near
    PUSH         ES
    CLI
    LES          BX,int_frust_p
    CMP          byte ptr ES:[BX],0cd
    JNZ          frustration_failure
    ADD          BX,2
    CMP          byte ptr ES:[BX],13
    JNZ          frustration_failure
    MOV          DI,control_break_handler
    MOV          AX,EmptIntr
    CLD
    STOSW        ES:DI
    MOV          AX,CS
    STOSW        ES:DI
    MOV          DI,print_screen_handler
    MOV          AX,EmptIntr
    CLD
    STOSW        ES:DI
    MOV          AX,CS
    STOSW        ES:DI
    MOV          AX,0
epilog: 
    STI
    POP          ES
    POP          BP
    RET
frustration_failure:
    MOV          AX,-1
    JMP          epilog
IhbtIntr endp
;
EmptIntr proc near
    IRET
EmptIntr endp
;
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