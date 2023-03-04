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
#include <icore/basic/iBasic.hpp>

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

            class iLevel
                : public i::core::basic::iBasicDataType<iLevel, Level>
            {
                iObject(iLevel);
            public:

                iLevel(int lv = 0) :_lv(getLevelFromNum(lv))
                { }

                iLevel(Level lv) :_lv(lv)
                { }

                iLevel(CRef<iLevel> lv) :_lv(lv.getLevel())
                { }

                ~iLevel()
                { }

            public:

                virtual Level data()const
                {
                    return _lv;
                }

            public:

                Level getlv()const
                {
                    return _lv;
                }

                Level getLevel()const
                {
                    return _lv;
                }

                void setLevel(Level _iLevel)
                {
                    _lv = _iLevel;
                }

                void setLevel(int _iLevel)
                {
                    _lv = getLevelFromNum(_iLevel);
                }

            public:

                static int getNumFromLevel(Level lv)
                {
                    return (int)lv;
                }

                static Level getLevelFromNum(int lv)
                {
                    return (Level)lv;
                }


            public:

                Ref<iLevel> operator=(int lv)
                {
                    _lv = getLevelFromNum(lv);
                    return *this;
                }

                Ref<iLevel> operator=(CRef<iLevel> lv)
                {
                    _lv = lv.data();
                    return *this;
                }

                bool operator==(int lv)
                {
                    return getNumFromLevel(_lv) == lv;
                }

                bool operator==(CRef<Level> lv)
                {
                    return getNumFromLevel(_lv) == getNumFromLevel(lv);
                }

                bool operator>(int lv)
                {
                    return getNumFromLevel(_lv) > lv;
                }

                bool operator>(CRef<Level> lv)
                {
                    return getNumFromLevel(_lv) > getNumFromLevel(lv);
                }

                bool operator<(int lv)
                {
                    return getNumFromLevel(_lv) < lv;
                }

                bool operator<(CRef<Level> lv)
                {
                    return getNumFromLevel(_lv) < getNumFromLevel(lv);
                }

                bool operator>=(int lv)
                {
                    return getNumFromLevel(_lv) >= lv;
                }

                bool operator>=(CRef<Level> lv)
                {
                    return getNumFromLevel(_lv) >= getNumFromLevel(lv);
                }

                bool operator<=(int lv)
                {
                    return getNumFromLevel(_lv) <= lv;
                }

                bool operator<=(CRef<Level> lv)
                {
                    return getNumFromLevel(_lv) <= getNumFromLevel(lv);
                }

                bool operator!=(int lv)
                {
                    return getNumFromLevel(_lv) != lv;
                }

                bool operator!=(CRef<Level> lv)
                {
                    return getNumFromLevel(_lv) != getNumFromLevel(lv);
                }

            protected:
            private:
                Level _lv;
            };//class iLevel

        }//SPACE(type)
    }//SPACE(core)
}//SPACE(i)
