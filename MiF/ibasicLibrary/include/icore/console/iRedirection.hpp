/****
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名：iRedirection.h
 * @创建时间：2022.9.9.10:09
 * @创建者：Lovelylavender4
 * -----------------------------------------------------------------------------
 * iRedirection
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 *
 ****/
#pragma once
#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.hpp>
#include <icore/basic/iBasicDataType.hpp>

#ifdef __WINDOWS__

SPACE(i)
{
	SPACE(core)
	{
		SPACE(io)
		{

			class iRedirection :
				public basic::iBasic<iRedirection>
			{
				using istring = data::text::istring;
				iObject(iRedirection);
			public:

				iRedirection(void) :
					_ChildInputWrite(0),
					_ChildOutputWrite(0),
					_ChildInputRead(0),
					_ChildOutputRead(0)
				{
					ZeroMemory(&CmdPI, sizeof(CmdPI));
				}

				~iRedirection(void)
				{
					stopProcess();
				}

			public:

				bool runProcess(CRef<std::wstring> process)
				{
					SECURITY_ATTRIBUTES   sa{};
					sa.bInheritHandle = TRUE;
					sa.lpSecurityDescriptor = NULL;
					sa.nLength = sizeof(sa);

					//创建子进程输出匿名管道 
					if (FALSE == ::CreatePipe(&_ChildOutputRead, &_ChildOutputWrite, &sa, 0))
					{
						return false;
					}

					//创建子进程输入匿名管道   
					if (FALSE == CreatePipe(&_ChildInputRead, &_ChildInputWrite, &sa, 0))
					{
						::CloseHandle(_ChildOutputWrite);
						::CloseHandle(_ChildOutputRead);
						return false;
					}

					ZeroMemory(&CmdPI, sizeof(CmdPI));
					STARTUPINFO  si;
					GetStartupInfo(&si);

					si.cb = sizeof(STARTUPINFO);
					si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
					si.wShowWindow = SW_HIDE;
					si.hStdInput = _ChildInputRead;//重定向子进程输入   
					si.hStdOutput = _ChildOutputWrite;//重定向子进程输入    
					si.hStdError = _ChildOutputWrite;

					if (FALSE == ::CreateProcess(NULL, (wchar_t*)process.data(), NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &CmdPI))
					{
						::CloseHandle(_ChildInputWrite);
						::CloseHandle(_ChildInputRead);
						::CloseHandle(_ChildOutputWrite);
						::CloseHandle(_ChildOutputRead);
						_ChildInputWrite = NULL;
						_ChildInputRead = NULL;
						_ChildOutputWrite = NULL;
						_ChildOutputRead = NULL;
						ZeroMemory(&CmdPI, sizeof(CmdPI));
						return false;
					}

					return true;
				}


				bool stopProcess(void)
				{
					::CloseHandle(_ChildInputWrite);
					::CloseHandle(_ChildInputRead);
					::CloseHandle(_ChildOutputWrite);
					::CloseHandle(_ChildOutputRead);
					_ChildInputWrite = NULL;
					_ChildInputRead = NULL;
					_ChildOutputWrite = NULL;
					_ChildOutputRead = NULL;
					::TerminateProcess(CmdPI.hProcess, -1);
					::CloseHandle(CmdPI.hProcess);
					::CloseHandle(CmdPI.hThread);
					ZeroMemory(&CmdPI, sizeof(CmdPI));
					return true;
				}


				bool getOutput(int timeout, Ref<istring> outstr)
				{
					if (NULL == _ChildOutputRead)
					{
						return false;
					}

					outstr = "";
					char buffer[4096] = { 0 };
					DWORD readBytes = 0;
					while (timeout > 0)
					{
						//对管道数据进行读，但不会删除管道里的数据，如果没有数据，就立即返回
						if (FALSE == PeekNamedPipe(_ChildOutputRead, buffer, sizeof(buffer) - 1, &readBytes, 0, NULL))
						{
							return false;
						}

						//检测是否读到数据，如果没有数据，继续等待
						if (0 == readBytes)
						{
							timeout -= 1;
							continue;
						}

						readBytes = 0;
						if (::ReadFile(_ChildOutputRead, buffer, sizeof(buffer) - 1, &readBytes, NULL))
						{
							outstr.insert(outstr.end(), buffer, buffer + readBytes);
							timeout -= 1;
						}
						else
						{
							return false;
						}
					}

					return false;
				}


				bool setInput(CRef<istring> cmd)
				{
					if (NULL == _ChildInputWrite)
					{
						return false;
					}

					std::string tmp = cmd.data() + "\r\n";
					DWORD writeBytes = 0;
					if (FALSE == ::WriteFile(_ChildInputWrite, tmp.c_str(), (DWORD)tmp.size(), &writeBytes, NULL))
					{
						return false;
					}
					return true;
				}

			private:
				handle _ChildInputWrite;
				handle _ChildInputRead;
				handle _ChildOutputWrite;
				handle _ChildOutputRead;
				PROCESS_INFORMATION CmdPI;

			};//class iRedirection

		}//SPACE(console)
	}//SPACE(core)
}//SPACE(i)

#endif //!__WINDOWS__
