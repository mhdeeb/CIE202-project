#include "opRotate.h"

#include <numbers>

opRotate::opRotate(controller* pCont) : operation(pCont) {}

opRotate::~opRotate() = default;

bool opRotate::Execute()
{
	Graph const* graph = pControl->GetGraph();
	if (shape* pShape = graph->getSelectedShape(); pShape && !pShape->Serialize().starts_with("CIRCLE"))
		pShape->Transform(
			[](Point& point, double angle, const Point& origin) {
				point.translate(-origin).rotate(angle).translate(origin);
			}
		, numbers::pi / 4, pShape->GetCenter());
		graph->Refresh(pControl->GetUI());
	return false;
}
