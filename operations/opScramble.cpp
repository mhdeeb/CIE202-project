#include "opScramble.h"

opScramble::opScramble(controller* pCont):operation(pCont) {}
opScramble::~opScramble() = default;
bool opScramble::Execute() {
	srand(time(nullptr));
	GUI* pUI = pControl->GetUI();
	Graph const* graph = pControl->GetGraph();
	Point p;
	Point c;
	for (auto* pShape : graph->GetShapeList()) {
		c = pShape->GetCenter();
		do {
			p.x = rand() % (pUI->getWidth() - c.x) - c.x;
			p.y = rand() % (pUI->getHeight() - c.y) - c.y;
		} while (!pUI->isInDrawArea(p + c));
		pShape->Transform(
			[](Point& point, double s, const Point& origin) {
				point.translate(origin);
			}
		, 0, p);
	}
	graph->Refresh(pUI);
	return false;
}