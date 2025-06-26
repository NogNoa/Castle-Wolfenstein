.radix  16
;
;
;   equates
       JoyA_AxisX    equ    1
       JoyA_AxisY    equ    2
       JoyA_Axes     equ    3
       JoyA_Butt1    equ    10
       JoyA_Butt2    equ    20
data	segment	byte public 'data'
;
       ptr_joystick_buffer  dw OFFSET joystick_buffer
       JoyButton1           db 0
       JoyButton2           db 0
       joystick_buffer      db 300d dup(0)
       extern JoyXDuration: byte
       extern JoyYDuration: byte
data ENDS
PROG    SEGMENT BYTE PUBLIC 'PROG'
        PUBLIC  Sum
        ASSUME  CS:PROG, DS:data

prflJystk proc near
;
       MOV        byte ptr [JoyButton1],0                          ;= FALSE
       MOV        byte ptr [JoyButton2],0                          ;= FALSE
       MOV        DI,word ptr [ptr_joystick_buffer]                ;= 1a27:9d54
       MOV        DX,201
       OUT        DX,AL                                            ;"fire joysticks four one-shots"
       MOV        CX,fa
sample_joystick:
       IN         AL,DX
       AND        AL,JoyA_Axes
       MOV        byte ptr [DI],AL
       JZ         sample_button1
       INC        DI
       LOOPNZ     sample_joystick
       MOV        byte ptr [JoyXDuration],ff                     ;joystick buffer exhusted
                
       MOV        byte ptr [JoyYDuration],ff
                
       JMP        Epilog
       NOP
sample_button1:  
       MOV        DX,201
       OUT        DX,AL
       IN         AL,DX
       TEST       AL,JoyA_Butt1
       JNZ        sample_button2
       MOV        byte ptr [JoyButton1],1                        ;= FALSE

sample_button2:  
       TEST       AL,JoyA_Butt2
       JNZ        clear_duration
       MOV        byte ptr [JoyButton2],1                        ;= FALSE
                
clear_duration:
       MOV        DI,word ptr [ptr_joystick_buffer]                  ;= 1a27:9d54
       MOV        byte ptr [JoyXDuration],0
                
       MOV        byte ptr [JoyYDuration],0
mesure_Duration:  
       MOV        AL,byte ptr [DI]
       INC        DI
       TEST       AL, JoyA_Axes
       JZ         Epilog
       TEST       AL,JoyA_AxisX
       JZ         check_Y_duration
       INC        byte ptr [JoyXDuration]
check_Y_duration:
       TEST       AL,JoyA_AxisY
       JZ         mesure_Duration
       INC        byte ptr [JoyYDuration]
       JMP        mesure_Duration
Epilog:
       POP        BP
       RET
prflJystk     endp


Sum proc near
;
;   bp.4    list    &int
;   bp.6    len     int
;
    push    BP
    mov     bp, sp
    mov     si, word ptr [bp + 4]
    push    CS
    mov     cx, word ptr [bp + 6]
    pop     DS                  ; load DS with program segment
for_cx:
    add     ax, word ptr [si]
    add     si, 2
    loop    for_cx
    push    ES
    pop     DS                  ; return DS to data segment
    pop     BP
    ret
Sum endp
prog ends
;
end
