#include "opRotate.h"

#include <numbers>

opRotate::opRotate(controller* pCont): operation(pCont) {}

opRotate::~opRotate() = default;

bool opRotate::Execute() {
	Graph* graph = pControl->GetGraph();
	GUI* pUI = pControl->GetUI();
	for (auto shape : graph->getSelectedShapes())
		shape->Transform(
			[](TRANSFORMATION) {
				point.translate(-origin).rotate(parameter).translate(origin);
			}
	, numbers::pi / 2, shape->GetCenter());
	graph->Refresh(pUI);
	graph->updateHistory(pUI);
	return false;
}