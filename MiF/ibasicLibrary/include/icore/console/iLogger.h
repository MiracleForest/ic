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


				template<class...Args>
				void info(CRef<istring> fmtstr, RRef<Args>...args)
				{
					_lock.lock();
					iConsole::writeLine(
						istring::format("{}{}{} Info {}[{}]:{}{}{}",
							COLORCAST(173, 216, 230),
							getTimeNow(),
							COLORCAST(148, 230, 207),
							COLORCAST(204, 204, 204),
							_title,
							COLORCAST(164, 164, 164),
							fmtstr,
							COLORCAST(255, 255, 255)
						), std::forward<Args>(args)...);
					output2file("[" + getTimeNow() + istring::format("][Info]:" + fmtstr, std::forward<Args>(args)...));
					_lock.unlock();
				}

				template<class...Args>
				void warn(CRef<istring> fmtstr, RRef<Args>...args)
				{
					_lock.lock();
					iConsole::writeLine(
						istring::format("{}{}{} Warn {}[{}]:{}{}{}",
							COLORCAST(242, 242, 205),
							getTimeNow(),
							COLORCAST(242, 220, 100),
							COLORCAST(208, 242, 146),
							_title,
							COLORCAST(242, 239, 26),
							fmtstr,
							COLORCAST(255, 255, 255)
						), std::forward<Args>(args)...);
					output2file("[" + getTimeNow() + istring::format("][Warn]:" + fmtstr, std::forward<Args>(args)...));
					_lock.unlock();
				}

				template<class...Args>
				void error(CRef<istring> fmtstr, RRef<Args>...args)
				{
					_lock.lock();
					iConsole::writeLine(
						istring::format("{}{}{} Error {}[{}]:{}{}{}",
							COLORCAST({ 242, 180, 180 }),
							getTimeNow(),
							COLORCAST({ 242, 68, 108 }),
							COLORCAST({ 242, 122, 122 }),
							_title,
							COLORCAST({ 242, 72, 72 }),
							fmtstr,
							COLORCAST({ 255, 255, 255 })
						), std::forward<Args>(args)...);
					output2file(
						"[" + getTimeNow() + istring::format("][Error]:" + fmtstr, std::forward<Args>(args)...));
					_lock.unlock();
				}

				template<class...Args>
				void note(CRef<istring> fmtstr, RRef<Args>...args)
				{
					_lock.lock();
					type::iTime t;
					t.getTimeNow();
					auto time = t.data();

					iConsole::writeLine(
						istring::sumString(COLORCAST(255, 170, 255),
							time.years,
							COLORCAST(240, 24, 28),
							".",
							COLORCAST(170, 255, 255),
							time.months,
							COLORCAST(240, 24, 28),
							".",
							COLORCAST(170, 170, 255),
							time.days,
							COLORCAST(240, 24, 28),
							".",
							COLORCAST(134, 255, 217),
							time.hours,
							COLORCAST(240, 24, 28),
							":",
							COLORCAST(255, 105, 252),
							time.minutes,
							COLORCAST(240, 24, 28),
							":",
							COLORCAST(255, 240, 82),
							time.seconds,
							COLORCAST(240, 24, 28),
							":",
							COLORCAST(39, 215, 231),
							time.milliseconds,
							COLORCAST(255, 170, 255),
							" N",
							COLORCAST(69, 255, 240),
							"o",
							COLORCAST(255, 255, 0),
							"t",
							COLORCAST(67, 236, 62),
							"e ",
							COLORCAST(156, 248, 255),
							"[",
							COLORCAST(228, 131, 255),
							_title,
							COLORCAST(156, 248, 255),
							"]",
							COLORCAST(240, 24, 28),
							":",
							COLORCAST(137, 221, 255),
							fmtstr,
							COLORCAST(255, 255, 255)
						), std::forward<Args>(args)...);
					output2file("[" + getTimeNow() + istring::format("][Note]:" + fmtstr, std::forward<Args>(args)...));
					_lock.unlock();
				}

				template<class...Args>
				void debug(CRef<istring> fmtstr, std::source_location sl, RRef<Args>...args)
				{
					_lock.lock();
					iConsole::writeLine(
						istring::sumString(COLORCAST({ 168, 255, 204 }),
							getTimeNow(),
							COLORCAST(0, 255, 0),
							" Debug ",
							COLORCAST(156, 248, 255),
#ifdef __WINDOWS__
							"[", _title, "][File:", _ISTDTEXT iEncoding::wideChar2ANSI(_ISTDTEXT iEncoding::UTF82wideChar(sl.file_name())), ":", sl.line(), ",",
							sl.column(), "][Func:", sl.function_name(), "]:",
#else//^^^^__WINDOWS__^^^^
							"[", _title, "][File:", sl.file_name(), ":", sl.line(), ",", sl.column(), "][Func:", sl.function_name(), "]:",
#endif//^^^^!__WINDOWS__^^^^
							COLORCAST(131, 255, 162),
							fmtstr,
							COLORCAST(255, 255, 255)
						), std::forward<Args>(args)...);
					output2file(istring::sumString("[", getTimeNow(), "][File:", sl.file_name(), ":", sl.line(), ",",
						sl.column(), "][Func:", sl.function_name(), "]",
						istring::format("[Debug]:" + fmtstr, std::forward<Args>(args)...)));

					_lock.unlock();
				}

			public:

				void output2file(CRef<istring> istr);

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
