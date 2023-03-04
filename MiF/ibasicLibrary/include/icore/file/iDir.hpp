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
#include <icore/data/text/istring.hpp>
#include <icore/file/iPath.hpp>

#include <fstream>


SPACE(i)
{
    SPACE(core)
    {
        SPACE(io)
        {

            class iDir :
                public basic::iBasic<iDir>
            {
            public:
                using istring = data::text::istring;
                iObject(iDir);
            public:

                iDir() noexcept
                { }

                iDir(CRef<iDir> dir) = default;

                iDir(RRef<iDir> dir) noexcept = default;

                iDir(CRef<::std::filesystem::directory_entry> dir)
                    : _dir(dir)
                { }

                iDir(CRef<::std::filesystem::path> path)
                    : _dir(path)
                { }

                explicit iDir(CRef<iPath> path)
                    : _dir(path.stdPath())
                { }

                ~iDir()
                { }

            public:

                Ref<iDir> operator = (CRef<iDir> other) = default;

                Ref<iDir> operator = (RRef<iDir> other) noexcept = default;

                operator ::std::filesystem::directory_entry()
                {
                    return _dir;
                }

                bool operator == (CRef<iDir> dir) const noexcept
                {
                    return _dir.operator==(dir._dir);
                }

                bool operator != (CRef<iDir> dir) const noexcept
                {
                    return _dir != dir._dir;
                }

            public:

                void assign(CRef<iDir> dir)
                {
                    _dir.assign(dir._dir);
                }

                Ref<iDir> replaceFileName(CRef<iPath> p)
                {
                    _dir.replace_filename(p.stdPath());
                    return *this;
                }

                Ref<iDir> refresh()
                {
                    _dir.refresh();
                    return *this;
                }

                CRef<::std::filesystem::path> stdPath() const noexcept
                {
                    return _dir.path();
                }

                bool exists() const
                {
                    return _dir.exists();
                }

                bool isBlockType() const
                {
                    return _dir.is_block_file();
                }

                bool isCharacterType() const
                {
                    return _dir.is_character_file();
                }

                bool isDirectoryType() const
                {
                    return _dir.is_directory();
                }

                bool isFifoType() const
                {
                    return _dir.is_fifo();
                }

                bool isRegularType() const
                {
                    return _dir.is_regular_file();
                }

                bool isSocketType() const
                {
                    return _dir.is_socket();
                }

                bool isSymLinkType() const
                {
                    return _dir.is_symlink();
                }

                ::std::uintmax_t fileSize() const
                {
                    return _dir.file_size();
                }

                ::std::uintmax_t hardLinkCount() const
                {
                    return _dir.hard_link_count();
                }

                ::std::filesystem::file_time_type lastWriteTime() const
                {
                    return _dir.last_write_time();
                }

                ::std::filesystem::file_type fileType() const
                {
                    return _dir.status().type();
                }

                ::std::filesystem::perms filePermissions() const
                {
                    return _dir.status().permissions();
                }

            private:

                ::std::filesystem::directory_entry _dir;
            };//class iDir

        }//SPACE(file)
    }//SPACE(core)
}//SPACE(i)