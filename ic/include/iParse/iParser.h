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
#include <Logger.h>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace MiracleForest::inline i
{
namespace icFamily
{
    inline Logger iParserLogger("iParser");

    class ICAPI iParser
    {
        using Pending                    = void;
        using iASTNode                   = AST::iASTNode;
        using iASTGlobalAreaNode         = AST::iASTGlobalAreaNode;
        using iASTStatementNode          = AST::iASTNode;
        using iASTImportStatementNode    = AST::iASTImportStatementNode;
        using iASTForStatementNode       = AST::iASTForStatementNode;
        using iASTVariableDefinitionNode = AST::iASTVariableDefinitionNode;
        using iASTBinaryOperatorNode     = AST::iASTBinaryOperatorNode;
        using iASTUnaryOperatorNode      = AST::iASTUnaryOperatorNode;
        using iASTLiteralNode            = AST::iASTNode;
        using iASTIntegerLiteralNode     = AST::iASTIntegerLiteralNode;
        using iASTFloatingLiteralNode    = AST::iASTFloatingLiteralNode;

    public:
        enum class iParserMatchedState
        {
            Unknow = -1,
            Already,
            ErrorP1,
            ErrorP2,
            End
        };

    private:
        std::vector<iToken> mTokens;
        size_t              mCurrent;
        bool                mParseEnd;

    public:
        iParser(CRef<std::vector<iToken>> tokens);

        ~iParser();

    public:
        Ptr<iASTGlobalAreaNode> parse();

        iParserMatchedState match(
            std::optional<iTokenID>         id       = std::nullopt,
            std::optional<std::string_view> matchstr = std::nullopt
        )
        {
            if (id.has_value() && mTokens[mCurrent].getID() != id.value())
            {
                iParserLogger
                    .error("无法将ID:{}与ID:{}匹配！", mTokens[mCurrent].getID2String(), (int)id.value());
                return iParserMatchedState::ErrorP1;
            }
            if (matchstr.has_value() && mTokens[mCurrent].getText() != matchstr.value())
            {
                iParserLogger
                    .error("无法将内容:{}与内容:{}匹配！", mTokens[mCurrent].getText(), matchstr.value());
                return iParserMatchedState::ErrorP2;
            }
            if (_nextToken()) { return iParserMatchedState::Already; }
            else
            {
                mParseEnd = true;
                iParserLogger.info("解析结束！");
                return iParserMatchedState ::End;
            }
            return iParserMatchedState::Unknow;
        }

    private:
        bool _nextToken()
        {
            if (mTokens.size() > mCurrent + 1)
            {
                mCurrent++;
                return true;
            }
            return false;
        }

        bool _lastToken()
        {
            if (mCurrent > 0)
            {
                mCurrent--;
                return true;
            }
            return false;
        }

    private:
        Ptr<iASTGlobalAreaNode> program()
        {
            Ptr<AST::iASTGlobalAreaNode> node = new AST::iASTGlobalAreaNode();
            while (!mParseEnd) { node->add(statement()); }
            return node;
        }

        Ptr<iASTNode> statement()
        {
            if (mTokens[mCurrent].getID() == iTokenID::Keyword && mTokens[mCurrent].getText() == "import")
            {
                return importStatement();
            }
            else if (((mTokens.size() - mCurrent) >= 5))
            {
                if (mTokens[mCurrent].getID() == iTokenID::Keyword
                    && mTokens[mCurrent + 1].getID() == iTokenID::Identifier
                    && mTokens[mCurrent + 2].getText() == "(")
                {
                    return function();
                }
            }
            iParserLogger.error("输入代码包含语法错误！");
            return nullptr;
        }

        Ptr<iASTImportStatementNode> importStatement()
        {
            Ptr<iASTImportStatementNode> node = new iASTImportStatementNode();
            match(iTokenID::Keyword, "import");
            node->mModule = hierarchicalInclusionExpression();
            match(iTokenID::Operator, ";");
            return node;
        }

        std::string hierarchicalInclusionExpression()
        {
            std::string result = "";
            if (mTokens[mCurrent].getText() == ";") { return ""; }
            match(iTokenID::Identifier);
            result += mTokens[mCurrent - 1].getText();
            while (mTokens[mCurrent].getText() != ";")
            {
                match(iTokenID::Operator, ".");
                result += ".";
                match(iTokenID::Identifier);
                result += mTokens[mCurrent - 1].getText();
            }
            return result;
        }

        struct iASTParamListNode : public iASTNode
        {
            std::vector<std::pair<std::string, std::string>> mParamList;
        };

        struct iASTFunctionNode : public iASTNode
        {
            std::string                mReturnType;
            std::string                mName;
            Ptr<iASTParamListNode>     mParamList = nullptr;
            std::vector<Ptr<iASTNode>> mBody;
        };

        struct iASTRealParamListNode : public iASTNode
        {
            std::vector<std::string> mRealParam;
        };

        struct iASTFunctionCallNode : public iASTNode
        {
            std::string                mCalledFunctionName;
            Ptr<iASTRealParamListNode> mRealParamList = nullptr;
        };

        Ptr<iASTFunctionNode> function()
        {
            Ptr<iASTFunctionNode> node = new iASTFunctionNode();
            match(iTokenID::Keyword);
            node->mReturnType = mTokens[mCurrent - 1].getText();
            match(iTokenID::Identifier);
            node->mName = mTokens[mCurrent - 1].getText();
            match(iTokenID::Operator, "(");
            node->mParamList = paramList();
            match(iTokenID::Operator, ")");
            node->mBody = functionBody();
            return node;
        }

        Ptr<iASTParamListNode> paramList()
        {
            if (mTokens[mCurrent].getText() == ")") { return nullptr; }
            Ptr<iASTParamListNode> node = new iASTParamListNode();
            match(iTokenID::Keyword);
            match(iTokenID::Identifier);
            node->mParamList.push_back(
                std::make_pair<>(mTokens[mCurrent - 2].getText(), mTokens[mCurrent - 1].getText())
            );
            while (mTokens[mCurrent].getText() != ")")
            {
                match(iTokenID::Operator, ",");
                std::pair<std::string, std::string> p {};
                match(iTokenID::Keyword);
                p.first = mTokens[mCurrent - 1].getText();
                match(iTokenID::Identifier);
                p.second = mTokens[mCurrent - 1].getText();
                node->mParamList.push_back(p);
            }
            return node;
        }

        Ptr<iASTNode> expression() { return functionCall(); }

        std::vector<Ptr<iASTNode>> functionBody()
        {
            std::vector<Ptr<iASTNode>> nodevec {};
            match(iTokenID::Operator, "{");
            while (mTokens[mCurrent].getText() != "}") { nodevec.push_back(expression()); }
            match(iTokenID::Operator, "}");
            return nodevec;
        }

        Ptr<iASTFunctionCallNode> functionCall()
        {
            Ptr<iASTFunctionCallNode> node = new iASTFunctionCallNode();
            match(iTokenID::Identifier);
            node->mCalledFunctionName = mTokens[mCurrent - 1].getText();
            match(iTokenID::Operator, "(");
            node->mRealParamList = realParamList();
            match(iTokenID::Operator, ")");
            match(iTokenID::Operator, ";");
            return node;
        }

        Ptr<iASTRealParamListNode> realParamList()
        {
            if (mTokens[mCurrent].getText() == ")") { return nullptr; }
            Ptr<iASTRealParamListNode> node = new iASTRealParamListNode();
            node->mRealParam.push_back(realParam());
            while (mTokens[mCurrent].getText() != ")")
            {
                match(iTokenID::Operator, ",");
                node->mRealParam.push_back(realParam());
            }
            return node;
        }

        std::string realParam()
        {
            switch (mTokens[mCurrent].getID())
            {
                case iTokenID::String:
                case iTokenID::Number:
                [[likely]] case iTokenID::Identifier: {
                    match();
                    return mTokens[mCurrent - 1].getText();
                    break;
                }
                default: {
                    break;
                }
            }
            iParserLogger.error("非法的参数类型：{}", mTokens[mCurrent].getID2String());
            return "";
        }
    };
} // namespace icFamily
} // namespace MiracleForest::inline i