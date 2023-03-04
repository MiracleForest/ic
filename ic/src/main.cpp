#include <icore/family/ifamily.hpp>
#include <icore/console/iconsole.hpp>
#include <icore/exception/error.hpp>
#include "../include/iLexer/iLexer.h"

iMain(_p_start)
{
	_p_start.pause = true;

	_ISTD io::iConsole::writeLine("喵");
	return _ISTD iexception::error::noError();
}