#include "opZoomIn.h"

opZoomIn::opZoomIn(controller* pCont): operation(pCont) {}

opZoomIn::~opZoomIn() = default;

bool opZoomIn::Execute() {
	Graph const* graph = pControl->GetGraph();
	GUI* pUI = pControl->GetUI();
	graph->GetShapeList();
	for (auto pShape : graph->GetShapeList())
		pShape->Transform(
			[](Point& point, double factor, const Point& origin) {
				point.translate(-origin).scale(factor).translate(origin);
			}
	, 1.1, pUI->getMousePosition());
	graph->Refresh(pUI);
	return false;
}