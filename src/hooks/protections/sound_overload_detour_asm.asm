EXTERN g_sound_overload_ret_addr: DQ

.CODE
    sound_overload_detour PROC
    	movzx eax, r8w
        lea rdx, [rcx + rcx * 2]
        cmp rdx, 190
        jle label_1
        mov rdx, 0
        jmp label_2
    label_1:
        inc ecx
        cmp r8w, [rbx + 28]
    label_2:
        push 0
        mov r11, g_sound_overload_ret_addr
        mov [rsp], r11
        ret
    sound_overload_detour ENDP

END