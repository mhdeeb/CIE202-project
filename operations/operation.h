#pragma once

#include "../controller.h"

//Base class for all possible operations
class operation
{
protected:
	controller* pControl;	//operations needs control to do their job

public:

	operation(controller* pControl) : pControl(pControl) {}	//constructor
	virtual ~operation() {}

	//Execute operation (code depends on operation type)
	virtual bool Execute() = 0;

	//To undo this operation (code depends on operation type)
	//virtual void Undo()=0;

	//To redo this operation (code depends on operation type)
	//virtual void Redo()=0;

};
