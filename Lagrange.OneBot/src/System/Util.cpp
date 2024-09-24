#include "System/Util.h"

// 这是因为Window的编码混乱才实现的

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

std::string UtilBase64::Encode(const std::string &data)
{
    const unsigned char *str = reinterpret_cast<const unsigned char *>(data.c_str());
    const char *base64Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int len = static_cast<int>(data.length());
    int pad = len % 3;
    int base64Len = 4 * ((len + 2) / 3);
    std::string strBase64(base64Len, '\0');
    for (int i = 0, j = 0; i < len; i += 3, j += 4)
    {
        strBase64[j] = base64Table[(str[i] >> 2)];
        if (j + 3 > base64Len) return std::string("");
        strBase64[j + 1] = base64Table[(((str[i] & 0x3) << 4) | (i + 1 < len ? str[i + 1] >> 4 : 0))];
        strBase64[j + 2] = (i + 1 < len) ? base64Table[(((str[i + 1] & 0xf) << 2) | (i + 2 < len ? str[i + 2] >> 6 : 0))] : '=';
        strBase64[j + 3] = (i + 2 < len) ? base64Table[(str[i + 2] & 0x3f)] : '=';
    }
    return strBase64;
}

std::string UtilBase64::Decode(const std::string &data)
{
    const char *base64Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const char base64Pad = '=';

    std::string decoded;
    int len = static_cast<int>(data.length());
    int pad = (data[len - 1] == base64Pad) + (data[len - 2] == base64Pad);
    int decodedLen = (len * 3) / 4 - pad;
    decoded.reserve(decodedLen);

    auto decodeChar = [](char c) -> unsigned char {
        if (c >= 'A' && c <= 'Z') return c - 'A';
        if (c >= 'a' && c <= 'z') return c - 'a' + 26;
        if (c >= '0' && c <= '9') return c - '0' + 52;
        if (c == '+') return 62;
        if (c == '/') return 63;
        return 0;
    };

    for (int i = 0; i < len; i += 4) {
        unsigned char b1 = decodeChar(data[i]);
        unsigned char b2 = decodeChar(data[i + 1]);
        unsigned char b3 = decodeChar(data[i + 2]);
        unsigned char b4 = decodeChar(data[i + 3]);

        decoded.push_back((b1 << 2) | (b2 >> 4));
        if (data[i + 2] != base64Pad) {
            decoded.push_back((b2 << 4) | (b3 >> 2));
        }
        if (data[i + 3] != base64Pad) {
            decoded.push_back((b3 << 6) | b4);
        }
    }

    return decoded;
}