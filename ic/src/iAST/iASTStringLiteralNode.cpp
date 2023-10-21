#include "../../include/iAST/iASTStringLiteralNode.h"
using namespace i::icFamily::AST;
using namespace i::core;

iASTStringLiteralNode::iASTStringLiteralNode()
	:data("")
	, iASTNode(nullptr, iASTNodeType::iASTStringLiteralNode, "iASTStringLiteralNode", 0, false, {})
{ }

iASTStringLiteralNode::iASTStringLiteralNode(istring data)
	:data(data)
	, iASTNode(nullptr, iASTNodeType::iASTStringLiteralNode, "iASTStringLiteralNode", 0, false, {})
{ }

iASTStringLiteralNode::~iASTStringLiteralNode()
{
	//basic::iBasic<iASTNode>::destroy(parent);
}


auto iASTStringLiteralNode::get()const noexcept->istring
{
	return this->data;
}

Ptr<iASTStringLiteralNode> iASTStringLiteralNode::set(CRef<istring> data)
{
	this->data = data;
	return this;
}