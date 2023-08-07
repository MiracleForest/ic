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
#pragma warning(disable:4251)

#include <icore/family/imacrofamily.h>
#include <icore/data/text/iChar.h>
#include <icore/data/text/iEncoding.h>
#include <sstream>
#include <iostream>
#include <regex>
#include <set>
#include <list>
#include <map>
#include <iomanip>
#include <string_view>
#include <format>
#include <codecvt>

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

                class IAPI istring final
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

                    istring();

                    explicit istring(CRef<std::string> str);

                    explicit istring(RRef<std::string> str) noexcept;

                    istring(size_type count, value_type ch);

                    istring(CRef<istring> other, size_type pos, size_t count);

                    istring(CRef<istring> other, size_type pos);

                    istring(CPtr<value_type> s, size_type count);

                    istring(CPtr<value_type> s);

                    template<typename T>
                    istring(T s)
                    {
                        if constexpr (std::is_same<std::string, T>::value ||
                            std::is_same<std::string_view, T>::value)
                        {
                            _data = s;
                        }
                        else
                        {
                            _data = toStdString(s);
                        }
                    }

                    istring(iChar ichar);

                    istring(CRef<istring> other);

                    istring(CRef<std::wstring> other);

                    istring(RRef<istring> other) noexcept;

                    istring(std::initializer_list<value_type> ilist);

                    template<class InputIt> istring(InputIt first, InputIt last)
                        : _data(first, last)
                    { }

                    ~istring();

                public:
                    /****
                    * @author ticks
                    * @since 22-6-23 上午11:59
                    * @brief 赋值
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
                    Ref<istring> assign(size_type count, value_type ch);

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
                    Ref<istring> assign(CRef<istring> str);

                    Ref<istring> assign(CRef<istring> str, size_type pos, size_type count);

                    Ref<istring> assign(CRef<istring> str, size_type pos);

                    Ref<istring> assign(RRef<istring> str) noexcept;

                    Ref<istring> assign(CPtr<value_type> s, size_type count);

                    Ref<istring> assign(CPtr<value_type> s);

                    Ref<istring> assign(std::initializer_list<value_type> ilist);

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
                    allocator_type getAllocator() const;

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
                    reference charAt(size_type pos);

                    const_reference charAt(size_type pos) const;

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
                    reference front();

                    const_reference front() const;

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
                    reference back();

                    const_reference back() const;

                    virtual std::string data()const;

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
                    CPtr<value_type> cStr() const noexcept;

                    /****
                    * @author ticks
                    * @since 22-6-23 下午12:59
                    * @brief 获取字符串开始迭代器
                    ****/
                    iterator begin() noexcept;

                    const_iterator begin() const noexcept;

                    const_iterator cbegin() const noexcept;

                    /****
                    * @author ticks
                    * @since 22-6-23 下午1:01
                    * @brief 获得 istring 的最后一个迭代器
                    ****/
                    iterator end() noexcept;

                    const_iterator end() const noexcept;

                    const_iterator cend() const noexcept;

                    reverse_iterator rbegin() noexcept;

                    const_reverse_iterator rbegin() const noexcept;

                    const_reverse_iterator crbegin() const noexcept;

                    reverse_iterator rend() noexcept;

                    const_reverse_iterator rend() const noexcept;

                    const_reverse_iterator crend() const noexcept;

                    bool empty() const noexcept;

                    size_type length() const noexcept;

                    size_type size() const noexcept;

                    size_type maxSize() const noexcept;

                    void reserve(size_type new_cap = static_cast<size_type>(0));

                    size_type capacity() const noexcept;

                    void fitAllocSize();

                    void clear() noexcept;

                    Ref<istring> insert(size_type pos, size_type count, value_type ch);

                    Ref<istring> insert(size_type pos, CPtr<value_type> s, size_type count);

                    Ref<istring> insert(size_type pos, CPtr<value_type> s);

                    Ref<istring> insert(size_type pos, CRef<istring> str);

                    Ref<istring> insert(size_type pos, CRef<istring> str, size_type str_pos, size_type str_count);

                    Ref<istring> insert(size_type pos, CRef<istring> str, size_type str_pos);

                    iterator insert(const_iterator pos, value_type ch);

                    iterator insert(const_iterator pos, size_type count, value_type ch);

                    iterator insert(const_iterator pos, std::initializer_list<value_type> ilist);

                    template<class InputIt> iterator insert(const_iterator pos, InputIt first, InputIt last)
                    {
                        return this->_data.insert(pos, first, last);
                    }

                    Ref<istring> erase(size_type pos = 0, size_type count = istring::npos);

                    iterator erase(const_iterator pos);

                    iterator erase(const_iterator first, const_iterator last);

                    void pushBack(value_type ch);

                    /****
                    * @author ticks
                    * @brief 移除istring最后一个字符
                    *
                    * @warning if istring length() == 0 , the behavior is undefined
                    ****/
                    void popBack();

                    Ref<istring> append(size_type count, value_type ch);

                    Ref<istring> append(CRef<istring> str);

                    Ref<istring> append(RRef<istring> str);

                    Ref<istring> append(CRef<std::string> str);

                    Ref<istring> append(CRef<istring> str, size_type pos, size_type count);

                    Ref<istring> append(CRef<istring> str, size_type pos);

                    Ref<istring> append(CPtr<value_type> s, size_type count);

                    Ref<istring> append(CPtr<value_type> s);

                    Ref<istring> append(std::initializer_list<value_type> ilist);

                    Ref<istring> append(value_type ch);

                    template <typename InputIt> Ref<istring> append(InputIt first, InputIt last)
                    {
                        this->_data.append(first, last);
                        return *this;
                    }

                    Ref<istring> append(int i);

                    Ref<istring> append(i::core::uint ui);

                    Ref<istring> append(long l);

                    Ref<istring> append(i::core::ulong ul);

                    Ref<istring> append(long long ll);

                    Ref<istring> append(i::core::uint64 ull);

                    Ref<istring> append(float f);

                    Ref<istring> append(double d);

                    istring substr(size_type start = 0, size_type length = istring::npos);

                    /****
                    * @author ticks
                    * @brief copy istring [pos, count) str to dest
                    *
                    * @throws std::out_of_range :  if pos > length()
                    ****/
                    size_type copy(Ptr<value_type> dest, size_type count, size_type pos = 0) const;

                    void resize(size_type count);

                    void resize(size_type count, value_type ch);

                    void swap(Ref<istring> other);

                    size_type find(CRef<istring> str, size_type pos = 0) const;

                    size_type find(CPtr<value_type> s, size_type pos, size_type count) const;

                    size_type find(CPtr<value_type> s, size_type pos = 0) const;

                    size_type find(value_type ch, size_type pos = 0) const;

                    size_type rfind(CRef<istring> str, size_type pos = istring::npos) const;

                    size_type rfind(CPtr<value_type> s, size_type pos, size_type count) const;

                    size_type rfind(CPtr<value_type> s, size_type pos = istring::npos) const;

                    size_type rfind(value_type ch, size_type pos = istring::npos) const;

                    bool startsWith(CRef<istring> str);

                    bool endsWith(CRef<istring> str);

                    bool match(CRef<std::basic_regex<value_type>> regex, bool search = false);

                public:

                    Ref<std::string> getDataRef();

                public:

                    static std::string toStdString(int value);

                    static std::string toStdString(uint value);

                    static std::string toStdString(long value);

                    static std::string toStdString(ulong value);

                    static std::string toStdString(int64 value);

                    static std::string toStdString(uint64 value);

                    static std::string toStdString(double value);

                    static std::string toStdString(float value);

                    static std::string toStdString(long double value);

                    static std::string toStdString(CPtr<char> value);

                    static std::string toStdString(char value);

                    static std::string toStdString(CRef<std::string> value);

                    static std::string toStdString(CPtr<char16_t> value);

                    static std::string toStdString(wchar_t value);

                    static std::string toStdString(CPtr<wchar_t> value);

                    static std::string toStdString(CRef<istring> value);

                    static std::string toStdString(__unk_type_v__ value);

