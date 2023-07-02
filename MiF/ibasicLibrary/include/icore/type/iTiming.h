/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：timing.hpp
* @创建时间：2022.10.01.11:38
* @创建者：HapiFive
* -----------------------------------------------------------------------------
*
*
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.h>
#include <chrono>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(type)
        {
            class IAPI iTiming
                :public core::basic::iBasic<iTiming>
            {
                using istring = data::text::istring;

                iObject(iTiming);
            public:

                iTiming(long long _millisecond);

                ~iTiming();

            public:

                bool expire()const;

            private:
                std::chrono::steady_clock::time_point __begin;
                long long __millisecond;
            };

        }//SPACE(type)
    }//SPACE(core)
}//SPACE(i)

