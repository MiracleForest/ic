/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iProcess.hpp
* @创建时间：2022.9.15.9:09
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* 进程类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.hpp>
#include <icore/system/iSystem.hpp>

#ifdef __WINDOWS__
#include <Windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#pragma comment(lib,"psapi.lib")
#elif defined(__UNIX__)
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#endif

#include <cstring>

SPACE(i)
{
	SPACE(core)
	{
		SPACE(process)
		{

			class iProcess
				: public basic::iBasic<iProcess>
			{
				using istring = data::text::istring;
				iObject(iProcess);
			public:

				iProcess()
				{ }


				~iProcess()
				{ }

			public:
#ifdef __WINDOWS__
				using iProcessMemory = PROCESS_MEMORY_COUNTERS;
#endif

			public:
#ifdef __WINDOWS__
				static bool is64bitProcess()
				{
					if (!System::iSystem::is64bitOS())
						return false;
					else
						return sizeof(void*) * 8 == 64;
				}
#endif

				static bool taskKill(CRef<istring> proName)
				{
#ifdef __WINDOWS__
					handle hSnapshot, hPro;
					bool isDone = false;
					hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
					if (hSnapshot == 0)
						return false;

					PROCESSENTRY32 pe = { sizeof(pe) };
					bool next = Process32First(hSnapshot, &pe);
					while (next)
					{
						if (strcmp(proName.cStr(), istring::wstr2str(pe.szExeFile).data()) == 0)
						{
							hPro = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
							if (hPro != 0)
							{
								TerminateProcess(hPro, -1);
								isDone = true;
								CloseHandle(hPro);
							}
						}
						next = Process32Next(hSnapshot, &pe);
					}

					CloseHandle(hSnapshot);
					return isDone;
#endif
					// todo 2023-1-3 Linux下待实现
					return false;
				}

#ifdef __WINDOWS__
				static iProcessMemory getMemoryInfo(void)
				{
					handle handle = GetCurrentProcess();
					PROCESS_MEMORY_COUNTERS pmc;
					GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
					return pmc;
				}
#endif

			public:

			public:
			public:
			protected:
			private:

			};//class iProcess


		}//SPACE(process)
	}//SPACE(core)
}//SPACE(i)