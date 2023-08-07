/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iconsole.hpp
* @创建时间：2022.9.7.18:24
* @创建者：HelloWorld
* -----------------------------------------------------------------------------
* i的控制台类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/exception/error.h>
#include <icore/type/type/type.h>
#include <icore/data/text/istring.h>
#include <icore/math/iVec2.hpp>

#ifdef __WINDOWS__

#include <Windows.h>

#endif

#include <tuple>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(io)
        {
            class IAPI iConsole
                : public basic::iBasic<iConsole>
            {
                using istring = data::text::istring;
                using iEncoding = data::text::iEncoding;
                iObject(iConsole);

            public:

                iConsole();

                ~iConsole();

            public:

                template<class... Args>
                static _iError write(CRef<istring> fmt, CRef<Args>... args)
                {
                    try
                    {
                        istring out = istring::format(fmt, args...);
                        printf("%s", out.cStr());
                    }
                    catch (CRef<std::format_error> fmtErr)
                    {
                        return _iError::make(_iErrorCode::theIllegalFormatString, std::source_location::current(), "",
                            fmtErr.what());
                    }
                    return _iError::noError();
                }

                template<class... Args>
                static _iError writeLine(CRef<istring> fmt, RRef<Args>... args)
                {
                    return write(fmt + "\n", std::forward<Args>(args)...);
                }

                template<class _Ty>
                static _iError writeLine(_Ty data)
                {
                    return write("{}\n", data);
                }

                static _iError writeLine()
                {
                    return write("\n");
                }

                template<class _Ty>
                static _iError write(_Ty data)
                {
                    return write("{}", data);
                }


                template<class... Args>
                static _iError print(CRef<istring> fmt, RRef<Args>... args)
                {
                    return write(fmt, std::forward<Args>(args)...);
                }

                template<class... Args>
                static _iError printl(CRef<istring> fmt, RRef<Args>... args)
                {
                    return writeLine(fmt, std::forward<Args>(args)...);
                }

                template<class... Args>
                static _iError printLine(CRef<istring> fmt, RRef<Args>... args)
                {
                    return writeLine(fmt, std::forward<Args>(args)...);
                }

                template<class... Args>
                static _iError read(Ref<Args>... args)
                {
                    try
                    {
                        (void)std::initializer_list<int>
                        {
                            ([&args]()
                                {
                                    std::cin >> args;
                                    if (std::cin.fail())
                                    {
                                        std::cin.clear();
                                        std::cin.ignore().ignore();
                                        throw _iErrorCode::theIllegalInput;
                                    }
                                }(), 0)...
                        };
                    }
                    catch (Ref<_iErrorCode> errCode)
                    {
                        return _iError::make(errCode, std::source_location::current());
                    }
                    return _iError::noError();
                }

                static _iError readLine(Ref<istring> _istr);

#ifdef __WINDOWS__

                static _iError setTitle(CRef<istring> istr);

#define tagINPUT INPUT

                static void sendKeyInput(const std::wstring wstr);

                static math::iVec2<short> getConsoleCursor();

#endif//^^^^__WINDOWS__^^^^

            private:
            }; //class iConsole
        } //SPACE(console)
    } //SPACE(core)
} //SPACE(i)
