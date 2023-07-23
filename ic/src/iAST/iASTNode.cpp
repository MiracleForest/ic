#include "../../include/iAST/iASTNode.h"
#include <icore/console/iconsole.h>
#include <icore/console/iLogger.h>
#include <icore/type/iVector.h>
#include <vector>
#include <iostream>
using namespace i::icSystem::AST;
using namespace i::core;

iASTNode::iASTNode()
	: parent(nullptr)
	, type(iASTNodeType::iASTNode)
	, name("iASTNode")
	, additionalNode(false)
	, tags({})
	, line(0)
{ }

iASTNode::iASTNode(
	_ISTD Ptr<iASTNode> parent,
	iASTNodeType type,
	_ISTD CRef<istring>name,
	int line,
	bool additionalNode,
	std::vector<istring> tags
)
	: parent(parent)
	, type(type)
	, name(name)
	, additionalNode(additionalNode)
	, tags(tags)
	, line(line)
{ }


iASTNode::~iASTNode()
{
	std::cout << "~iASTNode\n";
	//if (parent != nullptr)
	//{
	//	delete parent;
	//	parent = nullptr;
	//}
}

Ptr<iASTNode> iASTNode::addTag(_ISTD CRef<istring> tag)
{
	tags.push_back(tag);
	return this;
}

bool iASTNode::hasTag(_ISTD CRef<istring> tag)const
{
	return _ISTD vector::contains(tags, tag);
}

int iASTNode::getTagIndex(_ISTD CRef<istring> tag)const
{
	if (!hasTag(tag))
	{
		return -2;
	}
	for (int i = 0; auto & v : tags)
	{
		if (v == tag)
		{
			return i;
		}
		i++;
	}
	return -1;
}

bool iASTNode::removeTag(_ISTD CRef<istring> tag)
{
	if (!hasTag(tag))
	{
		return false;
	}
	tags.erase(tags.begin() + getTagIndex(tag));
	return true;
}

std::vector<iASTNode::istring> iASTNode::getAllTag()const
{
	return tags;
}