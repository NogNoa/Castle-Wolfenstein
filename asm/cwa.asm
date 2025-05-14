.radix  16
;
;   equates
    GFX_8by8_Font       equ  007c
    Get_keystroke       equ  0000
    check_for_keystroke equ  0100
    gt_dflt_drv         equ  1900
    gt_oem_os_version   equ  3000
;
    FIELD_SZ            equ  2000
    DISPLAY_BUFFER      equ 0b800
;
DGROUP  GROUP   DATA
;
data	segment	byte public 'data'
        public Key_scan_code, Is_Extended_Code, dflt_drv, GfxFileP
        dflt_drv db 0
        Key_scan_code db  0
        Is_Extended_Code db 0
        GfxFileP db 0
data ENDS
PGROUP  GROUP   PROG
PROG    SEGMENT BYTE PUBLIC 'PROG'
        PUBLIC  Goober, isDos210, SegmSt, SegmGt, CallStck, IsKStrok, GetStrok, setVideo, BiosVide, DrwLwMdl, RdSysFnt
        ASSUME  CS:PGROUP, ES:DGROUP
Goober proc near
;
;   bp.4    p1      void
;   bp.6    dest    &void
;
    push    bp
    mov     bp, sp
    mov     cx, word ptr [BP + 4]
    mov     ch, cl
    mov     cl, 14
    mov     al, 1
    mov     ah, 2
    mov     bx, word ptr [bp + 6]
    push    CS
    pop     ds
    mov     word ptr ds:[bx_load + 1], bx 
    ;comipiles to mov word ptr cs:[0xe0e], bx; 2E 89 1E 0E 0E
    push    ES
    pop     DS
bx_load label word
    mov     bx, 0
    push    bx
    mov     dl, byte ptr [dflt_drv]
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
        Assume nothing
        Assume CS:PGROUP, DS:DGROUP
;
DrwLwMdl proc near ;DrawLowMiddle
    push  bp
    push  es
    cld   
    mov   ax, DISPLAY_BUFFER
    mov   es, ax
    mov   bp, 1424
    mov   si, word ptr [GfxFileP]
whle1745:
    mov   di, bp
    mov   cx, 10
fr10fld0:
    movsw word ptr es:[di], word ptr [si]
    loop  fr10fld0
    mov   di, bp
    add   di, FIELD_SZ
    mov   cx, 10
fr10fld1:
    movsw word ptr es:[di], word ptr [si]
    loop  fr10fld1
    add   bp, 50
    cmp   bp, 1745
    jc    whle1745
    pop   es
    pop   bp
    ret   
DrwLwMdl endp
;
IsKStrok proc near
;calls hard-coded function                           
;BDOS_CKS 11                                         
;
;return boolean value but in AX    
        PUSH         BP
        MOV          AX,check_for_keystroke             ;check for keystroke
        INT          16                                 ;keyboard
        JZ           no_stroke                           ;set=no keystroke                                                                                                 on keyboard buffer
        MOV          AX,1
        POP          BP
        RET
no_stroke:
        MOV          AX,0
        POP          BP
        RET
IsKStrok endp
;
GetStrok proc near
        assume DS:data
;
; return either scan code or ascii
;
        PUSH         BP
        CMP          byte ptr [Is_Extended_Code],0    ;if we got null last time
        JZ           ask_keyboard                       ;nope
        MOV          byte ptr [Is_Extended_Code],0    ;Say no next time
        MOV          AL,[Key_scan_code]                 ;AL=previous Scan code
        JMP          get_stroke_final
ask_keyboard:
        MOV          AX,Get_keystroke                   ;get keystroke
        INT          16                               ;keyboard                                                                                            AL = Ascii code
        CMP          AL,0
        JNZ          get_stroke_final                   ;charecter is not zero
        MOV          byte ptr [Is_Extended_Code],1    ;We did get null
        MOV          byte ptr [Key_scan_code],AH        ;save scan code then
get_stroke_final: 
        XOR          AH,AH                              ;zero out AH                                                                                                so AX = AL
        POP          BP
        RET
