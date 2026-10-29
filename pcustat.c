/* PCUStat - PC Using Statistics
 * by romsk64
 */

#include <windows.h>
#include <shlobj.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>

#define PCUSTAT_MCR_STATFILE_NAME "_pcustat_stat.txt"


// wchar_t *pwszUserProfilePath;
// wchar_t *pwszStatfilePath;

int wstrcpy_bs(
    wchar_t *restrict dest,
    const wchar_t *restrict src,
    const size_t destMaxLength
) {
    size_t srcLength = wcslen(src);
    if ((srcLength + 1) > destMaxLength) {
        return 1;
    }

    wmemcpy(dest, src, srcLength);
    dest[srcLength] = L'\0';

    return 0;
}

int wstrcat_bs(
    wchar_t *restrict destStr1,
    const wchar_t *restrict str2,
    const size_t destMaxLength
) {
    size_t str1Length = wcslen(destStr1);
    size_t str2Length = wcslen(str2);

    if ((str1Length + str2Length + 1) > destMaxLength) {
        return 1;
    }

    wmemmove(destStr1 + str1Length, str2, str2Length);
    destStr1[str1Length + str2Length] = L'\0';

    return 0;
}


// структура для хранения статистики
struct PCUStat_STAT {
    size_t clicksCount;
    size_t *ptrToHoursCounts; // т.е. поинтер на счетчики для разных прог
};

static inline void PCUStat_Stat_initClicksCount(
    struct PCUStat_STAT *const stat,
    const size_t clicksCount
) {
    stat->clicksCount = clicksCount;
}

static inline void PCUStat_Stat_initPtrToHoursCounts(
    struct PCUStat_STAT *restrict const stat,
    const size_t *restrict const ptrToHoursCounts
) {
    stat->ptrToHoursCounts = ptrToHoursCounts;
}

int PCUStat_Stat_initAndReadStatfile(
    struct PCUStat_STAT *restrict const stat,
    const wchar_t *restrict const pwszStatfilePath
) {
    HANDLE hStatfile;

    DWORD dwBytesToRead;
    DWORD dwBytesReadden;
    char readingBuffer[1024 * 24];
    BOOL bReadingStatus;

    size_t lastByte;

    int errorCode;


    errorCode = 0;
    bool contentExists = true;
    HANDLE hStatfile = CreateFileW(
        (LPCWSTR)pwszStatfilePath,
        GENERIC_READ,
        FILE_SHARED_READ,
        (LPSECURITY_ATTRIBUTES)NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        (HANDLE)NULL
    );
    if (hStatfile == INVALID_HANDLE_VALUE) {
        DWORD dwLastError = GetLastError();

        if (dwLastError == ERROR_FILE_NOT_FOUND) {
            HANDLE hTmp_newStatfile = CreateFileW(
                (LPCWSTR)pwszStatfilePath,
                GENERIC_WRITE,
                (DWORD)0,
                (LPSECURITY_ATTRIBUTES)NULL,
                CREATE_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                (HANDLE)NULL
            );
            contentExists = false;

            CloseHandle(hTmp_newStatfile);
            return 1;
        }
    }

    // обработка файла
    ZeroMemory(readingBuffer, sizeof(readingBuffer));
    bReadingStatus = TRUE; // типа WinAPI true а не сишный
    dwBytesReadden = 0;
    dwBytesToRead = sizeof(readingBuffer);

    while (bReadingStatus) {
        // чтение файла в буффер
        bReadingStatus = ReadFile(
            hStatfile,
            readingBuffer,
            dwBytesToRead,
            &dwBytesReadden,
            (LPOVERLAPPED)NULL
        );
        if (!bReadingStatus) {
            errorCode = 2;
            goto lbCleanupFailed;
        }

        // ========== обработка файла =========
        if (dwBytesReadden == 0) {
            goto lbCleanupSuccess;
        }

        lastByte = (dwBytesReadden < dwBytesToRead) ?
            (dwBytesToRead - dwBytesReadden) :
            dwBytesToRead;

        // продолжить потом
    }


lbCleanupSuccess:
    CloseHandle(hStatfile);
    return 0;

lbCleanupFailed:
    CloseHandle(hStatfile);
    return errorCode;
}



int PCUStat_getUserProfilePath(wchar_t **pwszPath) {
    if (pwszPath != NULL) return 1;

    HRESULT hres = SHGetKnownFolderPath(
        &FOLDERID_Profile,
        0,
        NULL,
        (PWSTR *)pwszPath
    );

    return SUCCEEDED(hres) ? 0 : 2;
}

int PCUStat_freeUserProfilePath(wchar_t *pwszPath) {
    CoTaskMemFree((PWSTR)pwszPath);

    return 0;
}


int PCUStat_genStatfilePath(
    const wchar_t *pwszUserProfilePath,
    wchar_t **pwszResultStr
) {
    if (pwszUserProfilePath == NULL ||
        pwszResultStr == NULL) {
        return -1;
    }

    size_t lengthOfTwoStrings =
        wcslen(pwszUserProfilePath) +
        wcslen(PCUSTAT_MCR_STATFILE_NAME) + 1;

    {
        register const size_t lots_8divWithMod_res = lengthOfTwoStrings & 7;

        if (lots_8divWithMod_res != 0) {
            lengthOfTwoStrings += (8 - lots_8divWithMod_res);
        }
    }

    wchar_t *resStr = malloc(lengthOfTwoStrings * sizeof(wchar_t));
    if (resStr == NULL) return 1;

    int errorCode = 0;

    errorCode = wstrcpy_bs(
        resStr,
        pwszUserProfilePath,
        lengthOfTwoStrings
    );
    if (errorCode != 0) {
        errorCode += 100;
        goto lbCleanupFailed;
    }

    errorCode = wstrcat_bs(
        resStr,
        PCUSTAT_MCR_STATFILE_NAME,
        lengthOfTwoStrings
    );
    if (errorCode != 0) {
        errorCode += 200;
        goto lbCleanupFailed;
    }

    *pwszResultStr = resStr;
    return 0;


lbCleanupFailed:
    free(resStr);
    *pwszResultStr = NULL;
    return errorCode;
}

int PCUStat_freeStatfilePath(wchar_t **resStr) {
    if (resStr == NULL ||
        *resStr == NULL) {
        return 1;
    }

    free(*resStr);
    *resStr = NULL;

    return 0;
}


int PCUStat_savestat(
    struct PCUStat_STAT *restrict const stat,
    const wchar_t *restrict const pwszUserProfilePath
) {

