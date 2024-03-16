#pragma once
#include <aliases.h>
#include <fmt/core.h>
#include <fmt/printf.h>
#include <mutex>
#include <source_location>
#include <utils/StringUtils.h>
#include <utils/TimeUtils.h>
#define COLORCAST(r, g, b) "\033[38;2;" #r ";" #g ";" #b "m"


class Logger
{
    using ushort = MiracleForest::ushort;

    template<typename _Type>
    using RRef = MiracleForest::RRef<_Type>;
    template<typename _Type>
    using CPtr = MiracleForest::CPtr<_Type>;

public:
    explicit Logger(std::string_view loggerName = __builtin_FUNCTION());

public:
    template<class... Args>
    void info(fmt::format_string<Args...> fmtstr, RRef<Args>... args)
    {
        mLock.lock();
        fmt::print(
            fmt::runtime(
                fmt::format(
                    "{}{}{} Info {}[{}]:{}{}{}",
                    COLORCAST(173, 216, 230),
                    getTimeNow(),
                    COLORCAST(148, 230, 207),
                    COLORCAST(204, 204, 204),
                    mTitle,
                    COLORCAST(164, 164, 164),
                    fmtstr.get(),
                    COLORCAST(255, 255, 255)
                )
                + "\n"
            ),
            std::forward<Args>(args)...
        );
        mLock.unlock();
    }

    template<class... Args>
    void warn(fmt::format_string<Args...> fmtstr, RRef<Args>... args)
    {
        mLock.lock();
        fmt::print(
            fmt::runtime(
                fmt::format(
                    "{}{}{} Warn {}[{}]:{}{}{}",
                    COLORCAST(242, 242, 205),
                    getTimeNow(),
                    COLORCAST(242, 220, 100),
                    COLORCAST(208, 242, 146),
                    mTitle,
                    COLORCAST(242, 239, 26),
                    fmtstr.get(),
                    COLORCAST(255, 255, 255)
                )
                + "\n"
            ),
            std::forward<Args>(args)...
        );
        mLock.unlock();
    }

    template<class... Args>
    void error(fmt::format_string<Args...> fmtstr, RRef<Args>... args)
    {
        mLock.lock();
        fmt::print(
            fmt::runtime(
                fmt::format(
                    "{}{}{} Eror {}[{}]:{}{}{}",
                    COLORCAST(242, 180, 180),
                    getTimeNow(),
                    COLORCAST(242, 68, 108),
                    COLORCAST(242, 122, 122),
                    mTitle,
                    COLORCAST(242, 72, 72),
                    fmtstr.get(),
                    COLORCAST(255, 255, 255)
                )
                + "\n"
            ),
            std::forward<Args>(args)...
        );
        mLock.unlock();
    }

    template<class... Args>
    void note(fmt::format_string<Args...> fmtstr, RRef<Args>... args)
    {
        mLock.lock();
        auto time = getTimeNowStructure();
        fmt::print(
            fmt::runtime(
                sumString(
                    COLORCAST(255, 170, 255),
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
                    mTitle.data(),
                    COLORCAST(156, 248, 255),
                    "]",
                    COLORCAST(240, 24, 28),
                    ":",
                    COLORCAST(137, 221, 255),
                    fmtstr.get().data(),
                    COLORCAST(255, 255, 255)
                )
                + "\n"
            ),
            std::forward<Args>(args)...
        );
        mLock.unlock();
    }

private:
    std::string_view mTitle;
    std::mutex       mLock;
};
#undef COLORCAST
