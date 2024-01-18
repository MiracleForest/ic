#include "../../include/iAST/iASTImportStatementNode.h"
using namespace MiracleForest::i::icFamily::AST;


iASTImportStatementNode::iASTImportStatementNode()
    : parentModuleList({})
    , importModule("")
    , nicknameList({})
    , iASTNode(nullptr, iASTNodeType::iASTImportStatementNode, "iASTImportStatementNode", 0, false, {})
{
}

iASTImportStatementNode::iASTImportStatementNode(
    std::vector<std::string> pparentModuleList,
    CRef<std::string>        pimportModule,
    std::vector<std::string> pnicknameList
)
    : parentModuleList(pparentModuleList)
    , importModule(pimportModule)
    , nicknameList(pnicknameList)
    , iASTNode(nullptr, iASTNodeType::iASTImportStatementNode, "iASTImportStatementNode", 0, false, {})
{
}

iASTImportStatementNode::~iASTImportStatementNode() {}

Ptr<iASTImportStatementNode> iASTImportStatementNode::addNickname(CRef<std::string> nickname)
{
    this->nicknameList.push_back(nickname);
    return this;
}

Ptr<iASTImportStatementNode> iASTImportStatementNode::pushBackParentModule(CRef<std::string> parentModule)
{
    this->parentModuleList.push_back(parentModule);
    return this;
}

std::string iASTImportStatementNode::getImportModule() const noexcept
{
    return this->importModule;
}

std::vector<std::string> iASTImportStatementNode::getParentModuleList() const noexcept
{
    return this->parentModuleList;
}

std::vector<std::string> iASTImportStatementNode::getNicknameList() const noexcept
{
    return this->nicknameList;
}

Ptr<iASTImportStatementNode> iASTImportStatementNode::setParentModuleList(
    std::vector<std::string> pparentModuleList
)
{
    this->parentModuleList = pparentModuleList;
    return this;
}

Ptr<iASTImportStatementNode> iASTImportStatementNode::setImportModule(CRef<std::string> pimportModule)
{
    this->importModule = pimportModule;
    return this;
}

Ptr<iASTImportStatementNode> iASTImportStatementNode::setNicknameList(std::vector<std::string> pnicknameList)
{
    this->nicknameList = pnicknameList;
    return this;
}
