#include "include/family/iicfamily.h"
#include <string>
#include <windows.h>

std::wstring toWideChar(std::uint32_t code_page, CRef<std::string> src_str);
std::string  fromWideChar(std::uint32_t code_page, CRef<std::wstring> src_wstr);
bool         isWideCharHex(wchar_t wch);
bool         isHexChar(char c);
std::uint8_t wideChar2hex(wchar_t wch);
char         hex2char(uint8_t hex);
std::string  wideChar2UCS2(wchar_t wch);
char         hex2wideChar(uint8_t hex);
std::wstring wideChar2wideCharUCS2(wchar_t wch);
std::wstring UTF82wideChar(CRef<std::string> utf8);
std::string  wideChar2UTF8(CRef<std::wstring> wstr);
std::wstring ANSI2wideChar(CRef<std::string> ansi);
std::string  wideChar2ANSI(CRef<std::wstring> wstr);
std::wstring ANSIWithUCS22WideChar(
    CRef<std::string>  ansi_with_ucs2,
    CRef<std::wstring> not_unescape_wide_chars
);
std::string  wideChar2ANSIWithUCS2(CRef<std::wstring> wstr, CRef<std::wstring> force_escape_wide_chars);
std::wstring escapeWideChar(CRef<std::wstring> wstr, CRef<std::wstring> escape_wide_chars);
std::wstring unescapeWideChar(CRef<std::wstring> wstr_with_ucs2, CRef<std::wstring> not_unescape_wide_chars);
std::string  escapeUTF8(CRef<std::string> utf8, CRef<std::string> escape_utf8_chars);
std::string  unescapeUTF8(CRef<std::string> utf8_with_ucs2, CRef<std::string> not_unescape_utf8_chars);
wchar_t      UCS22WideChar(CRef<std::wstring> ucs2);
std::string  UTF82ANSI(CRef<std::string> utf8);
std::string  ANSI2UTF8(CRef<std::string> ansi);


std::wstring toWideChar(std::uint32_t code_page, CRef<std::string> src_str)
{
    if (src_str.empty()) { return L""; }
    auto len = MultiByteToWideChar(code_page, 0, src_str.c_str(), -1, nullptr, 0);
    if (!len) { return L""; }
    auto wstr_c = new wchar_t[len + 1];
    if (!wstr_c) { return L""; }
    memset(wstr_c, 0, static_cast<size_t>(len) + 1);
    MultiByteToWideChar(code_page, 0, src_str.c_str(), -1, wstr_c, len);
    std::wstring wstr(wstr_c);
    delete[] wstr_c;
    return wstr;
}

