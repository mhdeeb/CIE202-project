#include "opExit.h"

opExit::opExit(controller* pCont) : operation(pCont)
{
}

opExit::~opExit()
{
}

void opExit::Execute()
{
	pControl->close();
}
