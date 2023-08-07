/*
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:ifamily.hpp
 * @创建时间:2022.5.26.13:13
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * main函数所在地,程序的入口点
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once
#pragma warning(disable:4996)
#pragma warning(disable:4819)
#pragma warning(disable:4464)
#pragma warning(disable:4828)

#include <icore/family/imacrofamily.h>
#include <icore/exception/error.h>
#include <icore/basic/iBasic.h>

#ifdef __WINDOWS__
#include <conio.h>
#endif

#undef iMain
#undef iMainEnd

SPACE(i)
{
    SPACE(core)
    {

        struct _p_start
        {
            int argc = 0;
            PPtr<char> argv = nullptr;
            PPtr<char> envp = nullptr;
            bool pause = false;
        }; //struct _p_start 

        /****
         * @author Lovelylavender4
         * @since 2022.7.2.20:39
         * @brief C++程序的入口点
         *
         * @param argc argv中元素的个数
         * @param argv 命令行参数
         * @param envp 环境变量
         * @future 完善main
         * @retval 结束代码
         *
         * @warning 此函数不提供给用户调用，若想调用，请谨慎调用！
         *
         * @include "error.hpp"
         * @details
         * C++程序的入口点，程序从此处开始执行
         * @enddetails
         ****/
        int _iMain(
            int argc,
            PPtr<char> argv,
            PPtr<char> envp,
            std::function<_iError(Ref<_p_start>)> start
        )
        {
            try
            {
                _p_start p_start{ };
                p_start.argc = argc;
                p_start.argv = argv;
                p_start.envp = envp;
                p_start.pause = false;

                auto rt = start(p_start);

                if (p_start.pause == true)
                {
                    std::cout << "请按任意键继续...\n";
                    (void)getch();
                }

                if (rt.isNoError())
                {
                    return 0;
                }
                else if (rt.isCanBeIgnored())
                {
                    return 1;
                }
                else
                {
                    return (int)rt.getErrorInfo()._code;
                }
            }
            catch (CRef<::i::core::iexception::iCreateErrorFailed> e)
            {
                printf("%s", e.what());
                return -3;
            }
            catch (CRef<std::bad_alloc> e)
            {
                printf("%s", e.what());
                return -1000;
            }
            catch (CRef<std::bad_exception> e)
            {
                printf("%s", e.what());
                return -1001;
            }
            catch (CRef<std::bad_typeid> e)
            {
                printf("%s", e.what());
                return -1002;
            }
            catch (CRef<std::bad_cast> e)
            {
                printf("%s", e.what());
                return -1003;
            }
            catch (CRef<std::ios_base::failure> e)
            {
                printf("%s", e.what());
                return -1004;
            }
            catch (CRef<std::length_error> e)
            {
                printf("%s", e.what());
                return -1005;
            }
            catch (CRef<std::domain_error> e)
            {
                printf("%s", e.what());
                return -1006;
            }
            catch (CRef<std::out_of_range> e)
            {
                printf("%s", e.what());
                return -1007;
            }
            catch (CRef<std::invalid_argument> e)
            {
                printf("%s", e.what());
                return -1008;
            }
            catch (CRef<std::range_error> e)
            {
                printf("%s", e.what());
                return -1009;
            }
            catch (CRef<std::overflow_error> e)
            {
                printf("%s", e.what());
                return -1010;
            }
            catch (CRef<std::underflow_error> e)
            {
                printf("%s", e.what());
                return -1011;
            }
            catch (CRef<std::format_error> e)
            {
                printf("%s", e.what());
                return -1012;
            }
            catch (std::exception e)
            {
                printf("%s", e.what());
                return -2;
            }
            catch (...)
            {
                printf("other exception!");
                return -2;
            }
            return -1;
        }
    }
}

#ifndef iMain
#define iMain(x) int main(int argc,_ISTD PPtr<char> argv,_ISTD PPtr<char> envp){ using namespace i::core; return _ISTD _iMain(argc,argv,envp,[&](_ISTD Ref<_ISTD _p_start> x) 
#define iMainEnd );};
#endif //!iMain

