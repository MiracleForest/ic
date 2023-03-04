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
			using uchar = i::core::uchar;
			using uint = i::core::uint;
			using istring = _ISTDTEXT istring;
		public:

			iToken(uchar token_id, istring text);

		public:

			//获取文本
			istring getText()const;

			//获取编号
			uchar getID()const;

		public:

			istring getID2String()const;

		private:

			istring _text;
			uint _ID;

		};//iToken


	}
}