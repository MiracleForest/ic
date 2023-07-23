#include "../../include/iAST/iASTStringLiteralNode.h"
using namespace i::icSystem::AST;
using namespace i::core;

iASTStringLiteralNode::iASTStringLiteralNode()
	:_data("")
	, iASTNode(nullptr, iASTNodeType::iASTStringLiteralNode, "iASTStringLiteralNode", 0, false, {})
{ }

iASTStringLiteralNode::iASTStringLiteralNode(istring data)
	:_data(data)
	, iASTNode(nullptr, iASTNodeType::iASTStringLiteralNode, "iASTStringLiteralNode", 0, false, {})
{ }

iASTStringLiteralNode::~iASTStringLiteralNode()
{
	//_ISTD basic::iBasic<iASTNode>::destroy(parent);
}


[[nodiscard]] auto iASTStringLiteralNode::get()const noexcept->istring
{
	return _data;
}

_ISTD Ptr<iASTStringLiteralNode> iASTStringLiteralNode::set(CRef<istring> data)
{
	_data = data;
	return this;
}