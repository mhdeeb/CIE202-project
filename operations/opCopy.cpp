#include "opCopy.h"

opCopy::opCopy(controller* pCont): operation(pCont) {}

opCopy::~opCopy() = default;

bool opCopy::Execute() {
	Graph* graph = pControl->GetGraph();
	graph->Copy();
	return false;
}