.radix  16
;
;   equates
    FIELD_SZ       equ  2000
    DISPLAY_BUFFER equ 0b800
    control_break_handler equ 6c
    print_screen_handler  equ 14
    sys8255_control equ 0x61
;
data	segment	byte public 'data'
        PUBLIC prng0, prng1
        int_frust dw 000d, 0000
        carousel_count dw 0
        pr_flag db 0
        prng0 dw 0acb6
        prng1 dw 038fa
        dnt_tgl_snd db 0
        extern isDemo: byte
        extern GfxFileP: word
data ENDS
PROG    SEGMENT BYTE PUBLIC 'PROG' 
        PUBLIC  DrawCG, IhbtIntr, SpkRng
        ASSUME  CS:PROG, DS:data
IhbtIntr proc near
    PUSH         BP
    PUSH         ES
    CLI
    LES          BX,dword ptr [int_frust]
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
;
SpkRng proc near
;
    push bp
    push es
    cmp  byte ptr [isDemo], 0
    jnz  demo_seed
    mov  si, 40
    mov  es, si
    mov  bx, 6c
    mov  al, byte ptr es:[bx]
carousel:
    shr  al, 1
    ror  word ptr [prng0], 1
    ror  word ptr [prng1], 1
    mov  bx, word ptr [prng1]
    ror  bx, 1
    xor  ax, bx
    mov  word ptr [prng1], ax
    mov  ah, 0
    pop  es
    pop  bp
    cmp  byte ptr [carousel_count], al
    jbe  TglSpkr::return
SpkRng endp


TglSpkr proc near
;
    push ax
play_resume:
    cmp  byte ptr [pr_flag], 0
    jne  epilog
    in   al, sys8255_control
    and  al, 0fe
    xor  al, 2
    out  sys8255_control, al
epilog:
    pop  ax
return:
    ret  
demo_seed:
    inc  word ptr [GfxFileP]
    mov  si, word ptr [GfxFileP]
    mov  al, byte ptr [si]
    jmp  carousel
TglSpkr endp


PROG ends
end