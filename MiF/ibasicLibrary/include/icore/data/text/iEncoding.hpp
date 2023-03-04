/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iEncoding.hpp
* @创建时间：2022.12.31.23:08
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
*
*
*
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
//#define _USE_WINDOWS_H__

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasic.hpp>
#include <string>


SPACE(i)
{
    SPACE(core)
    {
        SPACE(data)
        {
            SPACE(text)
            {

                class iEncoding :
                    public basic::iBasic<iEncoding>
                {
                    iObject(iEncoding)
                public:

                    iEncoding()
                    { }

                    ~iEncoding()
                    { }

                public:

                    static std::wstring toWideChar(std::uint32_t code_page, CRef<std::string> src_str)
                    {
#ifdef __WINDOWS__
                        if (src_str.empty())
                        {
                            return L"";
                        }
                        auto len = MultiByteToWideChar(code_page, 0, src_str.c_str(), -1, nullptr, 0);
                        if (!len)
                        {
                            return L"";
                        }
                        auto wstr_c = new wchar_t[len + 1];
                        if (!wstr_c)
                        {
                            return L"";
                        }
                        memset(wstr_c, 0, static_cast<size_t>(len) + 1);
                        MultiByteToWideChar(code_page, 0, src_str.c_str(), -1, wstr_c, len);
                        std::wstring wstr(wstr_c);
                        delete[] wstr_c;
                        return wstr;
#elif defined(__LINUX__)
                        // todo 2023-1-3 Linux下待实现
                        return L"";
#endif
                    }

                    /****
                    * @author Lovelylavender4
                    * @include <string>,<stringapiset.h>,imacrofamily.h
                    ****/
                    static std::string fromWideChar(std::uint32_t code_page, CRef<std::wstring> src_wstr)
                    {
                        if (src_wstr.empty())
                        {
                            return "";
                        }
#ifdef __WINDOWS__
                        auto len = WideCharToMultiByte(code_page, 0, src_wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
                        if (!len)
                        {
                            return "";
                        }
                        auto str_c = new char[len + 1];
                        if (!str_c)
                        {
                            return "";
                        }
                        memset(str_c, 0, static_cast<size_t>(len) + 1);
                        WideCharToMultiByte(code_page, 0, src_wstr.c_str(), -1, str_c, len, nullptr, nullptr);
                        std::string str(str_c);
                        delete[] str_c;
                        return str;
#elif defined(__LINUX__)
                        // todo 2023-1-3 Linux下待实现
                        return "";
#endif
                    }

                    static bool isWideCharHex(wchar_t wch)
                    {
                        return (wch >= L'0' && wch <= L'9') || (wch >= L'a' && wch <= L'f') || (wch >= L'A' && wch <= L'F');
                    }


                    static bool isHexChar(char c)
                    {
                        return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
                    }


                    static std::uint8_t wideChar2hex(wchar_t wch)
                    {
                        if (wch >= L'0' && wch <= L'9')
                        {
                            return wch - L'0';
                        }
                        else if (wch >= L'a' && wch <= L'f')
                        {
                            return wch - L'a' + 10;
                        }
                        else
                        {// wch >= L'A' && wch <= L'F'
                            return wch - L'A' + 10;
                        }
                    }

                    static char hex2char(uint8_t hex)
                    {
                        if (hex <= 9)
                        {
                            return '0' + hex;
                        }
                        else
                        { // hex >= 10 && hex <= 15
                            return 'a' + hex - 10;
                        }
                    }

                    static std::string wideChar2UCS2(wchar_t wch)
                    {
                        auto wch_value = static_cast<uint16_t>(wch);
                        std::string ucs2;
                        ucs2.reserve(6);
                        ucs2 += "\\u";
                        ucs2 += hex2char(wch_value >> 12);
                        ucs2 += hex2char((wch_value >> 8) & 0xf);
                        ucs2 += hex2char((wch_value >> 4) & 0xf);
                        ucs2 += hex2char(wch_value & 0xf);
                        return ucs2;
                    }

                    static char hex2wideChar(uint8_t hex)
                    {
                        if (hex <= 9)
                        {
                            return L'0' + hex;
                        }
                        else
                        {
                            return L'a' + hex - 10;
                        }
                    }

                    static std::wstring wideChar2wideCharUCS2(wchar_t wch)
                    {
                        auto wch_value = static_cast<uint16_t>(wch);
                        std::wstring ucs2;
                        ucs2.reserve(6);
                        ucs2 += L"\\u";
                        ucs2 += hex2wideChar(wch_value >> 12);
                        ucs2 += hex2wideChar((wch_value >> 8) & 0xf);
                        ucs2 += hex2wideChar((wch_value >> 4) & 0xf);
                        ucs2 += hex2wideChar(wch_value & 0xf);
                        return ucs2;
                    }

                    /****
                    * @author Lovelylavender4
                    * @since ?
                    * @brief 将一个UTF8编码的字符串转换为一个宽字符串
                    *
                    * @retval 转换后的宽字符串
                    ****/
                    static std::wstring UTF82wideChar(CRef<std::string> utf8)
                    {
#ifdef __WINDOWS__
                        return toWideChar(CP_UTF8, utf8);
#elif defined(__LINUX__)
                        // todo 2023-1-3 Linux下待实现
                        return L"";
#endif
                    }

                    /****
                    * @author Lovelylavender4
                    * @since ?
                    * @brief 将宽字符串转换为UTF8编码的字符串
                    *
                    * @retval 转换后的UTF8编码的字符串

                    ****/
                    static std::string wideChar2UTF8(CRef<std::wstring> wstr)
                    {
#ifdef __WINDOWS__
                        return fromWideChar(CP_UTF8, wstr);
#elif defined(__LINUX__)
                        // todo 2023-1-3 Linux下待实现
                        return "";
#endif
                    }

                    /****
                    * @author Lovelylavender4
                    * @since ?
                    * @brief 将ANSI编码的字符串转换为宽字符串
                    *
                    * @param ansi 要转换的ANSI编码的字符串
                    * @retval 转换后的宽字符串

                    ****/
                    static std::wstring ANSI2wideChar(CRef<std::string> ansi)
                    {
#ifdef __WINDOWS__
                        return toWideChar(CP_ACP, ansi);
#elif defined(__LINUX__)
                        // todo 2023-1-3 Linux下待实现
                        return L"";
#endif
                    }

                    /****
                    * @author Lovelylavender4
                    * @since ?
                    * @brief 将宽字符串转换成ANSI编码的字符串
                    *
                    * @param wstr 要转换为编码的宽字符串
                    ****/
                    static std::string wideChar2ANSI(CRef<std::wstring> wstr)
                    {
#ifdef __WINDOWS__
                        return fromWideChar(CP_ACP, wstr);
#elif defined(__LINUX__)
                        // todo 2023-1-3 Linux下待实现
                        return "";
#endif
                    }

                    /****
                    * @author Lovelylavender4
                    * @since ?
                    * @brief 将ANSI编码的混合UCS2编码的字符串转换为宽字符串
                    *
                    * @param ansi_with_ucs2 要转换的ANSI编码的混合UCS2编码的字符串
                    * @param not_unescape_wide_chars 广义的字符集，没有反转的转义
                    * @retval 转换后的宽字符串
                    ****/
                    static std::wstring ANSIWithUCS22WideChar(CRef<std::string> ansi_with_ucs2, CRef<std::wstring> not_unescape_wide_chars)
                    {
                        return unescapeWideChar(ANSI2wideChar(ansi_with_ucs2), not_unescape_wide_chars);
                    }

                    static std::string wideChar2ANSIWithUCS2(CRef<std::wstring> wstr, CRef<std::wstring> force_escape_wide_chars)
                    {
                        if (wstr.empty())
                        {
                            return "";
                        }
#ifdef __WINDOWS__
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
                            len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, &need_escape);
                            if (!len)
                            {
                                return "";
                            }
                        }
                        if (!need_escape)
                        {
                            auto ansi_c = new char[len + 1];
                            if (!ansi_c)
                            {
                                return "";
                            }
                            memset(ansi_c, 0, len + 1);
                            WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, ansi_c, len, nullptr, nullptr);
                            std::string ansi(ansi_c);
                            delete[] ansi_c;
                            return ansi;
                        }
                        else
                        {
                            auto wstr_c_tmp = new wchar_t[2];
                            if (!wstr_c_tmp)
                            {
                                return "";
                            }
                            wstr_c_tmp[1] = L'\0';
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
                                        need_escape = 0;
                                        wstr_c_tmp[0] = it;
                                        auto len = WideCharToMultiByte(CP_ACP, 0, wstr_c_tmp, -1, nullptr, 0, nullptr, &need_escape);
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
#elif defined(__LINUX__)
                        // todo 2023-1-3 Linux下待实现
                        return "";
#endif
                    }

                    static std::wstring escapeWideChar(CRef<std::wstring> wstr, CRef<std::wstring> escape_wide_chars)
                    {
                        if (wstr.empty())
                        {
                            return L"";
                        }
                        if (escape_wide_chars.empty())
                        {
                            return wstr;
                        }
                        std::wstring wstr_with_ucs2;
                        for (wchar_t wch : wstr)
                        {
                            if (escape_wide_chars.find(wch) == std::wstring::npos)
                            {
                                wstr_with_ucs2 += wch;
                            }
                            else
                            {
                                wstr_with_ucs2 += wideChar2wideCharUCS2(wch);
                            }
                        }
                        return wstr_with_ucs2;
                    }

                    static std::wstring unescapeWideChar(CRef<std::wstring> wstr_with_ucs2, CRef<std::wstring> not_unescape_wide_chars)
                    {
                        if (wstr_with_ucs2.empty())
                        {
                            return L"";
                        }
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
                                                    auto wch = UCS22WideChar(ucs2_tmp);
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
                                if (it == cend)
                                {
                                    break;
                                }
                            }
                            wstr += *it;
                        }
                        return wstr;
                    }

                    static std::string escapeUTF8(CRef<std::string> utf8, CRef<std::string> escape_utf8_chars)
                    {
                        return wideChar2UTF8(escapeWideChar(UTF82wideChar(utf8), UTF82wideChar(escape_utf8_chars)));
                    }

                    static std::string unescapeUTF8(CRef<std::string> utf8_with_ucs2, CRef<std::string> not_unescape_utf8_chars)
                    {
                        return wideChar2UTF8(unescapeWideChar(UTF82wideChar(utf8_with_ucs2), UTF82wideChar(not_unescape_utf8_chars)));
                    }

                    static wchar_t UCS22WideChar(CRef<std::wstring> ucs2)
                    {
                        auto it = ucs2.cbegin();
                        it += 2; // L'\\u'
                        uint16_t wch_value = 0;
                        for (auto i = 0; i < 4; i++)
                        {
                            wch_value <<= 4;
                            wch_value += wideChar2hex(*it);
                            it++;
                        }
                        auto wch = static_cast<wchar_t>(wch_value);
                        return wch;
                    }

                    static std::string UTF82ANSI(CRef<std::string> utf8)
                    {
                        return wideChar2ANSI(UTF82wideChar(utf8));
                    }

                    static std::string ANSI2UTF8(CRef<std::string> utf8)
                    {
                        return wideChar2UTF8(ANSI2wideChar(utf8));
                    }

                private:
                };

            }//SPACE(text)
        }//SPACE(data)
    }//SPACE(core)
}//SPACE(i)

SPACE(nlohmann)
{

}

