#include <icore/family/ifamily.hpp>
#include <icore/console/iconsole.hpp>
#include <icore/console/iLogger.hpp>
#include <icore/exception/error.hpp>
#include <icore/data/text/istring.hpp>

#include "../include/iLexer/iLexer.h"

#include <iostream>
#include <fstream>
#include <streambuf>
#include <chrono>
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

	return _ISTD iexception::error::noError();
}