std::string fromWideChar(std::uint32_t code_page, CRef<std::wstring> src_wstr)
{
    if (src_wstr.empty()) { return ""; }
    auto len = WideCharToMultiByte(code_page, 0, src_wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (!len) { return ""; }
    auto str_c = new char[len + 1];
    if (!str_c) { return ""; }
    memset(str_c, 0, static_cast<size_t>(len) + 1);
    WideCharToMultiByte(code_page, 0, src_wstr.c_str(), -1, str_c, len, nullptr, nullptr);
    std::string str(str_c);
    delete[] str_c;
    return str;
}

bool isWideCharHex(wchar_t wch)
{
    return (wch >= L'0' && wch <= L'9') || (wch >= L'a' && wch <= L'f') || (wch >= L'A' && wch <= L'F');
}

bool isHexChar(char c) { return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'); }

std::uint8_t wideChar2hex(wchar_t wch)
{
    if (wch >= L'0' && wch <= L'9') { return wch - L'0'; }
    else if (wch >= L'a' && wch <= L'f') { return wch - L'a' + 10; }
    else
    { // wch >= L'A' && wch <= L'F'
        return wch - L'A' + 10;
    }
}

char hex2char(uint8_t hex)
{
    if (hex <= 9) { return '0' + hex; }
    else
    { // hex >= 10 && hex <= 15
        return 'a' + hex - 10;
    }
}

std::string wideChar2UCS2(wchar_t wch)
{
    auto        wch_value = static_cast<uint16_t>(wch);
    std::string ucs2;
    ucs2.reserve(6);
    ucs2 += "\\u";
    ucs2 += hex2char(wch_value >> 12);
    ucs2 += hex2char((wch_value >> 8) & 0xf);
    ucs2 += hex2char((wch_value >> 4) & 0xf);
    ucs2 += hex2char(wch_value & 0xf);
    return ucs2;
}

char hex2wideChar(uint8_t hex)
{
    if (hex <= 9) { return L'0' + hex; }
    else { return L'a' + hex - 10; }
}

std::wstring wideChar2wideCharUCS2(wchar_t wch)
{
    auto         wch_value = static_cast<uint16_t>(wch);
    std::wstring ucs2;
    ucs2.reserve(6);
    ucs2 += L"\\u";
    ucs2 += hex2wideChar(wch_value >> 12);
    ucs2 += hex2wideChar((wch_value >> 8) & 0xf);
    ucs2 += hex2wideChar((wch_value >> 4) & 0xf);
    ucs2 += hex2wideChar(wch_value & 0xf);
    return ucs2;
}

std::wstring UTF82wideChar(CRef<std::string> utf8) { return toWideChar(CP_UTF8, utf8); }

std::string wideChar2UTF8(CRef<std::wstring> wstr) { return fromWideChar(CP_UTF8, wstr); }

std::wstring ANSI2wideChar(CRef<std::string> ansi) { return toWideChar(CP_ACP, ansi); }

std::string wideChar2ANSI(CRef<std::wstring> wstr) { return fromWideChar(CP_ACP, wstr); }

std::wstring ANSIWithUCS22WideChar(
    CRef<std::string>  ansi_with_ucs2,
    CRef<std::wstring> not_unescape_wide_chars
)
{
    return unescapeWideChar(ANSI2wideChar(ansi_with_ucs2), not_unescape_wide_chars);
}

std::string wideChar2ANSIWithUCS2(CRef<std::wstring> wstr, CRef<std::wstring> force_escape_wide_chars)
{
    if (wstr.empty()) { return ""; }
    int need_escape = 0;
    if (!force_escape_wide_chars.empty())
    {
        for (auto wch : wstr)
        {
            if (force_escape_wide_chars.find(wch) != std::wstring::npos)
            {
                need_escape = 1;
                break;
            }
        }
    }
    int len;
    if (need_escape == 0)
    {
        need_escape = 0;
        len         = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, &need_escape);
        if (!len) { return ""; }
    }
    if (!need_escape)
    {
        auto ansi_c = new char[len + 1];
        if (!ansi_c) { return ""; }
        memset(ansi_c, 0, len + 1);
        WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, ansi_c, len, nullptr, nullptr);
        std::string ansi(ansi_c);
        delete[] ansi_c;
        return ansi;
    }
    else
    {
        auto wstr_c_tmp = new wchar_t[2];
        if (!wstr_c_tmp) { return ""; }
        wstr_c_tmp[1]   = L'\0';
        auto ansi_c_tmp = new char[8];
        if (!ansi_c_tmp)
        {
            delete[] wstr_c_tmp;
            return "";
        }
        std::string ansi_with_ucs2;
        for (auto it : wstr)
        {
            if (force_escape_wide_chars.find(it) == std::wstring::npos)
            {
                if (static_cast<uint16_t>(it) <= 0x7f)
                {
                    ansi_with_ucs2 += static_cast<char>(it);
                    continue;
                }
                else if ((uint16_t)(it) >> 11 != 0b11011)
                {
                    need_escape   = 0;
                    wstr_c_tmp[0] = it;
                    auto len =
                        WideCharToMultiByte(CP_ACP, 0, wstr_c_tmp, -1, nullptr, 0, nullptr, &need_escape);
                    if (!len)
                    {
                        delete[] wstr_c_tmp;
                        delete[] ansi_c_tmp;
                        return "";
                    }
                    if (!need_escape)
                    {
                        memset(ansi_c_tmp, 0, len + 1);
                        WideCharToMultiByte(CP_ACP, 0, wstr_c_tmp, -1, ansi_c_tmp, len, nullptr, nullptr);
                        ansi_with_ucs2 += ansi_c_tmp;
                        continue;
                    }
                }
            }
            ansi_with_ucs2 += wideChar2UCS2(it);
        }
        delete[] wstr_c_tmp;
        delete[] ansi_c_tmp;
        return ansi_with_ucs2;
    }
}

