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


int PCUStat_getUserProfilePath(wchar_t *pwszPath) {
    if (pwszPath != NULL) return 1;

    HRESULT hres = SHGetKnownFolderPath(
        &FOLDERID_Profile,
        0,
        NULL,
        (PWSTR *)&pwszPath
    );

    if (SUCCEEDED(hres)) {
        return 0;
    }
    else {
        return 2;
    }
}

int PCUStat_freeUserProfilePath(wchar_t *pwszPath) {
    CoTaskMemFree((PWSTR)pwszPath);

    return 0;
}


int PCUStat_genStatfilePath(
    wchar_t *pwszUserProfilePath,
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
        wcslen(pwszUserProfilePath) + 1
    );
    if (errorCode != 0) {
        errorCode += 100;
        goto PCUStat_genStatfilePath_lb_cleanupFailed;
    }

    errorCode = wstrcat_bs(
        resStr,
        PCUSTAT_MCR_STATFILE_NAME,
        lengthOfTwoStrings
    );
    if (errorCode != 0) {
        errorCode += 200;
        goto PCUStat_genStatfilePath_lb_cleanupFailed;
    }

    *pwszResultStr = resStr;
    return 0;


PCUStat_genStatfilePath_lb_cleanupFailed:
    free(resStr);
    *pwszResultStr = NULL;
    return errorCode;
}

int PCUStat_freeStatfilePath(wchar_t **resStr) {
    free(*resStr);
    *resStr = NULL;

    return 0;
}


int PCUStat_savestat(
    wchar_t *pwszUserProfilePath
