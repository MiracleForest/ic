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

#include <icore/family/imacrofamily.h>
#include "iToken.h"

SPACE(i)
{
	SPACE(icSystem)
	{

		class iLexer
		{
			using uchar = _ISTD uchar;
			using uint = _ISTD uint;
			using istring = _ISTDTEXT istring;

		public:

			iLexer(istring text);

		public:

			//向下读取一个Token
			iToken read();

			//返回整个token数组
			std::vector<iToken> parse();

		protected:

			/*模拟正则，每个分组判断过去，符合则返回配对长度，不符合返回0*/
			//读取空白字符
			int readSpace();

			//读取一个字符串
			int readString();

			//读取一个数
			int readNumber();

			//十进制
			int readDecNumber();

			//十六进制
			int readHexNumber();

			//八进制
			int readOctNumber();

			//单行注释
			int readLineComment();

			//多行注释
			int readBigComment();

			//读取一个标识符
			int readIdentifier();

			//判断该标识符是否为关键字
			bool isKeyword(istring id)const;

		private:
			istring _targetCode;
			const std::vector<istring> _keywords = { "char", "i16", "i32", "i64", "u16", "u32", "u64", "f32", "f64",
												 "string", "enum", "label", "keyword", "struct", "symbol", "self", "type", "source", "target",
												 "opt", "pretreatment", "defspace", "class", "break", "continue", "interface", "for", "foreach",
												 "if", "elif", "else", "_asm", "_cpp", "attributes", "namespace", "template", "try", "catch",
												 "throw", "return", "assert", "operator", "delete", "goto", "particulor", "virtual", "export",
												 "static", "const", "ref", "ptr", "final", "mutable", "explicit", "true", "false", "new", "void",
												 "default", "null", "nullptr", "or", "not", "and", "is", "nand", "nor", "xor", "xnor", "in", "as",
												 "add", "sub", "mul", "div", "equal","get","set"
			};
		};//iLexer
	}
}