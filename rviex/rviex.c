/****************************************************************************************
 * Romsk64's Vi Extended
 *
 * Расширенный Vi, написанный с нуля на C и более ориентированный на мои личные задачи
 *
 ***************************************************************************************/


#if defined(__GNUC__) || defined(__clang__)
    #if defined(__x86_64__)
        #define RVIEXMCR_ARCH_X86_64
    #elif defined(__i386__)
        #define RVIEXMCR_ARCH_X86_32

        #error "Unsupported architecture now!"
    #else
        #error "Unsupported architecture!"
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        #define RVIEXMCR_OS_WINDOWS
    #elif defined(__linux__)
        #define RVIEXMCR_OS_LINUX

        #error "Unsupported system now!"
    #else
        #error "Unsupported system!"
    #endif
#endif


#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#if defined(RVIEXMCR_OS_WINDOWS)
    #include <windows.h>
#endif


int main(int argc, char *argv[]) {
    return 0;
}
