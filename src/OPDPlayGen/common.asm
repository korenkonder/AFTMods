EXTERN ?originalRobCloth__CtrlOsagePlayData_mid1@@3P6AXXZEA : QWORD
EXTERN ?originalRobCloth__CtrlOsagePlayData_mid2@@3P6AXXZEA : QWORD
EXTERN ?originalRobOsage__CtrlOsagePlayData_mid1@@3P6AXXZEA : QWORD
EXTERN ?originalRobOsage__CtrlOsagePlayData_mid2@@3P6AXXZEA : QWORD

EXTERN ?originalrob_chara_item_equip__set_opd_blend_data_mid@@3P6AXXZEA : QWORD

EXTERN ?originalExClothBlock__CtrlMain_mid@@3P6AXXZEA : QWORD
EXTERN ?originalExOsageBlock__CtrlMain_mid@@3P6AXXZEA : QWORD
EXTERN ?originalExExpressionBlock__Calc_mid@@3P6AXXZEA : QWORD
EXTERN ?originalExOsageBlock__CtrlStep_mid@@3P6AXXZEA : QWORD

EXTERN ?opd_play_gen_run@@3U?$atomic@_N@std@@A : BYTE

.DATA
?get_delta_frame@@YAMXZ QWORD 140192D50h ; float_t get_delta_frame()
__real@3f800000 DWORD 3F800000h ; 1.0f

.CODE
?implOfRobCloth__CtrlOsagePlayData_mid1@@YAXXZ PROC PUBLIC
    jb end_func
    cmp byte ptr [rbx-0Bh], 0 ; opd_blend_data + 0x0D
    jz end_func
    movss xmm9, xmm2
    subss xmm9, __real@3f800000

end_func:
    jmp ?originalRobCloth__CtrlOsagePlayData_mid1@@3P6AXXZEA
?implOfRobCloth__CtrlOsagePlayData_mid1@@YAXXZ ENDP

?implOfRobCloth__CtrlOsagePlayData_mid2@@YAXXZ PROC PUBLIC
    jb end_func
    cmp byte ptr [rbx-0Bh], 0 ; opd_blend_data + 0x0D
    jz end_func
    cvtss2si rdx, xmm2
    lea rcx, [rdx-01h]

end_func:
    jmp ?originalRobCloth__CtrlOsagePlayData_mid2@@3P6AXXZEA
?implOfRobCloth__CtrlOsagePlayData_mid2@@YAXXZ ENDP

?implOfRobOsage__CtrlOsagePlayData_mid1@@YAXXZ PROC PUBLIC
    jb end_func
    cmp byte ptr [rsi+0Ch], 0 ; opd_blend_data + 0x0D
    jz end_func
    movss xmm8, xmm2
    subss xmm8, __real@3f800000

end_func:
    jmp ?originalRobOsage__CtrlOsagePlayData_mid1@@3P6AXXZEA
?implOfRobOsage__CtrlOsagePlayData_mid1@@YAXXZ ENDP

?implOfRobOsage__CtrlOsagePlayData_mid2@@YAXXZ PROC PUBLIC
    jb end_func
    cmp byte ptr [rsi+0Ch], 0 ; opd_blend_data + 0x0D
    jz end_func
    cvtss2si rax, xmm2
    lea r9, [rax-01h]

end_func:
    jmp ?originalRobOsage__CtrlOsagePlayData_mid2@@3P6AXXZEA
?implOfRobOsage__CtrlOsagePlayData_mid2@@YAXXZ ENDP

?implOfrob_chara_item_equip__set_opd_blend_data_mid@@YAXXZ PROC PUBLIC
    mov byte ptr [rsp+2Dh], 0
    jmp ?originalrob_chara_item_equip__set_opd_blend_data_mid@@3P6AXXZEA
?implOfrob_chara_item_equip__set_opd_blend_data_mid@@YAXXZ ENDP

?implOfExClothBlock__CtrlMain_mid@@YAXXZ PROC PUBLIC
    movss xmm0, __real@3f800000
    cmp ?opd_play_gen_run@@3U?$atomic@_N@std@@A, 0
    jnz end_func
    call ?get_delta_frame@@YAMXZ

end_func:
    jmp ?originalExClothBlock__CtrlMain_mid@@3P6AXXZEA
 ?implOfExClothBlock__CtrlMain_mid@@YAXXZ ENDP

?implOfExOsageBlock__CtrlMain_mid@@YAXXZ PROC PUBLIC
    movss xmm0, __real@3f800000
    cmp ?opd_play_gen_run@@3U?$atomic@_N@std@@A, 0
    jnz end_func
    call ?get_delta_frame@@YAMXZ

end_func:
    jmp ?originalExOsageBlock__CtrlMain_mid@@3P6AXXZEA
 ?implOfExOsageBlock__CtrlMain_mid@@YAXXZ ENDP

?implOfExExpressionBlock__Calc_mid@@YAXXZ PROC PUBLIC
    movss xmm0, __real@3f800000
    cmp ?opd_play_gen_run@@3U?$atomic@_N@std@@A, 0
    jnz end_func
    call ?get_delta_frame@@YAMXZ

end_func:
    jmp ?originalExExpressionBlock__Calc_mid@@3P6AXXZEA
 ?implOfExExpressionBlock__Calc_mid@@YAXXZ ENDP

?implOfExOsageBlock__CtrlStep_mid@@YAXXZ PROC PUBLIC
    movss xmm0, __real@3f800000
    cmp ?opd_play_gen_run@@3U?$atomic@_N@std@@A, 0
    jnz end_func
    call ?get_delta_frame@@YAMXZ

end_func:
    jmp ?originalExOsageBlock__CtrlStep_mid@@3P6AXXZEA
 ?implOfExOsageBlock__CtrlStep_mid@@YAXXZ ENDP
END