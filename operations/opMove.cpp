#include "opMove.h"

opMove::opMove(controller* pCont): operation(pCont) {}

opMove::~opMove() = default;

bool opMove::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* graph = pControl->GetGraph();
	Point p1{0, 0};
	Point p2{0, 0};
	pUI->PrintMessage("Move Selected: Click on graph to start moving");
	if (!pUI->GetPointClickedNoOp(p1.x, p1.y)) {
		pUI->ClearStatusMessage();
		return false;
	}
	pUI->storeImage();
	while (pUI->MouseDrag(p2.x, p2.y)) {
		for (auto shape : graph->getSelectedShapes()) {
			shape->Transform(
				[](Point& point, double s, const Point& origin) {
					point.translate(origin);
				}
			, 0, p2 - p1);

			shape->Draw(pUI);
		}
		Sleep(16);
		pUI->loadImage();
		p1 = p2;
	}
	graph->Refresh(pUI);
	pUI->ClearStatusMessage();
	graph->updateHistory(pUI);
	return false;
}