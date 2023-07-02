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
#include <icore/data/text/istring.h>

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

            class IAPI iTime
                :public core::basic::iBasic<iTime>
            {
                using istring = data::text::istring;

                iObject(iTime);
            public:

                iTime(time_s _time = {});

                ~iTime();

            public:

                void getTimeNow();

                istring getFormatTime(CRef<istring> fmtstr = "{0}.{1}.{2}.{4}:{5}:{6}:{7}:{8}:{9} {3}-{10}-{11}")const;

                time_s data()const;

                void set(time_s _stime);

                void setTime(time_s _stime);

            public:

                static bool isLeapYear(int year)
                {
                    if (year % 4 != 0)
                    {
                        return false;
                    }
                    else if (year % 100 != 0)
                    {
                        return true;
                    }
                    else if (year % 400 == 0)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }

                time_s operator+(const time_s& t1)
                {
                    time_s result;
                    result.nanoseconds = __stime.nanoseconds + t1.nanoseconds;
                    result.microseconds = __stime.microseconds + t1.microseconds + result.nanoseconds / 1000;
                    result.nanoseconds = result.nanoseconds % 1000;
                    result.milliseconds = __stime.milliseconds + t1.milliseconds + result.microseconds / 1000;
                    result.microseconds = result.microseconds % 1000;
                    result.seconds = __stime.seconds + t1.seconds + result.milliseconds / 1000;
                    result.milliseconds = result.milliseconds % 1000;
                    result.minutes = __stime.minutes + t1.minutes + result.seconds / 60;
                    result.seconds = result.seconds % 60;
                    result.hours = __stime.hours + t1.hours + result.minutes / 60;
                    result.minutes = result.minutes % 60;
                    result.weeks = __stime.weeks + t1.weeks;
                    result.days = __stime.days + t1.days + result.weeks * 7;
                    while (result.days > 365)
                    {
                        result.years++;
                        if (isLeapYear(result.years))
                        {
                            result.days -= 366;
                        }
                        else
                        {
                            result.days -= 365;
                        }
                    }
                    while (result.days < 0)
                    {
                        result.years--;
                        if (isLeapYear(result.years))
                        {
                            result.days += 366;
                        }
                        else
                        {
                            result.days += 365;
                        }
                    }
                    int leap = isLeapYear(result.years);
                    int days_in_month[] = { 0, 31, 28 + leap, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
                    result.months = __stime.months + t1.months;
                    while (result.months > 12)
                    {
                        result.years++;
                        result.months -= 12;
                    }
                    while (result.months < 1)
                    {
                        result.years--;
                        result.months += 12;
                    }
                    result.days += __stime.yday + t1.yday;
                    while (result.days > days_in_month[result.months])
                    {
                        result.days -= days_in_month[result.months];
                        result.months++;
                        if (result.months > 12)
                        {
                            result.years++;
                            result.months -= 12;
                        }
                    }
                    while (result.days < 1)
                    {
                        result.months--;
                        if (result.months < 1)
                        {
                            result.years--;
                            result.months += 12;
                        }
                        result.days += days_in_month[result.months];
                    }
                    result.yday = result.days;
                    for (int i = 1; i < result.months; i++)
                    {
                        result.yday += days_in_month[i];
                    }
                    if (result.yday > 365 + leap)
                    {
                        result.yday -= 365 + leap;
                        result.years++;
                        leap = isLeapYear(result.years);
                    }
                    if (result.yday == 0 && leap)
                    {
                        result.yday = 366;
                    }
                    result.isdst = __stime.isdst | t1.isdst;
                    return result;
                }
            public:

            protected:
            private:
                time_s __stime;
            };



        }//SPACE(type)
    }//SPACE(core)
}//SPACE(i)

