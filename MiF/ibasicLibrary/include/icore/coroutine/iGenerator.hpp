/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iGenerator.hpp
* @创建时间：2022.12.27.19:34
* @创建者：ticks-tan
* -----------------------------------------------------------------------------
* i的协程懒序列生成器
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#include <icore/type/type/concepts.hpp>
#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasic.hpp>
#include <coroutine>
#include <utility>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(coroutine)
        {
            // 协程懒序列生成器
            template <typename T>
            class iGenerator :
                public basic::iBasic<iGenerator<T>>
            {
                iObject(iGenerator)
            public:
                // 序列无值异常
                class NoValueException :
                    public std::exception
                {
                public:
                    explicit NoValueException(CPtr<char> str)
                        : std::exception(), _what(str)
                    {}

                    [[nodiscard]] CPtr<char> what() const noexcept override
                    {
                        return this->_what;
                    }

                private:
                    CPtr<char> _what;
                }; // NoValueException

                struct promise_type
                {
                    // 序列值
                    T _value;
                    // 序列值是否准备好
                    bool _ready = false;

                    // 协程返回类型
                    iGenerator get_return_object()
                    {
                        return iGenerator{std::coroutine_handle<iGenerator::promise_type>::from_promise(*this)};
                    }

                    // 初始化协程，始终暂停
                    std::suspend_always initial_suspend()
                    {
                        return {};
                    }

                    // 协程结束，始终暂停
                    std::suspend_always final_suspend() noexcept
                    {
                        return {};
                    }

                    // 处理协程函数中 co_await
                    std::suspend_always await_transform(T val)
                    {
                        this->_value = val;
                        // 值已经准备好
                        this->_ready = true;
                        return {};
                    }

                    // 处理协程函数中 co_yield
                    std::suspend_always yield_value(T val)
                    {
                        this->_value = val;
                        // 值已经准备好
                        this->_ready = true;
                        return {};
                    }

                    // 协程异常处理
                    void unhandled_exception()
                    {
                        auto t = std::current_exception();
                        std::rethrow_exception(t);
                    }

                    // 协程没有返回值
                    void return_void()
                    {}

                }; // promise_type
            public:
                explicit iGenerator(std::coroutine_handle<iGenerator::promise_type> h)
                    : _handle(h)
                {}
                iGenerator(RRef<iGenerator> gen) noexcept
                    : _handle(std::exchange(gen._handle, {}))
                {}

                iGenerator(CRef<iGenerator>) = delete;

                Ref<iGenerator> operator =(CRef<iGenerator>) = delete;

                ~iGenerator()
                {
                    if (_handle)
                    {
                        _handle.destroy();
                    }
                }

            public:
                // 判断序列是否有值
                bool has_next()
                {
                    // 协程如果已经结束，没有值可获取
                    if (!_handle || _handle.done())
                    {
                        return false;
                    }
                    if (!_handle.promise()._ready)
                    {
                        // 值未准备好，恢复协程
                        _handle.resume();
                    }
                    // 判断协程是否结束
                    return !_handle.done();
                }

                // 获取下一个序列值
                T next()
                {
                    if (has_next())
                    {
                        // 值已经获取，值状态变为未准备
                        _handle.promise()._ready = false;
                        return _handle.promise()._value;
                    }
                    // 协程没有值，抛出异常
                    throw NoValueException("Current Generator have none value");
                }

                // 构造一个序列生成器
                template <typename... Args>
                iGenerator static from(Args... args)
                {
                    (co_yield args, ...);
                }

                // 遍历序列
                template <typename F>
                void for_each(F f)
                {
                    while (has_next())
                    {
                        f(next());
                    }
                }

                // 序列 map 操作，将序列映射为另外一个序列
                template <typename F>
                iGenerator<std::invoke_result_t<F, T>> map(F f)
                {
                    while (has_next())
                    {
                        co_yield f(next());
                    }
                }

                // 序列 flat_map 操作，将序列每一个元素映射成新序列，再依次展开序列
                template <typename F>
                std::invoke_result_t<F, T> flat_map(F f)
                {
                    while (has_next())
                    {
                        // 生成新序列
                        auto generator = f(next());
                        // 展开新序列
                        while (generator.has_next())
                        {
                            co_yield generator.next();
                        }
                    }
                }

                // 过滤序列值
                template <typename F>
                iGenerator filter(F f)
                {
                    while (has_next())
                    {
                        T val = next();
                        if (f(val))
                        {
                            co_yield val;
                        }
                    }
                }

                // 截取前 n 个值
                iGenerator task(uint n)
                {
                    uint i = 0;
                    while (i++ < n && has_next())
                    {
                        co_yield next();
                    }
                }

                // 截取值，直到满足条件
                template <typename F>
                iGenerator take_with(F f)
                {
                    while (has_next())
                    {
                        T val = next();
                        if (f(val))
                        {
                            co_yield val;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                // 序列求和
                template <Numeric U>
                auto sum()
                {
                    U sum;
                    while (has_next())
                    {
                        sum += next();
                    }
                    return sum;
                }

            private:
                std::coroutine_handle<iGenerator::promise_type> _handle;
            }; // iGenerator
        }
    }
}
