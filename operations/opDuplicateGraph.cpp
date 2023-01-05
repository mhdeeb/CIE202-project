#include "opDuplicateGraph.h"

opDuplicateGraph::opDuplicateGraph(controller* pCont):operation(pCont) {}
opDuplicateGraph::~opDuplicateGraph() = default;
bool opDuplicateGraph::Execute() {
	for (Graph* pGraph = pControl->GetGraph(); const auto * pShape : pGraph->GetShapeList())
		pGraph->Addshape(GUI::ParseShape(pShape->Serialize()), pControl->GetUI());
	return false;
}