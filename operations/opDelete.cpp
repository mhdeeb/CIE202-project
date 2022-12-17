#include "opDelete.h"
Delete::Delete(controller* pCont) :operation(pCont)
{}
Delete::~Delete()
{}
bool Delete::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* graph = pControl->getGraph();
	graph->deleteSelectedShape();
	graph->Refresh(pUI);
	graph->Draw(pUI);
	return false;
}