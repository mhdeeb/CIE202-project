#include "opScramble.h"
#include <random>

opScramble::opScramble(controller* pCont):operation(pCont) {}
opScramble::~opScramble() = default;
bool opScramble::Execute() {
	Graph const* graph = pControl->GetGraph();
	vector<shape*> shapes = graph->GetShapeList();
	auto seed = unsigned(chrono::system_clock::now().time_since_epoch().count());
	ranges::shuffle(shapes.begin(), shapes.end(), default_random_engine(seed));
	auto n = int(sqrt(shapes.size()));
	for (int i = 0; i < shapes.size(); i++) {
		Point p(i / n * 120 + pControl->GetUI()->getWidth() / 4, i % n * 120 + pControl->GetUI()->getHeight() / 4);
		shapes[i]->Transform(
			[](Point& point, double s, const Point& origin) {
				point.translate(origin);
			}
		, 0, p - shapes[i]->GetCenter());
	}
	graph->Refresh(pControl->GetUI());
	return false;
}