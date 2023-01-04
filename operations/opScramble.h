#pragma once
#include "operation.h"

class opScramble: public operation {
public:
	explicit opScramble(controller* pCont);
	~opScramble() override;
	bool Execute() override;
};