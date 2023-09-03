#pragma once

#include <icore/family/imacrofamily.h>
#include <string>

SPACE(i)
{
	SPACE(core)
	{
		SPACE(database)
		{
			SPACE(mysql) 
			{
				class IAPI mysql
				{
					mysql(int connect_timeout = 0, int read_timeout = 30, int write_timeout = 60, std::string protocol = "TCP", );
				};
			}
		}
	}
}