#include "opSelect.h"
#include<ranges>
#include<vector>

Select::Select(controller* pCont) :operation(pCont)
{}
Select::~Select()
{}
bool Select::Execute() {
	GUI* pUI = pControl->GetUI();

	Graph* graph = pControl->getGraph();

	int x, y;

	pUI->getMouseLocation(x, y);

	shape* pSsh = graph->Getshape({ x, y });

	for (auto i : (graph->GetShapeList())) {
		if (i)
			i->SetSelected(false);
	}
	if (pSsh) {
		pSsh->SetSelected(true);
		pSsh->PrintInfo(pUI);
	}
	return false;
}