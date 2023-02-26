/****
*
* Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
*
* @文件名：lexer.cpp
* @创建时间：2023/2/20
* @创建者：github.com/Climber-Rong
* -----------------------------------------------------------------------------
*文件描述
词法分析器
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/



#ifndef LEXER_CPP
#define LEXER_CPP

#include<iostream>
using namespace std;

#include<string>
#include<vector>
#include<string.h>
#include<stdlib.h>

#define KEYWORD_NUM 76 					//关键字个数 

//token类型及编号
enum TokenID {
    TokenString = 0,
    TokenNumber,
    TokenIdentifier,
    TokenKeyword,
    TokenOperator,
    TokenEOL,
    TokenEOF
};

using namespace std;

class Token;
class Lexer;

class Token {
		// Private section
		string text;
		unsigned int ID;
	public:
		Token(unsigned char token_id, string text);
		string getText();			//获取文本
		unsigned char getID();		//获取编号
		string IDtoString() {
			if(ID==TokenString) {
				return "string";
			}
			if(ID==TokenNumber) {
				return "number";
			}
			if(ID==TokenIdentifier) {
				return "identifier";
			}
			if(ID==TokenKeyword) {
				return "keyword";
			}
			if(ID==TokenOperator) {
				return "operator";
			}
			if(ID==TokenEOL) {
				return "end-of-line";
			}
			if(ID==TokenEOF) {
				return "end-of-file";
			}
		}
		// Public Declarations
	protected:
		// Protected Declarations
};

Token::Token(unsigned char token_id, string text) {
	this->ID = token_id;
	this->text = text;
}

string Token::getText() {
	return this->text;
}

unsigned char Token::getID() {
	return this->ID;
}


class Lexer {
		// Private section
		string text;
		const char* keywords[KEYWORD_NUM] = {"char", "i16", "i32", "i64", "u16", "u32", "u64", "f32", "f64",
		                                     "string", "enum", "label", "keyword", "struct", "symbol", "self", "type", "source", "target",
		                                     "opt", "pretreatment", "defspace", "class", "break", "continue", "interface", "for", "foreach",
		                                     "if", "elif", "else", "_asm", "_cpp", "attributes", "namespace", "template", "try", "catch",
		                                     "throw", "return", "assert", "operator", "delete", "goto", "particulor", "virtual", "export",
		                                     "static", "const", "ref", "ptr", "final", "mutable", "explicit", "true", "false", "new", "void",
		                                     "default", "null", "nullptr", "or", "not", "and", "is", "nand", "nor", "xor", "xnor", "in", "as",
		                                     "add", "sub", "mul", "div", "equal"
		                                    };		//关键字
	public:
		Lexer(string text);
		Token read();				//向下读取一个Token
		vector<Token> parse();		//返回整个token数组
		// Public Declarations
	protected:
		/*模拟正则，每个分组判断过去，符合则返回配对长度，不符合返回0*/
		int readSpace();			//读取空白字符
		int readString();			//读取一个字符串
		int readNumber();			//读取一个数
		int readDecNumber();		//十进制
		int readHexNumber();		//十六进制
		int readOctNumber();		//八进制
		int readLineComment();		//单行注释
		int readBigComment();		//多行注释
		int readIden();				//读取一个标识符
		bool isKeyword(string id);	//判断该标识符是否为关键字
		// Protected Declarations
};

Lexer::Lexer(string text) {
	this->text = text;
	/*设置关键字*/
}

Token Lexer::read() {

	int result = 0;
	while(text!="") {		//找到有用token就返回
		int len = text.length();

		if(text[0]=='\n') {
			text = text.substr(1, text.length());
			return Token(TokenEOL, "");
		}

		if(result = readString()) {
			string token_str = text.substr(0, result);		//token_str = text[0:result]
			text = text.substr(result, len);			//text = text[result:]
			return Token(TokenString, token_str);
		}

		if(result = readNumber()) {
			string token_str = text.substr(0, result);
			text = text.substr(result, len);
			return Token(TokenNumber, token_str);
		}

		if(result = readIden()) {
			string token_str = text.substr(0, result);
			text = text.substr(result, len);
			if(isKeyword(token_str)==true) {
				return Token(TokenKeyword, token_str);
			}
			return Token(TokenIdentifier, token_str);
		}

		if(result = readSpace()) {
			text = text.substr(result, len);
		} else if(result = readLineComment()) {
			text = text.substr(result, len);
		} else if(result = readBigComment()) {
			text = text.substr(result, len);
		} else {			//到这里为止什么都没有，肯定是运算符
			string op = text.substr(0,1);
			text = text.substr(1, len);
			return Token(TokenOperator, op);
		}
	}

	if(text=="") {
		//未找到可用Token，返回EOF
		return Token(TokenEOF, "");
	}
}

