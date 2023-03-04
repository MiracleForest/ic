/****
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名：imacrofamily.h
 * @创建时间：2022.5.2.17:09
 * @创建者：Lovelylavender4
 * -----------------------------------------------------------------------------
 * 此文件定义了一些全局性的宏，别名等
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 *
 ****/
#pragma once
#ifdef _MSVC_LANG
#define _STL_LANG _MSVC_LANG
#elif defined(__cplusplus) // ^^^ use _MSVC_LANG / use __cplusplus vvv
#define _STL_LANG __cplusplus
#else // ^^^ use __cplusplus / no C++ support vvv
#define _STL_LANG 0L
#endif // ^^^ no C++ support ^^^

#ifndef _HAS_CXX14
#if _STL_LANG > 201108L
#define _HAS_CXX14 true
#else
#define _HAS_CXX14 false
#endif
#endif // _HAS_CXX14

#ifndef _HAS_CXX17
#if _STL_LANG > 201402L
#define _HAS_CXX17 true
#else
#define _HAS_CXX17 false
#endif
#endif // _HAS_CXX17

#ifndef _HAS_CXX20
#if _HAS_CXX17 && _STL_LANG > 201703L
#define _HAS_CXX20 true
#else
#define _HAS_CXX20 false
#endif
#endif // _HAS_CXX20

#ifndef _HAS_CXX23
#if _HAS_CXX20 && _STL_LANG > 202002L
#define _HAS_CXX23 true
#else
#define _HAS_CXX23 false
#endif
#endif // _HAS_CXX23

#undef _STL_LANG

#if _HAS_CXX20 && !_HAS_CXX17
#error _HAS_CXX20 must imply _HAS_CXX17.
#endif

#if _HAS_CXX23 && !_HAS_CXX20
#error _HAS_CXX23 must imply _HAS_CXX20.
#endif

 /*------------------------编译器判断------------------------*/
#if defined(__ICC) || defined(__INTEL_COMPILER)
#define __ICC__ __INTEL_COMPILER
#elif defined(__clang__)
#define __CLANG__ __clang_version__
#elif defined(__GNUC__) || defined(__GNUG__)
#define __GCC__ 1
#define __GCCV__                                                               \
  std::to_string(__GNUC__) + "." + std::to_string(__GNUC_MINOR__) + "." +      \
      std::to_string(__GNUC_PATCHLEVEL__)
#elif defined(__HP_cc) || defined(__HP_aCC)
#define __HP__ true
#elif defined(__IBMCPP__)
#define __ILECPP__ __IBMCPP__
#elif defined(_MSC_VER)
#define __MSVC__ _MSC_VER
#elif defined(__PGI)
#define __PGCPP__ __PGI
#elif defined(__SUNPRO_CC)
#define __SUNPRO__ __SUNPRO_CC
#else
#define __UNKNOWN__ true
#endif

/*------------------------C++标准判断------------------------*/
#if !defined(__CPP_23__) && !defined(__CPP_20__) && !defined(__CPP_17__) &&    \
    !defined(__CPP_14__) && !defined(__CPP_11__)
#if _HAS_CXX23
#define __CPP_23__ true
#define __CPP_20__ true
#define __CPP_17__ true
#define __CPP_14__ true
#define __CPP_11__ true
#elif _HAS_CXX20
#define __CPP_20__ true
#define __CPP_17__ true
#define __CPP_14__ true
#define __CPP_11__ true
#elif _HAS_CXX17
#define __CPP_17__ true
#define __CPP_14__ true
#define __CPP_11__ true
#elif _HAS_CXX14
#define __CPP_14__ true
#define __CPP_11__ true
#else
#define __CPP_11__ true
#endif
#endif

/*------------------------平台的判断------------------------*/
#ifdef _WIN64
#define __WIN64__ true
#endif
#ifdef _WIN32
#define __WIN32__ true
#define __WINDOWS__ true
#elif defined __linux__
#define __LINUX__ true
#elif defined __APPLE__
#define __APPLE__ true
#elif defined __unix__
#define __UNIX__ true
#else
#define __UNK__ true
#endif

#ifdef _USE_WINDOWS_H__
#ifdef __WINDOWS__
#include <Windows.h>
#endif
#endif

/*------------------------数学------------------------*/

#define IS_FLOAT_DIFFERENT(a, b) (fabsf((a) - (b)) > FLT_EPSILON)
#define IS_FLOAT_EQUAL(a, b) (fabsf((a) - (b)) < FLT_EPSILON)
#define IS_DOUBLE_DIFFERENT(a, b) (fabs((a) - (b)) > DBL_EPSILON)
#define IS_DOUBLE_EQUAL(a, b) (fabs((a) - (b)) < DBL_EPSILON)

