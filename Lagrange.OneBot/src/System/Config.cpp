#include "./System/Config.h"

bool OnebotConfig::readConfig(const std::string &path)
{
    // 通过utf8 path + cpp标准库读取json并使用meojson库解析文件
    std::ifstream configFile(path);
    if (!configFile.is_open())
    {
        return false;
    }
    std::stringstream buffer;
    buffer << configFile.rdbuf();
    std::string configContent = buffer.str();
    configFile.close();
    auto jsondata = json::parse5(configContent);
    return true;
}

bool OnebotConfig::writeConfig(const std::string &path)
{
    return false;
}

bool OnebotConfig::getValue(const std::string &key)
{
    return false;
}
