%include "winapi64.inc"

%include "main-win64.inc"


global __start


section .text
__start:
    ; сохранение регистров
    ; +----------------------------------------+
    ; 8 байт - перед вызовом __start
    ; ==========================================
    ; 32 байт - shadow space
    ; 16 байт - r12, r13
    ; 8 байт - argc (позже сохраняется в r13)
    ; ==========================================
    ; 8 байт - выравнивание
    ; +----------------------------------------+
    sub rsp, 32+16+8
    mov [rsp + 32], r12
    mov [rsp + 40], r13

    call GetCommandLineW

    mov rcx, rax ; аргумент 1 - указатель на строку
    lea rdx, [rsp + 48] ; аргумент 2 - указатель на число в стеке
    call CommandLineToArgvW

    mov r12, rax ; указатель на массив строк
    mov r13, [rsp + 48] ; argc

    ; вызов _main
    ; mov rcx, r12
    ; mov rdx, r13
    call _main
    mov [rsp + 48], rax

    ; очищение массива строк командной строки
    mov rcx, r12
    call LocalFree

    ; возврат регистров
    mov r12, [rsp + 32]
    mov r13, [rsp + 40]

    ; конец
    mov ecx, [rsp + 48]
    call ExitProcess
