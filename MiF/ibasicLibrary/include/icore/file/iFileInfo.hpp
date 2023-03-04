/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iFileInfo.hpp
* @创建时间：2022.9.9.9:19
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* iFileInfo
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#include <icore/family/imacrofamily.h>
#include <icore/type/iTime.hpp>

#include <memory>
#include <fstream>
#include <optional>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(io)
        {

            struct iFileInfo
            {
                using istring = data::text::istring;
                using iTime = i::core::type::iTime;

                istring name = "";            //文件名
                istring fname = "";           //文件名（含扩展名）
                istring path = "";            //文件路径
                istring extensionName = "";   //扩展名
                size_t size = 0;                    //文件大小
                int lineCount = 0;                  //文件行数
                iTime createTime = {};        //创建时间
                iTime modifyTime = {};        //修改时间
                __unk_type__ md5 = nullptr;         //md5
                __unk_type__ authority = nullptr;   //权限
                iTime lastVisitTime = {};     //最后访问时间
                bool isBinary = false;              //是否为二进制文件
            };//struct iFileInfo

        }//SPACE(file)
    }//SPACE(core)
}//SPACE(i)