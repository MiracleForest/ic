/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：ibasic.hpp
* @创建时间：2022.4.30.11:53
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* 所有i类的基类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#include <icore/family/imacrofamily.h>
#include <icore/type/type/type.hpp>
#include <icore/type/type/concepts.hpp>
#include <functional>
#include <new>

SPACE(i)
{
	SPACE(core)
	{
		SPACE(basic)
		{

			enum class ClassMemberAccessRights
				:int
			{
				unk = -1,
				_public,
				_protected,
				_private
				/* unstd */
			};//enum class ClassMemberAccessRights :int

			enum class Retouchs
				:int
			{
				unk = -1,
				_static,
				_virtual,
				_friend,
				_const,
				_override,
				_delete,
				_default,
				_explicit,
				_mutable,
				___inline,
				_final,
				_constexpr,
				_consteval,
				_constinit,
				_export,
				_extern,
				_noexcept,
				_register,
				_signed,
				_unsigned,
				/* unstd */
				___event,
				___based,
				___single_inheritance,
				___multiple_inheritance,
				___virtual_inheritance,
				___ptr32,
				___ptr64,
				___restrict,
				___sptr,
				___uptr,
				___unaligned
			};//enum class Retouchs :int

			enum class CppFunctionCallRules
				:int
			{
				unk = -1,
				___cdecl,
				___stdcall,
				/* 0 */___pascal = 1,
				___fastcall,
				___thiscall,
				___naked,
				/* 1 */___usercall,
				/* unstd */
				___vectorcall
			};//enum class CppFunctionCallRules :int


			using ClassConstructorAccessRights = ClassMemberAccessRights;
			using ClassDestructorAccessRights = ClassMemberAccessRights;

			template<typename Type>
			class iBasic
			{
			public:
				virtual ~iBasic() = default;

				virtual itype getType()const = 0;

				virtual void destructor()const = 0;

				template<class...A>
				static std::function<Type()> constructNew(ClassMemberAccessRights c, A...a)
				{
					if (c == ClassConstructorAccessRights::_public || c == ClassConstructorAccessRights::unk)
					{
						return [a...]()
						{
							return Type(a...);
						};
					}
					return std::function<Type()>();
				}

				static void destroy(Type* pointer)
				{
					pointer->~Type();
				}

				static void destroy(Type& obj)
				{
					obj.~Type();
				}


			};//class iBasic


		}//SPACE(basic)
	}//SPACE(core)
}//SPACE(i)
