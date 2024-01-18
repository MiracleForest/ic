/*
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iToken.h
 * @创建时间:2022.3.4.14:03
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * Token
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include "../family/iicfamily.h"

namespace MiracleForest::inline i
{
namespace icFamily
{

    enum class iTokenID
    {
        Unk = -1,
        String,
        Number,
        Identifier,
        Keyword,
        Operator,
        EOL,
        EOF_
    }; // enum class iTokenID


    class ICAPI iToken
    {
        using uchar = unsigned char;
        using uint  = unsigned int;
    public:
        iToken();

        iToken(iTokenID token_id, int currentLine, std::string text);

        iToken(CRef<iToken> itoken);

    public:
        // 获取文本
        std::string getText() const noexcept;

        // 获取编号
        iTokenID getID() const noexcept;

        int getLine() const noexcept;

        // 设置文本
        void setText(CRef<std::string> text);

    public:
        std::string getID2String() const;

    public:
        Ref<iToken> operator=(CRef<iToken>);

    private:
        std::string _text;
        iTokenID    _ID;
        int         _currentLine;

    }; // iToken

} // namespace icFamily
} // namespace MiracleForest::inline i