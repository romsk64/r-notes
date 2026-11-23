%include "winapi64.inc"


global _main


section .rdata
flagc_enablechars             dw __utf16__("-c")
flagc_enablecharsfull         dw __utf16__("--chars")
flagc_enablewords             dw __utf16__("-w")
flagc_enablewordsfull         dw __utf16__("--words")
flagc_enablelines             dw __utf16__("-l")
flagc_enablelinesfull         dw __utf16__("--lines")
flagc_enableparagraphs        dw __utf16__("-p")
flagc_enableparagraphsfull    dw __utf16__("--paragraphs")
lenflagc_enableparagraphsfull equ $ - flagc_enableparagraphsfull
flagc_enablesentences         dw __utf16__("-s")
flagc_enablesentencesfull     dw __utf16__("-sentences")
lenflagc_enablesentencesfull  equ $ - flagc_enablesentencesfull
flagc_freq                    dw __utf16__("-f")
flagc_freqfull                dw __utf16__("--freq")
lenflagc_freqfull             equ $ - flagc_freqfull
flagst_encoding               dw __utf16__("--encoding")
lenflagst_encoding            equ $ - flagst_encoding
flagst_output                 dw __utf16__("-o")
flagst_outputfull             dw __utf16__("--output")
lenflagst_outputfull          equ $ - flagst_outputfull
flagst_outputfmt              dw __utf16__("-ofmt")
flagst_outputfmtfull          dw __utf16__("--output-format")
flagparam_encoding_utf8       dw __utf16__("utf8")
flagparam_encoding_utf16      dw __utf16__("utf16")
flagparam_outputfmt_json      dw __utf16__("json")
flagparam_outputfmt_xml       dw __utf16__("xml")
flagparam_outputfmt_csv       dw __utf16__("csv")
lenshortargs                  equ 4 ; 2*2
lenshortformats               equ 6 ; 3*2
lenshortfullargs              equ 14 ; 7*2


section .text
_main:
    ; r12 - указатель на массив строк
    ; r13 - количество строк в массиве
    test r12, r12
    mov rax, 1
    jz .startupret

    ; разбор аргументов
    mov ecx, 1
.arglp:
.arglp_strcmp:
    pcmpistri
    inc ecx

.startupret
    ret
