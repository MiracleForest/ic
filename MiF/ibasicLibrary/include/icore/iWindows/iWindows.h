/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iWindows
* @创建时间：2022.10.2.19:40
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* Windows系统相关
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#include <icore/family/imacrofamily.h>

#ifndef __WINDOWS__
#pragma message("The contents of <iWindows.h> are available only with Windows.")
#else

#include <Windows.h>
#include <filesystem>
#include <icore/data/text/istring.h>
#include <Psapi.h>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(Windows)
        {

            class IAPI iWindows
                :basic::iBasic<iWindows>
            {
                using istring = data::text::istring;
                iObject(iWindows);
            public:

                iWindows();

                ~iWindows();

            public:

                static istring getLastErrorMessage(ulong errorMessageID);

                static istring getLastErrorMessage();

                static std::pair<int, istring> newProcessSync(CRef<istring> process, int timeLimit, bool noReadOutput);

                static istring getModulePath(HMODULE handle);

                static istring getModuleName(HMODULE handle);

                static HMODULE getCurrentModule();

                enum _SHUTDOWN_ACTION
                {
                    ShutdownNoReboot,
                    ShutdownReboot,
                    ShutdownPowerOff
                };
                using SHUTDOWN_ACTION = _SHUTDOWN_ACTION;

                typedef ulong(WINAPI* typeNtShutdownSystem)(SHUTDOWN_ACTION Action);

                /****
                * @author Lovelylavender4
                * @since 2023.2.22.13:14
                *
                * @retval bool
                ****/
                static bool getShutdownPrivilege();

                /****
                * @author Lovelylavender4
                * @since 2023.2.22.13:14
                *
                * @param SHUTDOWN_ACTION
                * @retval ulong
                ****/
                static ulong ntShutdownSystem(SHUTDOWN_ACTION action);

            public:
            protected:
            private:
            };//class iWindows

        }//SPACE(Windows)
    }//SPACE(core)
}//SPACE(i)

#endif //^^^^__WINDOWS__^^^^
