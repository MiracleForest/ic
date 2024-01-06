#include <icore/console/iconsole.h>
#include <icore/console/iLogger.h>
#include <icore/data/text/istring.h>
#include <icore/exception/error.h>
#include <icore/family/ifamily.h>

#include "../include/iLexer/iLexer.h"
#include "../include/iParse/iParser.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <streambuf>
using namespace std::chrono;
using iEncoding = _ISTDTEXT iEncoding;



iMain(_p_start)
{
	_p_start.pause = true;
	using istring = _ISTDTEXT istring;

	_ISTD io::iLogger logger("ic");

	std::fstream inputFile("../../../../script.is");
	if (!inputFile.good())
	{
		logger.error("打开目标文件失败！");
		return _ISTD iexception::error::make(-1);
	}
	std::string inputCode = "";
	inputCode.assign(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>());
	logger.info("输入的代码：{}", iEncoding::UTF82ANSI(inputCode));
	inputFile.close();

	using clock = std::chrono::high_resolution_clock;
	std::vector<i::icFamily::iToken> tokens;

	auto t1 = clock::now();//计时开始

	i::icFamily::iLexer lexer(inputCode);
	tokens = lexer.parse();
	auto t2 = clock::now();//计时结束
	tokens = lexer.mergeConsecutiveStringsToken(tokens);

	auto t3 = clock::now();//计时开始
	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].getID() != i::icFamily::iTokenID::Unk)
		{
			logger.info("<{},{}> \t{}", tokens[i].getID2String(), tokens[i].getLine(), iEncoding::UTF82ANSI(tokens[i].getText().data()));
		}
		else
		{
			logger.warn("<{},{}> \t{}", tokens[i].getID2String(), tokens[i].getLine(), iEncoding::UTF82ANSI(tokens[i].getText().data()));
		}
	}
	auto t4 = clock::now();//计时结束


#define TIMECAST(p1,p2) std::chrono::duration_cast<std::chrono::nanoseconds>(p1-p2).count()
	logger.note("解析用时：{}纳秒", TIMECAST(t2, t1));
	logger.note("等于：{}毫秒", TIMECAST(t2, t1) / 1e+6);
	logger.note("等于：{}秒", TIMECAST(t2, t1) / 1e+9);
	logger.note("打印用时：{}纳秒", TIMECAST(t4, t3));
	logger.note("等于：{}毫秒", TIMECAST(t4, t3) / 1e+6);
	logger.note("等于：{}秒", TIMECAST(t4, t3) / 1e+9);
#undef TIMECAST

	for (;;)
	{
		Ptr<i::icFamily::AST::iASTGlobalAreaNode> astnode = new i::icFamily::AST::iASTGlobalAreaNode;
		logger.info("hasTag:{}", astnode->hasTag("1"));
		logger.info("addTag:{}", astnode->addTag("1")->getAllTag()[0]);
		logger.info("getTagIndex:{}", astnode->getTagIndex("1"));
		logger.info("removeTag:{}", astnode->removeTag("1"));
		logger.info("removeTag:{}", astnode->removeTag("2"));
		logger.info("hasTag:{}", astnode->hasTag("1"));
		logger.info("additionalNode:{}", astnode->additionalNode);
		logger.info("additionalNode:{}", astnode->setAdditionalNode()->additionalNode);
		logger.info("name:{}", astnode->name);
		logger.info("type:{}", (int)astnode->type);
		Ptr<i::icFamily::AST::iASTStringLiteralNode> test_1 = new i::icFamily::AST::iASTStringLiteralNode(1);
		Ptr<i::icFamily::AST::iASTStringLiteralNode> test_2 = new i::icFamily::AST::iASTStringLiteralNode(2);
		Ptr<i::icFamily::AST::iASTStringLiteralNode> test_3 = new i::icFamily::AST::iASTStringLiteralNode(3);
		Ptr<i::icFamily::AST::iASTStringLiteralNode> test_4 = new i::icFamily::AST::iASTStringLiteralNode(4);
		astnode->add(test_1);
		astnode->add(test_2);
		astnode->add(test_3);
		astnode->add(test_4);
		logger.info("getCount:{}", astnode->getCount());
		astnode->next();
		logger.info("getIndex:{}", astnode->getIndex());
		if (auto buf = astnode->get(); buf->type == i::icFamily::AST::iASTNodeType::iASTStringLiteralNode)
		{
			Ptr<i::icFamily::AST::iASTStringLiteralNode> b = (Ptr<i::icFamily::AST::iASTStringLiteralNode>)buf;
			istring test2 = b->get();
			logger.info("test2:{}", test2);
			logger.info("getIndex:{}", astnode->getIndex());
		}
		astnode->remove();
		//astnode->setIndex(2);
		if (auto buf = astnode->get(); buf->type == i::icFamily::AST::iASTNodeType::iASTStringLiteralNode)
		{
			Ptr<i::icFamily::AST::iASTStringLiteralNode> b = (Ptr<i::icFamily::AST::iASTStringLiteralNode>)buf;
			istring test2 = b->get();
			logger.info("test2:{}", test2);
			logger.info("getCount:{}", astnode->getCount());
		}

		_ISTD basic::iBasic<i::icFamily::AST::iASTStringLiteralNode>::destroy(test_1);
		_ISTD basic::iBasic<i::icFamily::AST::iASTStringLiteralNode>::destroy(test_2);
		_ISTD basic::iBasic<i::icFamily::AST::iASTStringLiteralNode>::destroy(test_3);
		_ISTD basic::iBasic<i::icFamily::AST::iASTStringLiteralNode>::destroy(test_4);
		_ISTD basic::iBasic<i::icFamily::AST::iASTGlobalAreaNode>::destroy(astnode);
		delete test_1;
		delete test_2;
		delete test_3;
		delete test_4;
		delete astnode;
	}
	return _ISTD iexception::error::noError();
}
iMainEnd