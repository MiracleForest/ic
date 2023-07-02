/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：CGIPassRead.hpp
* @创建时间：2022.9.15.7:48
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* CGIPassRead
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.h>
#ifdef __WINDOWS__
#include <conio.h>
#endif
#ifdef __LINUX__
#include <ncurses.h>
#endif

SPACE(i)
{
	SPACE(core)
	{
		SPACE(gadgets)
		{
			inline data::text::istring CGIPassRead(int len = -1)
			{
				using istring = data::text::istring;
                auto custom_getch = []()-> auto {
#ifdef __WINDOWS__
                    return _getch();
#endif
#ifdef __LINUX__
                    return ::getch();
#endif
                };
                auto custom_putch = [](int ch) -> auto {
#ifdef __WINDOWS__
                    return _putch(ch);
#endif
#ifdef __LINUX__
                    return ::putchar(ch);
#endif
                };

				try
				{
					char ch;
					int n = 0;
					istring s = "";
					while (len<0 || len>n)
					{
						ch = (char)custom_getch();
						if (ch == '\r')
						{
							custom_putch('\r');
							custom_putch('\n');
							break;
						}
						else if (ch == '\b' && n > 0)
						{
							custom_putch('\b');
							custom_putch(' ');
							custom_putch('\b');
							--n;
							s.erase(s.size() - 1, 1);
						}
						else
						{
							custom_putch('*');
							++n;
							s.append(1, ch);
						}
					}
					return s;
				}
				catch (...)
				{
					return "";
				}
			}

		}//SPACE(gadgets)
	}//SPACE(core)
}//SPACE(i)

