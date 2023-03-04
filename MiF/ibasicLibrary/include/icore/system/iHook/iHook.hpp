/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：IhOOK.hpp
* @创建时间：2022.10.3.21:12
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* iHookAPI
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#define _USE_WINDOWS_H__

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasic.hpp>
#include <icore/exception/error.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <map>
#include <set>
#include <utility>
#include <detours/detours.h>

#ifdef _DEBUG
#if __WIN64__
#pragma comment(lib,"../../../../third-party/detours/Dlib/libx64/detours.lib")
#else//__WIN64__
#pragma comment(lib,"../../../../third-party/detours/Dlib/libx86/detours.lib")
#endif//!__WIN64__
#else//DEBUG
#if __WIN64__
#pragma comment(lib,"../../../../third-party/detours/Rlib/libx64/detours.lib")
#else//__WIN64__
#pragma comment(lib,"../../../../third-party/detours/Rlib/libx86/detours.lib")
#endif//!__WIN64__
#endif//!DEBUG


SPACE(i)
{
	SPACE(core)
	{
		SPACE(System)
		{



		}//SPACE(System)
	}//SPACE(core)
}//SPACE(i)


