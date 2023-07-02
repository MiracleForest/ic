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

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasic.h>
#include <string>
#ifdef __WINDOWS__
#include <windows.h>
#include <stringapiset.h>
#endif


SPACE(i)
{
    SPACE(core)
    {
        SPACE(data)
        {
            SPACE(text)
            {
                class istring;

                class IAPI iEncoding :
                    public basic::iBasic<iEncoding>
                {
                    iObject(iEncoding)
                public:

                    iEncoding()
                    { }

                    ~iEncoding()
                    { }

                public:

                    static std::wstring toWideChar(std::uint32_t code_page, CRef<istring> src_str);

                    /****
                    * @author Lovelylavender4
                    * @include <string>,<stringapiset.h>,imacrofamily.h
                    ****/
                    static std::string fromWideChar(std::uint32_t code_page, CRef<std::wstring> src_wstr);

                    static bool isWideCharHex(wchar_t wch);


                    static bool isHexChar(char c);


                    static std::uint8_t wideChar2hex(wchar_t wch);

                    static char hex2char(uint8_t hex);

                    static std::string wideChar2UCS2(wchar_t wch);

                    static char hex2wideChar(uint8_t hex);

                    static std::wstring wideChar2wideCharUCS2(wchar_t wch);

                    /****
                    * @author Lovelylavender4
                    * @since 2023.6.6.12:58
                    * @brief 将一个UTF8编码的字符串转换为一个宽字符串
                    *
                    * @retval 转换后的宽字符串
                    ****/
                    static std::wstring UTF82wideChar(CRef<istring> utf8);

                    /****
                    * @author Lovelylavender4
                    * @since 2023.6.6.12:58
                    * @brief 将宽字符串转换为UTF8编码的字符串
                    *
                    * @retval 转换后的UTF8编码的字符串

                    ****/
                    static std::string wideChar2UTF8(CRef<std::wstring> wstr);

                    /****
                    * @author Lovelylavender4
                    * @since 2023.6.6.12:58
                    * @brief 将ANSI编码的字符串转换为宽字符串
                    *
                    * @param ansi 要转换的ANSI编码的字符串
                    * @retval 转换后的宽字符串

                    ****/
                    static std::wstring ANSI2wideChar(CRef<istring> ansi);

                    /****
                    * @author Lovelylavender4
                    * @since 2023.6.6.12:58
                    * @brief 将宽字符串转换成ANSI编码的字符串
                    *
                    * @param wstr 要转换为编码的宽字符串
                    ****/
                    static std::string wideChar2ANSI(CRef<std::wstring> wstr);

                    /****
                    * @author Lovelylavender4
                    * @since 2023.6.6.12:58
                    * @brief 将ANSI编码的混合UCS2编码的字符串转换为宽字符串
                    *
                    * @param ansi_with_ucs2 要转换的ANSI编码的混合UCS2编码的字符串
                    * @param not_unescape_wide_chars 广义的字符集，没有反转的转义
                    * @retval 转换后的宽字符串
                    ****/
                    static std::wstring ANSIWithUCS22WideChar(CRef<istring> ansi_with_ucs2, CRef<std::wstring> not_unescape_wide_chars);

                    static std::string wideChar2ANSIWithUCS2(CRef<std::wstring> wstr, CRef<std::wstring> force_escape_wide_chars);

                    static std::wstring escapeWideChar(CRef<std::wstring> wstr, CRef<std::wstring> escape_wide_chars);

                    static std::wstring unescapeWideChar(CRef<std::wstring> wstr_with_ucs2, CRef<std::wstring> not_unescape_wide_chars);

                    static std::string escapeUTF8(CRef<istring> utf8, CRef<istring> escape_utf8_chars);

                    static std::string unescapeUTF8(CRef<istring> utf8_with_ucs2, CRef<istring> not_unescape_utf8_chars);

                    static wchar_t UCS22WideChar(CRef<std::wstring> ucs2);

                    static std::string UTF82ANSI(CRef<istring> utf8);

                    static std::string ANSI2UTF8(CRef<istring> ansi);

                private:
                };

            }//SPACE(text)
        }//SPACE(data)
    }//SPACE(core)
}//SPACE(i)

SPACE(nlohmann)
{

}