/*------------------------关于库------------------------*/
#ifdef ___STATICLIB___
#define IAPI
#elif defined(__MSVC__)

#ifdef ___ILIBRARYEXPORT___
#define IAPI _declspec(dllexport)
#else
#define IAPI _declspec(dllimport)
#endif

#define IAPI_EXPORT _declspec(dllexport)
#define IAPI_IMPORT _declspec(dllimport)

#elif defined(__GCC__)
#define IAPI __attribute__​((visibility(​ "​default​"​)))
#else
#define IAPI
#endif

/*------------------------类------------------------*/
#define _CGETVF(rt,cname,lname) rt get ## cname()const{return _ ## lname;}
#define _CSETVF(rt,pt,cname,lname) rt& set ## cname(_ISTD CRef<pt> lname){_ ## lname =lname;return *this;}
#define iObject(className) public:\
virtual itype getType()const{return iType::className;}\
virtual void destructor()const{className::~className();}\
private:

/*------------------------快捷------------------------*/
#define CATCH(x)                                                               \
  catch (...) {                                                                \
    printf(x);                                                                 \
  }
#define TCATCH(_try,x)                                                         \
  try{                                                                         \
    _try                                                                       \
  }                                                                            \
  catch (...) {                                                                \
    printf(x);                                                                 \
  }
#define IERROR ::i::core::iexception::error
#define SPACE(namespaceName) namespace namespaceName
#define SPACE_ namespace
#define ECLASS(className) enum class className
#define ECLASS_ enum class

#define _iError  i::core::iexception::error
#define _iErrorCode  i::core::iexception::ErrorCode
#define iMain(pname) iError i::core::Main::start(N_ISTD Ref<_p_start> pname)

/*------------------------命名空间------------------------*/
#define _ITYPE i::core::type::
#define _IBASIC i::core::type::basic::
#define _ISTDMATH i::core::math::
#define _ISTDGEOMETRY i::core::math::geometry::
#define _ISTD i::core::
#define _ISTDTEXT i::core::data::text::

/*------------------------时间------------------------*/
#define TMYEAR2CALENDAR(Y) ((Y) + 1970) //完整的四位数年份 
#define CALENDARYR2TM(Y) ((Y) - 1970)
#define TMYEAR2Y2K(Y) ((Y) - 30) // 偏移量是从2000年开始的
#define Y2KYEAR2TM(Y) ((Y) + 30)   

#define SECS_PER_MIN ((time_t)(60UL))//每分钟的秒数
#define SECS_PER_HOUR ((time_t)(3600UL))//每小时的秒数
#define SECS_PER_DAY ((time_t)(SECS_PER_HOUR * 24UL))//每天的秒数
#define DAYS_PER_WEEK ((time_t)(7UL))//每星期的天数
#define SECS_PER_WEEK ((time_t)(SECS_PER_DAY * DAYS_PER_WEEK))//每星期的秒数
#define SECS_YR_2000 ((time_t)(946684800UL))

#define NUMBEROfSECONDS(_time_) ((_time_) % SECS_PER_MIN)  
#define NUMBEROfMINUTES(_time_) (((_time_) / SECS_PER_MIN) % SECS_PER_MIN) 
#define NUMBEROfHOURS(_time_) (((_time_) % SECS_PER_DAY) / SECS_PER_HOUR)
#define DAYOFWEEK(_time_) ((((_time_) / SECS_PER_DAY + 4)  % DAYS_PER_WEEK)+1) // 1 = Sunday
#define ELAPSEDDAYS(_time_) ((_time_) / SECS_PER_DAY)  // this is number of days since Jan 1 1970
#define ELAPSEDSECS2DAY(_time_) ((_time_) % SECS_PER_DAY)   // the number of seconds since last midnight 

