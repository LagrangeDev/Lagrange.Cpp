#include "Common.h"
#include "meojson/include/json5.hpp"
#include <fstream>
#include <sstream>
#include <optional>
class OnebotConfig
{
    static bool readConfig(const std::string &path);
    static bool writeConfig(const std::string &path);
    static bool getValue(const std::string &key);
};