/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：concepts.hpp
* @创建时间：2022.4.30.12:12
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* 一些concept
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/type/type/type_traits.hpp>

#ifndef __CPP_20__
#pragma message("The contents of <concepts> are available only with C++20 concepts support.")
#else

#include <concepts>

SPACE(i)
{
    SPACE(core)
    {
        template <typename _Ty>
        concept Arithmetic = std::is_arithmetic<_Ty>::value;

        template <typename _Ty>
        concept StdString = i::core::type::type_traits::is_std_string_v<_Ty>;

        template <typename _Ty>
        concept Numeric = std::is_integral_v<_Ty> || std::is_floating_point_v<_Ty>;

        template<typename _Ty>
        concept HasDataFunction = requires(_Ty t)
        {
            t.data();
        };

        template<typename _Ty>
        concept Has2StdStringFunction = requires(_Ty t)
        {
            t.toStdString();
        };

        template<typename _Ty>
        concept HasNo2StdStringFunction = requires(_Ty t)
        {
            requires !t.toStdString();
        };

        template<typename _Ty>
        concept Has2iStringFunction = requires(_Ty t)
        {
            t.toiString();
        };

        template<typename _Ty>
        concept HasNo2iStringFunction = requires(_Ty t)
        {
            requires !t.toiString();
        };

    }//SPACE(core)
}//SPACE(i)

#endif//!__CPP_20__
