#pragma once
#include "operation.h"
class opPrompt: public operation {
private:
	string prompt;
	string Response;
public:
	opPrompt(controller* pCont, const string& prompt);
	~opPrompt() override;
	bool Execute() override;
	string response() const;
	int isYes() const;
};
