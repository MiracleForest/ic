/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iASTImportStatementNode.h
 * @创建时间:2023.10.21.17:13
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iASTImportStatementNode
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include "../family/iicfamily.h"
#include "iASTNode.h"
#include "iASTTypeNode.h"

namespace MiracleForest::inline i
{
namespace icFamily
{
    namespace AST
    {
        class ICAPI iASTImportStatementNode : public iASTNode
        {
        public:
            std::vector<std::string> parentModuleList;
            std::string              importModule;
            std::vector<std::string> nicknameList;

        public:
            iASTImportStatementNode();

            iASTImportStatementNode(
                std::vector<std::string> pparentModuleList,
                CRef<std::string>        pimportModule,
                std::vector<std::string> pnicknameList
            );

            ~iASTImportStatementNode();

        public:
            Ptr<iASTImportStatementNode> addNickname(CRef<std::string> nickname);

            /*
             * @warning vector<std::string>的顺序代表着各级模块的所属关系
             */
            Ptr<iASTImportStatementNode> pushBackParentModule(CRef<std::string> parentModule);

            [[nodiscard]] std::string              getImportModule() const noexcept;
            [[nodiscard]] std::vector<std::string> getParentModuleList() const noexcept;
            [[nodiscard]] std::vector<std::string> getNicknameList() const noexcept;

            Ptr<iASTImportStatementNode> setParentModuleList(std::vector<std::string> pparentModuleList);
            Ptr<iASTImportStatementNode> setImportModule(CRef<std::string> pimportModule);
            Ptr<iASTImportStatementNode> setNicknameList(std::vector<std::string> pnicknameList);
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i