.radix  16
;
;   equates
        check_for_keystroke equ 0100
        Get_keystroke       equ 0000
;
DGROUP  GROUP   DATA
data	segment	byte public 'data'
        public Key_scan_code, Is_Extended_Code, dflt_drv
        dflt_drv db 0
        Key_scan_code db  0
        Is_Extended_Code db 0
data ENDS
PGROUP  GROUP   PROG
PROG    SEGMENT BYTE PUBLIC 'PROG'
        PUBLIC  IsKStrok, GetStrok           
        ASSUME  CS:PGROUP                
;
IsKStrok proc near
;calls hard-coded function                           
;BDOS_CKS 11                                         
;
;return boolean value but in AX    
        PUSH         BP
        MOV          AX,check_for_keystroke             ;check for keystroke
        INT          16                                 ;keyboard
        JZ           no_stoke                           ;set=no keystroke                                                                                                 on keyboard buffer
        MOV          AX,1
        POP          BP
        RET
no_stoke:
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
prog ends
;
end