#include "opRotate.h"

#include <numbers>

opRotate::opRotate(controller* pCont): operation(pCont) {}

opRotate::~opRotate() = default;

bool opRotate::Execute() {
	Graph const* graph = pControl->GetGraph();
	for (auto shape : graph->getSelectedShapes())
		shape->Transform(
			[](Point& point, double angle, const Point& origin) {
				point.translate(-origin).rotate(angle).translate(origin);
			}
	, numbers::pi / 4, shape->GetCenter());
	graph->Refresh(pControl->GetUI());
	return false;
}