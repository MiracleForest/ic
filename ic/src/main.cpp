#include <icore/family/ifamily.h>
#include <icore/console/iconsole.h>
#include <icore/console/iLogger.h>
#include <icore/exception/error.h>
#include <icore/data/text/istring.h>

#include "../include/iLexer/iLexer.h"
#include "../include/iParse/iParser.h"

#include <iostream>
#include <fstream>
#include <streambuf>
#include <chrono>
using namespace std::chrono;

//#pragma comment(lib,"iBasicLibrary_debug.lib")

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

	typedef std::chrono::high_resolution_clock Clock;
	auto t1 = Clock::now();//计时开始


	icSystem::iLexer lexer(inputCode);
	auto tokens = lexer.parse();

	auto t2 = Clock::now();//计时结束

	typedef std::chrono::high_resolution_clock Clock;
	auto t3 = Clock::now();//计时开始
	for (int i = 0; i < tokens.size(); i++)
	{
		logger.info("<{}> \t{}", tokens[i].getID2String(), iEncoding::UTF82ANSI(tokens[i].getText().data()));
	}
	auto t4 = Clock::now();//计时结束

	logger.note("解析用时：{}纳秒", std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count());
	logger.note("等于：{}毫秒", std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e+6);
	logger.note("等于：{}秒", std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e+9);
	logger.note("打印用时：{}纳秒", std::chrono::duration_cast<std::chrono::nanoseconds>(t4 - t3).count());
	logger.note("等于：{}毫秒", std::chrono::duration_cast<std::chrono::nanoseconds>(t4 - t3).count() / 1e+6);
	logger.note("等于：{}秒", std::chrono::duration_cast<std::chrono::nanoseconds>(t4 - t3).count() / 1e+9);

	icSystem::AST::iASTGlobalAreaNode* astnode = new icSystem::AST::iASTGlobalAreaNode;
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

	icSystem::AST::iASTGlobalAreaNode* astnode2 = new icSystem::AST::iASTGlobalAreaNode;
	icSystem::AST::iASTNode* test_1 = new icSystem::AST::iASTNode(1);
	icSystem::AST::iASTNode* test_2 = new icSystem::AST::iASTNode(2);
	icSystem::AST::iASTNode* test_3 = new icSystem::AST::iASTNode(3);
	icSystem::AST::iASTNode* test_4 = new icSystem::AST::iASTNode(4);
	astnode->add(test_1);
	astnode->add(test_2);
	astnode->add(test_3);
	astnode->add(astnode2);
	logger.info("getCount:{}", astnode->getCount());
	astnode->next();
	logger.info("getIndex:{}", astnode->getIndex());
	if (auto buf = astnode->get(); buf->type == icSystem::AST::iASTNodeType::properties)
	{
		istring test2 = buf->getValue();
		logger.info("test2:{}", test2);
		logger.info("getIndex:{}", astnode->getIndex());
	}
	astnode->remove();
	astnode->setIndex(2);
	if (auto buf = astnode->get(); buf->type == icSystem::AST::iASTNodeType::properties)
	{
		istring test2 = buf->getValue();
		logger.info("test2:{}", test2);
		logger.info("getCount:{}", astnode->getCount());
	}

	_ISTD basic::iBasic<icSystem::AST::iASTNode>::destroy(test_1);
	_ISTD basic::iBasic<icSystem::AST::iASTNode>::destroy(test_2);
	_ISTD basic::iBasic<icSystem::AST::iASTNode>::destroy(test_3);
	_ISTD basic::iBasic<icSystem::AST::iASTNode>::destroy(test_4);
	_ISTD basic::iBasic<icSystem::AST::iASTGlobalAreaNode>::destroy(astnode);
	return _ISTD iexception::error::noError();
}