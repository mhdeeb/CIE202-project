#include "opAddIrregPoly.h"

#include "../Shapes/IrregPoly.h"
#include "../Shapes/Circle.h"
#include "../Shapes/Line.h"

opAddIrregPoly::opAddIrregPoly(controller* pCont) :operation(pCont)
{}
opAddIrregPoly::~opAddIrregPoly()
{}


void opAddIrregPoly::Execute()
{
	vector<int> xpoints, ypoints;
	int px, py;
	GUI* pUI = pControl->GetUI();
	pUI->PrintMessage("New Irregular Polygon: Click to add points");
	GfxInfo gfxInfo;
	gfxInfo.DrawClr = pUI->getCrntDrawColor();
	gfxInfo.FillClr = pUI->getCrntFillColor();
	gfxInfo.BorderWdth = pUI->getCrntPenWidth();
	gfxInfo.isFilled = false;
	gfxInfo.isSelected = false;
	pUI->GetPointClicked(px, py);
	Circle circ = Circle({ px , py }, 10, gfxInfo);
	pUI->DrawCircle(&circ);
	xpoints.push_back(px);
	ypoints.push_back(py);
	string msg = "Click on first point to complete the shape: p" + to_string(xpoints.size()) + "(" + to_string(px) + ", " + to_string(py) + ") ";
	pUI->PrintMessage(msg);
	pUI->GetPointClicked(px, py);
	while (sqrt(pow(xpoints[0] - px, 2) + pow(ypoints[0] - py, 2)) > 10) {
		circ = Circle({ px , py }, 10, gfxInfo);
		pUI->DrawCircle(&circ);
		Line line = Line({ xpoints[xpoints.size() - 1], ypoints[ypoints.size() - 1] }, { px, py }, gfxInfo);
		pUI->DrawLine(&line);
		xpoints.push_back(px);
		ypoints.push_back(py);
		msg += "p" + to_string(xpoints.size()) + "(" + to_string(px) + ", " + to_string(py) + ") ";
		pUI->PrintMessage(msg);
		pUI->GetPointClicked(px, py);
	};
	pUI->ClearStatusBar();

	IrregPoly* R = new IrregPoly(xpoints, ypoints, gfxInfo);
	Graph* pGr = pControl->getGraph();
	pGr->Addshape(R);
}
