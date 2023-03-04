/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iFindCtrl.hpp
* @创建时间：2022.9.15.8:11
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* iFindCtrl
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.hpp>
#include <icore/file/iPath.hpp>
#include <icore/file/iDir.hpp>

SPACE(i)
{
	SPACE(core)
	{
		SPACE(io)
		{

			class iFindCtrl
				: public basic::iBasic<iFindCtrl>
			{
				using istring = data::text::istring;
				iObject(iFindCtrl);
			public:

				explicit iFindCtrl(CRef<istring> filepath)try
					:hFind(0)
				{
					istring path = iPath::checkPath(filepath);
					if (iDir::isDirExist(path))
					{
						if (path[path.size() - 1] != '\\' && path[path.size() - 1] != '/')
							path += "\\";
						path += "*.*";

						hFind = FindFirstFile(istring::str2wstr(path.cStr()).data(), &filedata);
					}
				}
				catch (...)
				{
					hFind = 0;
				}

				iFindCtrl(CRef<iFindCtrl>) = delete;

				iFindCtrl(RRef<iFindCtrl> f) noexcept
					:hFind(f.hFind), filedata(f.filedata)
				{
					f.hFind = 0;
				}

				~iFindCtrl()
				{
					try
					{
						if (hFind > 0)
							FindClose(hFind);
					}
					catch (...)
					{
					}
				}
			public:

				Ref<iFindCtrl> operator=(CRef<iFindCtrl>) = delete;

				Ref<iFindCtrl> operator=(RRef<iFindCtrl> f) noexcept
				{
					if (this != &f)
					{
						hFind = f.hFind;
						filedata = f.filedata;
					}
					return *this;
				}

			public:

				istring getName() noexcept
				{
					return istring(filedata.cFileName);
				}

				explicit operator bool() const noexcept
				{
					return hFind > 0;
				}

				bool next()
				{
					try
					{
						return FindNextFile(hFind, &filedata);
					}
					catch (...)
					{
						return false;
					}
				}

				uint64 getSize() const noexcept
				{
					try
					{
						return ((uint64)filedata.nFileSizeHigh << 32) | (uint64)filedata.nFileSizeLow;
					}
					catch (...)
					{
						return 1;
					}
				}

				bool isDir() const noexcept
				{
					return (filedata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
				}

				bool nextToDot()
				{
					if (this->getName() == ".")
						this->next();
					if (this->getName() == "..")
						if (!this->next())
							return false;
					return true;
				}

			private:
				HANDLE hFind;
				WIN32_FIND_DATA filedata;

			};

		}//SPACE(file)
	}//SPACE(core)
}//SPACE(i)

