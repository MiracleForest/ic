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
#include <icore/data/text/istring.hpp>

#include <filesystem>
#include <fstream>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(io)
        {

            class iPath :
                public basic::iBasic<iPath>
            {
            public:

                using istring = i::core::data::text::istring;
                iObject(iPath);
            public:

                iPath() noexcept
                { }

                iPath(CRef<::std::filesystem::path> p)
                    : _path(p)
                { }

                iPath(CRef<::std::filesystem::path&> p)
                    : _path(p)
                { }

                iPath(CRef<iPath> p) = default;

                iPath(RRef<iPath> p) noexcept = default;

                iPath(RRef<istring> source)
                    : _path(std::move(source.data()))
                { }

                iPath(Ref<istring> source)
                    : _path(source.data())
                { }

                template<class Source>
                iPath(CRef<Source> source)
                    : _path(source)
                { }

                template<class Input>
                iPath(Input first, Input last)
                    : _path(first, last)
                { }

                ~iPath()
                { }

            public:

                Ref<iPath> operator = (CRef<iPath> p) = default;

                Ref<iPath> operator = (RRef<iPath> p) noexcept = default;

                Ref<iPath> operator = (RRef<istring> source)
                {
                    _path = std::move(source.data());
                    return *this;
                }

                Ref<iPath> operator = (Ref<istring> source)
                {
                    _path = source.data();
                    return *this;
                }

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
                Ref<iPath> operator += (CRef<iPath> p)
                {
                    _path += p._path;
                    return *this;
                }

                Ref<iPath> operator += (RRef<istring> source)
                {
                    _path += std::move(source.data());
                    return *this;
                }

                Ref<iPath> operator += (Ref<istring> source)
                {
                    _path += source.data();
                    return *this;
                }

                template<class Char>
                Ref<iPath> operator += (Char ch)
                {
                    _path += ch;
                    return *this;
                }

                template<class Source>
                Ref<iPath> operator += (CRef<Source> source)
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
                Ref<iPath> operator /= (CRef<iPath> p)
                {
                    _path /= p._path;
                    return *this;
                }

                Ref<iPath> operator /= (RRef<istring> source)
                {
                    _path /= std::move(source.data());
                    return *this;
                }

                Ref<iPath> operator /= (Ref<istring> source)
                {
                    _path /= source.data();
                    return *this;
                }

                template<class Source>
                Ref<iPath> operator /= (CRef<Source> source)
                {
                    _path /= source;
                    return *this;
                }

                friend iPath operator / (CRef<iPath> l, const iPath r)
                {
                    return iPath(l._path / r._path);
                }

                friend bool operator == (const iPath l, CRef<iPath> r) noexcept
                {
                    return l._path == r._path;
                }

                friend bool operator != (const iPath l, CRef<iPath> r) noexcept
                {
                    return l._path != r._path;
                }

                friend bool operator < (const iPath l, CRef<iPath> r) noexcept
                {
                    return l._path < r._path;
                }

                friend bool operator <= (const iPath l, CRef<iPath> r) noexcept
                {
                    return l._path <= r._path;
                }

                friend bool operator > (const iPath l, CRef<iPath> r) noexcept
                {
                    return l._path > r._path;
                }

                friend bool operator >= (const iPath l, CRef<iPath> r) noexcept
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

                istring toiString()const
                {
                    return istring(_path.c_str());
                }

            public:

                Ref<iPath> assign(RRef<istring> source)
                {
                    _path.assign(std::move(source.data()));
                    return *this;
                }

                Ref<iPath> assign(Ref<istring> source)
                {
                    _path.assign(source.data());
                    return *this;
                }

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
                    * @par 示例
                    * @code
                    * iPath path = "C:/User/.ssh/";
                    * iPath p1 = path.join("id_rsa");
                    * assets(path, "C:/User/.ssh/id_rsa")
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                template<class Source>
                iPath join(CRef<Source> source)
                {
                    return operator/=(source);
                }

                void clear() noexcept
                {
                    _path.clear();
                }

                [[nodiscard]]
                bool empty() const noexcept
                {
                    return _path.empty();
                }

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
                    * @include <iPath.hpp>
                    ****/
                Ref<iPath> changePreferred()
                {
                    _path.make_preferred();
                    return *this;
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 删除路径文件名，如果有
                    *
                    * @param
                    *
                    * @retval iPath 新的iPath对象
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                Ref<iPath> removeFileName()
                {
                    _path.remove_filename();
                    return *this;
                }

                Ref<iPath> replaceFileName(CRef<iPath> p)
                {
                    _path.replace_filename(p._path);
                    return *this;
                }

                Ref<iPath> removeExtension()
                {
                    if (_path.has_extension())
                    {
                        auto p = _path.stem();
                        _path.remove_filename();
                        _path += p;
                    }
                    return *this;
                }

                Ref<iPath> replaceExtension(CRef<iPath> p)
                {
                    _path.replace_extension(p._path);
                    return *this;
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 获取路径文件名,如果有
                    *
                    * @param
                    *
                    * @retval iPath 新的iPath对象
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                iPath fileName() const
                {
                    return iPath(_path.filename());
                }

                iPath extension() const
                {
                    return iPath(_path.extension());
                }

                iPath rootName() const
                {
                    return iPath(_path.root_name());
                }

                iPath rootPath() const
                {
                    return iPath(_path.root_path());
                }

                iPath parentPath() const
                {
                    return iPath(_path.parent_path());
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 获取路径对应的绝对路径，如果存在
                    *
                    * @param
                    *
                    * @retval iPath 新的iPath对象
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                iPath absolute() const
                {
                    return iPath(::std::filesystem::absolute(_path));
                }

                Ref<::std::filesystem::path> stdPath()
                {
                    return _path;
                }

                CRef<::std::filesystem::path> stdPath() const
                {
                    return _path;
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 获取路径软连接对象路径（如果存在）
                    *
                    * @param
                    *
                    * @retval iPath 新的iPath对象
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                iPath symLinkPath() const
                {
                    return iPath(::std::filesystem::read_symlink(_path));
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 路径是否含有文件名
                    *
                    * @param
                    *
                    * @retval bool 是否含有文件名
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                bool hasFileName() const noexcept
                {
                    return _path.has_filename();
                }

                bool hasExtension() const
                {
                    return _path.has_extension();
                }

                bool hasParentPath() const
                {
                    return _path.has_parent_path();
                }

                bool hasRootName() const
                {
                    return _path.has_root_name();
                }

                bool hasRootPath() const
                {
                    return _path.has_root_path();
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 路径是否为绝对路径
                    *
                    * @param
                    *
                    * @retval bool 是否为绝对路径
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                bool isAbsolute() const
                {
                    return _path.is_absolute();
                }

                bool isRelative() const
                {
                    return _path.is_relative();
                }

                CPtr<::std::filesystem::path::value_type> cStr() const
                {
                    return _path.c_str();
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 判断路径是否存在
                    *
                    * @param
                    *
                    * @retval bool 路径是否存在
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                bool exists() const
                {
                    return ::std::filesystem::exists(_path);
                }

                ::std::uintmax_t fileSize()
                {
                    return ::std::filesystem::file_size(_path);
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 获取路径硬链接数量，如果路径存在且为链接类型
                    *
                    * @param
                    *
                    * @retval uintmax_t 硬链接数量
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                ::std::uintmax_t hardLinkCount() const
                {
                    return ::std::filesystem::hard_link_count(_path);
                }

                ::std::filesystem::file_time_type lastWriteTime() const
                {
                    return ::std::filesystem::last_write_time(_path);
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 创建路径目录
                    *
                    * @param
                    *
                    * @retval bool 是否创建成功
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                bool createDir() const
                {
                    return ::std::filesystem::create_directory(_path);
                }

                bool createDirs() const
                {
                    return ::std::filesystem::create_directories(_path);
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 创建从当前路径到指定路径的硬链接
                    *
                    * @param to 目标路径
                    *
                    * @retval bool 是否成功
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                bool hardLinkTo(CRef<iPath> to) const
                {
                    if (!exists())
                    {
                        return false;
                    }
                    ::std::filesystem::create_hard_link(_path, to._path);
                    return true;
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 创建从当前路径到指定路径的软链接，自动判断是否为目录
                    *
                    * @param to 目标路径
                    *
                    * @retval bool 是否创建成功
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                bool symLinkTo(CRef<iPath> to) const
                {
                    if (!exists())
                    {
                        return false;
                    }
                    if (isDirectoryType())
                    {
                        ::std::filesystem::create_directory_symlink(_path, to._path);
                    }
                    else
                    {
                        ::std::filesystem::create_symlink(_path, to._path);
                    }
                    return true;
                }

                bool copySymLinkTo(CRef<iPath> to) const
                {
                    if (!exists())
                    {
                        return false;
                    }
                    ::std::filesystem::copy_symlink(_path, to._path);
                    return true;
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 获取当前路径类型，参考 std::filesystem::file_type
                    *
                    * @param
                    *
                    * @retval file_type std::filesystem::file_type类型
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                ::std::filesystem::file_type fileType() const
                {
                    return ::std::filesystem::status(_path).type();
                }

                ::std::filesystem::file_type symLinkFileType() const
                {
                    return ::std::filesystem::symlink_status(_path).type();
                }

                bool isNoneType() const
                {
                    return ::std::filesystem::file_type::none == ::std::filesystem::status(_path).type();
                }

                bool isNotFoundType() const
                {
                    return ::std::filesystem::file_type::not_found == ::std::filesystem::status(_path).type();
                }

                bool isRegularType() const
                {
                    return ::std::filesystem::file_type::regular == ::std::filesystem::status(_path).type();
                }

                bool isDirectoryType() const
                {
                    return ::std::filesystem::file_type::directory == ::std::filesystem::status(_path).type();
                }

                bool isSymLinkType() const
                {
                    return ::std::filesystem::file_type::symlink == ::std::filesystem::status(_path).type();
                }

                bool isBlockType() const
                {
                    return ::std::filesystem::file_type::block == ::std::filesystem::status(_path).type();
                }

                bool isCharacterType() const
                {
                    return ::std::filesystem::file_type::character == ::std::filesystem::status(_path).type();
                }

                bool isFifoType() const
                {
                    return ::std::filesystem::file_type::fifo == ::std::filesystem::status(_path).type();
                }

                bool isSocketType() const
                {
                    return ::std::filesystem::file_type::socket == ::std::filesystem::status(_path).type();
                }

                bool isUnknownType() const
                {
                    return ::std::filesystem::file_type::unknown == ::std::filesystem::status(_path).type();
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 获取路径权限信息（如果存在）
                    *
                    * @param
                    *
                    * @retval perms std::filesystem::perms类型
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                ::std::filesystem::perms permissions() const
                {
                    return ::std::filesystem::status(_path).permissions();
                }

                ::std::filesystem::perms symLinkPermissions() const
                {
                    return ::std::filesystem::symlink_status(_path).permissions();
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 设置路径权限（如果存在），模式为 replace
                    *
                    * @param perms 要设置的权限信息
                    *
                    * @retval
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                void setPermissions(::std::filesystem::perms perms)
                {
                    ::std::filesystem::permissions(_path, perms, ::std::filesystem::perm_options::replace);
                }

                void addPermissions(::std::filesystem::perms perms)
                {
                    ::std::filesystem::permissions(_path, perms, ::std::filesystem::perm_options::add);
                }

                void removePermissions(::std::filesystem::perms perms)
                {
                    ::std::filesystem::permissions(_path, perms, ::std::filesystem::perm_options::remove);
                }

                bool canNothing() const
                {
                    auto pem = ::std::filesystem::status(_path).permissions();
                    return pem == ::std::filesystem::perms::none || pem == ::std::filesystem::perms::unknown;
                }

                /****
                    * @author ticks
                    * @since 23-2-15 下午17:34
                    * @brief 判断路径拥有者是否可读（如果存在）
                    *
                    * @param
                    *
                    * @retval bool 是否可读
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include \<iPath.hpp\>
                    ****/
                bool canOwnerRead() const
                {
                    auto pem = ::std::filesystem::status(_path).permissions();
                    return (pem & ::std::filesystem::perms::owner_read) != ::std::filesystem::perms::none;
                }

                bool canOwnerWrite() const
                {
                    auto pem = ::std::filesystem::status(_path).permissions();
                    return (pem & ::std::filesystem::perms::owner_write) != ::std::filesystem::perms::none;
                }

                bool canOwnerExec() const
                {
                    auto pem = ::std::filesystem::status(_path).permissions();
                    return (pem & ::std::filesystem::perms::owner_exec) != ::std::filesystem::perms::none;
                }

                bool canOwnerAll() const
                {
                    auto pem = ::std::filesystem::status(_path).permissions();
                    return (pem & ::std::filesystem::perms::owner_all) != ::std::filesystem::perms::none;
                }

                bool canGroupRead() const
                {
                    auto pem = ::std::filesystem::status(_path).permissions();
                    return (pem & ::std::filesystem::perms::group_read) != ::std::filesystem::perms::none;
                }

                bool canGroupWrite() const
                {
                    auto pem = ::std::filesystem::status(_path).permissions();
                    return (pem & ::std::filesystem::perms::group_write) != ::std::filesystem::perms::none;
                }

                bool canGroupExec() const
                {
                    auto pem = ::std::filesystem::status(_path).permissions();
                    return (pem & ::std::filesystem::perms::group_exec) != ::std::filesystem::perms::none;
                }

                bool canGroupAll() const
                {
                    auto pem = ::std::filesystem::status(_path).permissions();
                    return (pem & ::std::filesystem::perms::group_all) != ::std::filesystem::perms::none;
                }

                bool canOthersRead() const
                {
                    auto pem = ::std::filesystem::status(_path).permissions();
                    return (pem & ::std::filesystem::perms::others_read) != ::std::filesystem::perms::none;
                }

                bool canOthersWrite() const
                {
                    auto pem = ::std::filesystem::status(_path).permissions();
                    return (pem & ::std::filesystem::perms::others_write) != ::std::filesystem::perms::none;
                }

                bool canOthersExec() const
                {
                    auto pem = ::std::filesystem::status(_path).permissions();
                    return (pem & ::std::filesystem::perms::others_exec) != ::std::filesystem::perms::none;
                }

                bool canOthersAll() const
                {
                    auto pem = ::std::filesystem::status(_path).permissions();
                    return (pem & ::std::filesystem::perms::others_all) != ::std::filesystem::perms::none;
                }

                bool canAll() const
                {
                    auto pem = ::std::filesystem::status(_path).permissions();
                    return (pem & ::std::filesystem::perms::all) != ::std::filesystem::perms::none;
                }

                bool removeFile() const
                {
                    return ::std::filesystem::remove(_path);
                }

                ::std::uintmax_t removeAllFile() const
                {
                    return ::std::filesystem::remove_all(_path);
                }

                void renameFile(CRef<iPath> new_path)
                {
                    ::std::filesystem::rename(_path, new_path._path);
                    _path = new_path;
                }

                void resizeFile(::std::uintmax_t new_size) const
                {
                    ::std::filesystem::resize_file(_path, new_size);
                }

                void copyTo(CRef<iPath> to, bool recursive = true)
                {
                    if (recursive)
                    {
                        ::std::filesystem::copy(_path, to._path, ::std::filesystem::copy_options::recursive);
                    }
                    else
                    {
                        ::std::filesystem::copy(_path, to._path);
                    }
                }
                void copyTo(CRef<iPath> to, ::std::filesystem::copy_options opts)
                {
                    ::std::filesystem::copy(_path, to._path, opts);
                }

            private:
                ::std::filesystem::path _path;
            };

        }//SPACE(file)
    }//SPACE(core)
}//SPACE(i)

