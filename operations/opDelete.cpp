#include "opDelete.h"
Delete::Delete(controller* pCont):operation(pCont) {}
Delete::~Delete() {}
bool Delete::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* graph = pControl->GetGraph();
	graph->deleteSelectedShape();
	pUI->ClearStatusMessage();
	graph->Refresh(pUI);
	return false;
}