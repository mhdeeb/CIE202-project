#include "opDelete.h"
Delete::Delete(controller* pCont) :operation(pCont)
{}
Delete::~Delete()
{}
void Delete::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* graph = pControl->getGraph();
	graph->deleteSelectedShape();
	graph->Refresh(pUI);
	graph->Draw(pUI);
}