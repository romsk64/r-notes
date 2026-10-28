/* Windows Version Control System
 * Система контроля версий для меня
 */

#include <stdio.h>
#include <stdint.h>


int main(int argc, char *argv[]) {
    if (argc == 1) {
        WinVCS_Help_printHelp();

        return 1;
    }

    return 0;
}
