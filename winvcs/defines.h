/* WinVCS
 * макросы
 */

#if !defined(INCLGUARD_WINVCS_DEFINES_H)
#define INCLGUARD_WINVCS_DEFINES_H


#if defined(__GNUC__) || defined(__clang__)
    #if defined(_WIN32) || defined(_WIN64)
        #define WINVCS_MCR_OS_WINDOWS
    #elif defined(__linux__)
        #define WINVCS_MCR_OS_LINUX

        #error "Not realized now!"
    #else
        #error "Unknown system!"
    #endif
#endif


#endif
