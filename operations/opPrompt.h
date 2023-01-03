#pragma once
#include "operation.h"
class opPrompt: public operation {
private:
	string prompt;
	string Response;
public:
	opPrompt(controller* pCont, string prompt);
	virtual ~opPrompt() override;
	virtual bool Execute() override;
	string response() const;
	int isYes() const;
};
