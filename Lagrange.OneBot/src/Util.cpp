#include "Util.h"
#ifdef _WIN_PLATFORM_
#include <Windows.h>
#include <string>
#endif
namespace UtilCharset
{
    std::string Utf16ToUtf8(const std::wstring &utf16)
    {
        int length = WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, NULL, 0, NULL, NULL);
        std::string utf8(length, 0);
        WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, &utf8[0], length, NULL, NULL);
        utf8.pop_back();
        return utf8;
    }
    std::wstring Utf8ToUtf16(const std::string &utf8)
    {
        int length = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
        std::wstring utf16(length, 0);
        MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &utf16[0], length);
        utf16.pop_back();
        return utf16;
    }
}