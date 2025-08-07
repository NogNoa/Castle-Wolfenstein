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
        carousel_count dw 0
        pr_flag db 0
        extern isDemo: byte
        extern GfxFileP: word
data ENDS
PROG    SEGMENT BYTE PUBLIC 'PROG' 
        PUBLIC  DrawCG, IhbtIntr
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
DrawCG proc near
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
DrawCG endp
;
SPK03A1 proc near
;
    push bp
    push es
    cmp  byte ptr [isDemo], 0
    jnz  step
    mov  si, 0x40
    mov  es, si
    mov  bx, 0x6c
    mov  al, byte ptr es:[bx]
carousel:
    shr  al, 1
    ror  word ptr [0x7712], 1
    ror  word ptr [0x7714], 1
    mov  bx, word ptr [0x7714]
    ror  bx, 1
    xor  ax, bx
    mov  word ptr [0x7714], ax
    mov  ah, 0
    pop  es
    pop  bp
    cmp  byte ptr [carousel_count], al
    jbe  return
    push ax
play_resume:
    cmp  byte ptr [pr_flag], 0
    jne  epilog
    in   al, 0x61
    and  al, 0xfe
    xor  al, 2
    out  0x61, al
epilog:
    pop  ax
return:
    ret  
step:
    inc  word ptr [GfxFileP]
    mov  si, word ptr [GfxFileP]
    mov  al, byte ptr [si]
    jmp  0x14

PROG ends
end