/****
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名：iRedirection.h
 * @创建时间：2022.9.9.10:09
 * @创建者：Lovelylavender4
 * -----------------------------------------------------------------------------
 * iRedirection提供了一些方法执行指定进程，并从该进程获取输出，向该进程输入。
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 *
 ****/
#pragma once
#include <icore/family/imacrofamily.h>
#include <icore/exception/error.h>
#include <icore/data/text/istring.h>
#include <icore/basic/iBasicDataType.h>

#ifdef __WINDOWS__

SPACE(i)
{
	SPACE(core)
	{
		SPACE(io)
		{


			class IAPI iRedirection :
				public basic::iBasic<iRedirection>
			{
				using istring = data::text::istring;
				iObject(iRedirection);
			public:

				iRedirection(void);

				~iRedirection(void);

			public:

				/****
				* @author Lovelylavender4
				* @since 2023.6.6
				* @brief 运行指定的进程
				*
				* @param process 进程
				*
				* @retval 如果进程启动成功，返回true；否则，返回false
				****/
				bool runProcess(CRef<std::wstring> process);

				/****
				* @author Lovelylavender4
				* @since 2023.6.6
				* @brief 停止当前正在运行的进程
				*
				* @retval 如果进程被成功停止，则返回true，否则返回false
				****/
				bool stopProcess(void);

				/****
				* @author Lovelylavender4
				* @since 2023.6.6
				* @brief 获取进程输出 
				*
				* @param timeout 超时时间
				* @param outstr 输出字符串
				*
				* @warning 如果在超时时间内未收到任何输出，则返回false
				* @retval 如果进程启动成功，返回true；否则，返回false
				****/
				bool getOutput(int timeout, Ref<istring> outstr);

				/****
				* @author Lovelylavender4
				* @since 2023.6.6
				* @brief 向进程输入命令
				*
				* @param cmd 命令
				*
				* @retval 如果命令已经成功发送，则返回true。
				****/
				bool setInput(CRef<istring> cmd);

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
