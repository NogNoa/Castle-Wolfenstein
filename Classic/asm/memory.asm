PGROUP	GROUP	PROG
PROG	SEGMENT	BYTE PUBLIC 'PROG'
	PUBLIC	seg0_memmove, seg_memset
	ASSUME	CS:PGROUP
seg0_memmove proc near
;
;   bp.4    i           word
;   bp.6    source.i    byte
;   bp.c    numBytes    word
;   bp.e    dest        &byte
;   bp.10   source      &byte
    push        bp
    sub         sp,8
    mov         bp, sp
    mov         word ptr [bp+4], 0
for_numBytes:
    mov          ax, [bp +4]
    CMP          AX, [BP + 0Ch]
    JGE          return
    MOV          SI, [BP + 10h]
    ADD          SI,AX
    MOV          BL, [SI]
    MOV          CX, [BP + 0Eh]
    ADD          CX,AX
    MOV          [BP + 6],BL
    XOR          BH,BH
    PUSH         BX
    PUSH         CX
    XOR          AX,AX
    PUSH         AX
    CALL         seg_memset
    MOV          SP,BP
    INC          word ptr [BP + 4]
    JMP          for_numBytes
return:
    add         sp, 8
    pop         bp
    ret
seg0_memmove endp

seg_memset  proc near
;
;   bp.4    segm    word
;   bp.6    index   &byte
;   bp.8    value   byte
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
seg_memset endp
prog ends
end