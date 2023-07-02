/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：type_traits.hpp
* @创建时间：2022.4.26.13:00
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* type traits
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#include <icore/family/imacrofamily.h>

#include <type_traits>
#include <string>


SPACE(i)
{
	SPACE(core)
	{
		SPACE(type)
		{
			SPACE(type_traits)
			{

				template <typename Type>
				struct is_std_string : std::false_type
				{ };

				template<>
				struct is_std_string<std::string> : std::true_type
				{ };

				template<>
				struct is_std_string<std::wstring> : std::true_type
				{ };

#ifdef __cpp_lib_char8_t
				template<>
				struct is_std_string<std::u8string> : std::true_type
				{ };
#endif


				template<>
				struct is_std_string<std::u16string> : std::true_type
				{ };

				template<>
				struct is_std_string<std::u32string> : std::true_type
				{ };

				template <typename Type>
				constexpr bool is_std_string_v = is_std_string<Type>::value;

				template <typename Type>
				struct is_a_char : std::false_type
				{ };

				template <>
				struct is_a_char<char> : std::true_type
				{ };

				template <>
				struct is_a_char<wchar_t> : std::true_type
				{ };

#ifdef __cpp_lib_char8_t
				template <>
				struct is_a_char<char8_t> : std::true_type
				{ };
#endif // __cpp_lib_char8_t

				template <>
				struct is_a_char<char16_t> : std::true_type
				{ };

				template <>
				struct is_a_char<char32_t> : std::true_type
				{ };

				template <typename Type>
				constexpr bool is_a_char_v = is_a_char<Type>::value;


			}//SPACE(type_traits)
		}//SPACE(type)
	}//SPACE(core)
}//SPACE(i)
