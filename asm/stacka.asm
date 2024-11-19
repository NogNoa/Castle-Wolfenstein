.radix  16
;
;   equates
;
PGROUP  GROUP   PROG
PROG    SEGMENT BYTE PUBLIC 'PROG'
        PUBLIC  CallStack, orrery
        ASSUME  CS:PGROUP
    extrn   default_:far
;
OnStack proc far
;
;   bp.4    arg1    word
;
    mov     ax, 201
    mov     bx, 7c62
    mov     cl, 14
    mov     ch, [BP + 4]
    mov     dx, [default_]
    nop  
    nop  
    ret
OnStack endp
;
CallStack proc near
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
CallStack endp
;
BuildFuncOnStuck proc near
;
;   bp.16    arg    word
;
    push    BP
    SUB     SP,12
    MOV     BP,SP
    MOV     word ptr [BP + 2],  1b8
    MOV     word ptr [BP + 4],0bb02
    MOV     AX,7c62
    MOV     word ptr [BP + 8],14b9
    MOV     BX,word ptr [BP + 16]
    SUB     BX,4600
orrery label word
    MOV     CL, byte ptr [default_]
    XOR     CH,CH
    MOV     word ptr [bp + 0e], 9090
    MOV     word ptr [bp + 10],  0cb
    MOV     word ptr [bp + 6], AX
    MOV     word ptr [bp + 0c], cx
    MOV     word ptr [bp + 0a], BX
    call    CallStack_
    mov     AX, 1000
    and     ax, 0ff00
    mov     word ptr [bp + 16], 1
    mov     word ptr [bp + 2], ax
clear_stack:
    mov     ax, word ptr [bp + 16]
    cmp     ax, 7
    JG      finally
    shl     ax, 1
    mov     si, ax
    mov     word ptr [bp + si + 2], 0
    inc     word ptr [bp + 16]
    jmp     clear_stack
finally:
    cmp     word ptr [bp + 2], 1000
    jnz     ret_1
    XOR     AX, AX
    add     sp, 12
    POP     BP
    ret
ret_1:
    mov     ax, 1
    add     sp, 12
    POP     bp
    ret
BuildFuncOnStuck endp   

PROG ends
end
