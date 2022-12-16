#include "opSelect.h"
#include<ranges>
#include<vector>

Select::Select(controller* pCont) :operation(pCont)
{}
Select::~Select()
{}
void Select::Execute() {
	GUI* pUI = pControl->GetUI();

	Graph* graph = pControl->getGraph();

	shape* pSsh = graph->Getshape(pUI->getMouseLocation());
	for (auto i : (graph->GetShapeList())) {
		if (i == pSsh) {
			if(pSsh)
			pSsh->SetSelected(true);
		}
		else {
			if (i)
				i->SetSelected(false);
		}

	}
}