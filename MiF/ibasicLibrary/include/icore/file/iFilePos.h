/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iFilePos.hpp
* @创建时间：2022.5.20.12:59
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* 祝大家520快乐！
* 文件坐标
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasicDataType.h>
#include <icore/data/text/istring.h>
#include <source_location>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(io)
        {

            struct fPos
            {
                data::text::istring _fileName = "";
                int x = 0;
                int y = 0;
            };//struct fPos


            class IAPI iFilePos
                : public _ISTD basic::iBasicDataType<iFilePos, fPos>
            {
                using istring = data::text::istring;
                iObject(iFilePos);
            public:

                iFilePos();

                iFilePos(istring fileName, int x, int y);

                iFilePos(fPos pos);

                iFilePos(std::source_location loc);

                ~iFilePos();

            public:

                istring getFileName()const;

                void setFileName(istring fileName);

                int getX() const;

                void setX(int x);

                void setY(int y);

                int getY()const;

                fPos data()const;

            public:
            protected:
            private:
                fPos _pos;
            };//class iFilePos

        }//SPACE(type)
    }//SPACE(core)
}//SPACE(i)
