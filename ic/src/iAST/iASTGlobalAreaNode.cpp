#include "../../include/iAST/iASTGlobalAreaNode.h"
using namespace i::icSystem::AST;
using namespace i::core;

iASTGlobalAreaNode::iASTGlobalAreaNode()
	: childElementsList({})
	, _childElementsListIndex(0)
	, iASTNode(nullptr, iASTNodeType::iASTGlobalAreaNode, "iASTGlobalAreaNode", 0, false, {})
{ }

iASTGlobalAreaNode::iASTGlobalAreaNode(Ptr<iASTNode> childElements)
	:childElementsList({ childElements })
	, _childElementsListIndex(0)
	, iASTNode(nullptr, iASTNodeType::iASTGlobalAreaNode, "iASTGlobalAreaNode", 0, false, {})

{ }

iASTGlobalAreaNode::iASTGlobalAreaNode(std::vector<Ptr<iASTNode>> childElementsList)
	:childElementsList(childElementsList)
	, _childElementsListIndex(0)
	, iASTNode(nullptr, iASTNodeType::iASTGlobalAreaNode, "iASTGlobalAreaNode", 0, false, {})
{ }

iASTGlobalAreaNode::~iASTGlobalAreaNode()
{
	std::cout << "~iASTGlobalAreaNode\n";
	for (auto& v : this->childElementsList)
	{
		basic::iBasic<iASTNode>::destroy(v);
	}
}

int iASTGlobalAreaNode::getCount()const
{
	return this->childElementsList.size();
}

int iASTGlobalAreaNode::getIndex()const
{
	return _childElementsListIndex;
}

_ISTD Ptr<iASTGlobalAreaNode> iASTGlobalAreaNode::setIndex(int index)
{
	_childElementsListIndex = index;
	return this;
}

Ptr<iASTGlobalAreaNode> iASTGlobalAreaNode::next()const
{
	this->_childElementsListIndex++;
	return const_cast<Ptr<iASTGlobalAreaNode>>(this);
}


Ptr<iASTNode> iASTGlobalAreaNode::getNext()const
{
	this->_childElementsListIndex++;
	return this->get();
}

Ptr<iASTNode> iASTGlobalAreaNode::get()const
{
	if (this->_childElementsListIndex > getCount())
	{
		return nullptr;
	}
	return this->childElementsList[this->_childElementsListIndex];
}

Ptr<iASTGlobalAreaNode> iASTGlobalAreaNode::setNext(Ptr<iASTNode> node)
{
	this->_childElementsListIndex++;
	this->set(node);
	return this;
}

Ptr<iASTGlobalAreaNode> iASTGlobalAreaNode::set(Ptr<iASTNode> node)
{
	this->childElementsList[this->_childElementsListIndex] = node;
	node->setParent(this);
	return this;
}

_ISTD Ptr<iASTGlobalAreaNode> iASTGlobalAreaNode::add(_ISTD Ptr<iASTNode> node)
{
	this->childElementsList.push_back(node);
	node->setParent(this);
	return this;
}

_ISTD Ptr<iASTGlobalAreaNode> iASTGlobalAreaNode::remove()
{
	std::cout << "-\n";
	_ISTD basic::iBasic<iASTNode>::destroy(this->get());
	this->childElementsList.erase(this->childElementsList.begin() + this->_childElementsListIndex);
	_childElementsListIndex--;
	std::cout << "--\n";
	return this;
}