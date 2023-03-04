/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：time.hpp
* @创建时间：2022.6.28.21:26
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
*
*
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#pragma warning(disable:4996)
#pragma warning(disable:4819)
#pragma warning(disable:4244)

#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.hpp>

#ifdef __WINDOWS__
#include <windows.h>
#endif

#include <chrono>
#include <ctime>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(type)
        {

            struct time_s
            {
                ushort years = 0;//年
                ushort months = 0;//月
                ushort days = 0;//日
                ushort weeks = 0;//星期
                ushort hours = 0;//时
                ushort minutes = 0;//分
                ushort seconds = 0;//秒
                ushort milliseconds = 0;//毫秒
                ushort microseconds = 0;//微秒
                ushort nanoseconds = 0;//纳秒
                ushort yday = 0;//一年中的第n天
                int isdst = 0;//是否启用夏令时
            };

            class iTime
                :public core::basic::iBasic<iTime>
            {
                using istring = data::text::istring;

                iObject(iTime);
            public:

                iTime(time_s _time = {})
                    :__stime(_time)
                { }

                ~iTime()
                { }

            public:

                void getTimeNow()
                {
                    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

                    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
                    Ptr<std::tm> now_tm = std::localtime(&now_time_t);
                    __stime.years = now_tm->tm_year + 1900;
                    __stime.months = now_tm->tm_mon + 1;
                    __stime.days = now_tm->tm_mday;
                    __stime.weeks = now_tm->tm_wday + 1;
                    __stime.hours = now_tm->tm_hour;
                    __stime.minutes = now_tm->tm_min;
                    __stime.seconds = now_tm->tm_sec;

                    __stime.yday = now_tm->tm_yday;
                    __stime.isdst = now_tm->tm_isdst;

                    std::chrono::milliseconds ms;
                    std::chrono::microseconds cs;
                    std::chrono::nanoseconds ns;

                    ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
                    cs = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;
                    ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()) % 1000000000;

                    __stime.milliseconds = ms.count();
                    __stime.microseconds = cs.count() % 1000;
                    __stime.nanoseconds = ns.count() % 1000;
                }

                istring getFormatTime(CRef<istring> fmtstr = "{0}.{1}.{2}.{4}:{5}:{6}:{7}:{8}:{9} {3}-{10}-{11}")const
                {
                    return istring::format(fmtstr,
                        /*0*/__stime.years,
                        /*1*/__stime.months,
                        /*2*/__stime.days,
                        /*3*/__stime.weeks,
                        /*4*/__stime.hours,
                        /*5*/__stime.minutes,
                        /*6*/__stime.seconds,
                        /*7*/__stime.milliseconds,
                        /*8*/__stime.microseconds,
                        /*9*/__stime.nanoseconds,
                        /*10*/__stime.yday,
                        /*11*/__stime.isdst);
                }

                time_s data()const
                {
                    return __stime;
                }

                void set(time_s _stime)
                {
                    __stime = _stime;
                }

                void setTime(time_s _stime)
                {
                    __stime = _stime;
                }

            public:

            public:

            protected:
            private:
                time_s __stime;
            };



        }//SPACE(type)
    }//SPACE(core)
}//SPACE(i)

