.radix  16
;
;   equates
;
PGROUP  GROUP   PROG
PROG    SEGMENT BYTE PUBLIC 'PROG'
        PUBLIC  setVideoMode_, BiosVideo_
        ASSUME  CS:PGROUP
;
setVideoMode_ proc near
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
setVideoMode_    endp
;
;
BiosVideo_ proc near
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
BiosVideo_   endp
PROG ends
end