vector<Token> Lexer::parse() {
	vector<Token> result;
	Token tok(-1, "");
	while((tok = read()).getID() != TokenEOF) {
		result.push_back(tok);
	}
	return result;
}

int Lexer::readSpace() {
	int result = 0;
	while(result<text.length() && (text[result]==' '||text[result]=='\t')) {
		result++;
	}
	return result;
}

int Lexer::readString() {
	int result = 0;
	if(text[0] != '\"') {
		return 0;
	}
	result++;				//左引号

	while(result<(text.length()-1) && text[result]!='\"') {
		//只要没到底，没读完，那就继续读
		if(text[result]=='\\') {
			result++;		//转义字符不转，直接保留
		}
		result++;
	}

	if(text[result]!='\"') {
		return 0;			//没有右边的引号
	}
	result++;				//右引号
	return result;
}

int Lexer::readNumber() {
	int result = 0;

	result = readHexNumber();
	if(result!=0) {
		return result;
	}

	result = readOctNumber();
	if(result!=0) {
		return result;
	}

	result = readDecNumber();
	if(result!=0) {
		return result;
	}

	return 0;
}

int Lexer::readHexNumber() {
	int result = 0;

	if(text.length()<=2) {
		return 0;			//长度过小
	}

	if(text[0]=='0'&&text[1]=='x') {
		result += 2;
	} else {
		return 0;
	}

	while(result<text.length() && ('0'<=text[result] && text[result]<='F')) {
		result++;
	}
	return result;
}

int Lexer::readOctNumber() {
	int result = 0;

	if(text.length()<=1) {
		return 0;			//长度过小
	}

	if(text[0]=='0') {
		result += 1;
	} else {
		return 0;
	}

	result++;				//至少是个位数

	while(result<text.length() && ('0'<=text[result] && text[result]<='8')) {
		result++;
	}
	return result;
}


int Lexer::readDecNumber() {
	int result = 0;

	while(result<text.length() && ('0'<=text[result] && text[result]<='9')) {
		result++;
	}

	return result;
}

int Lexer::readLineComment() {
	int result = 0;
	if(text.length()<=1) {		//长度过小
		return 0;
	}

	if(text[0]=='/' && text[1]=='/') {
		result += 2;					//加上两个斜杠
	} else {
		return 0;
	}

	while(result<text.length() && text[result]!='\n') {
		result++;
	}

	return result;
}


int Lexer::readBigComment() {
	int result = 0;

	if(text.length()<=3) {
		return 0;
	}

	if(text[0]=='/'&&text[1]=='*') {
		result += 2;	//加上/*
	} else {
		return 0;
	}

	while(result<(text.length()-2) && (text[result]!='*'||text[result+1]!='/')) {
		result++;
	}

	result += 2;		//加上*/

	return result;
}

int Lexer::readIden() {
	int result = 0;
	if(('A'<=text[0]&&text[0]<='Z')||('a'<=text[0]&&text[0]<='z')||text[0]=='_') {
		result++;
	}
	while(result<text.length()&&
	        (('A'<=text[result]&&text[result]<='Z')||('a'<=text[result]&&text[result]<='z')||('0'<=text[result]&&text[result]<='9')||text[result]=='_')) {
		result++;
	}

	return result;
}

bool Lexer::isKeyword(string id) {
	for(int i=0; i<KEYWORD_NUM; i++) {
		if(id==keywords[i]) {
			return true;
		}
	}

	return false;
}

#endif

