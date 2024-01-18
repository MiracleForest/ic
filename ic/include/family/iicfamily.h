/*
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iicfamily.h
 * @创建时间:2022.7.1.22:26
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iicfamily
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include <string>
#include <vector>

#ifdef ___STATICLIB___
#    define ICAPI
#elif defined(__MSVC__)

#    ifdef ___ICEXPORT___
#        define ICAPI _declspec(dllexport)
#    else
#        define ICAPI _declspec(dllimport)
#    endif

#    define ICAPIAPI_EXPORT _declspec(dllexport)
#    define ICAPIAPI_IMPORT _declspec(dllimport)

#elif defined(__GCC__)
#    define ICAPI __attribute__((visibility("default")))
#else
#    define ICAPI
#endif

template<typename _Type>
using Ptr = _Type*;

template<typename _Type>
using PPtr = _Type**;

template<typename _Type>
using CPtr = const _Type*;

template<typename _Type>
using CPPtr = const _Type**;

template<typename _Type>
using CRef = const _Type&;

template<typename _Type>
using CRRef = const _Type&&;

template<typename _Type>
using Ref = _Type&;

template<typename _Type>
using RRef = _Type&&;

namespace vector
{
template<class T>
bool contains(std::vector<T> v, T element)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == element) { return true; }
    }

    return false;
}
} // namespace vector

namespace string
{
inline bool replace(Ref<std::string> str, CRef<std::string> oldStr, CRef<std::string> newStr)
{
    bool    found = false;
    size_t  pos   = 0;
    while ((pos = str.find(oldStr.data(), pos)) != std::string::npos)
    {
        found = true;
        str.replace(pos, oldStr.length(), newStr.data());
        pos += newStr.length();
    }
    return found;
}
}