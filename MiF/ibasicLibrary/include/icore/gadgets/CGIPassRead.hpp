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
#include <icore/data/text/istring.hpp>
#include <conio.h>

SPACE(i)
{
	SPACE(core)
	{
		SPACE(gadgets)
		{
			inline data::text::istring CGIPassRead(int len = -1)
			{
				using istring = data::text::istring;

				try
				{
					char ch;
					int n = 0;
					istring s = "";
					while (len<0 || len>n)
					{
						ch = getch();
						if (ch == '\r')
						{
							putch('\r');
							putch('\n');
							break;
						}
						else if (ch == '\b' && n > 0)
						{
							putch('\b');
							putch(' ');
							putch('\b');
							--n;
							s.erase(s.size() - 1, 1);
						}
						else
						{
							putch('*');
							//fflush(stdin);
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

