#include "opLoad.h"

opLoad::opLoad(controller* pCont) : operation(pCont)
{
}

opLoad::~opLoad()
{
}

bool opLoad::Execute()
{
	cout << "Loaded!\n";
	return false;
}