std::wstring escapeWideChar(CRef<std::wstring> wstr, CRef<std::wstring> escape_wide_chars)
{
    if (wstr.empty()) { return L""; }
    if (escape_wide_chars.empty()) { return wstr; }
    std::wstring wstr_with_ucs2;
    for (wchar_t wch : wstr)
    {
        if (escape_wide_chars.find(wch) == std::wstring::npos) { wstr_with_ucs2 += wch; }
        else { wstr_with_ucs2 += wideChar2wideCharUCS2(wch); }
    }
    return wstr_with_ucs2;
}

std::wstring unescapeWideChar(CRef<std::wstring> wstr_with_ucs2, CRef<std::wstring> not_unescape_wide_chars)
{
    if (wstr_with_ucs2.empty()) { return L""; }
    std::wstring wstr;
    wstr.reserve(wstr_with_ucs2.size());
    std::wstring ucs2_tmp;
    ucs2_tmp.reserve(6);
    for (auto it = wstr_with_ucs2.cbegin(), cend = wstr_with_ucs2.cend(); it != cend; it++)
    {
        if (*it == L'\\')
        {
            ucs2_tmp = L"\\";
            it++;
            if (it != cend && *it == L'u')
            {
                ucs2_tmp += L'u';
                it++;
                if (it != cend && isWideCharHex(*it))
                {
                    ucs2_tmp += *it;
                    it++;
                    if (it != cend && isWideCharHex(*it))
                    {
                        ucs2_tmp += *it;
                        it++;
                        if (it != cend && isWideCharHex(*it))
                        {
                            ucs2_tmp += *it;
                            it++;
                            if (it != cend && isWideCharHex(*it))
                            {
                                ucs2_tmp += *it;
                                auto wch  = UCS22WideChar(ucs2_tmp);
                                if (not_unescape_wide_chars.find(wch) == std::wstring::npos)
                                {
                                    wstr += wch;
                                    continue;
                                }
                            }
                        }
                    }
                }
            }
            wstr += ucs2_tmp;
            if (it == cend) { break; }
        }
        wstr += *it;
    }
    return wstr;
}

std::string escapeUTF8(CRef<std::string> utf8, CRef<std::string> escape_utf8_chars)
{
    return wideChar2UTF8(escapeWideChar(UTF82wideChar(utf8), UTF82wideChar(escape_utf8_chars)));
}

std::string unescapeUTF8(CRef<std::string> utf8_with_ucs2, CRef<std::string> not_unescape_utf8_chars)
{
    return wideChar2UTF8(
        unescapeWideChar(UTF82wideChar(utf8_with_ucs2), UTF82wideChar(not_unescape_utf8_chars))
    );
}

wchar_t UCS22WideChar(CRef<std::wstring> ucs2)
{
    auto it             = ucs2.cbegin();
    it                 += 2; // L'\\u'
    uint16_t wch_value  = 0;
    for (auto i = 0; i < 4; i++)
    {
        wch_value <<= 4;
        wch_value  += wideChar2hex(*it);
        it++;
    }
    auto wch = static_cast<wchar_t>(wch_value);
    return wch;
}

std::string UTF82ANSI(CRef<std::string> utf8) { return wideChar2ANSI(UTF82wideChar(utf8)); }

std::string ANSI2UTF8(CRef<std::string> ansi) { return wideChar2UTF8(ANSI2wideChar(ansi)); }