#ifdef __cpp_lib_char8_t

                    static std::string toStdString(CRef<std::u8string> value);

#endif//^^^^__cpp_lib_char8_t^^^^

                    template<HasDataFunction _Ty> requires HasNo2StdStringFunction<_Ty>&& HasNo2iStringFunction<_Ty>
                    static std::string toStdString(CRef<_Ty> value)
                    {
                        if (std::convertible_to<typeof(value.data()), std::string>)
                        {
                            return toStdString(value.data());
                        }
                        else
                        {
                            return {};
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
                    * @include <list>,"istring.hpp"
                    ****/
                    static std::list<std::string> istringSplit2List(
                        CRef<istring> str,
                        CRef<istring> delimiters,
                        bool pushEmpty = false,
                        bool vInversion = false);

                    static std::vector<std::string> istringSplit2Vector(
                        CRef<istring> str,
                        CRef<istring> delimiters,
                        bool pushEmpty = false);

                    static std::wstring str2wstr(CRef<std::string> str);

                    static std::wstring str2wstr(CRef<std::string> str, i::core::uint codePage);

                    static Ptr<wchar> str2cwstr(CRef<std::string> str);

                    static std::string wstr2str(CRef<std::wstring> wstr);

                    static istring wstr2istr(CRef<std::wstring> wstr);

                    static std::string wstr2str(CRef<std::wstring> wstr, uint codePage);

                    static std::string u16str2str(CRef<std::u16string> u16str);

#ifdef __cpp_lib_char8_t

                    static std::string UTF82String(std::u8string str);

#endif //^^^^__cpp_lib_char8_t^^^^

                    static std::string UTF82String(std::string str);

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

                    static std::string makeSafeName(CRef<std::string> name);

                    static std::string eraseAll(CRef<std::string> str, CRef<std::string> subString);

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

                    static istring str2hex(istring s, bool upper = true);

                    static istring hex2str(istring s);

                    static void char2hex(char dat, Ptr<char> high_hex, Ptr<char> low_hex, bool upper = true);

                    static char hex2char(char high_hex, char low_hex);

                public:

                    /****
                    * @author Lovelylavender4
                    *
                    * @param delimiters
                    * @param pushEmpty = false
                    * @param vInversion = false
                    * @retval std::list<std::string>
                    ****/
                    std::list<std::string> split2List(
                        CRef<istring> delimiters,
                        bool pushEmpty = false,
                        bool vInversion = false);

                    std::vector<std::string> split2Vector(
                        CRef<istring> delimiters,
                        bool pushEmpty = false);

                    std::set<std::string> split2Set(
                        CRef<istring> delimiters,
                        bool pushEmpty = false);


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
                        std::string tmp;
                        while (std::getline(f, tmp, ':'))
                        {
                            elems.push_back(parse<T>(tmp));
                        }
                        return elems;
                    }

                    static istring toUpper(CRef<istring> str);

                    static istring toLower(CRef<istring> str);

                    static istring ltrim(CRef<istring> str);

                    static istring rtrim(CRef<istring> str);

                    static istring trim(CRef<istring> s);

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

                    static bool isAlphabetic(CRef<std::string> str1, CRef<std::string> str2);

                    static bool isMatch(CRef<std::string> pattern, CRef<std::string> string);

                    static bool isNum(CRef<std::string> string);

                    template<class...Args>
                    static istring format(CRef<istring> fmtstr, Args...args)
                    {
                        return std::vformat(toStdString(fmtstr.data()), std::make_format_args(toStdString(std::forward<Args>(args))...));
                    }

                public:

                    constexpr uint64_t doHash();

                    constexpr uint64 doHash2();

                public:

                    static constexpr uint64 doHash(CPtr<char> x, int len);

                    static constexpr uint64 doHash2(std::string_view x);

                    static constexpr uint64 doHash(CPtr<char> x);

                    static std::vector<std::string> splitStrWithPattern(CRef<std::string> str, CRef<std::string> pattern);

#pragma region 关于replace

                    Ref<istring> replace(size_type pos, size_type count, CRef<istring> str);

                    Ref<istring> replace(const_iterator first, const_iterator last, CRef<istring> str);

                    Ref<istring> replace(size_type pos, size_type count, CRef<istring> str,
                        size_type str_pos, size_type str_count = istring::npos);

                    template <typename InputIt>
                    Ref<istring> replace(const_iterator first, const_iterator last, InputIt first1, InputIt last1)
                    {
                        this->_data.replace(first, last, first1, last1);
                        return *this;
                    }

                    Ref<istring> replace(size_type pos, size_type count, CPtr<value_type> s, size_type s_count);

                    Ref<istring> replace(size_type pos, size_type count, CPtr<value_type> s);

                    Ref<istring> replace(const_iterator first, const_iterator last, CPtr<value_type> s);

                    Ref<istring> replace(size_type pos, size_type count, size_type ch_count, value_type ch);

                    Ref<istring> replace(const_iterator first, const_iterator last, size_type count, value_type ch);

                    Ref<istring> replace(const_iterator first, const_iterator last, std::initializer_list<value_type> ilist);

                    Ref<istring> replace(size_type pos, size_type count, std::initializer_list<value_type> ilist);

                public:

                    static bool replaceLast(Ref<istring> str, CRef<istring> oldStr, CRef<istring> newStr);

                    static bool replaceiStr(
                        Ref<istring> str,
                        CRef<istring> oldStr,
                        CRef<istring> newStr
                    );


                    static istring replaceiStr(
                        CRef<istring> istr,
                        CRef<istring> oldStr,
                        CRef<istring> newStr
                    );

                    static istring fixCurlyBracket(istring str);

                public:

                    void fixCurlyBracket();

                    bool replace(
                        CRef<istring> oldStr,
                        CRef<istring> newStr
                    );

                    bool replaceLast(CRef<istring> oldStr, CRef<istring> newStr);

#pragma endregion 关于replace

                public:

                    bool contains(CRef<istring> find);

                    bool isAlphabetic()const;

                    bool isMatch(CRef<std::string> pattern)const;

                    bool isNum()const;

                    Ref<istring> toUpper();

                    Ref<istring> toLower();

                    Ref<istring> ltrim();

                    Ref<istring> rtrim();

                    Ref<istring> trim();

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
                    istring toHexiStr();

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
                    istring toDeciStr();

                public:

                    Ref<istring> operator=(CRef<istring> str);

                    Ref<istring> operator=(RRef<istring> str)noexcept;

                    Ref<istring> operator=(CPtr<value_type> s);

                    Ref<istring> operator=(value_type ch);

                    Ref<istring> operator=(std::initializer_list<value_type> ilist);

                    reference operator[](size_type pos);

                    const_reference operator[](size_type pos) const;

                    Ref<istring> operator+=(CRef<istring> str);

                    Ref<istring> operator+=(value_type ch);

                    Ref<istring> operator+=(CPtr<value_type> s);

                    Ref<istring> operator+=(std::initializer_list<value_type> ilist);

                    friend bool operator==(CRef<istring> ls, CRef<istring> rs) noexcept
                    {
                        return ls._data == rs._data;
                    }

                    friend bool operator!=(CRef<istring> ls, CRef<istring> rs) noexcept
                    {
                        return ls._data != rs._data;
                    }

                    friend bool operator<(CRef<istring> ls, CRef<istring> rs) noexcept
                    {
                        return ls._data < rs._data;
                    }

                    friend bool operator<=(CRef<istring> ls, CRef<istring> rs) noexcept
                    {
                        return ls._data <= rs._data;
                    }

                    friend bool operator>(CRef<istring> ls, CRef<istring> rs) noexcept
                    {
                        return ls._data > rs._data;
                    }

                    friend bool operator>=(CRef<istring> ls, CRef<istring> rs) noexcept
                    {
                        return ls._data >= rs._data;
                    }

                    friend bool operator==(CPtr<value_type> s, CRef<istring> rs) noexcept
                    {
                        return s == rs._data;
                    }

                    friend bool operator==(CRef<istring> ls, CPtr<value_type> s)
                    {
                        return ls.cStr() == s;
                    }

                    friend bool operator!=(CRef<istring> ls, CPtr<value_type> s)
                    {
                        return ls.data() != s;
                    }

                    friend bool operator<(CRef<istring> ls, CPtr<value_type> s)
                    {
                        return ls.data() < s;
                    }

                    friend bool operator<=(CRef<istring> ls, CPtr<value_type> s)
                    {
                        return ls.data() <= s;
                    }

                    friend bool operator>(CRef<istring> ls, CPtr<value_type> s)
                    {
                        return ls.data() > s;
                    }

                    friend bool operator>=(CRef<istring> ls, CPtr<value_type> s)
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

                    Ref<istring> operator<<(CRef<istring> str);

                    Ref<istring> operator<<(CPtr<value_type> s);

                    Ref<istring> operator<<(CRef<std::string> str);

                    Ref<istring> operator<<(value_type ch);

                    Ref<istring> operator<<(int i);

                    Ref<istring> operator<<(i::core::uint ui);

                    Ref<istring> operator<<(long l);

                    Ref<istring> operator<<(i::core::ulong ul);

                    Ref<istring> operator<<(long long ll);

                    Ref<istring> operator<<(i::core::uint64 ull);

                    Ref<istring> operator<<(float f);

                    Ref<istring> operator<<(double d);

                    Ref<istring> operator<<(std::initializer_list<value_type> ilist);

                    friend istring operator+(CRef<istring> ls, CRef<istring> rs)
                    {
                        istring str(ls);
                        str.append(rs);
                        return str;
                    }

                    friend istring operator+(RRef<istring> ls, CRef<istring> rs)
                    {
                        ls.append(rs);
                        return ls;
                    }

                    friend istring operator+(RRef<istring> ls, RRef<istring> rs)
                    {
                        ls.append(rs);
                        return ls;
                    }

                    friend istring operator+(CRef<istring> ls, CPtr<value_type> s)
                    {
                        istring str(ls);
                        str.append(s);
                        return str;
                    }

                    friend istring operator+(RRef<istring> ls, CPtr<value_type> s)
                    {
                        ls.append(s);
                        return ls;
                    }

                    friend istring operator+(CRef<istring> ls, value_type ch)
                    {
                        istring str(ls);
                        str.pushBack(ch);
                        return str;
                    }

                    friend istring operator+(RRef<istring> ls, value_type ch)
                    {
                        ls.pushBack(ch);
                        return ls;
                    }

                    friend istring operator+(CRef<istring> ls, std::initializer_list<value_type> ilist)
                    {
                        istring str(ls);
                        str.append(ilist);
                        return str;
                    }

                    friend istring operator+(RRef<istring> ls, std::initializer_list<value_type> ilist)
                    {
                        ls.append(ilist);
                        return ls;
                    }

                    friend istring operator+(value_type ch, CRef<istring> rs)
                    {
                        istring str(1, ch);
                        str.append(rs);
                        return str;
                    }

                    friend istring operator+(value_type ch, RRef<istring> rs)
                    {
                        istring str(1, ch);
                        str.append(rs);
                        return str;
                    }

                    friend istring operator+(CPtr<value_type> s, CRef<istring> rs)
                    {
                        istring str(s);
                        str.append(rs);
                        return str;
                    }

                    friend istring operator+(CPtr<value_type> s, RRef<istring> rs)
                    {
                        istring str(s);
                        str.append(rs);
                        return str;
                    }

                    friend istring operator+(std::initializer_list<value_type> ilist, CRef<istring> rs)
                    {
                        istring str(ilist);
                        str.append(rs);
                        return str;
                    }

                    friend istring operator+(std::initializer_list<value_type> ilist, RRef<istring> rs)
                    {
                        istring str(ilist);
                        str.append(rs);
                        return str;
                    }

                public:

                    template<class...Args>
                    size_t findFirstOf(RRef<Args>...args)
                    {
                        return _data.find_first_of(std::forward<Args>(args)...);
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

#ifdef __LINUX__

static inline _ISTD unkType memcpy_s(
    _ISTD unkType dest,
    [[maybe_unused]] _ISTD ulong dest_size,
    _ISTD unkType src,
    _ISTD ulong src_size
)
{
    return memcpy(dest, src, src_size);
}

#endif//^^^^__LINUX__^^^^

#endif//^^^^INCLUDE_NLOHMANN_JSON_HPP_^^^^
