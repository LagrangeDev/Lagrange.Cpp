#include "System/Command.h"

std::map<std::string, std::string> BaseCommand::commandList = {};

void BaseCommand::parseCommand(int argc, char *argv[])
{
    commandList["Module"] = argv[0];
    for (size_t i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        bool isParam = arg.starts_with("--") || arg.starts_with("-");
        if (arg.starts_with("--"))
        {
            arg = arg.substr(2);
        }
        else if (arg.starts_with("-"))
        {
            arg = arg.substr(1);
        }
        bool hasValue = arg.find('=') != std::string::npos;
        std::string key = "";
        std::string value = "";
        if (hasValue)
        {
            key = arg.substr(0, arg.find('='));
            value = arg.substr(arg.find('=') + 1);
        }
        else
        {
            key = arg;
        }
        commandList[key] = value;
    }
    return;
}
