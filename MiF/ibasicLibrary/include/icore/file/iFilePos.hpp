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
#include <icore/basic/iBasicDataType.hpp>
#include <icore/data/text/istring.hpp>
#include <source_location>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(type)
        {

            struct fPos
            {
                data::text::istring _fileName = "";
                int x = 0;
                int y = 0;
            };//struct fPos


            class iFilePos
                : public _ISTD basic::iBasicDataType<iFilePos, fPos>
            {
                using istring = data::text::istring;
            public:virtual itype getType()const
            {
                return iType::iFilePos;
            }virtual void destructor()const
            {
                iFilePos::~iFilePos();
            }private:;
            public:

                iFilePos() :_pos({})
                { }

                iFilePos(istring fileName, int x, int y) :_pos({ fileName, x, y })
                { }

                iFilePos(fPos pos) :_pos(pos)
                { }

                iFilePos(std::source_location loc)
                {
                    _pos._fileName = loc.file_name();
                    _pos.x = loc.column();
                    _pos.y = loc.line();
                }

                ~iFilePos()
                { }

            public:

                istring getFileName()const
                {
                    return _pos._fileName;
                }

                void setFileName(istring fileName)
                {
                    _pos._fileName = fileName;
                }

                int getX() const
                {
                    return _pos.x;
                }

                void setX(int x)
                {
                    _pos.x = x;
                }

                void setY(int y)
                {
                    _pos.y = y;
                }

                int getY()const
                {
                    return _pos.y;
                }

                fPos data()const
                {
                    return _pos;
                }

            public:
            protected:
            private:
                fPos _pos;
            };//class iFilePos

        }//SPACE(type)
    }//SPACE(core)
}//SPACE(i)
