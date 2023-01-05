#include "opSelect.h"
#include<ranges>
#include<vector>

Select::Select(controller* pCont):operation(pCont) {}
Select::~Select() = default;
bool Select::Execute() {
	GUI* pUI = pControl->GetUI();

	Graph* graph = pControl->GetGraph();

	int x;
	int y;

	pUI->getMouseLocation(x, y);

	shape* pSsh = graph->Getshape({x, y});

	if (graph->getGroupPreview()) {
		for (auto i : graph->GetShapeList()) {
			if (i->getId() == pUI->getGid()) i->SetSelected(true);
			else i->SetSelected(false);
		}
		if (pSsh) {
			if (pSsh->getId() == pUI->getGid()) {
				pSsh->setId(-1);
				pSsh->SetSelected(false);
			} else {
				pSsh->setId(pUI->getGid());
				pSsh->SetSelected(true);
			}
		} else
			pUI->PrintMessage("Select an operation.");
	} else {
		graph->updateSelectedShapes(pUI);
		if (pSsh) {
			pSsh->SetSelected(true);
			pUI->PrintMessage(pSsh->PrintInfo());
		} else
			pUI->PrintMessage("Select an operation.");
	}
	graph->Refresh(pUI);
	return false;
}