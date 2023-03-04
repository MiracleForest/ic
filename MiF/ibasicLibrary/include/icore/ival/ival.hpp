#pragma once
#include <icore/family/imacrofamily.h>
// It still needs to be improved.
class iVal
    :public basic::iBasic<iVal>
{
	iObject(iVal); 
	public:
	
		iVal(int x){};

                iVal(double x){};

	public:

                void clear();

	public:
		int _val;
		double _val;

};
