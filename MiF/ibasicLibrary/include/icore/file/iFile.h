/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iFile.hpp
* @创建时间：2022.9.30.15:07
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* i文件类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#ifdef _WIN32
#define _USE_WINDOWS_H__
#include <Windows.h>
#include <Psapi.h>
#include <io.h>
#else
#endif
#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.h>

#include <filesystem>
#include <fstream>


SPACE(i)
{
	SPACE(core)
	{
		SPACE(io)
		{

			class IAPI iFile :
				public basic::iBasic<iFile>
			{
				using istring = data::text::istring;
				iObject(iFile);
			public:

				iFile();

				~iFile();

			public:

#ifdef __WINDOWS__

				istring getCallerModuleFileName(ulong FramesToSkip = 0);

#endif//^^^^__WINDOWS__^^^^

			public:

				static bool isFileExist(CRef<istring> csFile);

#ifdef __WINDOWS__

				static bool releaseResFile(ulong dwResName, CPtr<char> lpResType, CPtr<char> lpFilePathName);

#endif//^^^^__WINDOWS__^^^^

				static bool isFileExists(CRef<istring> fileName);

				static std::optional<std::string> readAllFile(CRef<std::string> filePath, bool isBinary);

				static bool writeAllFile(CRef<std::string> filePath, CRef<std::string> content, bool isBinary);

				static std::vector<std::string> getFileNameList(CRef<std::string> dir);

			public:

			public:
			protected:
			private:

			};//class iFile

		}//SPACE(file)
	}//SPACE(core)
}//SPACE(i)
