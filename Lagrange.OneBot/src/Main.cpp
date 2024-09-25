#include "System/Util.h"
#include "System/Command.h"
int startApplication(int argc, char *argv[])
{
    system("chcp 65001 & cls");
    BaseCommand::parseCommand(argc, argv);
    for (auto &item : BaseCommand::commandList)
    {
        std::cout << item.first << " : " << item.second << std::endl;
    }
    return 0;
}

#ifdef _WIN_PLATFORM_
int main(int argc, char *argv[])
{
    // main入口需要处理Ansi-->Utf8的转换 WinMain直接使用UTF16-->UTF8
    char **argvUtf8 = new char *[argc];
    for (int i = 0; i < argc; ++i)
    {
        std::string utf8Str = UtilCharset::AnsiToUtf8(argv[i]);
        argvUtf8[i] = new char[utf8Str.size() + 1];
        strcpy_s(argvUtf8[i], utf8Str.size() + 1, utf8Str.c_str());
    }
    int result = startApplication(argc, argvUtf8);
    for (int i = 0; i < argc; ++i)
    {
        delete[] argvUtf8[i];
    }
    delete[] argvUtf8;
    return result;
}
#endif

#ifdef _LINUX_PLATFORM_
int main(int argc, char *argv[])
{
    return startApplication(argc, argv);
}
#endif

#ifdef _MAC_PLATFORM_
int main(int argc, char *argv[])
{
    return startApplication(argc, argv);
}
#endif