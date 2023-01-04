#include "opResize.h"

opResize::opResize(controller* pCont): operation(pCont) {}

opResize::~opResize() = default;

bool opResize::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph const* graph = pControl->GetGraph();
	if (shape* pShape = graph->getSelectedShape()) {
		Point p1 = pShape->GetCenter();
		Point p2{0, 0};
		pUI->PrintMessage("Resize Selected: Click on graph to start resizing");
		if (!pUI->GetPointClicked(p2.x, p2.y)) {
			pUI->ClearStatusMessage();
			return false;
		}
		double distance = p1.distance(p2);
		double prev = 1;
		double curr;
		pUI->storeImage();
		while (pUI->MouseDrag(p2.x, p2.y)) {
			curr = p1.distance(p2) / distance;
			pShape->Transform(
				[](Point& point, double s, const Point& origin) {
					point.translate(-origin).scale(s).translate(origin);
				}
			, 1 / prev, p1);
			pShape->Transform(
				[](Point& point, double s, const Point& origin) {
					point.translate(-origin).scale(s).translate(origin);
				}
			, curr, p1);
			prev = curr;
			pShape->Draw(pUI);
			Sleep(16);
			pUI->loadImage();
		}
	}
	graph->Refresh(pControl->GetUI());
	pUI->ClearStatusMessage();
	return false;
}