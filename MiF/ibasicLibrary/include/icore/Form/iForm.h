/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iForm.hpp
* @创建时间：2022.9.15.8:51
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* 窗口类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#define _USE_WINDOWS_H__

#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.h>


SPACE(i)
{
	SPACE(core)
	{
		SPACE(Form)
		{

			class IAPI iForm
				: public basic::iBasic<iForm>
			{
				iObject(iForm);
			public:

				iForm();

				~iForm();

			public:

#ifdef __WINDOWS__

				static bool hideWindow(Ref<handle> hWindow, const int try_times = 0);

				static lresult CALLBACK defWndProc(
					hwnd hwnd,
					uint Message,
					wparam wParam,
					lparam lParam
				);

				static hwnd createHideWindow(
					CPtr<wchar> windowClass,
					CPtr<wchar> windowCapital = L"",
					WNDPROC windowProc = defWndProc
				);

				static void runMessageProcedure(hwnd hwnd = 0);

#endif //^^^^__WINDOWS__^^^^

			public:
			protected:
			private:

			};//class iForm


		}//SPACE(Form)
	}//SPACE(core)
}//SPACE(i)


