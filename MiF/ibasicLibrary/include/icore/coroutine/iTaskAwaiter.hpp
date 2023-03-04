/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iTaskAwaiter.hpp
* @创建时间：2022.12.28.21:56
* @创建者：ticks-tan
* -----------------------------------------------------------------------------
* i Task 协程通用 Awaiter
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#include <icore/family/imacrofamily.h>
#include <coroutine>
#include <functional>
#include <optional>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(coroutine)
        {
            // Task 协程通用 Awaiter，方便扩展
            // 如果需要在 Task协程中使用 co_await ，继承自该 Awaiter
            template <typename Ret>
            class iTaskBaseAwaiter
            {
            public:
                // Task协程基础调度器
                class iTaskBaseExecutor;
                // Task协程返回值类型
                template <typename _Ret> class iTaskResult;

                // 设置Awaiter调度器
                void set_executor(Ptr<iTaskBaseExecutor> executor_ptr)
                {
                    _executor = executor_ptr;
                }
                // 恢复协程
                void resume(Ret value)
                {
                    // value 为 co_await 返回值，设置值之后恢复协程
                    dispatch([this, value]()
                        {
                            _result = iTaskResult<Ret>(static_cast<Ret>(value));
                            if (_handle)
                            {
                                _handle.resume();
                            }
                        });
                }

                // 不关心返回值，直接恢复协程
                void resume_unsafe()
                {
                    dispatch([this]()
                        {
                            if (_handle)
                            {
                                _handle.resume();
                            }
                        });
                }

                // 出现异常，异常作为返回值并恢复协程
                void resume_exception(RRef<std::exception_ptr> e)
                {
                    dispatch([this, e]()
                        {
                            _result = iTaskResult<Ret>(static_cast<std::exception_ptr>(e));
                            if (_handle)
                            {
                                _handle.resume();
                            }
                        });
                }

            public:

                // 协程是否挂起，返回false挂起
                // 一个优化点，如果协程不需要挂起可以直接返回true
                bool await_ready() const
                {
                    return is_ready();
                }

                // 协程挂起后执行
                void await_suspend(std::coroutine_handle<> handle)
                {
                    // 记录当前协程句柄，方便恢复
                    _handle = handle;
                    // 子类可扩展该函数
                    after_suspend();
                }

                // 协程恢复后执行
                Ret await_resume()
                {
                    // 子类可扩展该函数
                    before_resume();
                    // 返回值为 co_await 结果
                    return _result->get_or_exception();
                }

            private:

                // 使用调度器执行函数
                void dispatch(RRef<std::function<void()>> func)
                {
                    if (_executor)
                    {
                        // 有调度器，使用调度器执行函数
                        _executor->execute(std::move(func));
                    }
                    else
                    {
                        //没有调度器，直接执行
                        func();
                    }
                }
            protected:
                // 子类需要实现的函数，方便扩展
                virtual bool is_ready()
                {
                    return false;
                }

                virtual void after_suspend()
                { }

                virtual void before_resume()
                { }

            protected:

                // 存储结果，方便子类访问
                std::optional<iTaskResult<Ret>> _result;

            private:
                // 调度器指针，指向调度器基类
                Ptr<iTaskBaseExecutor> _executor = nullptr;
                // 协程句柄，恢复协程时需要
                std::coroutine_handle<> _handle = nullptr;
            };
        }
    }
}
