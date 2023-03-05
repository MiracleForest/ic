#include <icore/family/ifamily.hpp>
#include <icore/console/iconsole.hpp>
#include <icore/console/iLogger.hpp>
#include <icore/exception/error.hpp>
#include <iostream>
#include <fstream>
#include <streambuf>
#include "../include/iLexer/iLexer.h"

iMain(_p_start)
{
	_p_start.pause = true;
	using istring = _ISTDTEXT istring;

	_ISTD io::iLogger logger("ic");

	std::fstream targetFile("script.is");
	if (!targetFile.good())
	{
		logger.error("打开目标文件失败！");
		return _ISTD iexception::error::make(-1);
	}
	std::string codeString = "";
	codeString.assign(std::istreambuf_iterator<char>(targetFile), std::istreambuf_iterator<char>());
	logger.info("输入代码：{}",codeString);

	targetFile.close();

	icSystem::iLexer lexer(codeString);
	auto tokens = lexer.parse();

	for (int i = 0; i < tokens.size(); i++)
	{
		logger.info("<{}> {}", tokens[i].getID2String(), tokens[i].getText());
	}

	return _ISTD iexception::error::noError();
}