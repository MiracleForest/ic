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

#include "../family/iicfamily.h"
#include "iToken.h"

namespace MiracleForest::inline i
{
namespace icFamily
{

    class ICAPI iLexer
    {
        using uchar = unsigned char;
        using uint  = unsigned int;

    private:
        std::string _inputCode;

        const std::vector<std::string> _keywords = {
            "char",     "i16",   "i32",        "i64",      "u16",       "u32",        "u64",
            "f32",      "f64",   "string",     "enum",     "label",     "keyword",    "struct",
            "symbol",   "self",  "type",       "source",   "target",    "opt",        "pretreatment",
            "defspace", "class", "break",      "continue", "interface", "for",        "foreach",
            "if",       "elif",  "else",       "_asm",     "_cpp",      "attributes", "namespace",
            "template", "try",   "catch",      "throw",    "return",    "assert",     "operator",
            "delete",   "goto",  "particulor", "virtual",  "export",    "import",     "static",
            "const",    "ref",   "ptr",        "final",    "mutable",   "explicit",   "true",
            "false",    "YES",   "NO",         "Yes",      "No",        "new",        "void",
            "default",  "null",  "nullptr",    "or",       "not",       "and",        "is",
            "nand",     "nor",   "xor",        "xnor",     "in",        "as",         "add",
            "sub",      "mul",   "div",        "equal",    "get",       "set",        "readonly",
            "writeonly"
        };

        const std::vector<std::string> _operatorsSeparateCharacter = {
            "+", "-", "*", "/", "=", "%", "<", ">", "!", "^", "|",          "&",           ".", "[", "]",
            "(", ")", "{", "}", "@", "$", "#", ";", "~", "`", /*"´",*/ ",", /*"¥",*/ "\\", ":", "?"
        };

        const std::vector<std::string> _operatorsMultipleCharacter = {
            "+=", "-=", "/=",  "*=", "%=", "<=",  ">=", "==",  "!=",  "<<", ">>",  "<<=", ">>=", "^=", "|=",
            "&=", "..", "...", "=>", "->", "<=>", "?=", "??=", "!?=", "?:", "!=:", "==:", "||",  "&&", "::"
        };

        int _pos;
        int _len;
        int _currentLine;

    public:
        iLexer(std::string inputCode);

    public:
        // 向下读取一个Token
        iToken read();

        // 返回整个token数组
        std::vector<iToken> parse();

        static std::vector<iToken> mergeConsecutiveStringsToken(CRef<std::vector<iToken>> input);

    protected:
        // 读取空白字符
        int readSpace(int pos);

        // 读取一个字符串
        int readString(int pos);

        // 读取一个数
        int readNumber(int pos);

        // 十进制
        int readDecNumber(int pos);

        // 十六进制
        int readHexNumber(int pos);

        // 二进制
        int readBinNumber(int pos);

        // 八进制
        int readOctNumber(int pos);

        // 单行注释
        int readLineComment(int pos);

        // 多行注释
        int readBigComment(int pos);

        // 读取一个标识符
        int readIdentifier(int pos);

        // 读取一个标识符
        int readOperator(int pos);

        // 判断该标识符是否为关键字
        bool isKeyword(std::string id) const;

    public:
        Ref<iLexer> operator=(CRef<iLexer>);

    }; // iLexer
} // namespace icFamily
} // namespace MiracleForest::inline i