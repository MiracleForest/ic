#include "../../include/iAST/iASTNode.h"
#include <iostream>
#include <vector>
using namespace MiracleForest::i::icFamily::AST;


iASTNode::iASTNode()
    : parent(nullptr)
    , type(iASTNodeType::iASTNode)
    , name("iASTNode")
    , additionalNode(false)
    , tags({})
    , line(0)
{
}

iASTNode::iASTNode(
    Ptr<iASTNode>            parent,
    iASTNodeType             type,
    CRef<std::string>        name,
    int                      line,
    bool                     additionalNode,
    std::vector<std::string> tags
)
    : parent(parent)
    , type(type)
    , name(name)
    , additionalNode(additionalNode)
    , tags(tags)
    , line(line)
{
}


iASTNode::~iASTNode()
{
    std::cout << "~iASTNode\n";
    // if (parent != nullptr)
    //{
    //	delete parent;
    //	parent = nullptr;
    // }
}

Ptr<iASTNode> iASTNode::addTag(CRef<std::string> tag)
{
    tags.push_back(tag);
    return this;
}

bool iASTNode::hasTag(CRef<std::string> tag) const { return vector::contains(tags, tag); }

int iASTNode::getTagIndex(CRef<std::string> tag) const
{
    if (!hasTag(tag)) { return -2; }
    for (int i = 0; auto& v : tags)
    {
        if (v == tag) { return i; }
        i++;
    }
    return -1;
}

bool iASTNode::removeTag(CRef<std::string> tag)
{
    if (!hasTag(tag)) { return false; }
    tags.erase(tags.begin() + getTagIndex(tag));
    return true;
}

std::vector<std::string> iASTNode::getAllTag() const { return tags; }