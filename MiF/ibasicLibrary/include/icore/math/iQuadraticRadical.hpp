/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iQuadraticRadical.hpp
* @创建时间：2023.1.10.22:10
* @创建者：Minsecrus
* -----------------------------------------------------------------------------
* iBasicLibrary 二次根式类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/

#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasicDataType.hpp>
#include "iFraction.hpp"


SPACE(i)
{
	SPACE(core)
	{
		SPACE(math)
		{
			class iQuadraticRadical
				:public basic::iBasicDataType<iQuadraticRadical, std::list<std::pair<iFraction, int>>>
			{
				iObject(iQuadraticRadical);

			public:

				std::list<std::pair<iFraction, int>> terms;

			public:

				iQuadraticRadical(int n) :_size(1)
				{
					int coefficient = 1;
					for (int i = 1; i < sqrt(n) + 1; i++)
					{
						if (n % (i * i) == 0)
						{
							n /= (i * i);
							coefficient *= i;
						}
					}
					terms.push_back({ iFraction(coefficient,1),n });
				}

			public:

				int size()
				{
					return _size;
				}

				double toDouble()
				{
					double sum = 0;
					for (auto& term : terms)
					{
						sum += term.first.data() * sqrt(term.second);
					}
					return sum;
				}

			public:

				virtual std::list<std::pair<iFraction, int>> data() const
				{
					// TODO
					return std::list<std::pair<iFraction, int>>();
				}

			private:

				int _size;
			};
		}
	}
}