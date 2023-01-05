#include "opDelete.h"
Delete::Delete(controller* pCont):operation(pCont) {}
Delete::~Delete() {}
bool Delete::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* graph = pControl->GetGraph();
	for (auto shape : graph->getSelectedShapes())
		graph->Removeshape(shape, pUI);
	pUI->ClearStatusMessage();
	graph->Refresh(pUI);
	return false;
}