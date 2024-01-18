#include "../include/iLexer/iLexer.h"
#include "../include/iParse/iParser.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <streambuf>
using namespace std::chrono;


int main()
{

    std::fstream inputFile("../../../../script.is");
    if (!inputFile.good())
    {
        std::cout << "打开目标文件失败！" << std::endl;
        return 0;
    }
    std::string inputCode = "";
    inputCode.assign(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>());
    std::cout << "输入的代码：" << inputCode << std::endl;
    inputFile.close();

    using clock = std::chrono::high_resolution_clock;
    std::vector<MiracleForest::i::icFamily::iToken> tokens;

    auto t1 = clock::now(); // 计时开始

    MiracleForest::i::icFamily::iLexer lexer(inputCode);
    tokens  = lexer.parse();
    auto t2 = clock::now(); // 计时结束
    tokens  = lexer.mergeConsecutiveStringsToken(tokens);

    auto t3 = clock::now(); // 计时开始
    for (int i = 0; i < tokens.size(); i++)
    {
        std::cout << "<" << tokens[i].getID2String() << "," << tokens[i].getLine() << "> \t"
                  << tokens[i].getText().data() << std::endl;
    }
    auto t4 = clock::now(); // 计时结束


#define TIMECAST(p1, p2) std::chrono::duration_cast<std::chrono::nanoseconds>(p1 - p2).count()
    std::cout << "解析用时：" << TIMECAST(t2, t1) << "纳秒" << std::endl;
    std::cout << "等于：" << TIMECAST(t2, t1) / 1e+6 << "毫秒" << std::endl;
    std::cout << "等于：" << TIMECAST(t2, t1) / 1e+9 << "秒" << std::endl;
    std::cout << "打印用时：" << TIMECAST(t4, t3) << "纳秒" << std::endl;
    std::cout << "等于：" << TIMECAST(t4, t3) / 1e+6 << "毫秒" << std::endl;
    std::cout << "等于：" << TIMECAST(t4, t3) / 1e+9 << "秒" << std::endl;
#undef TIMECAST

    // for (;;)
    //{
    //     Ptr<MiracleForest::i::icFamily::AST::iASTGlobalAreaNode> astnode = new
    //     MiracleForest::i::icFamily::AST::iASTGlobalAreaNode; logger.info("hasTag:{}",
    //     astnode->hasTag("1")); logger.info("addTag:{}", astnode->addTag("1")->getAllTag()[0]);
    //     logger.info("getTagIndex:{}", astnode->getTagIndex("1"));
    //     logger.info("removeTag:{}", astnode->removeTag("1"));
    //     logger.info("removeTag:{}", astnode->removeTag("2"));
    //     logger.info("hasTag:{}", astnode->hasTag("1"));
    //     logger.info("additionalNode:{}", astnode->additionalNode);
    //     logger.info("additionalNode:{}", astnode->setAdditionalNode()->additionalNode);
    //     logger.info("name:{}", astnode->name);
    //     logger.info("type:{}", (int)astnode->type);
    //     Ptr<MiracleForest::i::icFamily::AST::iASTStringLiteralNode> test_1 = new
    //     MiracleForest::i::icFamily::AST::iASTStringLiteralNode(1);
    //     Ptr<MiracleForest::i::icFamily::AST::iASTStringLiteralNode> test_2 = new
    //     MiracleForest::i::icFamily::AST::iASTStringLiteralNode(2);
    //     Ptr<MiracleForest::i::icFamily::AST::iASTStringLiteralNode> test_3 = new
    //     MiracleForest::i::icFamily::AST::iASTStringLiteralNode(3);
    //     Ptr<MiracleForest::i::icFamily::AST::iASTStringLiteralNode> test_4 = new
    //     MiracleForest::i::icFamily::AST::iASTStringLiteralNode(4); astnode->add(test_1);
    //     astnode->add(test_2);
    //     astnode->add(test_3);
    //     astnode->add(test_4);
    //     logger.info("getCount:{}", astnode->getCount());
    //     astnode->next();
    //     logger.info("getIndex:{}", astnode->getIndex());
    //     if (auto buf = astnode->get(); buf->type ==
    //     MiracleForest::i::icFamily::AST::iASTNodeType::iASTStringLiteralNode)
    //     {
    //         Ptr<MiracleForest::i::icFamily::AST::iASTStringLiteralNode> b =
    //             (Ptr<MiracleForest::i::icFamily::AST::iASTStringLiteralNode>)buf;
    //         std::string test2 = b->get();
    //         logger.info("test2:{}", test2);
    //         logger.info("getIndex:{}", astnode->getIndex());
    //     }
    //     astnode->remove();
    //     // astnode->setIndex(2);
    //     if (auto buf = astnode->get(); buf->type ==
    //     MiracleForest::i::icFamily::AST::iASTNodeType::iASTStringLiteralNode)
    //     {
    //         Ptr<MiracleForest::i::icFamily::AST::iASTStringLiteralNode> b =
    //             (Ptr<MiracleForest::i::icFamily::AST::iASTStringLiteralNode>)buf;
    //         std::string test2 = b->get();
    //         logger.info("test2:{}", test2);
    //         logger.info("getCount:{}", astnode->getCount());
    //     }

    //    delete test_1;
    //    delete test_2;
    //    delete test_3;
    //    delete test_4;
    //    delete astnode;
    //}
    return 0;
}