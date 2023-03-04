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
#include <Psapi.h>
#include <io.h>
#else
#endif
#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.hpp>

#include <filesystem>
#include <fstream>


SPACE(i)
{
	SPACE(core)
	{
		SPACE(io)
		{

			class iFile :
				public basic::iBasic<iFile>
			{
				using istring = data::text::istring;
				iObject(iFile);
			public:

				iFile()
				{ }

				~iFile()
				{ }

			public:

#ifdef __WINDOWS__
				istring getCallerModuleFileName(ulong FramesToSkip = 0)
				{
					static const int maxFrameCount = 1;
					void* frames[maxFrameCount];
					int frameCount = CaptureStackBackTrace(FramesToSkip + 2, maxFrameCount, frames, NULL);

					handle hProcess = GetCurrentProcess();

					if (0 < frameCount)
					{
						HMODULE hModule;
						GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
							(CPtr<wchar>)frames[0], &hModule);
						wchar_t buf[MAX_PATH] = { 0 };
						GetModuleFileNameEx(GetCurrentProcess(), hModule, buf, MAX_PATH);
						return istring::toStdString(std::filesystem::path(buf).filename().u8string());
					}
					return "Unknown";
				}
#endif

			public:

				static bool isFileExist(CRef<istring> csFile)
				{
					/*
					ulong dwAttrib = GetFileAttributes(istring::str2wstr(csFile.cStr()).data());
					return dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY) == 0;
					*/
					return access(csFile.cStr(), 00) == 0;
				}

#ifdef __WINDOWS__
				static bool releaseResFile(ulong dwResName, CPtr<char> lpResType, CPtr<char> lpFilePathName)
				{
					HMODULE hInstance = ::GetModuleHandle(0);

					HRSRC hResID = ::FindResource(hInstance, MAKEINTRESOURCE(dwResName), istring::str2wstr(lpResType).data());
					HGDIOBJ hRes = ::LoadResource(hInstance, hResID);
					unkType pRes = ::LockResource(hRes);

					if (pRes == 0)
					{
						return false;
					}
					ulong dwResSize = ::SizeofResource(hInstance, hResID);
					handle hResFile = CreateFile(istring::str2wstr(lpFilePathName).data(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

					if (INVALID_HANDLE_VALUE == hResFile)
					{
						return false;
					}

					ulong dwWritten = 0;
					WriteFile(hResFile, pRes, dwResSize, &dwWritten, 0);
					CloseHandle(hResFile);

					return (dwResSize == dwWritten);
				}
#endif

				static bool isFileExists(CRef<istring> fileName)
				{
					std::ifstream f(fileName.data());
					return f.good();
				}

				static std::optional<std::string> readAllFile(CRef<std::string> filePath, bool isBinary)
				{
					std::ifstream fRead;

					std::ios_base::openmode mode = std::ios_base::in;
					if (isBinary)
						mode |= std::ios_base::binary;

#ifdef __MSVC__
					fRead.open(istring::str2wstr(filePath), mode);
#else
					fRead.open(filePath, mode);
#endif
					if (!fRead.is_open())
					{
						return std::nullopt;
					}
					std::string data((std::istreambuf_iterator<char>(fRead)),
						std::istreambuf_iterator<char>());
					fRead.close();
					return data;
				}

				static bool writeAllFile(CRef<std::string> filePath, CRef<std::string> content, bool isBinary)
				{
					std::ofstream fWrite;

					std::ios_base::openmode mode = std::ios_base::out;
					if (isBinary)
						mode |= std::ios_base::binary;

#ifdef __MSVC__
					fWrite.open(istring::str2wstr(filePath), mode);
#else
					fWrite.open(filePath, mode);
#endif
					if (!fWrite.is_open())
					{
						return false;
					}
					fWrite << content;
					fWrite.close();
					return true;
				}

				static std::vector<std::string> getFileNameList(CRef<std::string> dir)
				{
					std::filesystem::directory_entry d(dir);
					if (!d.is_directory())
						return {};

					std::vector<std::string> list;
					std::filesystem::directory_iterator deps(d);
					for (auto& i : deps)
					{
						list.push_back(istring::UTF82String(i.path().filename().u8string()));
					}
					return list;
				}

			public:

			public:
			protected:
			private:

			};//class iFile

		}//SPACE(file)
	}//SPACE(core)
}//SPACE(i)
