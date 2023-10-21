#include "../../include/iAST/iASTNode.h"
#include <icore/console/iconsole.h>
#include <icore/console/iLogger.h>
#include <icore/type/iVector.h>
#include <iostream>
#include <vector>
using namespace i::icFamily::AST;
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
	Ptr<iASTNode> parent,
	iASTNodeType type,
	CRef<istring>name,
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

Ptr<iASTNode> iASTNode::addTag(CRef<istring> tag)
{
	tags.push_back(tag);
	return this;
}

bool iASTNode::hasTag(CRef<istring> tag)const
{
	return  vector::contains(tags, tag);
}

int iASTNode::getTagIndex(CRef<istring> tag)const
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

bool iASTNode::removeTag(CRef<istring> tag)
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