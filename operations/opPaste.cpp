#include "opPaste.h"

opPaste::opPaste(controller* pCont): operation(pCont) {}

opPaste::~opPaste() = default;

bool opPaste::Execute() {
	Graph* graph = pControl->GetGraph();
	auto shapes = graph->Paste(pControl->GetUI());
	if (shapes.empty()) return false;
	Point center{0, 0};
	for (const shape* i : shapes)
		center += i->GetCenter();
	center /= shapes.size();
	for (auto i : shapes) {
		i->Transform(
			[](Point& point, double s, const Point& origin) {
				point.translate(origin);
			},
			0, pControl->GetUI()->getMousePosition() - center);
		i->SetSelected(true);
	}
	graph->Refresh(pControl->GetUI());
	return false;
}