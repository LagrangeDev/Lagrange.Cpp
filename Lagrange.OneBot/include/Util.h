#include "Common.h"
#include <string>
namespace UtilCharset
{
    std::string Utf16ToUtf8(const std::wstring &utf16);
    std::wstring Utf8ToUtf16(const std::string &utf8);
    std::string UtilCharset::AnsiToUtf8(const std::string &ansi);
    std::wstring UtilCharset::AnsiToUtf16(const std::string &ansi);
}