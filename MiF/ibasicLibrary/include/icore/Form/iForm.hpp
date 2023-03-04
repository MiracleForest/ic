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
#include <icore/data/text/istring.hpp>

#ifdef __WINDOWS__

SPACE(i)
{
	SPACE(core)
	{
		SPACE(Form)
		{

			class iForm
				: public basic::iBasic<iForm>
			{
				iObject(iForm);
			public:

				iForm()
				{ }

				~iForm()
				{ }

			public:

				static bool hideWindow(Ref<handle> hWindow, const int try_times = 0)
				{
					try
					{
						if (hWindow <= 0)
							return false;

						bool shown;
						int now = -1;
						ShowWindow((hwnd)hWindow, SW_HIDE);
						while (true)
						{
							if (try_times > 0)
								if (++now > try_times)
									return false;
							shown = ShowWindow((hwnd)hWindow, SW_HIDE);
							if (!shown)
								return true;
						}
					}
					catch (...)
					{
						return false;
					}
				}

				static lresult CALLBACK defWndProc(
					hwnd hwnd,
					uint Message,
					wparam wParam,
					lparam lParam
				)
				{
					switch (Message)
					{
					case WM_DESTROY:
					{
						PostQuitMessage(0);
						break;
					}

					default:
						return DefWindowProc(hwnd, Message, wParam, lParam);
					}
					return 0;
				}

				static hwnd createHideWindow(
					CPtr<wchar> windowClass,
					CPtr<wchar> windowCapital = L"",
					WNDPROC windowProc = defWndProc
				)
				{
					WNDCLASSEX wc;
					hwnd _hwnd;
					HINSTANCE hInstance = GetModuleHandle(0);

					memset(&wc, 0, sizeof(wc));
					wc.cbSize = sizeof(WNDCLASSEX);
					wc.lpfnWndProc = windowProc;
					wc.hInstance = hInstance;
					wc.lpszClassName = windowClass;

					ushort res;
					if ((res = RegisterClassEx(&wc)) == 0)
						return 0;

					_hwnd = CreateWindowEx(0, (CPtr<wchar>)(ulong)res, windowCapital
						, 0, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, 0, hInstance, 0);

					return _hwnd;
				}

				static void runMessageProcedure(hwnd hwnd = 0)
				{
					MSG msg;
					while (GetMessage(&msg, hwnd, 0, 0) > 0)
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}

			public:
			protected:
			private:

			};//class iForm


		}//SPACE(Form)
	}//SPACE(core)
}//SPACE(i)

#endif //!__WINDOWS__

