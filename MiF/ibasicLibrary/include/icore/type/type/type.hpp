/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：type.hpp
* @创建时间：2022.4.30.12:06
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* i类型
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#include <icore/family/imacrofamily.h>
#include <windows.h>
#include <stringapiset.h>
#include <string>
#include <algorithm>
#include <typeinfo>

SPACE(i)
{
	SPACE(core)
	{

		enum class TypeList
			:int
		{
			unkType = -1,
			iclass,
			itype,
			ibasic,
			ibasic_data_type,
			iMain,
			iErrorInfo,
			error,
			iErrorCode_,
			iCreateErrorFailed,
			iIndexOutOfBounds,
			_p_start,
			is_std_string,
			arithmetic,
			stdString,
			is_std_string_v,
			iRGB,
			iRGBA,
			iColor,
			iColors,
			iImageType,
			iConsoleTargetType,
			iGradient,
			ifPos,
			iFilePos,
			istring,
			iwstring,
			iu8string,
			iu16string,
			iu32string,
			iLevel,
			itime_s,
			iTime,
			iTiming,
			iRect,
			iConsoleType,
			iConsole,
			iFileInfo,
			iShellLinkFile,
			iMatrix,
			iVec2,
			iVec3,
			iVec4,
			iComplex,
			iQuadraticRadical,
			iFraction,
			iAngle,
			iLine,
			iLineF,
			iPoint,
			iPointF,
			iTriangle,
			iRectangle,
			iRectangleF,
			iSquare,
			iPoint3D,
			iLine3D,
			iCuboid,
			iCube,
			iBigInteger,
			iBigDecimal,
			iProcess,
			iPosition,
			iLibrary,
			iRedirection,
			iFindCtrl,
			iForm,
			iWindows,
			iSystem,
			iDir,
			iPath,
			iFile,
			iEaseCurve,
			iGenerator,
			iChar,
			iEncoding,
			iRBStream,
			iWBStreamImpl,
			iBinVariant,
			iLogger,
			iCriticalSectionLock,
			iCriticalSectionLockHolder
		};//ECLASS(TypeList)

		using iType = TypeList;


		class itype
		{
		public:

			itype() :mType(iType::unkType)
			{ }

			itype(iType t) :mType(t)
			{ }

			itype(CRef<itype>) = delete;

			void operator=(CRef<itype>) = delete;

			~itype()
			{ }

		public:

			/****
			* @author Lovelylavender4
			* @since 2022.6.21.13:25
			* @brief 获取类型枚举
			*
			* @retval 获取到的类型枚举
			*
			* @par Example
			* @code
			* 代码示例
			* @endcode
			*
			* @include -
			* @details
			* 获取类型枚举
			* @enddetails
			****/
			virtual itype getType()const
			{
				return TypeList::itype;
			}

			virtual iType data()const
			{
				return mType;
			}

			/****
			* @author Lovelylavender4
			* @since 2022.6.21.13:28
			* @brief 设置mType的值
			*
			* @param t mType的新值
			*
			* @par Example
			* @code
			* 代码示例
			* @endcode
			*
			* @include -
			* @details
			* 设置mType的值
			* @enddetails
			****/
			void setData(iType t)
			{
				mType = t;
			}

		public:

			/****
			* @author Lovelylavender4
			* @since 2022.6.21.13:30
			* @brief 获取类型枚举的字符串名称
			*
			* @param t 类型枚举
			* @retval 类型枚举的字符串名称
			*
			* @par 示例
			* @code
			* 代码示例
			* @endcode
			*
			* @details
			* 获取类型枚举的字符串名称
			* @enddetails
			****/
			static CPtr<char> getString(iType t)
			{
				switch (t)
				{
				case iType::unkType:
				{
					return "unkType";
				}
				case iType::itype:
				{
					return "itype";
				}
				case iType::istring:
				{
					return "istring";
				}
				default:
				{
					return "unk-Type";
				}
				}
			}

			/****
			* @author Lovelylavender4
			* @since 2022.6.21.13:34
			* @brief 获取类型的字符串名称
			*
			* @tparam Type 类型
			* @retval 类型的字符串名称
			*
			* @par Example
			* @code
			* 代码示例
			* @endcode
			*
			* @include 需要包含的头文件
			* @details
			* 获取类型的字符串名称
			* @enddetails
			****/
			template<typename Type>
			static CPtr<char> getTypeString()
			{
				return typeid(Type).name();
			}

			/****
			* @author Lovelylavender4
			* @since 2022.6.21.13:35
			* @brief 获取类型的字符串名称
			*
			* @param t -
			* @retval 类型的字符串名称
			*
			* @par Example
			* @code
			* 代码示例
			* @endcode
			*
			* @include -
			* @details
			* 获取类型的字符串名称
			* @enddetails
			****/
			template<typename Type>
			static CPtr<char> getTypeString(Type t)
			{
				return typeid(t).name();
			}

			template <typename T>
			constexpr const std::type_info& getTypeId(T&& t)
			{
				return typeid(std::forward<T>(t));
			}

			template <typename T>
			std::string getTypeName(T&& t)
			{
				return std::string{ getTypeId(std::forward<T>(t)).name() };
			}

#ifdef __cpp_char8_t
			template <typename T>
			std::u8string getTypeU8strName(T&& t)
			{
				const std::string cstr{ getTypeId(std::forward<T>(t)).name() };
				std::u8string u8str{};
				u8str.reserve(cstr.length() + 1);
				std::transform(std::cbegin(cstr), std::cend(cstr), std::begin(u8str),
					[](const auto ch)
					{
						return static_cast<char8_t>(ch);
					});
				return u8str;
			}
#endif

			template <typename T>
			std::wstring getTypeWStrName(T&& t)
			{
				const std::string cstr{ getTypeId(std::forward<T>(t)).name() };
				std::wstring wstr{};
				wstr.reserve(cstr.length() + 1);
				std::transform(std::cbegin(cstr), std::cend(cstr), std::begin(wstr),
					[](const auto ch)
					{
						return static_cast<wchar_t>(ch);
					});
				return wstr;
			}

			template <typename T>
			std::u16string getTypeU16strName(T&& t)
			{
				const std::string cstr{ getTypeId(std::forward<T>(t)).name() };
				std::u16string u16str{};
				u16str.reserve(cstr.length() + 1);
				std::transform(std::cbegin(cstr), std::cend(cstr), std::begin(u16str),
					[](const auto ch)
					{
						return static_cast<char16_t>(ch);
					});
				return u16str;
			}

			template <typename T>
			std::u32string getTypeU32strName(T&& t)
			{
				const std::string cstr{ getTypeId(std::forward<T>(t)).name() };
				std::u32string u32str{};
				u32str.reserve(cstr.length() + 1);
				std::transform(std::cbegin(cstr), std::cend(cstr), std::begin(u32str),
					[](const auto ch)
					{
						return static_cast<char32_t>(ch);
					});
				return u32str;
			}



		protected:
		private:
			iType mType;
		};//class itype


	}//SPACE(core)
}//SPACE(i)
