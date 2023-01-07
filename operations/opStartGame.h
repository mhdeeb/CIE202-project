#pragma once
#include "operation.h"
class opStartGame:
	public operation {
public:
	explicit opStartGame(controller* pCont);
	~opStartGame() override;
	bool Execute() override;
};
