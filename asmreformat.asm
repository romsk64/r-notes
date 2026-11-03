                                                     ; Форматтер ассемблера на ассемблере, лол

global _start
global main

extern GetStdHandle                                   ; блок объявлений
extern ReadFile
extern WriteFile
extern CreateFileW
extern CommandLineToArgvW
extern GetCommandLineW
extern LocalFree

section .text
_start:
    sub       rsp, 32 + 8 + 8                        ; выравнивание стека (8 на указаель, 8 на сохр. r12)

    call      GetCommandLineW

    mov       rcx, rax                               ; первый аргумент (результат CommandLineToArgvW)
    mov       QWORD PTR [rsp + 32], 0
    lea       rdx, [rsp + 32]                        ; второй аргумент (указатель на argc)
    call      CommandLineToArgvW                     ; выхов функции
;   mov       QWORD PTR [rsp + 32 + 8], r12          ; сохранение r12
;   mov       r12, rax                               ; сохранение в r12 результата работы CommandLineToArgvW

    mov       rcx, QWORD [rsp + 32]                  ; argc
    mov       rdx, rax                               ; argv
    call      wmain                                  ;
