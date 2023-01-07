#include "opToggleGroup.h"

opToggleGroup::opToggleGroup(controller* pCont): operation(pCont) {}

opToggleGroup::~opToggleGroup() = default;

bool opToggleGroup::Execute() {
	Graph* graph = pControl->GetGraph();
	GUI* pUI = pControl->GetUI();
	graph->setGroupPreview(!graph->getGroupPreview());
	graph->updateSelectedShapes(pUI);
	if (graph->getGroupPreview()) {
		pUI->PrintMessage(format("Group Mode Activated: Selected Group is {}", pUI->getGid()));
	} else {
		pUI->ClearStatusMessage();
	}

	graph->Refresh(pUI);
	return false;
}