/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iPath.hpp
* @创建时间：2022.9.30.15:07
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
*
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
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

            class IAPI iPath :
                public basic::iBasic<iPath>
            {
            public:

                using istring = i::core::data::text::istring;
                iObject(iPath);
            public:

                iPath() noexcept;

                iPath(CRef<::std::filesystem::path> p);

                iPath(CRRef<::std::filesystem::path> p);

                iPath(CRef<iPath> p) = default;

                iPath(RRef<iPath> p) noexcept = default;

                iPath(RRef<istring> source);

                iPath(Ref<istring> source);

                template<class Source>
                iPath(CRef<Source> source)
                    : _path(source)
                { }

                template<class Input>
                iPath(Input first, Input last)
                    : _path(first, last)
                { }

                ~iPath();

            public:

                Ref<iPath> operator=(CRef<iPath> p) = default;

                Ref<iPath> operator=(RRef<iPath> p) noexcept = default;

                Ref<iPath> operator=(RRef<istring> source);

                Ref<iPath> operator=(Ref<istring> source);

                template<class Source>
                Ref<iPath> operator = (CRef<Source> source)
                {
                    _path = source;
                    return *this;
                }

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 拼接路径，只是简单字符串连接，不会加上目录分隔符号
                *
                * @param p 新的连接路径，iPath对象
                *
                * @retval Ref\<iPath\> iPath对象引用
                * @par 示例
                * @code
                * iPath path = "C:/User/.ssh";
                * path += iPath("id_rsa");
                * assets(path, "C:/User/.sshid_rsa")
                * @endcode
                *
                * @include \<iPath.hpp\>
                ****/
                Ref<iPath> operator+=(CRef<iPath> p);

                Ref<iPath> operator+=(RRef<istring> source);

                Ref<iPath> operator+=(Ref<istring> source);

                template<class Char>
                Ref<iPath> operator += (Char ch)
                {
                    _path += ch;
                    return *this;
                }

                template<class Source>
                Ref<iPath> operator+=(CRef<Source> source)
                {
                    _path += source;
                    return *this;
                }

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 拼接路径，会自动加上目录分隔符号
                *
                * @param p 新的连接路径，iPath对象
                *
                * @retval Ref\<iPath\> iPath对象引用
                * @par 示例
                * @code
                * iPath path = "C:/User/.ssh";
                * path += iPath("id_rsa");
                * assets(path, "C:/User/.sshid_rsa")
                * @endcode
                *
                * @include \<iPath.hpp\>
                ****/
                Ref<iPath> operator/=(CRef<iPath> p);

                Ref<iPath> operator/=(RRef<istring> source);

                Ref<iPath> operator/=(Ref<istring> source);

                template<class Source>
                Ref<iPath> operator/=(CRef<Source> source)
                {
                    _path /= source;
                    return *this;
                }

                friend iPath operator/(CRef<iPath> l, const iPath r)
                {
                    return iPath(l._path / r._path);
                }

                friend bool operator==(const iPath l, CRef<iPath> r) noexcept
                {
                    return l._path == r._path;
                }

                friend bool operator!=(const iPath l, CRef<iPath> r) noexcept
                {
                    return l._path != r._path;
                }

                friend bool operator<(const iPath l, CRef<iPath> r) noexcept
                {
                    return l._path < r._path;
                }

                friend bool operator<=(const iPath l, CRef<iPath> r) noexcept
                {
                    return l._path <= r._path;
                }

                friend bool operator>(const iPath l, CRef<iPath> r) noexcept
                {
                    return l._path > r._path;
                }

                friend bool operator>=(const iPath l, CRef<iPath> r) noexcept
                {
                    return l._path >= r._path;
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 判断两个路径是否为同一个文件对象
                    *
                    * @param l iPath对象
                    * @param r iPath对象
                    *
                    * @retval bool 是否相同
                    *
                    * @include \<iPath.hpp\>
                    ****/
                friend bool equalPath(CRef<iPath> l, CRef<iPath> r)
                {
                    return ::std::filesystem::equivalent(l._path, r._path);
                }

                operator ::std::filesystem::path::string_type() const
                {
                    return _path.operator ::std::filesystem::path::string_type();
                }

                operator istring()
                {
                    return istring(_path.c_str());
                }

                istring toiString()const;

            public:

                Ref<iPath> assign(RRef<istring> source);

                Ref<iPath> assign(Ref<istring> source);

                template<class Source>
                Ref<iPath> assign(CRef<Source> source)
                {
                    _path.assign(source);
                    return *this;
                }

                template<class Input>
                Ref<iPath> assign(Input first, Input last)
                {
                    _path.assign(first, last);
                    return *this;
                }

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 连接两个路径，会自动加上目录分隔符
                *
                * @param source 新的连接路径，可以字符串或者iPath对象
                *
                * @retval iPath 新的iPath对象
                *
                * @include \<iPath.h\>
                ****/
                template<class Source>
                iPath join(CRef<Source> source)
                {
                    return operator/=(source);
                }

                void clear() noexcept;

                [[nodiscard]]
                bool empty() const noexcept;

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief iPath 更改目录分隔符为操作系统喜好
                *
                * @retval Ref<iPath> iPath引用
                * @par 示例
                * @code
                * iPath path = "C:/User/xxx";
                * path.changePreferred();
                * assets(path, "C:\\User\\xxx")
                * @endcode
                *
                * @include \<iPath.h\>
                ****/
                Ref<iPath> changePreferred();

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 删除路径文件名，如果有
                *
                * @param
                *
                * @retval iPath 新的iPath对象
                *
                * @include \<iPath.h\>
                ****/
                Ref<iPath> removeFileName();

                Ref<iPath> replaceFileName(CRef<iPath> p);

                Ref<iPath> removeExtension();

                Ref<iPath> replaceExtension(CRef<iPath> p);

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 获取路径文件名,如果有
                *
                * @retval iPath 新的iPath对象
                * @par 示例
                * @code
                *
                * @endcode
                *
                * @include \<iPath.h\>
                ****/
                iPath fileName() const;

                iPath extension() const;

                iPath rootName() const;

                iPath rootPath() const;

                iPath parentPath() const;

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 获取路径对应的绝对路径，如果存在
                *
                * @retval iPath 新的iPath对象
                * @par 示例
                * @code
                *
                * @endcode
                *
                * @include \<iPath.h\>
                ****/
                iPath absolute() const;

                Ref<::std::filesystem::path> stdPath();

                CRef<::std::filesystem::path> stdPath() const;

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 获取路径软连接对象路径（如果存在）
                *
                * @retval iPath 新的iPath对象
                * @par 示例
                * @code
                *
                * @endcode
                *
                * @include \<iPath.h\>
                ****/
                iPath symLinkPath() const;

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 路径是否含有文件名
                *
                * @retval bool 是否含有文件名
                *
                * @include \<iPath.h\>
                ****/
                bool hasFileName() const noexcept;

                bool hasExtension() const;

                bool hasParentPath() const;

                bool hasRootName() const;

                bool hasRootPath() const;

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 路径是否为绝对路径
                *
                * @retval bool 是否为绝对路径
                *
                * @include \<iPath.h\>
                ****/
                bool isAbsolute() const;

                bool isRelative() const;

                CPtr<::std::filesystem::path::value_type> cStr() const;

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 判断路径是否存在
                *
                * @retval bool 路径是否存在
                *
                * @include \<iPath.h\>
                ****/
                bool exists() const;

                ::std::uintmax_t fileSize();

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 获取路径硬链接数量，如果路径存在且为链接类型
                *
                * @retval uintmax_t 硬链接数量
                *
                * @include \<iPath.h\>
                ****/
                ::std::uintmax_t hardLinkCount() const;

                ::std::filesystem::file_time_type lastWriteTime() const;

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 创建路径目录
                *
                * @retval bool 是否创建成功
                *
                * @include \<iPath.hpp\>
                ****/
                bool createDir() const;

                bool createDirs() const;

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 创建从当前路径到指定路径的硬链接
                *
                * @param to 目标路径
                *
                * @retval bool 是否成功
                *
                * @include \<iPath.h\>
                ****/
                bool hardLinkTo(CRef<iPath> to) const;

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 创建从当前路径到指定路径的软链接，自动判断是否为目录
                *
                * @param to 目标路径
                *
                * @retval bool 是否创建成功
                *
                * @include \<iPath.hpp\>
                ****/
                bool symLinkTo(CRef<iPath> to) const;

                bool copySymLinkTo(CRef<iPath> to) const;

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 获取当前路径类型，参考 std::filesystem::file_type
                *
                * @retval file_type std::filesystem::file_type类型
                *
                * @include \<iPath.h\>
                ****/
                ::std::filesystem::file_type fileType() const;

                ::std::filesystem::file_type symLinkFileType() const;

                bool isNoneType() const;

                bool isNotFoundType() const;

                bool isRegularType() const;

                bool isDirectoryType() const;

                bool isSymLinkType() const;

                bool isBlockType() const;

                bool isCharacterType() const;

                bool isFifoType() const;

                bool isSocketType() const;

                bool isUnknownType() const;

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 获取路径权限信息（如果存在）
                *
                * @retval perms std::filesystem::perms类型
                *
                * @include \<iPath.h\>
                ****/
                ::std::filesystem::perms permissions() const;

                ::std::filesystem::perms symLinkPermissions() const;

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 设置路径权限（如果存在），模式为 replace
                *
                * @param perms 要设置的权限信息
                *
                * @include \<iPath.hpp\>
                ****/
                void setPermissions(::std::filesystem::perms perms);

                void addPermissions(::std::filesystem::perms perms);

                void removePermissions(::std::filesystem::perms perms);

                bool canNothing() const;

                /****
                * @author ticks
                * @since 23-2-15 下午17:34
                * @brief 判断路径拥有者是否可读（如果存在）
                *
                * @retval bool 是否可读
                *
                * @include \<iPath.h\>
                ****/
                bool canOwnerRead() const;

                bool canOwnerWrite() const;

                bool canOwnerExec() const;

                bool canOwnerAll() const;

                bool canGroupRead() const;

                bool canGroupWrite() const;

                bool canGroupExec() const;

                bool canGroupAll() const;

                bool canOthersRead() const;

                bool canOthersWrite() const;

                bool canOthersExec() const;

                bool canOthersAll() const;

                bool canAll() const;

                bool removeFile() const;

                ::std::uintmax_t removeAllFile() const;

                void renameFile(CRef<iPath> new_path);

                void resizeFile(::std::uintmax_t new_size) const;

                void copyTo(CRef<iPath> to, bool recursive = true);

                void copyTo(CRef<iPath> to, ::std::filesystem::copy_options opts);

            private:
                ::std::filesystem::path _path;
            };

        }//SPACE(file)
    }//SPACE(core)
}//SPACE(i)

