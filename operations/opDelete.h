#pragma once
#include "operation.h"
//Selected shape will be deleted. 
class Delete : public operation
{
public:
	Delete(controller* pCont);
	virtual ~Delete() override;
	virtual bool Execute() override;
};
