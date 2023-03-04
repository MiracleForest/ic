/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：istring.hpp
* @创建时间：2023.1.1.0:0
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* i字符串类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
//#define _USE_WINDOWS_H__

#include <icore/family/imacrofamily.h>
#include <icore/data/text/iChar.hpp>
#include <icore/data/text/iEncoding.hpp>
#include <sstream>
#include <iostream>
#include <regex>
#include <set>
#include <list>
#include <map>
#include <iomanip>
#include <string_view>
#include <format>

#ifdef __WINDOWS__
#include <stringapiset.h>
#endif

SPACE(i)
{
    SPACE(core)
    {
        SPACE(data)
        {
            SPACE(text)
            {

                class istring final
                    : public i::core::basic::iBasicDataType<istring, std::string>
                {
                    iObject(istring);
                public:

                    using traits_type = std::string::traits_type;
                    using value_type = std::string::value_type;
                    using allocator_type = std::string::allocator_type;
                    using size_type = std::string::size_type;
                    using difference_type = std::string::difference_type;
                    using reference = std::string::reference;
                    using const_reference = std::string::const_reference;
                    using pointer = std::string::pointer;
                    using const_pointer = std::string::const_pointer;
                    using iterator = std::string::iterator;
                    using const_iterator = std::string::const_iterator;
                    using reverse_iterator = std::string::reverse_iterator;
                    using const_reverse_iterator = std::string::const_reverse_iterator;
                    static const size_type npos = std::string::npos;

                public:

                    explicit istring()
                        : _data()
                    { }

                    explicit istring(CRef<std::string> str)
                        : _data(str)
                    { }

                    explicit istring(RRef<std::string> str) noexcept
                        : _data(str)
                    { }

                    istring(size_type count, value_type ch)
                        : _data(count, ch)
                    { }

                    istring(CRef<istring> other, size_type pos, size_t count)
                        : _data(other.data(), pos, count)
                    { }

                    istring(CRef<istring> other, size_type pos)
                        : _data(other.data(), pos)
                    { }

                    istring(CPtr<value_type> s, size_type count)
                        : _data(s, count)
                    { }

                    istring(CPtr<value_type> s)
                        : _data(s)
                    { }

                    template<typename T>
                    istring(T s)
                    {
                        if constexpr (std::is_same<std::string, T>::value)
                        {
                            _data = s;
                        }
                        //else
                        //{
                        //    _data = toStdString(s);
                        //}
                    }

                    istring(iChar ichar)
                        : _data(1, ichar.data())
                    { }


                    istring(CRef<istring> other)
                        : _data(other._data)
                    { }

                    istring(CRef<std::wstring> other)
                        : _data(wstr2str(other))
                    { }

                    istring(RRef<istring> other) noexcept
                        : _data(std::move(other._data))
                    { }

                    istring(std::initializer_list<value_type> ilist)
                        : _data(ilist)
                    { }

                    template<class InputIt> istring(InputIt first, InputIt last)
                        : _data(first, last)
                    { }

                    ~istring()
                    { }

                public:
                    /****
                    * @author ticks
                    * @since 22-6-23 上午11:59
                    * @brief istring assign as stdString assign
                    *
                    * @param count: 要替换的下标(0开始)
                    * @param ch: 要替换的新字符
                    * @retval Ref<istring> istring引用
                    * @par 示例
                    * @code
                    * istring str = "Hello istring";
                    * str.assign(0, 'h');
                    * str ==> "hello istring"
                    * @endcode
                    *
                    * @include <string>
                    ****/
                    Ref<istring> assign(size_type count, value_type ch)
                    {
                        this->_data.assign(count, ch);
                        return *this;
                    }

                    /**
                    * @author ticks
                    * @since 22-6-23 下午12:05
                    *
                    * @brief 用新替换原字符串
                    *
                    * @param str: 新字符串
                    * @retval Ref<istring>: istring引用
                    *
                    * @par 示例
                    * @code
                    * istring str = "Hello istring";
                    * istring str1 = "hello";
                    * str.assign(str1);
                    * str ==> "hello"
                    * @endcode
                    *
                    * @include <string>
                    *
                    **/
                    Ref<istring> assign(CRef<istring> str)
                    {
                        if (*this == str)
                        {
                            return *this;
                        }
                        this->_data.assign(str._data);
                        return *this;
                    }

                    Ref<istring> assign(CRef<istring> str, size_type pos, size_type count)
                    {
                        this->_data.assign(str._data, pos, count);
                        return *this;
                    }

                    Ref<istring> assign(CRef<istring> str, size_type pos)
                    {
                        this->_data.assign(str._data, pos);
                        return *this;
                    }

                    Ref<istring> assign(RRef<istring> str) noexcept
                    {
                        this->_data.assign(std::move(str._data));
                        return *this;
                    }

                    Ref<istring> assign(CPtr<value_type> s, size_type count)
                    {
                        this->_data.assign(s, count);
                        return *this;
                    }

                    Ref<istring> assign(CPtr<value_type> s)
                    {
                        this->_data.assign(s);
                        return *this;
                    }

                    Ref<istring> assign(std::initializer_list<value_type> ilist)
                    {
                        this->_data.assign(ilist);
                        return *this;
                    }

                    template<class InputIt> Ref<istring> assign(InputIt first, InputIt last)
                    {
                        this->_data.assign(first, last);
                        return *this;
                    }

                    /****
                    * @author ticks
                    * @since 22-6-23 下午12:13
                    * @brief 获取 istring 底层内存分配器
                    *
                    * @retval allocator_type: 底层内存分配器
                    *
                    * @par 示例
                    * @code
                    * istring str = "";
                    * auto allocator = str.getAllocator();
                    * @endcode
                    *
                    * @include <string>
                    * @details
                    * 获取 istring 底层内存分配器
                    * @enddetails
                    *
                    ****/
                    allocator_type getAllocator() const
                    {
                        return this->_data.get_allocator();
                    }

                    /****
                    * @author ticks
                    * @since 22-6-23 下午12:21
                    * @brief 获取 istring指定下标的字符
                    *
                    * @param pos: 下标(0开始)
                    * @retval reference: 字符引用
                    * @throws std::out_of_range : 当 pos > length() 时抛出
                    *
                    * @note
                    * pos 应小于字符串长度
                    * @endnote
                    * @par 示例
                    * @code
                    *
                    * @endcode
                    *
                    * @include string
                    * @details
                    * 获取 istring指定下标的字符
                    * @enddetails
                    *
                    ****/
                    reference charAt(size_type pos)
                    {
                        return this->_data.at(pos);
                    }

                    const_reference charAt(size_type pos) const
                    {
                        return this->_data.at(pos);
                    }

                    /****
                    * @author ticks
                    * @since 22-6-23 下午12:42
                    * @brief 获取字符串第一个字符
                    *
                    * @retval reference: 字符串第一个字符引用
                    * @throws
                    *
                    * @note
                    * 字符串长度为0时不要使用该函数
                    * @endnote
                    * @pre length() > 0
                    * @par 示例
                    * @code
                    * istring str = "hello";
                    * str.front() = 'H';
                    * str ==> "Hello"
                    * @endcode
                    *
                    * @warning 如果字符串长度为0，行为未定义。
                    * @include
                    * @details
                    * 获取字符串第一个字符
                    * @enddetails
                    *
                    ****/
                    reference front()
                    {
                        return this->_data.front();
                    }

                    const_reference front() const
                    {
                        return this->_data.front();
                    }

                    /****
                    * @author ticks
                    * @since 22-6-23 下午12:46
                    * @brief 获取字符串最后一个字符
                    *
                    * @retval reference: 字符串最后一个字符引用
                    * @throws
                    *
                    * @note
                    * 字符串长度为0时不要使用
                    * @endnote
                    * @pre length() > 0
                    * @par 示例
                    * @code
                    * istring str = "hello";
                    * str.back() = 'O';
                    * str ==> "HellO"
                    * @endcode
                    *
                    * @warning 如果字符串长度为0,行为未定义
                    * @include string
                    * @details
                    * 获取字符串最后一个字符
                    * @enddetails
                    *
                    ****/
                    reference back()
                    {
                        return this->_data.back();
                    }

                    const_reference back() const
                    {
                        return this->_data.back();
                    }

                    virtual std::string data()const
                    {
                        return this->_data;
                    }


                    /****
                    * @author ticks
                    * @since 22-6-23 下午12:54
                    * @brief 获取字符串的c风格表示
                    *
                    * @retval CPtr<value_type> : 字符串指针
                    *
                    * @par 示例
                    * @code
                    * istring str = "Hello";
                    * auto* str1 = str.cStr();
                    * @endcode
                    *
                    * @include string
                    * @details
                    * 获取字符串的c风格表示
                    * @enddetails
                    *
                    ****/
                    CPtr<value_type> cStr() const noexcept
                    {
                        return this->_data.data();
                    }

                    /****
                    * @author ticks
                    * @since 22-6-23 下午12:59
                    * @brief 获取字符串开始迭代器
                    ****/
                    iterator begin() noexcept
                    {
                        return this->_data.begin();
                    }

                    const_iterator begin() const noexcept
                    {
                        return this->_data.begin();
                    }

                    const_iterator cbegin() const noexcept
                    {
                        return this->_data.cbegin();
                    }

                    /****
                    * @author ticks
                    * @since 22-6-23 下午1:01
                    * @brief 获得 istring 的最后一个迭代器
                    ****/
                    iterator end() noexcept
                    {
                        return this->_data.end();
                    }

                    const_iterator end() const noexcept
                    {
                        return this->_data.end();
                    }

                    const_iterator cend() const noexcept
                    {
                        return this->_data.cend();
                    }

                    reverse_iterator rbegin() noexcept
                    {
                        return this->_data.rbegin();
                    }

                    const_reverse_iterator rbegin() const noexcept
                    {
                        return this->_data.rbegin();
                    }

                    const_reverse_iterator crbegin() const noexcept
                    {
                        return this->_data.crbegin();
                    }

                    reverse_iterator rend() noexcept
                    {
                        return this->_data.rend();
                    }

                    const_reverse_iterator rend() const noexcept
                    {
                        return this->_data.rend();
                    }

                    const_reverse_iterator crend() const noexcept
                    {
                        return this->_data.crend();
                    }

                    bool empty() const noexcept
                    {
                        return this->_data.empty();
                    }

                    size_type length() const noexcept
                    {
                        return this->_data.length();
                    }

                    size_type size() const noexcept
                    {
                        return this->_data.size();
                    }

                    size_type maxSize() const noexcept
                    {
                        return this->_data.max_size();
                    }

                    void reserve(size_type new_cap = static_cast<size_type>(0))
                    {
                        this->_data.reserve(new_cap);
                    }

                    size_type capacity() const noexcept
                    {
                        return this->_data.capacity();
                    }

                    void fitAllocSize()
                    {
                        this->_data.shrink_to_fit();
                    }

                    void clear() noexcept
                    {
                        this->_data.clear();
                    }

                    Ref<istring> insert(size_type pos, size_type count, value_type ch)
                    {
                        this->_data.insert(pos, count, ch);
                        return *this;
                    }

                    Ref<istring> insert(size_type pos, CPtr<value_type> s, size_type count)
                    {
                        this->_data.insert(pos, s, count);
                        return *this;
                    }

                    Ref<istring> insert(size_type pos, CPtr<value_type> s)
                    {
                        this->_data.insert(pos, s);
                        return *this;
                    }

                    Ref<istring> insert(size_type pos, CRef<istring> str)
                    {
                        this->_data.insert(pos, str.data());
                        return *this;
                    }

                    Ref<istring> insert(size_type pos, CRef<istring> str, size_type str_pos, size_type str_count)
                    {
                        this->_data.insert(pos, str.data(), str_pos, str_count);
                        return *this;
                    }

                    Ref<istring> insert(size_type pos, CRef<istring> str, size_type str_pos)
                    {
                        this->_data.insert(pos, str.data(), str_pos);
                        return *this;
                    }

                    iterator insert(const_iterator pos, value_type ch)
                    {
                        return this->_data.insert(pos, ch);
                    }

                    iterator insert(const_iterator pos, size_type count, value_type ch)
                    {
                        return this->_data.insert(pos, count, ch);
                    }

                    iterator insert(const_iterator pos, std::initializer_list<value_type> ilist)
                    {
                        return this->_data.insert(pos, ilist);
                    }

                    template<class InputIt> iterator insert(const_iterator pos, InputIt first, InputIt last)
                    {
                        return this->_data.insert(pos, first, last);
                    }

                    Ref<istring> erase(size_type pos = 0, size_type count = istring::npos)
                    {
                        this->_data.erase(pos, count);
                        return *this;
                    }

                    iterator erase(const_iterator pos)
                    {
                        return this->_data.erase(pos);
                    }

                    iterator erase(const_iterator first, const_iterator last)
                    {
                        return this->_data.erase(first, last);
                    }

                    void pushBack(value_type ch)
                    {
                        this->_data.push_back(ch);
                    }

                    /****
                    * @author ticks
                    * @brief 移除istring最后一个字符
                    *
                    * @warning if istring length() == 0 , the behavior is undefined
                    ****/
                    void popBack()
                    {
                        this->_data.pop_back();
                    }

                    Ref<istring> append(size_type count, value_type ch)
                    {
                        this->_data.append(count, ch);
                        return *this;
                    }

                    Ref<istring> append(CRef<istring> str)
                    {
                        this->_data.append(str._data);
                        return *this;
                    }

                    Ref<istring> append(RRef<istring> str)
                    {
                        this->_data.append(std::move(str._data));
                        return *this;
                    }

                    Ref<istring> append(CRef<std::string> str)
                    {
                        this->_data.append(str);
                        return *this;
                    }

                    Ref<istring> append(CRef<istring> str, size_type pos, size_type count)
                    {
                        this->_data.append(str._data, pos, count);
                        return *this;
                    }

                    Ref<istring> append(CRef<istring> str, size_type pos)
                    {
                        this->_data.append(str._data, pos);
                        return *this;
                    }

                    Ref<istring> append(CPtr<value_type> s, size_type count)
                    {
                        this->_data.append(s, count);
                        return *this;
                    }

                    Ref<istring> append(CPtr<value_type> s)
                    {
                        this->_data.append(s);
                        return *this;
                    }

                    Ref<istring> append(std::initializer_list<value_type> ilist)
                    {
                        this->_data.append(ilist);
                        return *this;
                    }

                    Ref<istring> append(value_type ch)
                    {
                        this->_data.push_back(ch);
                        return *this;
                    }

                    template <typename InputIt> Ref<istring> append(InputIt first, InputIt last)
                    {
                        this->_data.append(first, last);
                        return *this;
                    }

                    Ref<istring> append(int i)
                    {
                        return this->append(std::move(istring::toStdString(i)));
                    }

                    Ref<istring> append(i::core::uint ui)
                    {
                        return this->append(std::move(istring::toStdString(ui)));
                    }

                    Ref<istring> append(long l)
                    {
                        return this->append(std::move(istring::toStdString(l)));
                    }

                    Ref<istring> append(i::core::ulong ul)
                    {
                        return this->append(std::move(istring::toStdString(ul)));
                    }

                    Ref<istring> append(long long ll)
                    {
                        return this->append(std::move(istring::toStdString(ll)));
                    }

                    Ref<istring> append(i::core::uint64 ull)
                    {
                        return this->append(std::move(istring::toStdString(ull)));
                    }

                    Ref<istring> append(float f)
                    {
                        return this->append(std::move(istring::toStdString(f)));
                    }

                    Ref<istring> append(double d)
                    {
                        return this->append(std::move(istring::toStdString(d)));
                    }


                    istring substr(size_type pos = 0, size_type count = istring::npos) const
                    {
                        istring str(this->_data.substr(pos, count).data());
                        return str;
                    }

                    /****
                    * @author ticks
                    * @brief copy istring [pos, count) str to dest
                    *
                    * @throws std::out_of_range :  if pos > length()
                    ****/
                    size_type copy(Ptr<value_type> dest, size_type count, size_type pos = 0) const
                    {
                        return this->_data.copy(dest, count, pos);
                    }

                    void resize(size_type count)
                    {
                        this->_data.resize(count);
                    }

                    void resize(size_type count, value_type ch)
                    {
                        this->_data.resize(count, ch);
                    }

                    void swap(Ref<istring> other)
                    {
                        if (*this == other)
                        {
                            return;
                        }
                        this->_data.swap(other._data);
                    }

                    size_type find(CRef<istring> str, size_type pos = 0) const
                    {
                        return this->_data.find(str._data, pos);
                    }

                    size_type find(CPtr<value_type> s, size_type pos, size_type count) const
                    {
                        return this->_data.find(s, pos, count);
                    }

                    size_type find(CPtr<value_type> s, size_type pos = 0) const
                    {
                        return this->_data.find(s, pos);
                    }

                    size_type find(value_type ch, size_type pos = 0) const
                    {
                        return this->_data.rfind(ch, pos);
                    }

                    size_type rfind(CRef<istring> str, size_type pos = istring::npos) const
                    {
                        return this->_data.rfind(str._data, pos);
                    }

                    size_type rfind(CPtr<value_type> s, size_type pos, size_type count) const
                    {
                        return this->_data.rfind(s, pos, count);
                    }

                    size_type rfind(CPtr<value_type> s, size_type pos = istring::npos) const
                    {
                        return this->_data.rfind(s, pos);
                    }

                    size_type rfind(value_type ch, size_type pos = istring::npos) const
                    {
                        return this->_data.rfind(ch, pos);
                    }

                    bool startsWith(CRef<istring> str)
                    {
                        return this->_data.starts_with(str._data);
                    }

                    bool endsWith(CRef<istring> str)
                    {
                        return this->_data.ends_with(str._data);
                    }

                    bool match(CRef<std::basic_regex<value_type>> regex, bool search = false)
                    {
                        if (!search)
                        {
                            return std::regex_match(this->_data, regex);
                        }
                        return std::regex_search(this->_data, regex);
                    }

                public:

                    Ref<std::string> getDataRef()
                    {
                        return _data;
                    }

                public:

                    static std::string toStdString(int value)
                    {
                        return std::to_string(value);
                    }

                    static std::string toStdString(uint value)
                    {
                        return std::to_string(value);
                    }

                    static std::string toStdString(long value)
                    {
                        return std::to_string(value);
                    }

                    static std::string toStdString(ulong value)
                    {
                        return std::to_string(value);
                    }

                    static std::string toStdString(int64 value)
                    {
                        return std::to_string(value);
                    }

                    static std::string toStdString(uint64 value)
                    {
                        return std::to_string(value);
                    }

                    static std::string toStdString(double value)
                    {
                        return std::to_string(value);
                    }

                    static std::string toStdString(float value)
                    {
                        return std::to_string(value);
                    }

                    static std::string toStdString(long double value)
                    {
                        return std::to_string(value);
                    }

                    static std::string toStdString(CPtr<char> value)
                    {
                        return std::string(value);
                    }

                    static std::string toStdString(char value)
                    {
                        return std::string(1, value);
                    }

                    static std::string toStdString(CRef<std::string> value)
                    {
                        return value;
                    }

                    static std::string toStdString(const wchar_t value)
                    {
                        return iEncoding::wideChar2UTF8(std::wstring(1, value));
                    }

                    static std::string toStdString(CPtr<wchar_t> value)
                    {
                        return iEncoding::wideChar2UTF8(value);
                    }

                    static std::string toStdString(CRef<istring> value)
                    {
                        return value.data();
                    }

#ifdef __cpp_lib_char8_t
                    static std::string toStdString(CRef<std::u8string> value)
                    {
                        return UTF82String(value);
                    }
#endif

                    template<HasDataFunction _Ty> requires HasNo2StdStringFunction<_Ty>&& HasNo2iStringFunction<_Ty>
                    static std::string toStdString(CRef<_Ty> value)
                    {
                        if (std::convertible_to<value.data(), std::string>)
                        {
                            return toStdString(value.data());
                        }
                    }

                    template<Has2StdStringFunction _Ty>
                    static std::string toStdString(CRef<_Ty> value)
                    {
                        return value.toStdString();
                    }

                    template<Has2iStringFunction _Ty>
                    static std::string toStdString(CRef<_Ty> value)
                    {
                        return value.toiString();
                    }

                    /****
                    * @author Lovelylavender4
                    * @include <list>,"istring.hpp",
                    ****/
                    static std::list<std::string> istringSplit2List(
                        CRef<istring> str,
                        CRef<istring> delimiters,
                        bool pushEmpty = false,
                        bool vInversion = false)
                    {
                        std::list<std::string> arr;
                        if (!str.empty())
                        {
                            size_type start = 0;
                            size_type end = str.data().find_first_of(delimiters.data(), start);
                            while (end != npos)
                            {
                                std::string token = str.data().substr(start, end - start);
                                if (!token.empty() || (token.empty() && pushEmpty))
                                {
                                    if (vInversion) arr.emplace_front(token);
                                    else arr.emplace_back(token);
                                }
                                start = end + 1;
                                end = str.data().find_first_of(delimiters.data(), start);
                            }
                            std::string token = str.data().substr(start);
                            if (!token.empty() || (token.empty() && pushEmpty))
                            {
                                if (vInversion)
                                {
                                    arr.emplace_front(token);
                                }
                                else
                                {
                                    arr.emplace_back(token);
                                }
                            }
                        }
                        return arr;
                    }

                    static std::vector<std::string> istringSplit2Vector(
                        CRef<istring> str,
                        CRef<istring> delimiters,
                        bool pushEmpty = false)
                    {
                        std::vector<std::string> arr;
                        if (!str.empty())
                        {
                            size_type start = 0;
                            size_type end = str.data().find_first_of(delimiters.data(), start);
                            while (end != npos)
                            {
                                std::string token = str.data().substr(start, end - start);
                                if (!token.empty() || (token.empty() && pushEmpty))
                                {
                                    arr.emplace_back(token);
                                }
                                start = end + 1;
                                end = str.data().find_first_of(delimiters.data(), start);
                            }
                            std::string token = str.data().substr(start);
                            if (!token.empty() || (token.empty() && pushEmpty))
                            {
                                arr.emplace_back(token);
                            }
                        }
                        return arr;
                    }

                    static std::wstring str2wstr(CRef<std::string> str)
                    {
                        return str2wstr(str, CP_UTF8);
                    }

                    static std::wstring str2wstr(CRef<std::string> str, i::core::uint codePage)
                    {
                        auto len = MultiByteToWideChar(codePage, 0, str.c_str(), -1, nullptr, 0);
                        auto* buffer = new wchar_t[len + 1];
                        MultiByteToWideChar(codePage, 0, str.c_str(), -1, buffer, len + 1);
                        buffer[len] = L'\0';

                        std::wstring result = std::wstring(buffer);
                        delete[] buffer;
                        return result;
                    }

                    static Ptr<wchar> str2cwstr(CRef<std::string> str)
                    {
                        auto len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
                        auto* buffer = new wchar_t[len + 1];
                        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, len + 1);
                        buffer[len] = L'\0';
                        return buffer;
                    }

                    static std::string wstr2str(CRef<std::wstring> wstr)
                    {
#ifdef __WINDOWS__
                        return iEncoding::wideChar2ANSI(wstr);
#else
                        return wstr2str(wstr, CP_UTF8);
#endif

                    }

                    static istring wstr2istr(CRef<std::wstring> wstr)
                    {
                        return wstr2str(wstr);
                    }


                    static std::string wstr2str(CRef<std::wstring> wstr, uint codePage)
                    {
                        auto len = WideCharToMultiByte(codePage, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
                        Ptr<char> buffer = new char[len + 1];
                        WideCharToMultiByte(codePage, 0, wstr.c_str(), -1, buffer, len + 1, nullptr, nullptr);
                        buffer[len] = '\0';

                        std::string result = std::string(buffer);
                        delete[] buffer;
                        return result;
                    }

#ifdef __cpp_lib_char8_t
                    static std::string UTF82String(std::u8string str)
                    {
                        return reinterpret_cast<Ref<std::string>>(str);
                    }
#endif //__cpp_lib_char8_t

                    static std::string UTF82String(std::string str)
                    {
                        return str;
                    }

                    template <typename T>
                    static bool matches(CPtr<T> str1, CPtr<T> str2)
                    {
                        unsigned int index = 0u;
                        T c1 = str1[index];
                        T c2 = str2[index];

                        while ((c1 != '\0') && (c2 != '\0'))
                        {
                            if (c1 != c2)
                            {
                                // 至少有一个字符是不同的
                                return false;
                            }

                            ++index;
                            c1 = str1[index];
                            c2 = str2[index];
                        }

                        // 至少达到一个字符串的末端，但该字符串可以是不同长度的
                        return (c1 == c2);
                    }

                    static std::string makeSafeName(CRef<std::string> name)
                    {
                        std::string safeName(name);

                        const size_t length = name.length();
                        for (size_t i = 0u; i < length; ++i)
                        {
                            if (
                                (name[i] == '\\') ||
                                (name[i] == '/') ||
                                (name[i] == '*') ||
                                (name[i] == '?') ||
                                (name[i] == '"') ||
                                (name[i] == '<') ||
                                (name[i] == '>') ||
                                (name[i] == '|') ||
                                (name[i] == ':') ||
                                (name[i] == ';') ||
                                (name[i] == ',') ||
                                (name[i] == '.')
                                )
                            {
                                safeName[i] = '_';
                            }
                        }
                        return safeName;
                    }

                    static std::string eraseAll(CRef<std::string> str, CRef<std::string> subString)
                    {
                        const size_t subStringLength = subString.length();
                        std::string result(str);

                        for (;;)
                        {
                            const size_t pos = result.find(subString);
                            if (pos == std::string::npos)
                            {
                                return result;
                            }

                            result.erase(pos, subStringLength);
                        }
                    }

                    template <class... Args>
                    static istring sumString(Args... args)
                    {
                        return (... + toStdString(std::forward<Args>(args)));
                    }

                    template <class... Args>
                    static std::string sumString2(Args... args)
                    {
                        return (... + toStdString(std::forward<Args>(args)));
                    }

                    static istring str2hex(istring s, bool upper = true)
                    {
                        try
                        {
                            istring res;
                            char Hc, hc;
                            for (size_t i = 0; i < s.size(); ++i)
                            {
                                char2hex(s[i], &Hc, &hc, upper);
                                res.append(1, Hc);
                                res.append(1, hc);
                            }
                            return res;
                        }
                        catch (...)
                        {
                            return "";
                        }
                    }

                    static istring hex2str(istring s)
                    {
                        try
                        {
                            if ((s.size() & 1) == 1)
                                return "";
                            istring res;
                            for (size_t i = 0; i < s.size(); i += 2)
                                res.append(1, hex2char(s[i], s[i] + 1));
                            return res;
                        }
                        catch (...)
                        {
                            return "";
                        }
                    }

                    static void char2hex(char dat, Ptr<char> high_hex, Ptr<char> low_hex, bool upper = true)
                    {
                        char Hc = (dat >> 4) & char(15);
                        char hc = dat & char(15);
                        if (high_hex)
                            *high_hex = Hc > 9 ? Hc - 10 + (upper ? 'A' : 'a') : Hc + '0';
                        if (low_hex)
                            *low_hex = hc > 9 ? hc - 10 + (upper ? 'A' : 'a') : hc + '0';
                    }

                    static char hex2char(char high_hex, char low_hex)
                    {
                        if (high_hex >= '0' && high_hex <= '9')
                            high_hex -= '0';
                        else if (high_hex >= 'A' && high_hex <= 'F')
                            high_hex -= 'A' - 10;
                        else if (high_hex >= 'a' && high_hex <= 'a')
                            high_hex -= 'a' - 10;
                        else
                            return '\0';

                        if (low_hex >= '0' && low_hex <= '9')
                            low_hex -= '0';
                        else if (low_hex >= 'A' && low_hex <= 'F')
                            low_hex -= 'A' - 10;
                        else if (low_hex >= 'a' && low_hex <= 'a')
                            low_hex -= 'a' - 10;
                        else
                            return '\0';

                        return (high_hex << 4) | low_hex;
                    }

                public:

                    /****
                    * @author Lovelylavender4
                    * @since 编写此代码的时间或版本
                    *
                    * @param delimiters
                    * @param pushEmpty = false
                    * @param vInversion = false
                    * @retval std::list<std::string>
                    ****/
                    std::list<std::string> split2List(
                        CRef<istring> delimiters,
                        bool pushEmpty = false,
                        bool vInversion = false)
                    {
                        std::list<std::string> arr;
                        if (!this->_data.empty())
                        {
                            size_type start = 0;
                            size_type end = (this->_data).find_first_of(delimiters.data(), start);
                            while (end != npos)
                            {
                                std::string token = (this->_data).substr(start, end - start);
                                if (!token.empty() || (token.empty() && pushEmpty))
                                {
                                    if (vInversion) arr.emplace_front(token);
                                    else arr.emplace_back(token);
                                }
                                start = end + 1;
                                end = (this->_data).find_first_of(delimiters.data(), start);
                            }
                            std::string token = (this->_data).substr(start);
                            if (!token.empty() || (token.empty() && pushEmpty))
                            {
                                if (vInversion)
                                {
                                    arr.emplace_front(token);
                                }
                                else
                                {
                                    arr.emplace_back(token);
                                }
                            }
                        }
                        return arr;
                    }

                    std::vector<std::string> split2Vector(
                        CRef<istring> delimiters,
                        bool pushEmpty = false)
                    {
                        std::vector<std::string> arr;
                        if (!(this->_data).empty())
                        {
                            size_type start = 0;
                            size_type end = (this->_data).find_first_of(delimiters.data(), start);
                            while (end != npos)
                            {
                                std::string token = (this->_data).substr(start, end - start);
                                if (!token.empty() || (token.empty() && pushEmpty))
                                {
                                    arr.emplace_back(token);
                                }
                                start = end + 1;
                                end = (this->_data).find_first_of(delimiters.data(), start);
                            }
                            std::string token = (this->_data).substr(start);
                            if (!token.empty() || (token.empty() && pushEmpty))
                            {
                                arr.emplace_back(token);
                            }
                        }
                        return arr;
                    }

                    std::set<std::string> split2Set(
                        CRef<istring> delimiters,
                        bool pushEmpty = false)
                    {
                        std::set<std::string> arr;
                        if (!(this->_data).empty())
                        {
                            size_type start = 0;
                            size_type end = (this->_data).find_first_of(delimiters.data(), start);
                            while (end != npos)
                            {
                                std::string token = (this->_data).substr(start, end - start);
                                if (!token.empty() || (token.empty() && pushEmpty))
                                    arr.emplace(token);
                                start = end + 1;
                                end = (this->_data).find_first_of(delimiters.data(), start);
                            }
                            std::string token = (this->_data).substr(start);
                            if (!token.empty() || (token.empty() && pushEmpty))
                            {
                                arr.emplace(token);
                            }
                        }
                        return arr;
                    }


                public:

                    /****
                    * @brief 整数转为十六进制字符串。
                    *
                    * @tparam T      整数类型
                    * @param  value  整数值
                    * @param  upper  是否使用大写字母（0x1A或0x1a）。
                    * @param  no0x   是否省略0x前缀
                    * @param  noLeadingZero 是否省略前面的零
                    * @return std::string  十六进制字符串
                    *
                    * @par 示例
                    * @code
                    * IntToHexStr(15); // "F"
                    * IntToHexStr(16, true, true, false); // "0000000F"
                    * @endcode
                    *
                    ****/
                    template <typename T>
                    static istring intToHexStr(CRef<T> value, bool upper = true, bool no0x = false,
                        bool noLeadingZero = false)
                    {
                        istring result;
                        if (value < 0) result += '-';
                        if (!no0x) result += "0x";
                        auto hexStr = upper ? "0123456789ABCDEF" : "0123456789abcdef";
                        bool leadingZero = true;
                        for (int i = sizeof(T) * 2; i > 0; --i)
                        {
                            auto hex = (value >> (i - 1) * 4) & 0xF;
                            if (noLeadingZero && leadingZero && hex == 0) continue;
                            leadingZero = false;
                            result += hexStr[hex];
                        }
                        return result;
                    }

                    template<typename T>
                    static std::vector<T> parseArray(CRef<std::string> str)
                    {
                        std::vector<T> elems;
                        std::istringstream f(str);
                        std::string str;
                        while (std::getline(f, str, ':'))
                        {
                            elems.push_back(parse<T>(str));
                        }
                        return elems;
                    }

                    static istring toUpper(CRef<istring> str)
                    {
                        istring buff = str;
                        for (size_t i = 0; i < str.size(); i++)
                        {
                            buff[i] = toupper(str[i]);
                        }
                        return buff;
                    }

                    static istring toLower(CRef<istring> str)
                    {
                        istring buff = str;
                        for (size_t i = 0; i < str.size(); i++)
                        {
                            buff[i] = tolower(str[i]);
                        }
                        return buff;
                    }

                    static istring ltrim(CRef<istring> str)
                    {
                        istring s = str;
                        auto notSpace = [](unsigned char ch)
                        {
                            return !std::isspace(ch);
                        };
                        s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
                        return s;
                    }

                    static istring rtrim(CRef<istring> str)
                    {
                        istring s = str;
                        auto notSpace = [](unsigned char ch)
                        {
                            return !std::isspace(ch);
                        };
                        s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
                        return s;
                    }

                    static istring trim(CRef<istring> s)
                    {
                        return ltrim(rtrim(s));
                    }

                    template<typename T>
                    static istring join(CRef<std::vector<T>> v, CRef<istring> token)
                    {
                        std::ostringstream result;
                        for (typename std::vector<T>::const_iterator i = v.begin(); i != v.end(); i++)
                        {
                            if (i != v.begin())
                                result << token;
                            result << *i;
                        }
                        return result.str();
                    }

                    static bool isAlphabetic(CRef<std::string> str1, CRef<std::string> str2)
                    {
                        return static_cast<bool>(toLower(str1).data() < toLower(str2).data());
                    }

                    static bool isMatch(CRef<std::string> pattern, CRef<std::string> string)
                    {
                        const char* pattern_in = pattern.data();
                        const char* string_in = string.data();

                        if (*pattern_in == '\0' && *string_in == '\0')
                        {
                            return true;
                        }

                        if (*pattern_in == '*' && *(pattern_in + 1) != '\0' && *string_in == '\0')
                        {
                            return false;
                        }

                        if (*pattern_in == '?' || *pattern_in == *string_in)
                        {
                            return isMatch(pattern_in + 1, string_in + 1);
                        }

                        if (*pattern_in == '*')
                        {
                            return isMatch(pattern_in + 1, string_in) || isMatch(pattern_in, string_in + 1);
                        }
                        return false;
                    }

                    static bool isNum(CRef<std::string> string)
                    {
                        try
                        {
                            auto w = std::stod(string);
                            (void)w;
                            return true;
                        }
                        catch (...)
                        {
                            return false;
                        }
                    }

                    template<class...Args>
                    static istring format(CRef<istring> fmtstr, Args...args)
                    {
                        return std::vformat(toStdString(fmtstr.data()), std::make_format_args(toStdString(std::forward<Args>(args))...));
                    }

                public:

                    constexpr uint64_t doHash()
                    {
                        CPtr<char> x = this->_data.data();
                        // ap hash
                        uint64_t rval = 0;
                        for (size_t i = 0; x[i]; ++i)
                        {
                            if (i & 1)
                            {
                                rval ^= (~((rval << 11) ^ x[i] ^ (rval >> 5)));
                            }
                            else
                            {
                                rval ^= (~((rval << 7) ^ x[i] ^ (rval >> 3)));
                            }
                        }
                        return rval;
                    }


                    constexpr uint64 doHash2()
                    {
                        std::string_view x = this->_data.data();
                        // ap hash
                        uint64 rval = 0;
                        for (size_t i = 0; i < x.size(); ++i)
                        {
                            rval *= 128;
                            rval += x[i];
                            rval += 4;
                        }
                        return rval;
                    }

                public:

                    static constexpr uint64 doHash(CPtr<char> x, int len)
                    {
                        // ap hash
                        uint64 rval = 0;
                        for (size_t i = 0; i < len; ++i)
                        {
                            if (i & 1)
                            {
                                rval ^= (~((rval << 11) ^ x[i] ^ (rval >> 5)));
                            }
                            else
                            {
                                rval ^= (~((rval << 7) ^ x[i] ^ (rval >> 3)));
                            }
                        }
                        return rval;
                    }

                    static constexpr uint64 doHash2(std::string_view x)
                    {
                        // ap hash
                        uint64 rval = 0;
                        for (size_t i = 0; i < x.size(); ++i)
                        {
                            rval *= 128;
                            rval += x[i];
                            rval += 4;
                        }
                        return rval;
                    }

                    static constexpr uint64 doHash(CPtr<char> x)
                    {
                        // ap hash
                        uint64 rval = 0;
                        for (size_t i = 0; x[i]; ++i)
                        {
                            if (i & 1)
                            {
                                rval ^= (~((rval << 11) ^ x[i] ^ (rval >> 5)));
                            }
                            else
                            {
                                rval ^= (~((rval << 7) ^ x[i] ^ (rval >> 3)));
                            }
                        }
                        return rval;
                    }

                    static std::vector<std::string> splitStrWithPattern(CRef<std::string> str, CRef<std::string> pattern)
                    {
                        std::vector<std::string> resVec;

                        if (str.empty())
                            return resVec;

                        std::string strs = str + pattern;

                        size_t pos = strs.find(pattern);
                        size_t size = strs.size();

                        while (pos != std::string::npos)
                        {
                            std::string x = strs.substr(0, pos);
                            resVec.push_back(x);
                            strs = strs.substr(pos + 1, size);
                            pos = strs.find(pattern);
                        }

                        return resVec;
                    }

#pragma region 关于replace

                    Ref<istring> replace(size_type pos, size_type count, CRef<istring> str)
                    {
                        this->_data.replace(pos, count, str._data);
                        return *this;
                    }

                    Ref<istring> replace(const_iterator first, const_iterator last, CRef<istring> str)
                    {
                        this->_data.replace(first, last, str._data);
                        return *this;
                    }

                    Ref<istring> replace(size_type pos, size_type count, CRef<istring> str,
                        size_type str_pos, size_type str_count = istring::npos)
                    {
                        this->_data.replace(pos, count, str._data, str_pos, str_count);
                        return *this;
                    }

                    template <typename InputIt>
                    Ref<istring> replace(const_iterator first, const_iterator last, InputIt first1, InputIt last1)
                    {
                        this->_data.replace(first, last, first1, last1);
                        return *this;
                    }

                    Ref<istring> replace(size_type pos, size_type count, CPtr<value_type> s, size_type s_count)
                    {
                        this->_data.replace(pos, count, s, s_count);
                        return *this;
                    }

                    Ref<istring> replace(size_type pos, size_type count, CPtr<value_type> s)
                    {
                        this->_data.replace(pos, count, s);
                        return *this;
                    }

                    Ref<istring> replace(const_iterator first, const_iterator last, CPtr<value_type> s)
                    {
                        this->_data.replace(first, last, s);
                        return *this;
                    }

                    Ref<istring> replace(size_type pos, size_type count, size_type ch_count, value_type ch)
                    {
                        this->_data.replace(pos, count, ch_count, ch);
                        return *this;
                    }

                    Ref<istring> replace(const_iterator first, const_iterator last, size_type count, value_type ch)
                    {
                        this->_data.replace(first, last, count, ch);
                        return *this;
                    }

                    Ref<istring> replace(const_iterator first, const_iterator last, std::initializer_list<value_type> ilist)
                    {
                        this->_data.replace(first, last, ilist);
                        return *this;
                    }

                    Ref<istring> replace(size_type pos, size_type count, std::initializer_list<value_type> ilist)
                    {
                        this->_data.replace(this->_data.begin() + pos, this->_data.begin() + pos + count, ilist);
                        return *this;
                    }

                public:

                    static bool replaceLast(Ref<istring> str, CRef<istring> oldStr, CRef<istring> newStr)
                    {
                        size_t start_pos = str.rfind(oldStr);
                        if (start_pos == std::string::npos)
                            return false;
                        str.replace(start_pos, oldStr.length(), newStr);
                        return true;
                    }

                    static bool replaceiStr(
                        Ref<istring> str,
                        CRef<istring> oldStr,
                        CRef<istring> newStr
                    )
                    {
                        bool found = false;
                        size_t pos = 0;
                        while ((pos = str.find(oldStr.data(), pos)) != npos)
                        {
                            found = true;
                            str.replace(pos, oldStr.length(), newStr.data());
                            pos += newStr.length();
                        }
                        return found;
                    }


                    static CRef<istring> replaceiStr(
                        CRef<istring> istr,
                        CRef<istring> oldStr,
                        CRef<istring> newStr
                    )
                    {
                        istring str = istr;
                        for (std::string::size_type pos(0); pos != std::string::npos; pos += newStr.length())
                        {
                            if ((pos = str.find(oldStr, pos)) != std::string::npos)
                            {
                                str.replace(pos, oldStr.length(), newStr);
                            }
                            else
                            {
                                break;
                            }
                        }
                        return str;
                    }

                    static istring fixCurlyBracket(istring str)
                    {
                        replaceiStr(str, "{", "{{");
                        replaceiStr(str, "}", "}}");
                        return str;
                    }

                public:

                    void fixCurlyBracket()
                    {
                        istring buff = this->_data;
                        replaceiStr(buff, "{", "{{");
                        replaceiStr(buff, "}", "}}");
                        this->_data = buff.data();
                    }

                    bool replace(
                        CRef<istring> oldStr,
                        CRef<istring> newStr
                    )
                    {
                        istring str = this->_data;
                        bool found = false;
                        size_t pos = 0;
                        while ((pos = str.find(oldStr.data(), pos)) != npos)
                        {
                            found = true;
                            str.replace(pos, oldStr.length(), newStr.data());
                            pos += newStr.length();
                        }
                        this->_data = str.data();
                        return found;
                    }

                    bool replaceLast(CRef<istring> oldStr, CRef<istring> newStr)
                    {
                        istring str = this->_data;
                        size_t start_pos = str.rfind(oldStr);
                        if (start_pos == std::string::npos)
                            return false;
                        str.replace(start_pos, oldStr.length(), newStr);
                        this->_data = str.data();
                        return true;
                    }

#pragma endregion 关于replace

                public:

                    bool contains(CRef<istring> find)
                    {
                        return this->_data.find(find.data()) != std::string_view::npos;
                    }

                    bool isAlphabetic()const
                    {
                        return static_cast<bool>(toLower(this->cStr()).data() < toLower(this->cStr()).data());
                    }

                    bool isMatch(CRef<std::string> pattern)const
                    {
                        CPtr<char> pattern_in = pattern.data();
                        if (*pattern_in == '\0' && *this->_data.data() == '\0')
                        {
                            return true;
                        }

                        if (*pattern_in == '*' && *(pattern_in + 1) != '\0' && *this->_data.data() == '\0')
                        {
                            return false;
                        }

                        if (*pattern_in == '?' || *pattern_in == *this->_data.data())
                        {
                            return isMatch(pattern_in + 1, this->_data.data() + 1);
                        }

                        if (*pattern_in == '*')
                        {
                            return isMatch(pattern_in + 1, this->_data.data()) || isMatch(pattern_in, this->_data.data() + 1);
                        }
                        return false;
                    }

                    bool isNum()const
                    {
                        try
                        {
                            auto n = std::stod(this->_data);
                            return true;
                        }
                        catch (...)
                        {
                            return false;
                        }
                    }

                    Ref<istring> toUpper()
                    {
                        for (size_t i = 0; i < this->size(); i++)
                        {
                            this->_data[i] = toupper(this->_data[i]);
                        }
                        return *this;
                    }

                    Ref<istring> toLower()
                    {
                        for (size_t i = 0; i < this->size(); i++)
                        {
                            this->_data[i] = tolower(this->_data[i]);
                        }
                        return *this;
                    }

                    Ref<istring> ltrim()
                    {
                        auto notSpace = [](uchar ch)
                        {
                            return !std::isspace(ch);
                        };
                        this->_data.erase(this->_data.begin(), std::find_if(this->_data.begin(), this->_data.end(), notSpace));
                        return *this;
                    }

                    Ref<istring> rtrim()
                    {
                        auto notSpace = [](uchar ch)
                        {
                            return !std::isspace(ch);
                        };
                        this->_data.erase(std::find_if(this->_data.rbegin(), this->_data.rend(), notSpace).base(), this->_data.end());
                        return *this;
                    }

                    Ref<istring> trim()
                    {
                        rtrim();
                        ltrim();
                        return *this;
                    }

                    /****
                    * @author Lovelylavender4
                    * @since 2022.9.6
                    * @brief 转到十六进制i字符串
                    *
                    * @future 支持中文字符串
                    * @retval 转换好的十六进制i字符串
                    *
                    * @par 示例
                    * @code
                    * istring istr="Hello world!";
                    * istr.toHexiStr();
                    * @endcode
                    ****/
                    istring toHexiStr()
                    {
                        return str2hex(this->_data);
                    }

                    /****
                    * @author Lovelylavender4
                    * @since 2022.9.6
                    * @brief 转到十进制i字符串
                    *
                    * @future 支持中文字符串
                    * @retval 转换好的十进制i字符串
                    *
                    * @par 示例
                    * @code
                    * istring istr="Hello world!";
                    * istr.toDeciStr();
                    * @endcode
                    *
                    * @include <iosfwd>,<ios>
                    ****/
                    istring toDeciStr()
                    {
                        std::ostringstream os;
                        os << std::dec << this->_data;
                        return os.str();
                    }

                public:

                    Ref<istring> operator = (CRef<istring> str)
                    {
                        if (*this == str)
                        {
                            return *this;
                        }
                        this->_data = str._data;
                        return *this;
                    }

                    Ref<istring> operator = (RRef<istring> str) noexcept
                    {
                        if (*this == str)
                        {
                            return *this;
                        }
                        this->_data = std::move(str)._data;
                        return *this;
                    }

                    Ref<istring> operator = (CPtr<value_type> s)
                    {
                        this->_data = s;
                        return *this;
                    }

                    Ref<istring> operator = (value_type ch)
                    {
                        this->_data = ch;
                        return *this;
                    }

                    Ref<istring> operator = (std::initializer_list<value_type> ilist)
                    {
                        this->_data = ilist;
                        return *this;
                    }

                    reference operator [] (size_type pos)
                    {
                        return this->_data[pos];
                    }

                    const_reference operator [] (size_type pos) const
                    {
                        return this->_data[pos];
                    }

                    Ref<istring> operator += (CRef<istring> str)
                    {
                        this->_data += str._data;
                        return *this;
                    }

                    Ref<istring> operator += (value_type ch)
                    {
                        this->_data += ch;
                        return *this;
                    }

                    Ref<istring> operator += (CPtr<value_type> s)
                    {
                        this->_data += s;
                        return *this;
                    }

                    Ref<istring> operator += (std::initializer_list<value_type> ilist)
                    {
                        this->_data += ilist;
                        return *this;
                    }

                    friend bool operator == (CRef<istring> ls, CRef<istring> rs) noexcept
                    {
                        return ls._data == rs._data;
                    }

                    friend bool operator != (CRef<istring> ls, CRef<istring> rs) noexcept
                    {
                        return ls._data != rs._data;
                    }

                    friend bool operator < (CRef<istring> ls, CRef<istring> rs) noexcept
                    {
                        return ls._data < rs._data;
                    }

                    friend bool operator <= (CRef<istring> ls, CRef<istring> rs) noexcept
                    {
                        return ls._data <= rs._data;
                    }

                    friend bool operator > (CRef<istring> ls, CRef<istring> rs) noexcept
                    {
                        return ls._data > rs._data;
                    }

                    friend bool operator >= (CRef<istring> ls, CRef<istring> rs) noexcept
                    {
                        return ls._data >= rs._data;
                    }

                    friend bool operator == (CPtr<value_type> s, CRef<istring> rs) noexcept
                    {
                        return s == rs._data;
                    }

                    friend bool operator == (CRef<istring> ls, CPtr<value_type> s)
                    {
                        return ls.cStr() == s;
                    }

                    friend bool operator != (CRef<istring> ls, CPtr<value_type> s)
                    {
                        return ls.data() != s;
                    }

                    friend bool operator < (CRef<istring> ls, CPtr<value_type> s)
                    {
                        return ls.data() < s;
                    }

                    friend bool operator <= (CRef<istring> ls, CPtr<value_type> s)
                    {
                        return ls.data() <= s;
                    }

                    friend bool operator > (CRef<istring> ls, CPtr<value_type> s)
                    {
                        return ls.data() > s;
                    }

                    friend bool operator >= (CRef<istring> ls, CPtr<value_type> s)
                    {
                        return ls.data() >= s;
                    }

                    friend Ref<std::ostream> operator << (Ref<std::ostream> os, CRef<istring> str)
                    {
                        os << str._data;
                        return os;
                    }

                    friend Ref<std::istream> operator >> (Ref<std::istream> is, Ref<istring> str)
                    {
                        is >> str._data;
                        return is;
                    }

                    Ref<istring> operator << (CRef<istring> str)
                    {
                        return this->append(str);
                    }

                    Ref<istring> operator << (CPtr<value_type> s)
                    {
                        return this->append(s);
                    }

                    Ref<istring> operator << (CRef<std::string> str)
                    {
                        return this->append(str);
                    }

                    Ref<istring> operator << (value_type ch)
                    {
                        return this->append(ch);
                    }

                    Ref<istring> operator << (int i)
                    {
                        return this->append(i);
                    }

                    Ref<istring> operator << (i::core::uint ui)
                    {
                        return this->append(ui);
                    }

                    Ref<istring> operator << (long l)
                    {
                        return this->append(l);
                    }

                    Ref<istring> operator << (i::core::ulong ul)
                    {
                        return this->append(ul);
                    }

                    Ref<istring> operator << (long long ll)
                    {
                        return this->append(ll);
                    }

                    Ref<istring> operator << (i::core::uint64 ull)
                    {
                        return this->append(ull);
                    }

                    Ref<istring> operator << (float f)
                    {
                        return this->append(f);
                    }

                    Ref<istring> operator << (double d)
                    {
                        return this->append(d);
                    }

                    Ref<istring> operator << (std::initializer_list<value_type> ilist)
                    {
                        return this->append(ilist);
                    }

                    friend istring operator + (CRef<istring> ls, CRef<istring> rs)
                    {
                        istring str(ls);
                        str.append(rs);
                        return str;
                    }

                    friend istring operator + (RRef<istring> ls, CRef<istring> rs)
                    {
                        ls.append(rs);
                        return ls;
                    }

                    friend istring operator + (RRef<istring> ls, RRef<istring> rs)
                    {
                        ls.append(rs);
                        return ls;
                    }

                    friend istring operator + (CRef<istring> ls, CPtr<value_type> s)
                    {
                        istring str(ls);
                        str.append(s);
                        return str;
                    }

                    friend istring operator + (RRef<istring> ls, CPtr<value_type> s)
                    {
                        ls.append(s);
                        return ls;
                    }

                    friend istring operator + (CRef<istring> ls, value_type ch)
                    {
                        istring str(ls);
                        str.pushBack(ch);
                        return str;
                    }

                    friend istring operator + (RRef<istring> ls, value_type ch)
                    {
                        ls.pushBack(ch);
                        return ls;
                    }

                    friend istring operator + (CRef<istring> ls, std::initializer_list<value_type> ilist)
                    {
                        istring str(ls);
                        str.append(ilist);
                        return str;
                    }

                    friend istring operator + (RRef<istring> ls, std::initializer_list<value_type> ilist)
                    {
                        ls.append(ilist);
                        return ls;
                    }

                    friend istring operator + (value_type ch, CRef<istring> rs)
                    {
                        istring str(1, ch);
                        str.append(rs);
                        return str;
                    }

                    friend istring operator + (value_type ch, RRef<istring> rs)
                    {
                        istring str(1, ch);
                        str.append(rs);
                        return str;
                    }

                    friend istring operator + (CPtr<value_type> s, CRef<istring> rs)
                    {
                        istring str(s);
                        str.append(rs);
                        return str;
                    }

                    friend istring operator + (CPtr<value_type> s, RRef<istring> rs)
                    {
                        istring str(s);
                        str.append(rs);
                        return str;
                    }

                    friend istring operator + (std::initializer_list<value_type> ilist, CRef<istring> rs)
                    {
                        istring str(ilist);
                        str.append(rs);
                        return str;
                    }

                    friend istring operator + (std::initializer_list<value_type> ilist, RRef<istring> rs)
                    {
                        istring str(ilist);
                        str.append(rs);
                        return str;
                    }

                public:

                    template<class...Args>
                    size_t findFirstOf(Args...args)
                    {
                        return _data.find_first_of(args...);
                    }

                public:

                    bool operator<=> (CRef<istring>) const = default;

                protected:

                private:
                    std::string _data;

                };//class istring final

            }//SPACE(text)
        }//SPACE(data)
    }//SPACE(core)
}//SPACE(i)

#ifdef INCLUDE_NLOHMANN_JSON_HPP_

SPACE(nlohmann)
{

    //inline void to_json(_ISTD Ref<nlohmann::json> j, _ISTD CRef<_ISTDTEXT istring> value)
    //{
    //    j = value.data();
    //}

    inline void from_json(nlohmann::json j, _ISTD Ref<_ISTDTEXT istring> value)
    {
        value = j.get<std::string>();
    }

}

#endif//^^^^INCLUDE_NLOHMANN_JSON_HPP_
