// программа для счета файлов в папке
// сделано romsk64, 2026 год
// код лицензирован под AGPLv3, да, вот так вот


#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>

#define RECURSIVE true
#define UNRECURSIVE false


__attribute__((section(".copyright"), used))
const wchar_t ___unused_copyrightInfo[] = \
L"Copyright (c) 2026, romsk64\n\
Программа для нахождения количества файлов в директории.\n\
Распространяется под GNU Affero GPL, v3.0, прикиньте, да?";


uint64_t countFiles(const wchar_t *directory, bool recursive) {
    WIN32_FIND_DATAW findData;
    wchar_t searchPath[MAX_PATH];

    // маска поиска: "путь/*"
    int written = swprintf(searchPath, MAX_PATH, L"%ls\\*", directory);
    if (written < 0 || written >= MAX_PATH) {
        return 0; // путь превышает лимит MAX_PATH
    }

    HANDLE hFind = FindFirstFileW(searchPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return 0;
    }

    uint64_t filesCount = 0;

    do {
        if ((wcscmp(findData.cFileName, L".") == 0) ||
            (wcscmp(findData.cFileName, L"..") == 0))
        {
            continue;
        }

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (recursive) {
                wchar_t subDirectory[MAX_PATH];
                int subWritten = swprintf(subDirectory, MAX_PATH, L"%ls\\%ls", directory, findData.cFileName);

                if (subWritten > 0 && subWritten < MAX_PATH) {
                    filesCount += countFiles(subDirectory, true);
                }
            }
        }
        else {
            filesCount++;
        }
    } while (FindNextFileW(hFind, &findData));

    FindClose(hFind);
    return filesCount;
}


int wmain(int argc, wchar_t *argv[]) {
    _setmode(_fileno(stdout), _O_U16TEXT);

    LANGID langId = GetUserDefaultUILanguage();
    wchar_t *targetDirectory = NULL;

    if (argc == 1) {
lbUsageHelp:
        wchar_t exeFilePath[MAX_PATH];
        memset(exeFilePath, (int)'\0', sizeof(exeFilePath));
        DWORD exeFilePathLength = GetModuleFileNameW(NULL, exeFilePath, MAX_PATH);

        if (exeFilePathLength > 0 && exeFilePathLength < MAX_PATH) {
            if (langId == MAKELANGID(LANG_RUSSIAN, SUBLANG_RUSSIAN_RUSSIA)) {
                wprintf(L"Использование: %ls [-r] [-w!] <путь\\к\\папке>\n", exeFilePath);
                wprintf(L"\nНажмите Enter для выхода...");
                getwchar();
            }
            else {
                wprintf(L"Usage: %ls [-r] [-w!] <path\\to\\directory>\n", exeFilePath);
                wprintf(L"\nPress Enter to exit...");
                getwchar();
            }
        }

        return 1;
    }

    bool recursive = false;
    bool waitingForClickAtEnd = true;
    for (int i = 1; i < argc; i++) {
        if (wcscmp(argv[i], L"-r") == 0) {
            recursive = true;
        }

        else if (wcscmp(argv[i], L"-w!") == 0) {
            waitingForClickAtEnd = false;
        }

        else if (wcscmp(argv[i], L"-w") == 0) {
            waitingForClickAtEnd = true;
        }

        else {
            targetDirectory = argv[i];
        }
    }

    if (targetDirectory == NULL) {
        if (langId == MAKELANGID(LANG_RUSSIAN, SUBLANG_RUSSIAN_RUSSIA))
            wprintf(L"Путь к папке не передан!\n\n");
        else wprintf(L"Path to directory hasn't passed!\n\n");

        goto lbUsageHelp;
    }

    uint64_t flatResult;
    uint64_t deepResult;

    flatResult = countFiles(targetDirectory, UNRECURSIVE);
    if (recursive)
        deepResult = countFiles(targetDirectory, recursive);

    if (langId == MAKELANGID(LANG_RUSSIAN, SUBLANG_RUSSIAN_RUSSIA)) {
        if (recursive)
            wprintf(L"Программа отработала в рекурсивном режиме.\n\n");
        wprintf(L"Результаты работы:\n");
        wprintf(L"\tОтсканированная папка: %ls.\n", targetDirectory);
        wprintf(L"\tФайлов в корне: %llu.\n", flatResult);
        if (recursive)
            wprintf(L"\tФайлов всего (рекурсивно): %llu.\n", deepResult);

        if (waitingForClickAtEnd) {
            wprintf(L"\nНажмите Enter для выхода...");
            getwchar();
        }
    }
    else if (langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)) {
        if (recursive)
            wprintf(L"The program finished running in recursive mode.\n\n");
        wprintf(L"Working results:\n");
        wprintf(L"\tScanned folder: %ls.\n", targetDirectory);
        wprintf(L"\tFiles in root: %llu.\n", flatResult);
        if (recursive)
            wprintf(L"\tTotal files (recursive): %llu.\n", deepResult);

        if (waitingForClickAtEnd) {
            wprintf(L"\nPress Enter to exit...");
            getwchar();
        }
    }
    else {
        if (recursive)
            wprintf(L"The program has finished running in recursive mode.\n\n");
        wprintf(L"Working results:\n");
        wprintf(L"\tScanned directory: %ls.\n", targetDirectory);
        wprintf(L"\tFiles in root: %llu.\n", flatResult);
        if (recursive)
            wprintf(L"\tTotal files (recursively): %llu.\n", deepResult);

        if (waitingForClickAtEnd) {
            wprintf(L"\nPress Enter to exit...");
            getwchar();
        }
    }

    return 0;
}
