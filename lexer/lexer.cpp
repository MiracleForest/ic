/****
*
* Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
*
* @�ļ�����lexer.cpp
* @����ʱ�䣺2023/2/20
* @�����ߣ�github.com/Climber-Rong
* -----------------------------------------------------------------------------
*�ļ�����
�ʷ�������
* -----------------------------------------------------------------------------
* ����㷢����bug�������ȥGithub������(MiracleForest@Outlook.com)���������ǣ�
* ����һ����Ŭ�����ø��õģ�
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

#define KEYWORD_NUM 76 					//�ؼ��ָ��� 

//token���ͼ����
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
		string getText();			//��ȡ�ı�
		unsigned char getID();		//��ȡ���
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
		                                    };		//�ؼ���
	public:
		Lexer(string text);
		Token read();				//���¶�ȡһ��Token
		vector<Token> parse();		//��������token����
		// Public Declarations
	protected:
		/*ģ������ÿ�������жϹ�ȥ�������򷵻���Գ��ȣ������Ϸ���0*/
		int readSpace();			//��ȡ�հ��ַ�
		int readString();			//��ȡһ���ַ���
		int readNumber();			//��ȡһ����
		int readDecNumber();		//ʮ����
		int readHexNumber();		//ʮ������
		int readOctNumber();		//�˽���
		int readLineComment();		//����ע��
		int readBigComment();		//����ע��
		int readIden();				//��ȡһ����ʶ��
		bool isKeyword(string id);	//�жϸñ�ʶ���Ƿ�Ϊ�ؼ���
		// Protected Declarations
};

Lexer::Lexer(string text) {
	this->text = text;
	/*���ùؼ���*/
}

Token Lexer::read() {

	int result = 0;
	while(text!="") {		//�ҵ�����token�ͷ���
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
		} else {			//������Ϊֹʲô��û�У��϶��������
			string op = text.substr(0,1);
			text = text.substr(1, len);
			return Token(TokenOperator, op);
		}
	}

	if(text=="") {
		//δ�ҵ�����Token������EOF
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
	result++;				//������

	while(result<(text.length()-1) && text[result]!='\"') {
		//ֻҪû���ף�û���꣬�Ǿͼ�����
		if(text[result]=='\\') {
			result++;		//ת���ַ���ת��ֱ�ӱ���
		}
		result++;
	}

	if(text[result]!='\"') {
		return 0;			//û���ұߵ�����
	}
	result++;				//������
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
		return 0;			//���ȹ�С
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
		return 0;			//���ȹ�С
	}

	if(text[0]=='0') {
		result += 1;
	} else {
		return 0;
	}

	result++;				//�����Ǹ�λ��

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
	if(text.length()<=1) {		//���ȹ�С
		return 0;
	}

	if(text[0]=='/' && text[1]=='/') {
		result += 2;					//��������б��
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
		result += 2;	//����/*
	} else {
		return 0;
	}

	while(result<(text.length()-2) && (text[result]!='*'||text[result+1]!='/')) {
		result++;
	}

	result += 2;		//����*/

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

