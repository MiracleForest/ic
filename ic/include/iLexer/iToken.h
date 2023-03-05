/*
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iToken.h
 * @创建时间:2022.3.4.14:03
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * Token
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */

#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.hpp>

SPACE(i)
{

	SPACE(icSystem)
	{

#ifdef EOF
#undef EOF
#endif//^^^^EOF

		enum class iTokenID
		{
			Unk = -1,
			String,
			Number,
			Identifier,
			Keyword,
			Operator,
			EOL,
			EOF
		};//enum class iTokenID


		class iToken
		{
			using uchar = _ISTD uchar;
			using uint = _ISTD uint;
			using istring = _ISTDTEXT istring;
		public:

			iToken();

			iToken(iTokenID token_id, istring text);

		public:

			//获取文本
			istring getText()const;

			//获取编号
			iTokenID getID()const;

		public:

			istring getID2String()const;

		public:

			_ISTD Ref<iToken> operator=(_ISTD CRef<iToken>);

		private:

			istring _text;
			iTokenID _ID;

		};//iToken


	}
}