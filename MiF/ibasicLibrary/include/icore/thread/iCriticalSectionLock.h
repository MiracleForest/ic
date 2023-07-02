/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iCriticalSectionLock.hpp
* @创建时间：2023.1.9.15:41
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* csl
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#include <icore/family/imacrofamily.h>
#include <icore/type/type/type.h>
#include <icore/basic/iBasic.h>

#ifndef __WINDOWS__
#pragma message("The contents of <iCriticalSectionLock.h> are available only with WINDOWS support.")
#else
#include <Windows.h>
#include <minwinbase.h>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(thread)
        {

            class IAPI iCriticalSectionLock
                :public basic::iBasic<iCriticalSectionLock>
            {
                iObject(iCriticalSectionLock)
            public:

                iCriticalSectionLock();

                ~iCriticalSectionLock();

                bool tryLock();

                void lock();

                void unlock();

            private:
                bool _inited = false;
                CRITICAL_SECTION _cslock;
            };

            class IAPI iCriticalSectionLockHolder
                :public basic::iBasic<iCriticalSectionLockHolder>
            {
                iObject(iCriticalSectionLockHolder)
            public:

                iCriticalSectionLockHolder(Ref<iCriticalSectionLock> lock);

                ~iCriticalSectionLockHolder();

            private:
                Ref<iCriticalSectionLock> _locker;
            };

        }//SPACE(thread)
    }//SPACE(core)
}//SPACE(i)

#endif