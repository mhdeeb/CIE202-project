#include "SwitchToPlayMode.h"
#include "opDuplicateGraph.h"
#include "opScramble.h"

SwitchToPlayMode::SwitchToPlayMode(controller* pCont):operation(pCont) {}
SwitchToPlayMode::~SwitchToPlayMode() = default;
bool SwitchToPlayMode::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* graph = pControl->GetGraph();
	pUI->setInterfaceModeToPlay();
	graph->limitSize();
	opDuplicateGraph(pControl).Execute();
	opScramble(pControl).Execute();
	graph->Hide(pUI);
	graph->Show(pUI);
	graph->Refresh(pUI);
	pUI->CreatePlayToolBar();
	pUI->PrintMessage("Click Play to start the game");
	pUI->getWindow()->ChangeTitle("PLAY");
	return false;
}