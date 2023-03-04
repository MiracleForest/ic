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
#include <icore/type/type/type.hpp>
#include <icore/data/text/istring.hpp>
#include <icore/console/iConsole.hpp>
#include <icore/type/iColor.hpp>
#include <icore/type/iTime.hpp>
#include <icore/file/iFilePos.hpp>
#include <icore/type/iLevel.hpp>
#include <icore/thread/iCriticalSectionLock.hpp>
#include <icore/file/iFile.hpp>
#include <filesystem>
#include <mutex>


SPACE(i)
{
	SPACE(core)
	{
		SPACE(io)
		{

			class iLogger
				: public basic::iBasic<iLogger>
			{
				iObject(iLogger);
				using istring = data::text::istring;
			public:

				iLogger(
					CRef<istring> loggerName,
					type::iLevel timeLevel = type::Level::A,
					CRef<istring> logDir = "null"
				)
					: _title(loggerName),
					_logDir(logDir),
					_timeLevel(timeLevel)
				{ }

				iLogger()
					: _title(""),
					_logDir("null")
				{ }

			public:

#ifdef __WINDOWS__

				Ref<thread::iCriticalSectionLock> getLocker()
				{
					return _lock;
				}

#endif

			public:

				_CGETVF(istring, Title, title);

				_CSETVF(iLogger, istring, Title, title);

				_CGETVF(istring, LogDir, logDir);

				_CSETVF(iLogger, istring, LogDir, logDir);

			public:

				template<class...Args>
				void info(istring fmtstr, RRef<Args>...args)
				{
					_lock.lock();
					iConsole::writeLine(
						istring::sumString(type::iColor::getConsoleColoriString({ 173, 216, 230 }),
							getTimeNow(),
							type::iColor::getConsoleColoriString({ 148, 230, 207 }),
							" Info ",
							type::iColor::getConsoleColoriString({ 204, 204, 204 }),
							"[", _title, "]:",
							type::iColor::getConsoleColoriString({ 164, 164, 164 }),
							fmtstr,
							type::iColor::getConsoleColoriString({ 255, 255, 255 })
						), std::forward<Args>(args)...);
					output2file("[" + getTimeNow() + istring::format("][Info]:" + fmtstr, std::forward<Args>(args)...));
					_lock.unlock();
				}

				template<class...Args>
				void warn(istring fmtstr, RRef<Args>...args)
				{
					_lock.lock();
					iConsole::writeLine(
						istring::sumString(type::iColor::getConsoleColoriString({ 242, 242, 205 }),
							getTimeNow(),
							type::iColor::getConsoleColoriString({ 242, 220, 100 }),
							" Warn ",
							type::iColor::getConsoleColoriString({ 208, 242, 146 }),
							"[", _title, "]:",
							type::iColor::getConsoleColoriString({ 242, 239, 26 }),
							fmtstr,
							type::iColor::getConsoleColoriString({ 255, 255, 255 })
						), std::forward<Args>(args)...);
					output2file("[" + getTimeNow() + istring::format("][Warn]:" + fmtstr, std::forward<Args>(args)...));
					_lock.unlock();
				}

				template<class...Args>
				void error(istring fmtstr, RRef<Args>...args)
				{
					_lock.lock();
					iConsole::writeLine(
						istring::sumString(type::iColor::getConsoleColoriString({ 242, 180, 180 }),
							getTimeNow(),
							type::iColor::getConsoleColoriString({ 242, 68, 108 }),
							" Error ",
							type::iColor::getConsoleColoriString({ 242, 122, 122 }),
							"[", _title, "]:",
							type::iColor::getConsoleColoriString({ 242, 72, 72 }),
							fmtstr,
							type::iColor::getConsoleColoriString({ 255, 255, 255 })
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
						istring::sumString(type::iColor::getConsoleColoriString({ 255, 170, 255 }),
							time.years,
							type::iColor::getConsoleColoriString({ 240, 24, 28 }),
							".",
							type::iColor::getConsoleColoriString({ 170, 255, 255 }),
							time.months,
							type::iColor::getConsoleColoriString({ 240, 24, 28 }),
							".",
							type::iColor::getConsoleColoriString({ 170, 170, 255 }),
							time.days,
							type::iColor::getConsoleColoriString({ 240, 24, 28 }),
							".",
							type::iColor::getConsoleColoriString({ 134, 255, 217 }),
							time.hours,
							type::iColor::getConsoleColoriString({ 240, 24, 28 }),
							":",
							type::iColor::getConsoleColoriString({ 255, 105, 252 }),
							time.minutes,
							type::iColor::getConsoleColoriString({ 240, 24, 28 }),
							":",
							type::iColor::getConsoleColoriString({ 255, 240, 82 }),
							time.seconds,
							type::iColor::getConsoleColoriString({ 240, 24, 28 }),
							":",
							type::iColor::getConsoleColoriString({ 39, 215, 231 }),
							time.milliseconds,
							type::iColor::getConsoleColoriString({ 255, 170, 255 }),
							" N",
							type::iColor::getConsoleColoriString({ 69, 255, 240 }),
							"o",
							type::iColor::getConsoleColoriString({ 255, 255, 0 }),
							"t",
							type::iColor::getConsoleColoriString({ 67, 236, 62 }),
							"e ",
							type::iColor::getConsoleColoriString({ 156, 248, 255 }),
							"[",
							type::iColor::getConsoleColoriString({ 228, 131, 255 }),
							_title,
							type::iColor::getConsoleColoriString({ 156, 248, 255 }),
							"]",
							type::iColor::getConsoleColoriString({ 240, 24, 28 }),
							":",
							type::iColor::getConsoleColoriString({ 137, 221, 255 }),
							fmtstr,
							type::iColor::getConsoleColoriString({ 255, 255, 255 })
						), std::forward<Args>(args)...);
					output2file("[" + getTimeNow() + istring::format("][Note]:" + fmtstr, std::forward<Args>(args)...));
					_lock.unlock();
				}

				template<class...Args>
				void debug(istring fmtstr, std::source_location sl, RRef<Args>...args)
				{
					_lock.lock();
					iConsole::writeLine(
						istring::sumString(type::iColor::getConsoleColoriString({ 168, 255, 204 }),
							getTimeNow(),
							type::iColor::getConsoleColoriString({ 0, 255, 0 }),
							" Debug ",
							type::iColor::getConsoleColoriString({ 156, 248, 255 }),
#ifdef __WINDOWS__
							"[", _title, "][File:", _ISTDTEXT iEncoding::wideChar2ANSI(
								_ISTDTEXT iEncoding::UTF82wideChar(sl.file_name())), ":", sl.line(), ",",
							sl.column(), "][Func:", sl.function_name(), "]:",
#else
							"[", _title, "][File:", _ISTDTEXT sl.file_name(), ":", sl.line(), ",", sl.column(), "][Func:", sl.function_name(), "]:",
#endif
							type::iColor::getConsoleColoriString({ 131, 255, 162 }),
							fmtstr,
							type::iColor::getConsoleColoriString({ 255, 255, 255 })
						), std::forward<Args>(args)...);
					output2file(istring::sumString("[", getTimeNow(), "][File:", sl.file_name(), ":", sl.line(), ",",
						sl.column(), "][Func:", sl.function_name(), "]",
						istring::format("[Debug]:" + fmtstr, std::forward<Args>(args)...)));

					_lock.unlock();
				}

			public:

				void output2file(istring istr)
				{
					if (_logDir == "null")
					{
						return;
					}

					type::iTime t;
					t.getTimeNow();
					auto time = t.data();
					auto targetFile = istring::format("{3}\\{0}.{1}.{2}.ilog", time.years, time.months, time.days,
						_logDir);
					std::fstream log(targetFile.data(), std::ios::app);
					log << (istr.data() + "\n");
					log.close();
				}

			public:

				istring getTimeNow()
				{
					type::iTime t;
					t.getTimeNow();
					auto time = t.data();
					switch (_timeLevel.getLevel())
					{
						using
							enum type::Level;
					case φ:
					{
						return istring::format("{0}.{1}.{2}.{3}:{4}:{5}:{6}:{7}:{8}", time.years, time.months,
							time.days, time.hours, time.minutes, time.seconds, time.milliseconds,
							time.microseconds, time.nanoseconds);
					}
					case I:
					{
						return istring::format("{0}.{1}.{2}.{3}:{4}:{5}:{6}:{7}", time.years, time.months,
							time.days, time.hours, time.minutes, time.seconds, time.milliseconds,
							time.microseconds);
					}
					case A:
					{
						return istring::format("{0}.{1}.{2}.{3}:{4}:{5}:{6}", time.years, time.months, time.days,
							time.hours, time.minutes, time.seconds, time.milliseconds);
					}
					case B:
					{
						return istring::format("{0}.{1}.{2}.{3}:{4}:{5}", time.years, time.months, time.days,
							time.hours, time.minutes, time.seconds);
					}
					case C:
					{
						return istring::format("{0}.{1}.{2}.{3}:{4}", time.years, time.months, time.days,
							time.hours, time.minutes);
					}
					case D:
					{
						return istring::format("{0}.{1}.{2}.{3}", time.years, time.months, time.days, time.hours);
					}
					case E:
					{
						return istring::format("{0}.{1}.{2}", time.years, time.months, time.days);
					}
					case F:
					{
						return istring::format("{0}.{1}", time.years, time.months);
					}
					case G:
					{
						return istring::format("{0}", time.years);
					}
					case H:
					case FALSE:
					default:
					{
						return "";
					}
					}
				}

			private:
				istring _title;
				istring _logDir;
				type::iLevel _timeLevel;
#ifdef __WINDOWS__
				thread::iCriticalSectionLock _lock;
#else
				std::mutex _lock;
#endif
			};
		}
	}
}
