/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iDir.hpp
* @创建时间：2022.9.30.15:07
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* i目录类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.h>
#include <icore/file/iPath.h>

#include <fstream>


SPACE(i)
{
    SPACE(core)
    {
        SPACE(io)
        {

            class IAPI iDir :
                public basic::iBasic<iDir>
            {
            public:
                using istring = data::text::istring;
                iObject(iDir);
            public:

                iDir() noexcept;

                iDir(CRef<iDir> dir) = default;

                iDir(RRef<iDir> dir) noexcept = default;

                iDir(CRef<::std::filesystem::directory_entry> dir);

                iDir(CRef<::std::filesystem::path> path);

                explicit iDir(CRef<iPath> path);

                ~iDir();

            public:

                Ref<iDir> operator = (CRef<iDir> other) = default;

                Ref<iDir> operator = (RRef<iDir> other) noexcept = default;

                operator ::std::filesystem::directory_entry()
                {
                    return _dir;
                }

                bool operator == (CRef<iDir> dir) const noexcept;

                bool operator != (CRef<iDir> dir) const noexcept;

            public:

                void assign(CRef<iDir> dir);

                Ref<iDir> replaceFileName(CRef<iPath> p);

                Ref<iDir> refresh();

                CRef<::std::filesystem::path> stdPath() const noexcept;

                bool exists() const;

                bool isBlockType() const;

                bool isCharacterType() const;

                bool isDirectoryType() const;

                bool isFifoType() const;

                bool isRegularType() const;

                bool isSocketType() const;

                bool isSymLinkType() const;

                ::std::uintmax_t fileSize() const;

                ::std::uintmax_t hardLinkCount() const;

                ::std::filesystem::file_time_type lastWriteTime() const;

                ::std::filesystem::file_type fileType() const;

                ::std::filesystem::perms filePermissions() const;

            private:

                ::std::filesystem::directory_entry _dir;
            };//class iDir

        }//SPACE(file)
    }//SPACE(core)
}//SPACE(i)