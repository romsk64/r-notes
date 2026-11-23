#if defined(INCLGUARD_CLIFORCPP_HH)
#define INCLGUARD_CLIFORCPP_HH


#include <string>
// #include <string_view>
// #include <span>
#include <initializer_list>
#include <utility>
#include <vector>
#include <functional>
#include <cstring>
#include <iostream> // временно, потом будет ручная передача файлового потока

#if defined(_WIN32) || defined(_WIN64)
    #define CLI__OS_WINDOWS
    #include <windows.h>
#endif


namespace CLI
{
    enum class LANGS
    {
        BrEn,
        AmEn,
        Ru
    };

    LANGS getOSLanguage()
    {
#ifdef CLI__OS_WINDOWS
        LANGID langId = GetUserDefaultUILanguage();
        // WORD primaryLangId = PRIMARYLANGID(langId);
        // WORD subLangId = SUBLANGID(langId);

        switch (langId)
        {
            case MAKELANGID(LANG_RUSSIAN, SUBLANG_RUSSIAN_RUSSIA):
                return CLI::LANGS::Ru;
            case MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK):
                return CLI::LANGS::BrEn;
            case MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US):
                return CLI::LANGS::AmEn;

            default:
                return CLI::LANGS::BrEn;
        }
#endif
    }


    using DescriptionsItem = std::pair<CLI::LANGS, std::string>;
    using DescriptionsInitList = std::initializer_list<DescriptionsItem>;
    using DescriptionsList = std::vector<DescriptionsItem>;


    struct FLAG
    {
        std::string flagShortName;
        std::string flagName;
        CLI::DescriptionsList descriptionsList;
        std::reference_wrapper<bool> flagVariable;
    };

    class App
    {
    private:
        std::string m_appName;
        std::string m_appDesc;
        std::vector<CLI::LANGS> m_supportedLanguages;

        std::vector<CLI::FLAG> m_flags;

    public:
        App(
            std::string appName,
            std::string appDesc,
            std::initializer_list<CLI::LANGS> supportedLanguages
        ) : m_appName(std::move(appName)),
            m_appDesc(std::move(appDesc)),
            m_supportedLanguages(supportedLanguages)
        {
            m_flags.reserve(32);
        }

        CLI::App &addFlag(
            std::string flagShortName,
            std::string flagName,
            CLI::DescriptionsList descriptionsList,
            bool &flagVariable,
            unsigned int &error
        )
        {
            if (flagShortName == "-h" || flagName == "--help")
            {
                error = 1;
                return *this;
            }

            CLI::FLAG tmpflag = {
                std::move(flagShortName),
                std::move(flagName),
                std::move(descriptionsList),
                flagVariable
            };

            error = 0;
            this->m_flags.push_back(std::move(tmpflag));
            return *this;
        }

        int parse(
            const int argc,
            const char *const *argv
        )
        {
            if (!argv)
                return 1;

            bool found;

            for (int i = 1; i < argc; i++)
            {
                found = false;

                if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0))
                {
                    std::cout << this->m_appName << "\n"
                        << this->m_appDesc << "\n" << std::endl;

                    std::cout << "Flags:" << std::endl;
                    for (const FLAG &flag :
                    return -1;
                }

                for (const FLAG &flag : this->m_flags)
                {
                    if ((flag.flagShortName == argv[i]) || (flag.flagName == argv[i]))
                    {
                        flag.flagVariable.get() = true;
                        found = true;
                        break;
                    }
                }
                // дописать

            }

            return 0;
        }
    };
}


#endif
