#include "opPaste.h"

opPaste::opPaste(controller* pCont): operation(pCont) {}

opPaste::~opPaste() = default;

bool opPaste::Execute() {
	Graph* graph = pControl->GetGraph();
	shape* s = graph->Paste();
	if (s)
		s->Transform(
			[](Point& point, double s, const Point& origin) {
				point.translate(origin);
			},
			0, pControl->GetUI()->getMousePosition() - s->GetCenter());
	graph->Refresh(pControl->GetUI());
	return false;
}