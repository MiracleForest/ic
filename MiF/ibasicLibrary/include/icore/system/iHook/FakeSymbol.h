/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：FakeSymbol.hpp
* @创建时间：2022.10.3.21:44
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
*
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
//#define _USE_WINDOWS_H__

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasic.h>
#include <Demangler/include/MicrosoftDemangle.h>
#include <optional>
#include <string>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(gadgets)
        {

            class IAPI gFakeSymbol
            {
            public:

                static llvm::ms_demangle::SpecialIntrinsicKind consumeSpecialIntrinsicKind(Ref<StringView> MangledName);

                // generate fakeSymbol for virtual functions
                static std::optional<std::string> getFakeSymbol(CRef<std::string> fn);

            };//class gFakeSymbol

        }//SPACE(gadgets)
    }//SPACE(core)
}//SPACE(i)