GetStrok endp
;
setVideo proc near
;
;   bp.4    mode_p  byte
;   ret     mode flag or -1 on failure  int
;
    PUSH    BP
    MOV     BP, SP
    MOV     AX, word ptr [BP + 4]
    XOR     AH,AH
    CMP     AL, 7
    JA      invalid_mode    ;only modes up to 7 are supported
    INT     10
    XOR     AH,AH
epilog:
    POP     BP
    RET
invalid_mode:
    MOV     AX, -1
    JMP     epilog
setVideo    endp
;
SegmGt proc near
;
;   bp.4    segment word
;   bp.6    index   &byte
;   ret     value   byte
;
    push         BP
    MOV          BP,SP
    MOV          SI,word ptr [BP + 4]
    MOV          ES,SI  ;ES := segment
    MOV          BX,word ptr [BP + 6]
    MOV          AL,byte ptr ES:[BX]
    MOV          AH, 0
    POP          BP
    PUSH         DS
    POP          ES     ;ES := DS
    RET
SegmGt endp
;
SegmSt  proc near
;
;   bp.4    segm    word
;   bp.6    index   &byte
;   bp.8    value   byte
;   ret     bp.8
;
    PUSH         BP
    MOV          BP,SP
    MOV          SI, [BP + 4]
    MOV          ES,SI
    MOV          BX, [BP + 6]
    MOV          AL, [BP + 8]
    MOV          ES:[BX],AL
    MOV          AL, ES:[BX]
    MOV          AH,0
    MOV          BX,DS
    MOV          ES,BX
    POP          BP
    RET
SegmSt endp
;
BiosVide proc near
;   
;   arguments self-evident. no return
;
    PUSH    BP
    MOV          BP,SP
    PUSH         DS
    MOV          AX,word ptr [BP + 4]
    MOV          BX,word ptr [BP + 6]
    MOV          CX,word ptr [BP + 8]
    MOV          DX,word ptr [BP +0a]
    INT          10
    POP          DS
    POP          BP
    RET
BiosVide   endp
;
RdSysFnt proc near ; Redirect System Font
;
;   bp.4    font_pointer    &byte
;
    push    BP
    mov     bp, sp
    mov     ax, word ptr [BP+4]
    mov     si, 0
    mov     es, si
    mov     bx, GFX_8by8_Font+2
    mov     word ptr es:[bx], ds
    mov     bx, GFX_8by8_Font
    mov     word ptr es:[bx], ax
    mov     ax, 0
    mov     bx, ds
    mov     es, bx
    pop     bp
    ret
RdSysFnt endp
;
isDos210 proc near
;
;   ret 1- success 0- fail  bool
;
    push    bp
    mov     ax,gt_dflt_drv   ;get current default drive
    int     21
    mov     byte ptr [dflt_drv], AL
    CALL    DelInst5ff9
    mov     ax, gt_oem_os_version
    int     21
    CMP     AL, 2               ;is dos 2.?
    jnz     return_zero
    CMP     AH, 0a              ; is dos ?.10?
    jnz     return_zero
    mov     ax, 1
    pop     BP
    ret
isDos210 endp
;
return_zero proc near 
    mov     ax, 0
    POP     BP
    RET
return_zero endp
;
DelInst5ff9 proc near
;
    mov     bl, 90
    mov     byte ptr CS:[dest_write], BL    ; dest_write label in the Goober Procedure
    mov     bl, 90
    mov     byte ptr CS:[dest_write + 1], BL
    Ret
DelInst5ff9 endp
;
CallStck proc near
;
;   bp.6    old_bp    void*
;   bp.-4   OnStack   function
;
    push    bp
    SUB     sp, 6
    mov     bp, sp
    mov     bx, word ptr [bp + 6]
    mov     ax,SS
    push    ax
    add     bx, 2
    push    bx
    call    dword ptr [bp - 4]
    add     sp, 0a
    POP     bp
    ret
CallStck endp
;
prog ends
;
end