#include "opRestartGame.h"
#include "opScramble.h"

opRestartGame::opRestartGame(controller* pCont): operation(pCont) {}

bool opRestartGame::Execute() {
	Graph const* graph = pControl->GetGraph();
	GUI* pUI = pControl->GetUI();
	graph->Show(pUI);
	opScramble(pControl).Execute();
	graph->Refresh(pUI);
	return false;
}