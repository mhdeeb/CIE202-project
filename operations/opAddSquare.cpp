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
	Point p1, p2{ 0, 0 };
	pUI->CreateStatusBar("Square Selected: Click on graph to start drawing");
	pUI->GetPointClicked(p1.x, p1.y);
	if (GUI::isInDrawArea(p1)) {
		Square* S = new Square(p1, p2, gfxInfo);
		while (!pUI->GetLeftPointState(p2.x, p2.y)) {
			S->setC2(p2);
			pUI->DrawRect(S);
			pControl->getGraph()->Draw(pUI);
			pUI->CreateStatusBar(format("Point 1: ({}, {})    Point 2: ({}, {})", p1.x, p1.y, p2.x, p2.y));
			pUI->CreateDrawToolBar();
			Sleep(16);
			pUI->ClearDrawing();
		}
		pControl->getGraph()->Addshape(S);
	}
}
