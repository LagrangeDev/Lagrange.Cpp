#include "Util.h"

//这是因为Window的编码混乱才实现的

#ifdef _WIN_PLATFORM_
std::string UtilCharset::Utf16ToUtf8(const std::wstring &utf16)
{
    int length = WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, NULL, 0, NULL, NULL);
    std::string utf8(length, 0);
    WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, &utf8[0], length, NULL, NULL);
    utf8.pop_back();
    return utf8;
}

std::wstring UtilCharset::Utf8ToUtf16(const std::string &utf8)
{
    int length = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
    std::wstring utf16(length, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &utf16[0], length);
    utf16.pop_back();
    return utf16;
}

std::string UtilCharset::AnsiToUtf8(const std::string &ansi)
{
    std::wstring utf16 = AnsiToUtf16(ansi);
    return Utf16ToUtf8(utf16);
}

std::wstring UtilCharset::AnsiToUtf16(const std::string &ansi)
{
    int length = MultiByteToWideChar(CP_ACP, 0, ansi.c_str(), -1, NULL, 0);
    std::wstring utf16(length, 0);
    MultiByteToWideChar(CP_ACP, 0, ansi.c_str(), -1, &utf16[0], length);
    utf16.pop_back();
    return utf16;
}

#endif

// Linux下一般不调用这些函数
#ifdef _LINUX_PLATFORM_

std::string UtilCharset::Utf16ToUtf8(const std::wstring &utf16)
{
    std::string utf8;
    for (wchar_t wc : utf16)
    {
        if (wc <= 0x7f)
            utf8.push_back(static_cast<char>(wc));
        else if (wc <= 0x7ff)
        {
            utf8.push_back(static_cast<char>(0xc0 | ((wc >> 6) & 0x1f)));
            utf8.push_back(static_cast<char>(0x80 | (wc & 0x3f)));
        }
        else if (wc <= 0xffff)
        {
            utf8.push_back(static_cast<char>(0xe0 | ((wc >> 12) & 0x0f)));
            utf8.push_back(static_cast<char>(0x80 | ((wc >> 6) & 0x3f)));
            utf8.push_back(static_cast<char>(0x80 | (wc & 0x3f)));
        }
        else
        {
            utf8.push_back(static_cast<char>(0xf0 | ((wc >> 18) & 0x07)));
            utf8.push_back(static_cast<char>(0x80 | ((wc >> 12) & 0x3f)));
            utf8.push_back(static_cast<char>(0x80 | ((wc >> 6) & 0x3f)));
            utf8.push_back(static_cast<char>(0x80 | (wc & 0x3f)));
        }
    }
    return utf8;
}

std::wstring UtilCharset::Utf8ToUtf16(const std::string &utf8)
{
    std::wstring utf16;
    for (size_t i = 0; i < utf8.size();)
    {
        wchar_t wc = 0;
        unsigned char c = utf8[i];
        if (c <= 0x7f)
        {
            wc = c;
            i += 1;
        }
        else if (c <= 0xdf)
        {
            wc = (c & 0x1f) << 6;
            wc |= (utf8[i + 1] & 0x3f);
            i += 2;
        }
        else if (c <= 0xef)
        {
            wc = (c & 0x0f) << 12;
            wc |= (utf8[i + 1] & 0x3f) << 6;
            wc |= (utf8[i + 2] & 0x3f);
            i += 3;
        }
        else
        {
            wc = (c & 0x07) << 18;
            wc |= (utf8[i + 1] & 0x3f) << 12;
            wc |= (utf8[i + 2] & 0x3f) << 6;
            wc |= (utf8[i + 3] & 0x3f);
            i += 4;
        }
        utf16.push_back(wc);
    }
    return utf16;
}

std::string UtilCharset::AnsiToUtf8(const std::string &ansi)
{
    return ansi; // Assuming ANSI and UTF-8 are the same on Linux
}

std::wstring UtilCharset::AnsiToUtf16(const std::string &ansi)
{
    return Utf8ToUtf16(ansi); // Assuming ANSI and UTF-8 are the same on Linux
}

#endif