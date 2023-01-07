#include "SwitchToPlayMode.h"
#include "opDuplicateGraph.h"
#include "opScramble.h"

SwitchToPlayMode::SwitchToPlayMode(controller* pCont):operation(pCont) {}
SwitchToPlayMode::~SwitchToPlayMode() = default;
bool SwitchToPlayMode::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph const* graph = pControl->GetGraph();
	pUI->setInterfaceModeToPlay();
	opDuplicateGraph(pControl).Execute();
	opScramble(pControl).Execute();
	graph->Hide(pUI);
	graph->Show(pUI);
	graph->Refresh(pUI);
	pUI->CreatePlayToolBar();
	pUI->setScore(-1);
	pUI->PrintMessage("Click Play to start the game");
	return false;
}