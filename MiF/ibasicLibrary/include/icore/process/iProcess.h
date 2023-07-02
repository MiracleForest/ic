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
#include <icore/data/text/istring.h>
#include <icore/system/iSystem.h>

#ifdef __WINDOWS__
#include <Windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#pragma comment(lib,"psapi.lib")
#elif defined(__UNIX__)
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <sys/wait.h>
#endif

#include <cstring>

SPACE(i)
{
	SPACE(core)
	{
		SPACE(process)
		{

			class IAPI iProcess
				: public basic::iBasic<iProcess>
			{
				using istring = data::text::istring;
				iObject(iProcess);
			public:

				iProcess();

				~iProcess();

			public:

#ifdef __WINDOWS__

				using iProcessMemory = PROCESS_MEMORY_COUNTERS;

#endif//^^^^__WINDOWS__^^^^

			public:

#ifdef __WINDOWS__

				static bool is64bitProcess();

#endif//^^^^__WINDOWS__^^^^

				static bool taskKill(CRef<istring> proName);

#ifdef __WINDOWS__

				static iProcessMemory getMemoryInfo(void);

#endif//^^^^__WINDOWS__^^^^

			public:

			public:
			public:
			protected:
			private:

			};//class iProcess


		}//SPACE(process)
	}//SPACE(core)
}//SPACE(i)