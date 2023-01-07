#include "SwitchToDrawMode.h"

SwitchToDrawMode::SwitchToDrawMode(controller* pCont):operation(pCont) {}
SwitchToDrawMode::~SwitchToDrawMode() = default;
bool SwitchToDrawMode::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* graph = pControl->GetGraph();
	pUI->setInterfaceModeToDraw();
	pUI->ClearStatusMessage();
	graph->Clear();
	graph->Refresh(pUI);
	return false;
}