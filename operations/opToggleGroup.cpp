#include "opToggleGroup.h"

opToggleGroup::opToggleGroup(controller* pCont): operation(pCont) {}

opToggleGroup::~opToggleGroup() = default;

bool opToggleGroup::Execute() {
	Graph* graph = pControl->GetGraph();
	GUI* pUI = pControl->GetUI();
	graph->setGroupPreview(!graph->getGroupPreview());
	if (!graph->getGroupPreview()) {
		for (auto shape : graph->getSelectedShapes())
			shape->SetSelected(false);
	} else {
		for (auto shape : graph->GetShapeList())
			if (shape->getId() == pUI->getGid())
				shape->SetSelected(true);
	}
	pUI->ClearStatusMessage();
	graph->Refresh(pUI);
	return false;
}