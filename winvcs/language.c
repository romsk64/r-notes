#include "defines.h"
#include "language.h"

#if defined(WINVCS_MCR_OS_WINDOWS)
    #include <windows.h>
#endif


unsigned int WinVCS_Language_get() {
    register unsigned int language = 0;

#if defined(WINVCS_MCR_OS_WINDOWS)
    LANGID langId = GetUserDefaultUILanguage();

    WORD primaryLang = PRIMARYLANGID(langId);
    WORD subLang = SUBLANGID(langId);

    if (primaryLang == LANG_RUSSIAN) {
        language = WINVCS_MCR_LANG_RU;
    }
    else {
        language = WINVCS_MCR_LANG_EN;
    }
#endif

    return language;
}
