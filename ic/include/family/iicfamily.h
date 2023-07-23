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
#include <icore/family/imacrofamily.h>

#ifdef ___STATICLIB___
#define ICAPI
#elif defined(__MSVC__)

#ifdef ___ICEXPORT___
#define ICAPI _declspec(dllexport)
#else
#define ICAPI _declspec(dllimport)
#endif

#define ICAPIAPI_EXPORT _declspec(dllexport)
#define ICAPIAPI_IMPORT _declspec(dllimport)

#elif defined(__GCC__)
#define ICAPI __attribute__((visibility("default")))
#else
#define ICAPI
#endif
