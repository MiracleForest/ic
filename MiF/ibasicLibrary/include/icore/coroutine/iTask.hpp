/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iTask.hpp
* @创建时间：2022.12.28.21:56
* @创建者：ticks-tan
* -----------------------------------------------------------------------------
* i Task调度器协程
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#include <icore/family/imacrofamily.h>
#include <icore/coroutine/iTaskAwaiter.hpp>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>
#include <queue>
#include <list>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(coroutine)
        {
            // 前置声明
            template <typename Ret, typename Exe> class iTaskAwaiter;
            template <typename Ret, typename Exe> class iTask;
            template <typename Ret, typename Exe> class iTaskPromise;
            struct iExecutorAwaiter;

            // Task协程调度器基类
            class iTaskBaseExecutor
            {
            public:
                // 调度器执行函数，子类必须实现
                virtual void execute(RRef<std::function<void()>>) = 0;
            }; // iTaskBaseExecutor

            // 基础调度器，直接执行
            class iNoopExecutor :
                public iTaskBaseExecutor
            {
            public:
                void execute(RRef<std::function<void()>> func) override
                {
                    func();
                }
            }; // iNoopExecutor

            // 新线程调度器，新开一个线程执行
            class iNewThreadExecutor :
                public iTaskBaseExecutor
            {
            public:
                void execute(RRef<std::function<void()>> func) override
                {
                    std::thread(func).detach();
                }
            }; // iNewThreadExecutor

            // 使用标准库 async 线程调度，类似 NewThreadExecutor
            class iAsyncExecutor :
                public iTaskBaseExecutor
            {
            public:
                void execute(RRef<std::function<void()>> func) override
                {
                    auto future = std::async(func);
                }
            }; // iAsyncExecutor

            // 循环调度器，使用事件通知提交函数
            class iLooperExecutor :
                public iTaskBaseExecutor
            {
            public:
                void execute(RRef<std::function<void()>> func) override
                {
                    std::unique_lock lock(_queue_mutex);
                    if (_active.load(std::memory_order_relaxed))
                    {
                        // 如果线程没有关闭，添加到队列
                        _queue.push(func);
                        lock.unlock();
                        // 通知休眠线程
                        _queue_cv.notify_all();
                    }
                    // 不做处理
                }
            public:
                iLooperExecutor()
                    : _active(true)
                    , _thread(std::thread(&iLooperExecutor::thread_loop, this))
                { }
                ~iLooperExecutor()
                {
                    // 强制退出
                    stop(false);
                    if (_thread.joinable())
                    {
                        _thread.join();
                    }
                }

                // 停止Loop线程
                void stop(bool wait_tasks)
                {
                    _active.store(false, std::memory_order_relaxed);
                    if (!wait_tasks)
                    {
                        // 如果不等待任务完成，强制清除任务
                        std::unique_lock lock(_queue_mutex);
                        decltype(_queue) empty_queue;
                        std::swap(_queue, empty_queue);
                        lock.unlock();
                    }
                    // 通知线程
                    _queue_cv.notify_all();
                }
            private:
                // loop 线程执行函数
                void thread_loop()
                {
                    // 当线程活跃或者队列不为空时
                    while (_active.load(std::memory_order_relaxed) || !_queue.empty())
                    {
                        std::unique_lock lock(_queue_mutex);
                        if (_queue.empty())
                        {
                            // 如果队列为空，休眠线程等待通知
                            _queue_cv.wait(lock);
                            if (_queue.empty())
                            {
                                // 收到通知，但是队列为空，为退出通知
                                continue;
                            }
                        }
                        // 队列不为空，取出任务执行
                        auto func = _queue.front();
                        _queue.pop();
                        lock.unlock();
                        // 执行函数
                        func();
                    }
                }
            private:
                // 互斥锁
                std::mutex _queue_mutex;
                // 条件变量
                std::condition_variable _queue_cv;
                // 事件队列
                std::queue<std::function<void()>> _queue;
                // 循环线程是否结束
                std::atomic_bool _active;
                // loop 线程
                std::thread _thread;
            }; // iLooperExecutor

            // 全局共享LoopExecutor
            class iSharedLooperExecutor : public iTaskBaseExecutor
            {
            public:
                void execute(RRef<std::function<void()>> func) override
                {
                    static iLooperExecutor shared_loop_executor;
                    shared_loop_executor.execute(std::forward<RRef<std::function<void()>>>(func));
                }
            }; // iSharedLooperExecutor

            // Task协程返回值类型
            template <typename Ret>
            class iTaskResult
            {
            public:
                iTaskResult() = default;
                ~iTaskResult() = default;
                // 使用正常返回值构造
                explicit iTaskResult(RRef<Ret> val)
                    : _value(val)
                { }
                // 使用异常构造
                explicit iTaskResult(RRef<std::exception_ptr> expr)
                    : _expr(expr)
                { }

                // 获取返回值，有异常抛出异常
                Ret get_or_exception()
                {
                    if (_expr)
                    {
                        // 有异常，抛出异常
                        std::rethrow_exception(_expr);
                    }
                    return _value;
                }
            private:
                // 值
                Ret _value;
                // 异常
                std::exception_ptr _expr;
            }; // iTaskResult
            // iTaskResult void 模板特化
            template <>
            class iTaskResult<void>
            {
            public:
                explicit iTaskResult() = default;
                // 使用异常构造
                explicit iTaskResult(RRef<std::exception_ptr> expr)
                    : _expr(std::move(expr))
                { }

                // 获取返回值，只有异常抛出异常
                void get_or_exception()
                {
                    if (_expr)
                    {
                        // 有异常，抛出异常
                        std::rethrow_exception(_expr);
                    }
                }
            private:
                // 异常
                std::exception_ptr _expr;
            }; // iTaskResult<void>

            // Task协程Awaiter
            template <typename Ret, typename Exe>
            class iTaskAwaiter : public iTaskBaseAwaiter<Ret>
            {
            public:
                explicit iTaskAwaiter(RRef<iTask<Ret, Exe>> task)
                    : _task(std::move(task))
                { }

                iTaskAwaiter(RRef<iTaskAwaiter> awaiter) noexcept
                    : iTaskBaseAwaiter<Ret>(awaiter)
                    , _task(std::move(awaiter._task))
                { }

                iTaskAwaiter(CRef<iTaskAwaiter>) = delete;

                CRef<iTaskAwaiter> operator = (CRef<iTaskAwaiter>) = delete;

            protected:

                void after_suspend() override
                {
                    // 协程执行完后恢复挂起的协程
                    _task.finally([this]()
                        {
                            this->resume_unsafe();
                        });
                }

                void before_resume() override
                {
                    // 协程恢复，对结果赋值
                    this->_result = iTaskResult<Ret>(_task.get_result());
                }

            private:
                // Task协程
                iTask<Ret, Exe> _task;
            }; // iTaskAwaiter

            // 协程开始时使用协程指定的调度器执行协程
            struct iTaskExecutorAwaiter
            {
                explicit iTaskExecutorAwaiter(Ptr<iTaskBaseExecutor> executor)
                    : _executor(executor)
                { }

                // 协程开始前挂起，方便使用调度器恢复
                bool await_ready() const
                {
                    return false;
                }

                // 协程挂起后使用调度器恢复协程，继续执行
                void await_suspend(std::coroutine_handle<> handle)
                {
                    _executor->execute([handle]()
                        {
                            handle.resume();
                        });
                }

                void await_resume()
                { }

            private:
                Ptr<iTaskBaseExecutor> _executor;
            }; // iTaskExecutorAwaiter

            // 协程promise，控制协程行为
            template <typename Ret, typename Exe>
            class iTaskPromise
            {
            public:

                iTaskExecutorAwaiter initial_suspend()
                {
                    return iTaskExecutorAwaiter{ &_executor };
                }

                std::suspend_always final_suspend() noexcept
                {
                    return {};
                }

                iTask<Ret, Exe> get_return_object()
                {
                    return iTask<Ret, Exe>(std::coroutine_handle<iTaskPromise<Ret, Exe>>::from_promise(*this));
                }

                void unhandled_exception()
                {
                    {
                        std::unique_lock lock(_callback_mutex);
                        _result = iTaskResult<Ret>(std::move(std::current_exception()));
                    }
                    _callback_cv.notify_all();
                    // 执行回调
                    do_callbacks();
                }

                void return_value(Ret result)
                {
                    // co_return 返回值
                    {
                        std::unique_lock lock(_callback_mutex);
                        _result = iTaskResult<Ret>(std::move(result));
                    }
                    _callback_cv.notify_all();
                    // 执行回调
                    do_callbacks();
                }

                template <typename AwaiterImpl>
                AwaiterImpl await_transform(AwaiterImpl awaiter)
                {
                    awaiter.set_executor(&_executor);
                    return awaiter;
                }

                // 同步获取值
                Ret get_result()
                {
                    std::unique_lock lock(_callback_mutex);
                    if (!_result.has_value())
                    {
                        // 没有值，等待通知
                        _callback_cv.wait(lock);
                    }
                    // 返回值或者抛出异常
                    return _result->get_or_exception();
                }

                // task协程执行完成回调
                void on_completed(RRef<std::function<void(iTaskResult<Ret>)>> func)
                {
                    std::unique_lock lock(_callback_mutex);
                    if (_result.has_value())
                    {
                        auto value = _result.value();
                        lock.unlock();
                        func(value);
                    }
                    else
                    {
                        // 协程还没有返回值或者异常，添加到队列，等待有值后执行
                        _callback_list.push_back(func);
                    }

                }
            private:
                // 执行注册的回调
                void do_callbacks()
                {
                    auto value = _result.value();
                    for (auto& callback : _callback_list)
                    {
                        callback(value);
                    }
                    // 清空回调
                    _callback_list.clear();
                }
            private:
                // 协程调度器
                Exe _executor;
                // 结果值
                std::optional<iTaskResult<Ret>> _result;
                // 回调队列锁
                std::mutex _callback_mutex;
                // 回调队列条件变量
                std::condition_variable _callback_cv;
                // 异步回调函数链表
                std::list<std::function<void(iTaskResult<Ret>)>> _callback_list;
            }; // iTaskPromise

            // iTaskPromise void 特化
            template <typename Exe>
            class iTaskPromise<void, Exe>
            {
            public:

                iTaskExecutorAwaiter initial_suspend()
                {
                    return iTaskExecutorAwaiter{ &_executor };
                }

                std::suspend_always final_suspend() noexcept
                {
                    return {};
                }

                iTask<void, Exe> get_return_object()
                {
                    return iTask<void, Exe>(std::coroutine_handle<iTaskPromise<void, Exe>>::from_promise(*this));
                }

                void unhandled_exception()
                {
                    {
                        std::unique_lock lock(_callback_mutex);
                        _result = iTaskResult<void>(std::move(std::current_exception()));
                    }
                    _callback_cv.notify_all();
                    // 执行回调
                    do_callbacks();
                }

                void return_void()
                {
                    // co_return 返回值
                    {
                        std::unique_lock lock(_callback_mutex);
                        _result = iTaskResult<void>();
                    }
                    _callback_cv.notify_all();
                    // 执行回调
                    do_callbacks();
                }

                // 同步获取值
                void get_result()
                {
                    std::unique_lock lock(_callback_mutex);
                    if (!_result.has_value())
                    {
                        // 没有值，等待通知
                        _callback_cv.wait(lock);
                    }
                    // 返回值或者抛出异常
                    _result->get_or_exception();
                }

                // task协程执行完成回调
                void on_completed(std::function<void(iTaskResult<void>)>&& func)
                {
                    std::unique_lock lock(_callback_mutex);
                    if (_result.has_value())
                    {
                        auto value = _result.value();
                        lock.unlock();
                        func(value);
                    }
                    else
                    {
                        // 协程还没有返回值或者异常，添加到队列，等待有值后执行
                        _callback_list.push_back(func);
                    }
                }

            private:

                // 执行注册的回调
                void do_callbacks()
                {
                    auto value = _result.value();
                    for (auto& callback : _callback_list)
                    {
                        callback(value);
                    }
                    // 清空回调
                    _callback_list.clear();
                }

            private:
                // 协程调度器
                Exe _executor;
                // 结果值
                std::optional<iTaskResult<void>> _result;
                // 回调队列锁
                std::mutex _callback_mutex;
                // 回调队列条件变量
                std::condition_variable _callback_cv;
                // 异步回调函数链表
                std::list<std::function<void(iTaskResult<void>)>> _callback_list;
            }; // iTaskPromise<void, Exe>

            // 协程任务
            template <typename Ret, typename Exe>
            class iTask
            {
            public:
                using promise_type = iTaskPromise<Ret, Exe>;

                explicit iTask(std::coroutine_handle<promise_type> handle) noexcept
                    : _handle(handle)
                { }

                iTask(RRef<iTask> task) noexcept
                    : _handle(std::exchange(task._handle, {}))
                { }

                iTask(CRef<iTask>) = delete;

                Ref<iTask> operator=(CRef<iTask>) = delete;

                ~iTask()
                {
                    if (_handle)
                    {
                        _handle.destroy();
                    }
                }

            public:

                // 同步获取结果
                Ret get_result()
                {
                    return _handle.promise().get_result();
                }

                // 异步回调
                Ref<iTask> then(RRef<std::function<void(Ret)>> func)
                {
                    _handle.promise().on_completed([func](iTaskResult<Ret> result)
                        {
                            try
                            {
                                func(result.get_or_exception());
                            }
                            catch (Ref<std::exception> e)
                            {
                            }
                        });
                    return *this;
                }

                // 异步错误回调
                Ref<iTask> catching(RRef<std::function<void(Ref<std::exception> e)>> func)
                {
                    _handle.promise().on_completed([func](iTaskResult<Ret> result)
                        {
                            try
                            {
                                result.get_or_exception();
                            }
                            catch (Ref<std::exception> e)
                            {
                                func(e);
                            }
                        });
                    return *this;
                }
                // 不管是否异常
                Ref<iTask> finally(RRef<std::function<void()>> func)
                {
                    _handle.promise().on_completed([func](iTaskResult<Ret> result)
                        {
                            func();
                        });
                    return *this;
                }

                // 转为 iTaskAwaiter
                auto as_awaiter()
                {
                    return iTaskAwaiter<Ret, Exe>(std::move(*this));
                }

            private:
                std::coroutine_handle<promise_type> _handle;
            }; // iTask

            // iTask void 模板特化
            template <typename Exe>
            class iTask<void, Exe>
            {
            public:
                using promise_type = iTaskPromise<void, Exe>;

                explicit iTask(std::coroutine_handle<promise_type> handle) noexcept
                    : _handle(handle)
                { }

                iTask(RRef<iTask> task) noexcept
                    : _handle(std::exchange(task._handle, {}))
                { }

                iTask(CRef<iTask>) = delete;

                Ref<iTask> operator = (CRef<iTask>) = delete;

                ~iTask()
                {
                    if (_handle)
                    {
                        _handle.destroy();
                    }
                }

            public:

                // 同步获取结果
                void get_result()
                {
                    _handle.promise().get_result();
                }

                // 异步回调
                Ref<iTask> then(RRef<std::function<void()>> func)
                {
                    _handle.promise().on_completed([func](iTaskResult<void> result)
                        {
                            try
                            {
                                result.get_or_exception();
                                func();
                            }
                            catch (CRef<std::exception> e)
                            {
                            }
                        });
                    return *this;
                }

                // 异步错误回调
                Ref<iTask> catching(RRef<std::function<void(Ref<std::exception> e)>> func)
                {
                    _handle.promise().on_completed([func](iTaskResult<void> result)
                        {
                            try
                            {
                                result.get_or_exception();
                            }
                            catch (Ref<std::exception> e)
                            {
                                func(e);
                            }
                        });
                    return *this;
                }

                // 不管是否异常
                Ref<iTask> finally(RRef<std::function<void()>> func)
                {
                    _handle.promise().on_completed([func](iTaskResult<void> result)
                        {
                            func();
                        });
                    return *this;
                }
                // 转为 iTaskAwaiter
                auto as_awaiter()
                {
                    return iTaskAwaiter<void, Exe>(std::move(*this));
                }

            private:
                std::coroutine_handle<promise_type> _handle;
            }; // iTask<void, Exe>
        }
    }
}

