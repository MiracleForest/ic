#include "iPoint.h"
#include "iLine.h"

SPACE(i)
{
	SPACE(core)
	{
		SPACE(math)
		{
			std::pair<int, int> iPoint::data() const
			{
				return { _x,_y };
			}
		}
	}
}