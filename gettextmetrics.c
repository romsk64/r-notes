// программа для получения текстовых метрик в разных кодировках,
// на разных языках по размеру текстового файла
// на C99

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>


#define ___FLAG_BYTES     0
#define ___FLAG_KILOBYTES 1
#define ___FLAG_MEGABYTES 2
#define ___FLAG_GIGABYTES 3
#define ___FLAG_TERABYTES 4

#define KBYTE_BSIZE 1024 // размер килобайта в байтах
#define MBYTE_BSIZE 1024 * 1024 // размер мегабайта в байтах
#define A4_PAGE_SIZE_INCHARS 1800 // примерно 1800 символов на страницу A4
#define RUSSIAN_CHAR_UTF8_BSIZE 2 // 2 байта в UTF8
#define RUSSIAN_WORD_SIZE_INCHARS 7 // 7 символов среднее слово
#define RUSSIAN_CHAR_WIN1251_BSIZE 1 // 2 байта в Windows 1251


int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("No arguments!\n");
        return 1;
    }

    size_t size = 0;
    bool ___size_defined = false;
    uint8_t ___flag_size = ___FLAG_BYTES; // какой коэффицент

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-kb") == 0) {
            if (___flag_size != ___FLAG_BYTES) {
                printf("Error 2!\n");
                return 1;
            }

            ___flag_size = ___FLAG_KILOBYTES;
        }

        else if (strcmp(argv[i], "-mb") == ) {
            if (___flag_size != ___FLAG_BYTES) {
                printf("Error 2!\n");
                return 1;
            }

            ___flag_size = ___FLAG_MEGABYTES;
        }

        else if (strcmp(argv[i], "-gb") == 0) {
            if (___flag_size != ___FLAG_BYTES) {
                printf("Error 2!\n");
                return 1;
            }

            ___flag_size = ___FLAG_GIGABYTES;
        }

        else if (strcmp(argv[i], "-tb") == 0) {
            if (___flag_size != ___FLAG_BYTES) {
                printf("Error 2!\n");
                return 1;
            }

            ___flag_size = ___FLAG_TERABYTES;
        }

        else {
            if (___size_defined) {
                printf("Error 3: Unknown flag!\n");
                return 1;
            }

            char *endptr;
            size = (size_t)strtoull(&(argv[i]), &endptr, strlen(argv[i]));

            if (argv[i] == endptr) {
                printf("Error 4: Number at argument not found!\n");
                return 1;
            }
        }
    }

    return 0;
}
