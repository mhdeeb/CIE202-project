#include "opAddSquare.h"

#include "../Shapes/Square.h"

#include <format>

opAddSquare::opAddSquare(controller* pCont) :operation(pCont)
{}
opAddSquare::~opAddSquare()
{}

void opAddSquare::Execute()
{
	GUI* pUI = pControl->GetUI();
	GfxInfo gfxInfo;
	gfxInfo.DrawClr = pUI->getCrntDrawColor();
	gfxInfo.FillClr = pUI->getCrntFillColor();
	gfxInfo.BorderWdth = pUI->getCrntPenWidth();
	gfxInfo.isFilled = false;
	Point rad;
	int x, y;
	Square* S = new Square({}, {}, gfxInfo);
	pUI->PrintMessage("Square Selected: Click on graph to start drawing");
	pUI->GetPointClicked(x, y);
	S->setC1({ x, y });
	pUI->CreateStatusBar(format("({}, {})->", x, y));
	while (!pUI->GetLeftPointState(rad.x, rad.y)) {
		S->setC2(rad);
		pUI->DrawRect(S);
		pControl->getGraph()->Draw(pUI);
		pUI->CreateStatusBar(format("Point 1: ({}, {})    Point 2: ({}, {})", x, y, rad.x, rad.y));
		Sleep(16);
		pUI->Clear();
	}
	pUI->ClearStatusBar();
	pControl->getGraph()->Addshape(S);
}
