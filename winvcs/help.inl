/* WinVCS
 * несколько инлайн функций для вывода текста
 */

#if !defined(INCLGUARD_WINVCS_HELP_INL)
#define INCLGUARD_WINVCS_HELP_INL


#include <stdio.h>
#include <wchar.h>
#include "defines.h"
#include "language.h"


static inline void WinVCS_Help_printHelp() {
#if defined(WINVCS_MCR_OS_WINDOWS)
    const wchar_t *strHelpRu = \
L"WinVCS - Windows Version Control System.\n\
Простая система контроля версий для ОС Windows.\n\
Использование:\n\
\t\twinvcs <команда> <флаги>\n\n\
Команды и флаги:\n\
\t\"add\" - команда для добавления определенных файлов в репозиторий\n\
\t\"rm\" - команда для удаления определенных файлов из репозитория\n\
\t\"mv\" - команда для перемещения/переименовывания определенного файла в репозитории\n\
\t\"commit\" - команда для коммита\n\
\t\"status\" - команда для получения статуса файлов\n\
\t\"init <имя>\" - команда для инициализации репозитория в текущей рабочей директории\n\
\t\"deinit <имя>\" - команда для удаления репозитория из текущей рабочей директории (с сохранением всех файлов)\n\
\t\"remote\" - категория команд для работы с удаленным репозиторием\n\
\t\t\"add <имя>\" - команда для добавления удаленного репозитория (пока поддержка только локальных файлов)\n\
\t\"push <имя удаленного репозитория> <имя ветки>\" - команда для отправки всех коммитов в удаленный репозиторий\n\
\t\"pull <имя удаленного репозитория> <имя ветки>\" - команда для получения всех коммитов (которых у тебя нет) из удаленного репозитория\n\
";

    const wchar_t *strHelpEn = \
L"WinVCS - Windows Version Control System.\n\
";


    unsigned int language = WinVCS_Language_get();

    if (language == WINVCS_MCR_LANG_RU) {
        wprintf("%s", strHelpRu);
        return;
    }
    else {
        wprintf("%s", strHelpEn);
        return;
    }
#endif
}


#endif
