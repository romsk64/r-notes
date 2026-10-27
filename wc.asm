; Word counter
; программа для счета количества символов, слов и размера текста
;
; NASM, Windows

; макрос SYSTEM - отображает систему и архитектуру
; 1 - Windows x86-64
; 2 - Windows x86-32
%define MACRO_SYSTEM 1

%ifndef MACRO_SYSTEM
    %error "Please define macros \"MACRO_SYSTEM\" (flag \"-DMACRO_SYSTEM\")"
%endif


global _start ; точка входа


%if MACRO_SYSTEM == 1
; ветка для Windows

; Windows x86-64 ABI Calling Convention
; Регистр %rax - для возврата значения функции
; Регистры %rcx, %rdx, %r8, %r9 - для передачи аргументов в функцию

%define STD_INPUT_HANDLE -10
%define STD_OUTPUT_HANDLE -11
%define STD_ERROR_HANDLE -12
%define MODE_NORMAL 0
%define MODE_SSE3 1

extern GetCommandLineW
extern CommandLineToArgvW
extern LocalFree
extern GetStdHandle
extern CreateFile
extern CreateFileMapping
extern CloseHandle
extern ReadFile
extern WriteFile
extern GetFileAttributesW
extern ExitProcess

section .bss
    bytesWritten resd 1

section .text
_wc_strlen:     ; uint64_t _wc_strlen(const char *argv, uint32_t mode)
    ; в %rdx режим - 0 - normal, 1 - SSE3
    cmp rcx, 0
    jz _wc_strlen.err_exit

    xor r10, r10 ; счетчик, его инициализация

    cmp rdx, MODE_NORMAL
    jz _wc_strlen.main_cycle ; если нормальный режим
    cmp rdx, MODE_SSE3
    jz _wc_strlen.err_exit ; если режим SSE (не реализовано)
    jnz _wc_strlen.err_exit ; иначе выход

_wc_strlen.main_cycle
    cmp byte[rcx], 0
    jz _wc_strlen.main_cycle.exit

    inc rcx
    inc r10
    jmp _wc_strlen.main_cycle

_wc_strlen.main_cycle.exit:
    mov rax, r10
    ret

_wc_strlen.err_exit:
    xor rax, rax
    ret


_wc_print:      ; int _wc_print(char *argv)
    sub rsp, 40 ; аллокация стека под shadow space + 8 байт под аргумент 5 (ReadFile)

    mov rcx, STD_OUTPUT_HANDLE
    call GetStdHandle ; %rax = GetStdHandle(STD_OUTPUT_HANDLE)

    mov rcx, rax ; перемещение хендла вывода в аргумент 1
    mov rdx,
    ReadFile


_start:         ; int main(int argc, char *argv[])
    mov rcx, 0
    call ExitProcess


%elif MACRO_SYSTEM == 2
; ветка для Windows x86-32
; пока не сделано

%error "Not writed yet!"


%else
; все другие системы

%error "Unknown system!"


%endif
