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
#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasic.h>
#include <icore/data/text/istring.h>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(tool)
        {
            class IAPI iPlural : basic::iBasic<iPlural>
            {
                using istring = data::text::istring;
                iObject(iPlural)
            public:

                // TODO lots of things
                /**
                 * maybe the plurals of most of words are chaotic
                 * @param s a noun to become plural
                 */
                static istring plural(istring s);
            };
        }
    }
}
