#include "noOp.h"

noOp::noOp(controller* pCont) : operation(pCont) {}

noOp::~noOp() {}

bool noOp::Execute()
{
	return false;
}
