/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iLevel.hpp
* @创建时间：2022.5.20.13:00
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* 祝大家520快乐！
* 等级
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasicDataType.h>

#undef FALSE
#undef TRUE

SPACE(i)
{
    SPACE(core)
    {
        SPACE(type)
        {

            enum class Level
                :int
            {
                unk = -2,
                φ = -1,
                FALSE,
                I,
                A,
                B,
                C,
                D,
                E,
                F,
                G,
                H
            };//ECLASS(Level)

            class IAPI iLevel
                : public i::core::basic::iBasicDataType<iLevel, Level>
            {
                iObject(iLevel);
            public:

                iLevel(int lv = 0);

                iLevel(Level lv);

                iLevel(CRef<iLevel> lv);

                ~iLevel();

            public:

                virtual Level data()const;

            public:

                Level getlv()const;

                Level getLevel()const;

                void setLevel(Level _iLevel);

                void setLevel(int _iLevel);

            public:

                static int getNumFromLevel(Level lv);

                static Level getLevelFromNum(int lv);

            public:

                Ref<iLevel> operator=(int lv);

                Ref<iLevel> operator=(CRef<iLevel> lv);

                bool operator==(int lv);

                bool operator==(CRef<Level> lv);

                bool operator>(int lv);

                bool operator>(CRef<Level> lv);

                bool operator<(int lv);

                bool operator<(CRef<Level> lv);

                bool operator>=(int lv);

                bool operator>=(CRef<Level> lv);

                bool operator<=(int lv);

                bool operator<=(CRef<Level> lv);

                bool operator!=(int lv);

                bool operator!=(CRef<Level> lv);

            protected:
            private:
                Level _lv;
            };//class iLevel

        }//SPACE(type)
    }//SPACE(core)
}//SPACE(i)
