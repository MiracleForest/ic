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
#include <icore/type/type/type.hpp>
#include <icore/data/text/istring.hpp>
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
            class iConsole
                : public basic::iBasic<iConsole>
            {
                using istring = data::text::istring;
                using iEncoding = data::text::iEncoding;
                iObject(iConsole);

            public:
                iConsole() { }

                ~iConsole() { }

            public:
                template <class... Args>
                static _iError write(CRef<istring> fmt, CRef<Args>... args)
                {
                    try
                    {
                        istring out = istring::format(fmt, args...);

                        printf(out.cStr());
                    }
                    catch (CRef<std::format_error> fmtErr)
                    {
                        return _iError::make(_iErrorCode::theIllegalFormatString, std::source_location::current(), "",
                                             fmtErr.what());
                    }

                    return _iError::noError();
                }

                template <class... Args>
                static _iError writeLine(CRef<istring> fmt, RRef<Args>... args)
                {
                    return write(fmt + "\n", std::forward<Args>(args)...);
                }

                template <class _Ty>
                static _iError writeLine(_Ty data)
                {
                    return write("{}\n", data);
                }

                template <class _Ty>
                static _iError write(_Ty data)
                {
                    return write("{}", data);
                }

                template <class... Args>
                static _iError print(CRef<istring> fmt, RRef<Args>... args)
                {
                    return write(fmt, std::forward<Args>(args)...);
                }

                template <class... Args>
                static _iError printl(CRef<istring> fmt, RRef<Args>... args)
                {
                    return writeLine(fmt, std::forward<Args>(args)...);
                }

                template <class... Args>
                static _iError printLine(CRef<istring> fmt, RRef<Args>... args)
                {
                    return writeLine(fmt, std::forward<Args>(args)...);
                }

                template <class... Args>
                static _iError read(Ref<Args>... args)
                {
                    try
                    {
                        (void)std::initializer_list<int>{
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

                static _iError readLine(Ref<istring> _istr)
                {
                    try
                    {
                        std::string istr;
                        std::cin.ignore();
                        std::getline(std::cin, istr);
                        _istr = istr;
                    }
                    catch (...)
                    {
                        return _iError::make(_iErrorCode::theIllegalInput, std::source_location::current());
                    }
                    return _iError::noError();
                }

#ifdef __WINDOWS__

                static _iError setTitle(CRef<istring> istr)
                {
                    if (!SetConsoleTitle(iEncoding::ANSI2wideChar(istr.data()).data()))
                    {
                        return _iError::make(_iErrorCode::failedToSetConsoleTitle, std::source_location::current());
                    };
                    return _iError::noError();
                }

#define tagINPUT INPUT

                static void sendKeyInput(const std::wstring wstr)
                {
                    tagINPUT input[2];

                    for (size_t i = 0; i < wstr.size(); ++i)
                    {
                        memset(input, 0, 2 * sizeof(INPUT));

                        input[0].type = INPUT_KEYBOARD;
                        input[0].ki.wScan = wstr.data()[i];
                        input[0].ki.dwFlags = KEYEVENTF_UNICODE;

                        input[1].type = INPUT_KEYBOARD;
                        input[1].ki.wScan = wstr.data()[i];
                        input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;

                        SendInput(2, input, sizeof(INPUT));
                    }
                }

                static math::iVec2<short> getConsoleCursor()
                {
                    COORD coordScreen = {0, 0};
                    CONSOLE_SCREEN_BUFFER_INFO csbi;
                    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
                    {
                        coordScreen.X = csbi.dwCursorPosition.X;
                        coordScreen.Y = csbi.dwCursorPosition.Y;
                    }
                    return {coordScreen.X, coordScreen.Y};
                }

#endif

            private:
            }; //class iConsole
        } //SPACE(console)
    } //SPACE(core)
} //SPACE(i)
