/*
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iLexer.h
 * @创建时间:2022.3.4.14:02
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * 文件描述
 * 词法分析器
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/exception/error.h>
#include <icore/console/iconsole.h>
#include <icore/console/iLogger.h>
#include <icore/data/text/istring.h>
#include "iToken.h"
#include "../family/iicfamily.h"

SPACE(i)
{
	SPACE(icSystem)
	{

		class ICAPI iLexer
		{
			using uchar = _ISTD uchar;
			using uint = _ISTD uint;
			using istring = _ISTDTEXT istring;

		public:

			iLexer(istring inputCode);

		public:

			//向下读取一个Token
			iToken read();

			//返回整个token数组
			std::vector<iToken> parse();

		protected:

			/*模拟正则，每个分组判断过去，符合则返回配对长度，不符合返回0*/
			//读取空白字符
			int readSpace(int pos);

			//读取一个字符串
			int readString(int pos);

			//读取一个数
			int readNumber(int pos);

			//十进制
			int readDecNumber(int pos);

			//十六进制
			int readHexNumber(int pos);

			//二进制
			int readBinNumber(int pos);

			//八进制
			int readOctNumber(int pos);

			//单行注释
			int readLineComment(int pos);

			//多行注释
			int readBigComment(int pos);

			//读取一个标识符
			int readIdentifier(int pos);

			//判断该标识符是否为关键字
			bool isKeyword(istring id)const;

		public:

			_ISTD Ref<iLexer> operator=(_ISTD CRef<iLexer>);

		private:
			istring _inputCode;
			const std::vector<istring> _keywords = { "char", "i16", "i32", "i64", "u16", "u32", "u64", "f32", "f64",
												 "string", "enum", "label", "keyword", "struct", "symbol", "self", "type", "source", "target",
												 "opt", "pretreatment", "defspace", "class", "break", "continue", "interface", "for", "foreach",
												 "if", "elif", "else", "_asm", "_cpp", "attributes", "namespace", "template", "try", "catch",
												 "throw", "return", "assert", "operator", "delete", "goto", "particulor", "virtual", "export",
												 "static", "const", "ref", "ptr", "final", "mutable", "explicit", "true", "false","YES","NO",
												 "Yes","No", "new", "void","default", "null", "nullptr", "or", "not", "and", "is", "nand", "nor",
												 "xor", "xnor", "in", "as","add", "sub", "mul", "div", "equal","get","set","readonly","writeonly"
			};

			int _pos = 0;
			int len = _inputCode.length();
		};//iLexer
	}
}