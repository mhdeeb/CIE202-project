#pragma once
#include "operation.h"
class opRestartGame: public operation {
public:
	explicit opRestartGame(controller* pCont);
	~opRestartGame() override = default;
	bool Execute() override;
};