/*------------------------其他------------------------*/
#define LODWORD(x)  (*((_DWORD*)&(x)))  // low dword
#define HIDWORD(x)  (*((_DWORD*)&(x)+1))
#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define WORDn(x, n)   (*((_WORD*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)         // byte 1 (counting from 0)
#define BYTE2(x)   BYTEn(x,  2)
#define BYTE3(x)   BYTEn(x,  3)
#define BYTE4(x)   BYTEn(x,  4)
#define BYTE5(x)   BYTEn(x,  5)
#define BYTE6(x)   BYTEn(x,  6)
#define BYTE7(x)   BYTEn(x,  7)
#define BYTE8(x)   BYTEn(x,  8)
#define BYTE9(x)   BYTEn(x,  9)
#define BYTE10(x)  BYTEn(x, 10)
#define BYTE11(x)  BYTEn(x, 11)
#define BYTE12(x)  BYTEn(x, 12)
#define BYTE13(x)  BYTEn(x, 13)
#define BYTE14(x)  BYTEn(x, 14)
#define BYTE15(x)  BYTEn(x, 15)
#define WORD1(x)   WORDn(x,  1)
#define WORD2(x)   WORDn(x,  2)         // third word of the object, unsigned
#define WORD3(x)   WORDn(x,  3)
#define WORD4(x)   WORDn(x,  4)
#define WORD5(x)   WORDn(x,  5)
#define WORD6(x)   WORDn(x,  6)
#define WORD7(x)   WORDn(x,  7)

// now signed macros (the same but with sign extension)
#define SLOBYTE(x)   (*((int8*)&(x)))
#define SLOWORD(x)   (*((int16*)&(x)))
#define SLODWORD(x)  (*((int32*)&(x)))
#define SHIBYTE(x)   (*((int8*)&(x)+1))
#define SHIWORD(x)   (*((int16*)&(x)+1))
#define SHIDWORD(x)  (*((int32*)&(x)+1))
#define SBYTEn(x, n)   (*((int8*)&(x)+n))
#define SWORDn(x, n)   (*((int16*)&(x)+n))
#define SBYTE1(x)   SBYTEn(x,  1)
#define SBYTE2(x)   SBYTEn(x,  2)
#define SBYTE3(x)   SBYTEn(x,  3)
#define SBYTE4(x)   SBYTEn(x,  4)
#define SBYTE5(x)   SBYTEn(x,  5)
#define SBYTE6(x)   SBYTEn(x,  6)
#define SBYTE7(x)   SBYTEn(x,  7)
#define SBYTE8(x)   SBYTEn(x,  8)
#define SBYTE9(x)   SBYTEn(x,  9)
#define SBYTE10(x)  SBYTEn(x, 10)
#define SBYTE11(x)  SBYTEn(x, 11)
#define SBYTE12(x)  SBYTEn(x, 12)
#define SBYTE13(x)  SBYTEn(x, 13)
#define SBYTE14(x)  SBYTEn(x, 14)
#define SBYTE15(x)  SBYTEn(x, 15)
#define SWORD1(x)   SWORDn(x,  1)
#define SWORD2(x)   SWORDn(x,  2)
#define SWORD3(x)   SWORDn(x,  3)
#define SWORD4(x)   SWORDn(x,  4)
#define SWORD5(x)   SWORDn(x,  5)
#define SWORD6(x)   SWORDn(x,  6)
#define SWORD7(x)   SWORDn(x,  7)
#define _UNKNOWN char

#define EXPRESSIONSWITHCOMMAS(...) __VA_ARGS__

#include <stdint.h>

SPACE(i)
{
    SPACE(core)
    {

        using ushort = unsigned short;
        using sshort = signed short;
        using uint = unsigned int;
        using sint = signed int;
        using llong = long long;
        using ulong = unsigned long;
        using ullong = unsigned long long;
        using slong = signed long;
        using sllong = signed long long;
        using uchar = unsigned char;
        using schar = signed char;

        using __unk_type__ = void*;
        using unkType = void*;
        using handle = void*;
        using wchar = wchar_t;

#ifdef _USE_WINDOWS_H__
        using hmodule = HMODULE;
        using hrsrc = HRSRC;
        using hglobal = handle;
        using hwnd = HWND;
        using lresult = LRESULT;
        using wparam = WPARAM;
        using lparam = LPARAM;
        using lpcwstr = LPCWSTR;
#endif//_WINDOWS_

#ifdef __WINDOWS__

        using int64 = __int64;
        using uint64 = unsigned __int64;

#else  //__WINDOWS__
        using int64 = long long;
        using uint64 = unsigned long long;
#endif //!__WINDOWS__

        using _BYTE = uchar;
        using _WORD = ushort;
        using _DWORD = uint;
        using _QWORD = uint64;

#if !defined(_MSC_VER)
#define _OWORD __int128
#endif

        using VA = uint64;
        using RVA = uint;

        template <typename Type>
        using Ptr = Type*;

        template <typename Type>
        using DPtr = Type**;

        template <typename Type>
        using CPtr = const Type*;

        template <typename Type>
        using CDPtr = const Type**;

        template <typename Type>
        using CRef = const Type&;

        template <typename Type>
        using Ref = Type&;

        template <typename Type>
        using RRef = Type&&;

    } // SPACE(core)
} // SPACE(i)