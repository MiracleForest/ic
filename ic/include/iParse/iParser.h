/*
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iParser.h
 * @创建时间:2022.7.1.22:26
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iParser
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include "../family/iicfamily.h"
#include "../iAST/iASTGlobalAreaNode.h"
#include "../iLexer/iToken.h"

namespace MiracleForest::inline i
{
namespace icFamily
{

    class ICAPI iParser
    {
        using iASTGlobalAreaNode = AST::iASTGlobalAreaNode;
        using iASTStatementNode  = AST::iASTNode;

    private:
        std::vector<MiracleForest::i::icFamily::iToken> _tokens;

    public:
        iParser(CRef<std::vector<MiracleForest::i::icFamily::iToken>> tokens);

        ~iParser();

    public:
        Ptr<iASTGlobalAreaNode> parse();

    private:
        Ptr<iASTGlobalAreaNode> program();
        Ptr<iASTGlobalAreaNode> program_();
        Ptr<iASTStatementNode>  statement();
    };
} // namespace icFamily
} // namespace MiracleForest::inline i