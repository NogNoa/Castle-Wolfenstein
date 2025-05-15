.radix  16
;
;   equates
    FIELD_SZ       equ  2000
    DISPLAY_BUFFER equ 0b800
    control_break_handler equ 6c
    print_screen_handler  equ 14
;
data	segment	byte public 'data'
        int_frust dw 000d, 0000
data ENDS
PROG    SEGMENT BYTE PUBLIC 'PROG' 
        PUBLIC  DrawFld0, IhbtIntr
        ASSUME  CS:PROG, DS:data
IhbtIntr proc near
    PUSH         BP
    PUSH         ES
    CLI
    LES          BX,dword ptr int_frust 
    CMP          byte ptr ES:[BX],0cd
    JNZ          frustration_failure
    ADD          BX,2
    CMP          byte ptr ES:[BX],13
    JNZ          frustration_failure
    MOV          DI,control_break_handler
    MOV          AX,EmptIntr
    CLD
    STOSW        ES:[DI]
    MOV          AX,CS
    STOSW        ES:[DI]
    MOV          DI,print_screen_handler
    MOV          AX,EmptIntr
    CLD
    STOSW        ES:[DI]
    MOV          AX,CS
    STOSW        ES:[DI]
    MOV          AX,0
epilog: 
    STI
    POP          ES
    POP          BP
    RET
frustration_failure:
    MOV          AX,ES:[BX]
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