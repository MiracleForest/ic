/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iLogger.hpp
* @创建时间：2023.1.9.15:41
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* 日志类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/exception/error.h>
#include <icore/type/type/type.h>
#include <icore/data/text/istring.h>
#include <icore/console/iConsole.h>
#include <icore/type/iColor.h>
#include <icore/type/iTime.h>
#include <icore/file/iFilePos.h>
#include <icore/type/iLevel.h>
#include <icore/thread/iCriticalSectionLock.h>
#include <icore/file/iFile.h>
#include <filesystem>
#include <mutex>


SPACE(i)
{
	SPACE(core)
	{
		SPACE(io)
		{

			class IAPI iLogger
				: public basic::iBasic<iLogger>
			{
				iObject(iLogger);
				using istring = data::text::istring;
			public:

				iLogger(
					CRef<istring> loggerName,
					type::iLevel timeLevel = type::Level::A,
					CRef<istring> logDir = "null"
				);

				iLogger();

			public:

#ifdef __WINDOWS__

				Ref<thread::iCriticalSectionLock> getLocker();

#endif//^^^^__WINDOWS__^^^^

			public:

				_CGETVF(istring, Title, title);
				_CSETVF(iLogger, istring, Title, title);

				_CGETVF(istring, LogDir, logDir);
				_CSETVF(iLogger, istring, LogDir, logDir);

				_CGETVF(type::iLevel, TimeLevel, timeLevel);
				_CSETVF(iLogger, type::iLevel, TimeLevel, timeLevel);

			public:

#define ccolor(r,g,b) type::iColor::getConsoleColoriString({r,g,b})

				template<class...Args>
				void info(istring fmtstr, RRef<Args>...args)
				{
					_lock.lock();
					iConsole::writeLine(
						istring::format("{}{}{} Info {}[{}]:{}{}{}",
							ccolor(173, 216, 230),
							getTimeNow(),
							ccolor(148, 230, 207),
							ccolor(204, 204, 204),
							_title,
							ccolor(164, 164, 164),
							fmtstr,
							ccolor(255, 255, 255)
						), std::forward<Args>(args)...);
					output2file("[" + getTimeNow() + istring::format("][Info]:" + fmtstr, std::forward<Args>(args)...));
					_lock.unlock();
				}

				template<class...Args>
				void warn(istring fmtstr, RRef<Args>...args)
				{
					_lock.lock();
					iConsole::writeLine(
						istring::format("{}{}{} Warn {}[{}]:{}{}{}",
							ccolor(242, 242, 205),
							getTimeNow(),
							ccolor(242, 220, 100),
							ccolor(208, 242, 146),
							_title,
							ccolor(242, 239, 26),
							fmtstr,
							ccolor(255, 255, 255)
						), std::forward<Args>(args)...);
					output2file("[" + getTimeNow() + istring::format("][Warn]:" + fmtstr, std::forward<Args>(args)...));
					_lock.unlock();
				}

				template<class...Args>
				void error(istring fmtstr, RRef<Args>...args)
				{
					_lock.lock();
					iConsole::writeLine(
						istring::format("{}{}{} Error {}[{}]:{}{}{}",
							ccolor({ 242, 180, 180 }),
							getTimeNow(),
							ccolor({ 242, 68, 108 }),
							ccolor({ 242, 122, 122 }),
							_title,
							ccolor({ 242, 72, 72 }),
							fmtstr,
							ccolor({ 255, 255, 255 })
						), std::forward<Args>(args)...);
					output2file(
						"[" + getTimeNow() + istring::format("][Error]:" + fmtstr, std::forward<Args>(args)...));
					_lock.unlock();
				}

				template<class...Args>
				void note(istring fmtstr, RRef<Args>...args)
				{
					_lock.lock();
					type::iTime t;
					t.getTimeNow();
					auto time = t.data();

					iConsole::writeLine(
						istring::sumString(ccolor(255, 170, 255),
							time.years,
							ccolor(240, 24, 28),
							".",
							ccolor(170, 255, 255),
							time.months,
							ccolor(240, 24, 28),
							".",
							ccolor(170, 170, 255),
							time.days,
							ccolor(240, 24, 28),
							".",
							ccolor(134, 255, 217),
							time.hours,
							ccolor(240, 24, 28),
							":",
							ccolor(255, 105, 252),
							time.minutes,
							ccolor(240, 24, 28),
							":",
							ccolor(255, 240, 82),
							time.seconds,
							ccolor(240, 24, 28),
							":",
							ccolor(39, 215, 231),
							time.milliseconds,
							ccolor(255, 170, 255),
							" N",
							ccolor(69, 255, 240),
							"o",
							ccolor(255, 255, 0),
							"t",
							ccolor(67, 236, 62),
							"e ",
							ccolor(156, 248, 255),
							"[",
							ccolor(228, 131, 255),
							_title,
							ccolor(156, 248, 255),
							"]",
							ccolor(240, 24, 28),
							":",
							ccolor(137, 221, 255),
							fmtstr,
							ccolor(255, 255, 255)
						), std::forward<Args>(args)...);
					output2file("[" + getTimeNow() + istring::format("][Note]:" + fmtstr, std::forward<Args>(args)...));
					_lock.unlock();
				}

				template<class...Args>
				void debug(istring fmtstr, std::source_location sl, RRef<Args>...args)
				{
					_lock.lock();
					iConsole::writeLine(
						istring::sumString(ccolor({ 168, 255, 204 }),
							getTimeNow(),
							ccolor(0, 255, 0),
							" Debug ",
							ccolor(156, 248, 255),
#ifdef __WINDOWS__
							"[", _title, "][File:", _ISTDTEXT iEncoding::wideChar2ANSI(_ISTDTEXT iEncoding::UTF82wideChar(sl.file_name())), ":", sl.line(), ",",
							sl.column(), "][Func:", sl.function_name(), "]:",
#else//^^^^__WINDOWS__^^^^
							"[", _title, "][File:", sl.file_name(), ":", sl.line(), ",", sl.column(), "][Func:", sl.function_name(), "]:",
#endif//^^^^!__WINDOWS__^^^^
							ccolor(131, 255, 162),
							fmtstr,
							ccolor(255, 255, 255)
						), std::forward<Args>(args)...);
					output2file(istring::sumString("[", getTimeNow(), "][File:", sl.file_name(), ":", sl.line(), ",",
						sl.column(), "][Func:", sl.function_name(), "]",
						istring::format("[Debug]:" + fmtstr, std::forward<Args>(args)...)));

					_lock.unlock();
				}

#undef ccolor

			public:

				void output2file(istring istr);

			public:

				istring getTimeNow();

			private:
				istring _title;
				istring _logDir;
				type::iLevel _timeLevel;
#ifdef __WINDOWS__
				thread::iCriticalSectionLock _lock;
#else//^^^^__WINDOWS__^^^^
				std::mutex _lock;
#endif//^^^^!__WINDOWS__^^^^
			};
		}
	}
}
