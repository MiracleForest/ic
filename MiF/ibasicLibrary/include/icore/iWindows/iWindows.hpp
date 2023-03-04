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
#pragma message("The contents of <iWindows.hpp> are available only with Windows.")
#else

#include <Windows.h>
#include <filesystem>
#include <icore/data/text/istring.hpp>
#include <Psapi.h>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(Windows)
        {

            class iWindows
                :basic::iBasic<iWindows>
            {
                using istring = data::text::istring;
                iObject(iWindows);
            public:

                iWindows()
                { }

                ~iWindows()
                { }

            public:

                static istring getLastErrorMessage(ulong errorMessageID)
                {
                    if (errorMessageID == 0)
                        return "";

                    Ptr<wchar> message_buffer = nullptr;
                    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
                        nullptr, errorMessageID, MAKELANGID(0x09, SUBLANG_DEFAULT), (Ptr<wchar>) & message_buffer, 0, nullptr);
                    istring res = istring::wstr2str(std::wstring(message_buffer));
                    LocalFree(message_buffer);
                    return res;
                }

                static istring getLastErrorMessage()
                {
                    ulong errorMessageID = ::GetLastError();
                    if (errorMessageID == 0)
                        return "";

                    Ptr<wchar> message_buffer = nullptr;
                    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
                        nullptr, errorMessageID, MAKELANGID(0x09, SUBLANG_DEFAULT), (Ptr<wchar>) & message_buffer, 0, nullptr);
                    std::string res = istring::wstr2str(std::wstring(message_buffer));
                    LocalFree(message_buffer);
                    return res;
                }

                static std::pair<int, istring> newProcessSync(CRef<istring> process, int timeLimit, bool noReadOutput)
                {
                    SECURITY_ATTRIBUTES sa;
                    handle hRead, hWrite;
                    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
                    sa.lpSecurityDescriptor = nullptr;
                    sa.bInheritHandle = TRUE;

                    if (!CreatePipe(&hRead, &hWrite, &sa, 0))
                        return { -1, "" };
                    STARTUPINFOW si = { 0 };
                    PROCESS_INFORMATION pi;

                    si.cb = sizeof(STARTUPINFO);
                    GetStartupInfoW(&si);
                    si.hStdOutput = si.hStdError = hWrite;
                    si.dwFlags = STARTF_USESTDHANDLES;

                    auto wCmd = istring::str2cwstr(process.data());
                    if (!CreateProcessW(nullptr, wCmd, nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi))
                    {
                        delete[] wCmd;
                        return { -1, "" };
                    }
                    CloseHandle(hWrite);
                    CloseHandle(pi.hThread);

                    if (timeLimit == -1)
                        WaitForSingleObject(pi.hProcess, INFINITE);
                    else
                    {
                        WaitForSingleObject(pi.hProcess, timeLimit);
                        TerminateProcess(pi.hProcess, -1);
                    }
                    char buffer[4096];
                    istring strOutput;
                    ulong bytesRead, exitCode;

                    delete[] wCmd;
                    GetExitCodeProcess(pi.hProcess, &exitCode);
                    if (!noReadOutput)
                    {
                        while (true)
                        {
                            ZeroMemory(buffer, 4096);
                            if (!ReadFile(hRead, buffer, 4096, &bytesRead, nullptr))
                                break;
                            strOutput.append(buffer, bytesRead);
                        }
                    }
                    CloseHandle(hRead);
                    CloseHandle(pi.hProcess);
                    return { exitCode, strOutput };
                }

                static istring getModulePath(HMODULE handle)
                {
                    wchar_t buf[MAX_PATH] = { 0 };
                    GetModuleFileNameEx(GetCurrentProcess(), handle, buf, MAX_PATH);
                    return istring::wstr2str(std::wstring(buf));
                }

                static istring getModuleName(HMODULE handle)
                {
                    wchar_t buf[MAX_PATH] = { 0 };
                    GetModuleFileNameEx(GetCurrentProcess(), handle, buf, MAX_PATH);
                    return istring::UTF82String(std::filesystem::path(buf).filename().u8string());
                }

                /****
                * @author 时雨
                * @since 2023.1.3.11.28
                * @brief 该函数实现一个同网络资源的永久性链接（就是映射网络驱动器）
                *
                * @param lpszNetPath 要连接的网络名
                * @param lpszPassword 连接时使用的密码，若无需密码，该参数可填""
                * @param lpszLocalName 资源的本地名称，即该资源映射到本地的位置
                * @retval 错误码
                * @throws 抛出的异常
                *
                * @par 示例
                * @code
                * 代码示例
                * @endcode
                *
                * @include <Windows.h>,<icore/data/text/istring.hpp>
                ****/
                istring netAddConnection(istring lpszNetPath, istring lpszPassword, istring lpszLocalName)
                {
                    LPCWSTR
                        a = istring::str2cwstr(lpszNetPath.data()),
                        b = istring::str2cwstr(lpszPassword.data()),
                        c = istring::str2cwstr(lpszLocalName.data());
                    WNetAddConnection(a, b, c);
                    istring Error = GetLastError();
                    return Error;
                }
                /****
                * @author 时雨
                * @since 2023.1.3.13.14
                * @brief 结束一个网络连接
                *
                * @param lpszName 已连接资源的远程名称或本地名称
                * @param fForce 如为TRUE，表示断开连接（即使连接的资源上正有打开的文件或作业）
                * @retval 错误码
                * @throws 抛出的异常
                *
                * @par 示例
                * @code
                * 代码示例
                * @endcode
                *
                * @include <Windows.h>,<icore/data/text/istring.hpp>
                ****/
                istring wNetCancelConnection(istring lpszName, bool fForce)
                {
                    LPCWSTR  a = istring::str2cwstr(lpszName.data());
                    WNetCancelConnection(a, fForce);
                    istring error = GetLastError();
                    return error;
                }

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
                bool getShutdownPrivilege()
                {
                    HANDLE hToken;
                    TOKEN_PRIVILEGES tokenPriv;
                    LUID shutdownPrivilegeID;
                    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
                    {
                        return false;
                    }
                    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &shutdownPrivilegeID);
                    tokenPriv.PrivilegeCount = 1;
                    tokenPriv.Privileges[0].Luid = shutdownPrivilegeID;
                    tokenPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
                    return AdjustTokenPrivileges(hToken, FALSE, &tokenPriv, NULL, NULL, NULL);
                }

                /****
                * @author Lovelylavender4
                * @since 2023.2.22.13:14
                *
                * @param SHUTDOWN_ACTION
                * @retval ulong
                ****/
                ulong ntShutdownSystem(SHUTDOWN_ACTION action)
                {
                    HMODULE hDll = GetModuleHandle(L"ntdll.dll");
                    if (hDll == nullptr)
                    {
                        return -1;
                    }
                    typeNtShutdownSystem func = (typeNtShutdownSystem)GetProcAddress(hDll, "NtShutdownSystem");
                    return func(action);
                }

            public:
            protected:
            private:
            };//class iWindows

        }//SPACE(Windows)
    }//SPACE(core)
}//SPACE(i)

#endif //!__WINDOWS__
