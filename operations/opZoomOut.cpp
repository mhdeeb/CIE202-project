#include "opZoomOut.h"

opZoomOut::opZoomOut(controller* pCont): operation(pCont) {}

opZoomOut::~opZoomOut() = default;

bool opZoomOut::Execute() {
	Graph const* graph = pControl->GetGraph();
	GUI* pUI = pControl->GetUI();
	graph->GetShapeList();
	for (auto pShape : graph->GetShapeList())
		pShape->Transform(
			[](Point& point, double factor, const Point& origin) {
				point.translate(-origin).scale(factor).translate(origin);
			}
	, 0.9, pUI->getMousePosition());
	graph->Refresh(pUI);
	return false;
}