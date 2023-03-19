/****
*
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名：iPlural.hpp
 * @创建时间：2023.2.22.21:00
 * @创建者：Minsecrus
 * -----------------------------------------------------------------------------
 * iBasicLibrary 名词变复数工具
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 *
 ****/

#pragma once
#include "icore/basic/iBasic.hpp"
#include "icore/data/text/istring.hpp"
#include "icore/family/imacrofamily.h"

SPACE(i)
{
    SPACE(core)
    {
        SPACE(tool)
        {
            class iPlural : basic::iBasic<iPlural>
            {
                using istring = data::text::istring;
                iObject(iPlural)
            public:

                // TODO lots of things
                /**
                 * maybe the plurals of most of words are chaotic
                 * @param s a noun to become plural
                 */
                static istring plural(istring s)
                {
                    if (s.endsWith("s") || s.endsWith("x") || s.endsWith("ch") || s.endsWith("sh"))
                    {
                        return s + "es";
                    }
                    if (s.endsWith("f"))
                    {
                        return s.replaceLast("f","ves");
                    }
                    if(s.endsWith("fe"))
                    {
                        return s.replaceLast("fe","ves");
                    }

                    return s + "s";
                }
            };
        }
    }
}
