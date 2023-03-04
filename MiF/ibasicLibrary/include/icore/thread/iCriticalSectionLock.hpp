/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iCriticalSectionLock.hpp
* @创建时间：2023.1.9.15:41
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
*
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#include <icore/family/imacrofamily.h>
#include <icore/type/type/type.hpp>
#include <icore/basic/iBasic.hpp>

#include <minwinbase.h>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(thread)
        {

            class iCriticalSectionLock
                :public basic::iBasic<iCriticalSectionLock>
            {
                iObject(iCriticalSectionLock)
            public:

                iCriticalSectionLock()
                {
                    if (!_inited)
                    {
                        _inited = true;
                        InitializeCriticalSection(&_cslock);
                    }
                }

                ~iCriticalSectionLock()
                {
                    if (_inited)
                    {
                        DeleteCriticalSection(&_cslock);
                    }
                }

                bool tryLock()
                {
                    if (!_inited)
                    {
                        _inited = true;
                        InitializeCriticalSection(&_cslock);
                    }
                    return TryEnterCriticalSection(&_cslock);
                }

                void lock()
                {
                    if (!_inited)
                    {
                        _inited = true;
                        InitializeCriticalSection(&_cslock);
                    }
                    EnterCriticalSection(&_cslock);
                }

                void unlock()
                {
                    LeaveCriticalSection(&_cslock);
                }

            private:
                bool _inited = false;
                CRITICAL_SECTION _cslock;
            };

            class iCriticalSectionLockHolder
                :public basic::iBasic<iCriticalSectionLockHolder>
            {
                iObject(iCriticalSectionLockHolder)
            public:

                iCriticalSectionLockHolder(Ref<iCriticalSectionLock> lock)
                    : _locker(lock)
                {
                    _locker.lock();
                }

                ~iCriticalSectionLockHolder()
                {
                    _locker.unlock();
                }

            private:
                Ref<iCriticalSectionLock> _locker;
            };

        }//SPACE(thread)
    }//SPACE(core)
}//SPACE(i)

