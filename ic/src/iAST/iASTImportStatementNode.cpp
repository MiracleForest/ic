#include "../../include/iAST/iASTImportStatementNode.h"
using namespace i::icFamily::AST;
using namespace i::core;

iASTImportStatementNode::iASTImportStatementNode()
	: parentModuleList({})
	, importModule("")
	, nicknameList({})
	, iASTNode(nullptr, iASTNodeType::iASTImportStatementNode, "iASTImportStatementNode", 0, false, {})
{ }

iASTImportStatementNode::iASTImportStatementNode(std::vector<istring> pparentModuleList, CRef<istring> pimportModule, std::vector<istring> pnicknameList)
	: parentModuleList(pparentModuleList)
	, importModule(pimportModule)
	, nicknameList(pnicknameList)
	, iASTNode(nullptr, iASTNodeType::iASTImportStatementNode, "iASTImportStatementNode", 0, false, {})
{ }

iASTImportStatementNode::~iASTImportStatementNode()
{ }

Ptr<iASTImportStatementNode> iASTImportStatementNode::addNickname(CRef<istring> nickname)
{
	this->nicknameList.push_back(nickname);
	return this;
}

Ptr<iASTImportStatementNode> iASTImportStatementNode::pushBackParentModule(CRef<istring> parentModule)
{
	this->parentModuleList.push_back(parentModule);
	return this;
}

iASTImportStatementNode::istring iASTImportStatementNode::getImportModule()const noexcept
{
	return this->importModule;
}

std::vector<iASTImportStatementNode::istring> iASTImportStatementNode::getParentModuleList()const noexcept
{
	return this->parentModuleList;
}

std::vector<iASTImportStatementNode::istring> iASTImportStatementNode::getNicknameList()const noexcept
{
	return this->nicknameList;
}

Ptr<iASTImportStatementNode> iASTImportStatementNode::setParentModuleList(std::vector<istring> pimportModuleList)
{
	this->importModuleList = pimportModuleList;
	return this;
}

Ptr<iASTImportStatementNode> iASTImportStatementNode::setImportModule(CRef<istring> pimportModule)
{
	this->importModule = pimportModule;
	return this;
}

Ptr<iASTImportStatementNode> iASTImportStatementNode::setNicknameList(std::vector<istring> pnicknameList)
{
	this->nicknameList = pnicknameList;
	return this;
}

