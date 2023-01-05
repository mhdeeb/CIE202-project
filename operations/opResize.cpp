#include "opResize.h"

opResize::opResize(controller* pCont): operation(pCont) {}

opResize::~opResize() = default;

bool opResize::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* graph = pControl->GetGraph();
	auto shapes = graph->getSelectedShapes();
	Point center{0, 0};
	for (const shape* i : shapes)
		center += i->GetCenter();
	center /= shapes.size();
	Point p2{0, 0};
	pUI->PrintMessage("Resize Selected: Click on graph to start resizing");
	if (!pUI->GetPointClickedNoOp(p2.x, p2.y)) {
		pUI->ClearStatusMessage();
		return false;
	}
	double distance = center.distance(p2);
	double prev = 1;
	pUI->storeImage();
	while (pUI->MouseDrag(p2.x, p2.y)) {
		double curr = center.distance(p2) / distance;
		for (auto shape : shapes) {
			shape->Transform(
				[](Point& point, double s, const Point& origin) {
					point.translate(-origin).scale(s).translate(origin);
				}
			, 1 / prev, shape->GetCenter());
			shape->Transform(
				[](Point& point, double s, const Point& origin) {
					point.translate(-origin).scale(s).translate(origin);
				}
			, curr, shape->GetCenter());
			shape->Draw(pUI);
		}
		Sleep(16);
		pUI->loadImage();
		prev = curr;
	}
	graph->Refresh(pUI);
	pUI->ClearStatusMessage();
	graph->updateHistory(pUI);
	return false;
}