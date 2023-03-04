/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iBStream.hpp
* @创建时间：2023.1.2.13:02
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* BStream
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
//#define _USE_WINDOWS_H__

#include <icore/family/imacrofamily.h>
#include <icore/type/type/type.hpp>
#include <icore/basic/iBasic.hpp>
#include <cstdint>
#include <cstring>
#include <list>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <vector>

#ifdef BUF_CHK
#    define DO_BUF_CHK() assert(datamax > data)
#    define BUF_CHK_VAR uintptr_t datamax
#else
#    define DO_BUF_CHK()
#    define BUF_CHK_VAR
#endif

SPACE(i)
{
    SPACE(core)
    {
        SPACE(data)
        {

            template <class T>
            struct is_safe_obj
                : std::integral_constant<bool, !std::is_class<std::remove_reference_t<T>>::value>
            { };

            typedef uint bsize_t;

            class iRBStream
                :public basic::iBasic<iRBStream>
            {
                iObject(iRBStream)
            public:

                uintptr_t data;
                BUF_CHK_VAR;

            public:

                iRBStream(unkType dat, size_t len)
                {
                    data = (uintptr_t)dat;
                    (void)len;
#ifdef BUF_CHK
                    datamax = data;
                    datamax += len;
#endif
                }

                iRBStream(std::string_view x)
                {
                    *this = {
                        (unkType)x.data(),
                        (size_t)x.size()
                    };
                }

            private:

                template <typename T1, typename T2>
                void __get(Ref<std::unordered_map<T1, T2>> x)
                {
                    bsize_t sz;
                    __get(sz);
                    x.reserve(sz);
                    for (bsize_t i = 0; i < sz; ++i)
                    {
                        T1 local;
                        T2 local2;
                        __get(local);
                        __get(local2);
                        x.insert({ std::move(local), std::move(local2) });
                    }
                }

                template <typename T1>
                void __get(Ref<std::vector<T1>> x)
                {
                    bsize_t sz;
                    __get(sz);
                    x.reserve(sz);
                    for (bsize_t i = 0; i < sz; ++i)
                    {
                        T1 local;
                        __get(local);
                        x.push_back(std::move(local));
                    }
                }

                template <typename T1>
                void __get(Ref<std::list<T1>> x)
                {
                    bsize_t sz;
                    __get(sz);
                    for (bsize_t i = 0; i < sz; ++i)
                    {
                        T1 local;
                        __get(local);
                        x.push_back(std::move(local));
                    }
                }

                void __get(Ref<std::string> x)
                {
                    bsize_t sz;
                    __get(sz);
                    x.reserve(sz);
                    x.append((CPtr<char>)data, sz);
                    data += sz;
                    DO_BUF_CHK();
                }

                template <typename T>
                void __get(Ref<T> x)
                {
                    if constexpr (is_safe_obj<T>())
                    {
                        static_assert(!std::is_reference<T>());
                        memcpy(&x, (unkType)data, sizeof(x));
                        data += sizeof(T);
                        DO_BUF_CHK();
                    }
                    else
                    {
                        x.unpack(*this);
                    }
                }

            public:

                template <typename... T>
                void apply(Ref<T>... args)
                {
                    (__get(args), ...);
                }

                void read(unkType dst, size_t n)
                {
                    memcpy(dst, (unkType)data, n);
                    data += n;
                    DO_BUF_CHK();
                }

            };

            template <typename container>
            class iWBStreamImpl :
                public basic::iBasic<iWBStreamImpl<container>>
            {
                iObject(iWBStreamImpl)
            public:

                container data;

            private:

                template <typename T1, typename T2>
                void __put(Ref<std::unordered_map<T1, T2> const> x)
                {
                    bsize_t sz = (bsize_t)x.size();
                    __put(sz);
                    for (auto& [k, v] : x)
                    {
                        __put(k);
                        __put(v);
                    }
                }

                template <typename T2>
                void __put(Ref<std::vector<T2> const> x)
                {
                    bsize_t sz = x.size();
                    __put(sz);
                    for (auto i = x.begin(); i != x.end(); ++i)
                    {
                        __put(*i);
                    }
                }

                template <typename T2>
                void __put(Ref<std::list<T2> const> x)
                {
                    bsize_t sz = (bsize_t)x.size();
                    __put(sz);
                    for (auto i = x.begin(); i != x.end(); ++i)
                    {
                        __put(*i);
                    }
                }

                void __put(Ref<std::string const> x)
                {
                    __put((bsize_t)x.size());
                    data.append(x);
                }

                void __put(Ref<std::string_view const> x)
                {
                    __put((bsize_t)x.size());
                    data.append(x);
                }

                template <typename T>
                void __put(CRef<T> x)
                {
                    if constexpr (is_safe_obj<T>())
                    {
                        data.append((CPtr<char>) & x, sizeof(T));
                    }
                    else
                    {
                        x.pack(*this);
                    }
                }

            public:

                iWBStreamImpl()
                { }

                iWBStreamImpl(RRef<container> x)
                    : data(x)
                { }

            public:

                template <typename... T>
                void apply(CRef<T>... args)
                {
                    (__put(args), ...);
                }

                void write(const unkType src, size_t n)
                {
                    data.append((CPtr<char>)src, n);
                }

            public:

                operator std::string_view()
                {
                    return data;
                }
            };

            using iWBStream = iWBStreamImpl<std::string>;

            class iBinVariant
                :public basic::iBasic<iBinVariant>
            {
                iObject(iBinVariant)
            public:

                union VType
                {
                    int64 x;
                    std::string y;

                    VType()
                    { }

                    ~VType()
                    { }
                } v;

            public:

                uchar type;

            public:

                iBinVariant(int64 x)
                {
                    type = 1;
                    v.x = x;
                }


                iBinVariant(RRef<std::string> x)
                {
                    type = 2;
                    new (&v.y) std::string(std::move(x));
                }

                iBinVariant(CRef<std::string> x)
                {
                    type = 2;
                    new (&v.y) std::string(x);
                }

                iBinVariant()
                {
                    type = 0;
                }

                ~iBinVariant()
                {
                    if (type == 2)
                    {
                        v.y.~basic_string();
                    }
                }

            public:

                void unpack(Ref<iWBStream> rs)
                {
                    rs.apply(type);
                    switch (type)
                    {
                    case 1:
                    {
                        rs.apply(v.x);
                    } break;
                    case 2:
                    {
                        new (&v.y) std::string();
                        rs.apply(v.y);
                    }
                    }
                }

                void pack(Ref<iWBStream> ws) const
                {
                    ws.apply(type);
                    switch (type)
                    {
                    case 1:
                    {
                        ws.apply(v.x);
                    } break;
                    case 2:
                    {
                        ws.apply(v.y);
                    }
                    }
                }
            };

            static inline uint64 zigZag(int64 x)
            {
                return (x << 1) ^ (x >> 63);
            }

        }
    }
}

#ifdef INCLUDE_NLOHMANN_JSON_HPP_

SPACE(nlohmann)
{

}

#endif//^^^^INCLUDE_NLOHMANN_JSON_HPP_

