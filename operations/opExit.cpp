#include "opExit.h"

opExit::opExit(controller* pCont) : operation(pCont)
{
}

opExit::~opExit()
{
}

bool opExit::Execute()
{
	pControl->close();
	return false;
}
