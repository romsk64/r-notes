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
    sub       rsp, 32 + 16 + 8                       ; выравнивание стека (8 на указаель, 8 на сохр. r12)

    call      GetCommandLineW

    mov       rcx, rax                               ; первый аргумент (результат CommandLineToArgvW)
    mov       QWORD [rsp + 32], 0
    lea       rdx, [rsp + 32]                        ; второй аргумент (указатель на argc)
    call      CommandLineToArgvW                     ; выхов функции
    mov       QWORD [rsp + 32 + 8], r12              ; сохранение r12
    mov       r12, rax                               ; сохранение в r12 результата работы CommandLineToArgvW

    mov       rcx, QWORD [rsp + 32]                  ; argc
    mov       rdx, rax                               ; argvW
    call      wmain                                  ; вызов wmain

    mov       QWORD [rsp + 32 + 16], r13             ; сохранение r13
    mov       r13, rax                               ; сохранение в r13 результата работы wmain

;   mov       rcx, QWORD [rsp + 32 + 8]              ; argvW
    mov       rcx, r12                               ; argvW
    call      LocalFree                              ; очистка argvW
    mov       r12, QWORD [rsp + 32 + 8]              ; возвращение изначального значения r12

;   mov       rcx, QWORD [rsp + 32 + 16]             ; код выхода wmain в первый аргумент ExitProcess
    mov       rcx, r13
    mov       r13, QWORD [rsp + 32 + 16]             ; возвращение изначального значения r13
    add       rsp, 32 + 16 + 8
    call      ExitProcess                            ; завершение процесса

wmain:                                               ; начало программы
    mov       rax, 0
    ret


