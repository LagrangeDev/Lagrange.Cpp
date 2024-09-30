#pragma once
#include "Common.h"
#include <iostream>
#include <map>
#include <string>
namespace BaseCommand
{
    // 声明变量
    extern std::map<std::string, std::string> commandList;
    void parseCommand(int argc, char *argv[]);
}
