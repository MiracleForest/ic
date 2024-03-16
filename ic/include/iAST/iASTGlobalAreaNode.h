/*
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iParser.h
 * @创建时间:2022.7.1.22:26
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iASTGlobalAreaNode
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include "../family/iicfamily.h"
#include "iASTCompoundExpressionNode.h"
#include "iASTForStatementNode.h"
#include "iASTImportStatementNode.h"
#include "iASTNode.h"
#include "iASTStringLiteralNode.h"
#include "iASTBinaryOperatorNode.h"
#include "iASTFloatingLiteralNode.h"
#include "iASTIntegerLiteralNode.h"
#include "iASTReturnStatementNode.h"
#include "iASTTernaryOperatorNode.h"
#include "iASTTypeNode.h"
#include "iASTUnaryOperatorNode.h"
#include "iASTVariableDefinitionNode.h"

namespace MiracleForest::inline i
{
namespace icFamily
{
    namespace AST
    {
        class ICAPI iASTGlobalAreaNode : public iASTNode
        {
        private:
            mutable int _childElementsListIndex;

        public:
            std::vector<Ptr<iASTNode>> childElementsList;

        public:
            iASTGlobalAreaNode();

            iASTGlobalAreaNode(Ptr<iASTNode> childElements);

            iASTGlobalAreaNode(std::vector<Ptr<iASTNode>> childElementsList);

            ~iASTGlobalAreaNode();

        public:
        public:
            int           getCount() const;
            int           getIndex() const;
            Ptr<iASTNode> getNext() const;
            Ptr<iASTNode> get() const;

            Ptr<iASTGlobalAreaNode> setNext(Ptr<iASTNode> node);
            Ptr<iASTGlobalAreaNode> set(Ptr<iASTNode> node);
            Ptr<iASTGlobalAreaNode> setIndex(int index);

            Ptr<iASTGlobalAreaNode> add(Ptr<iASTNode> node);
            Ptr<iASTGlobalAreaNode> remove();
            Ptr<iASTGlobalAreaNode> next() const;
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i