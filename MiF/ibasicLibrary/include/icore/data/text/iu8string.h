/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：istring.hpp
* @创建时间：2023.1.1.0:0
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* i UTF-8编码字符串类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/data/text/iChar.h>
#include <icore/data/text/iEncoding.h>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(data)
        {
            SPACE(text)
            {
                class IAPI iu8string final
                    : public i::core::basic::iBasicDataType<iu8string, Ptr<char8_t>>
                {
                    iObject(iu8string);
                private:

                    Ptr<char8_t> _data;

                public:

                }


            }
        }
    }
}