#include "opAddLine.h"

#include "../Shapes/Line.h"

#include <format>

opAddLine::opAddLine(controller* pCont) :operation(pCont)
{}
opAddLine::~opAddLine()
{}

void opAddLine::Execute()
{
	GUI* pUI = pControl->GetUI();
	GfxInfo gfxInfo;
	gfxInfo.DrawClr = pUI->getCrntDrawColor();
	gfxInfo.FillClr = pUI->getCrntFillColor();
	gfxInfo.BorderWdth = pUI->getCrntPenWidth();
	gfxInfo.isFilled = false;
	Point p1, p2{ 0, 0 };
	pUI->CreateStatusBar("Line Selected: Click on graph to start drawing");
	pUI->GetPointClicked(p1.x, p1.y);
	Line* L = new Line(p1, p2, gfxInfo);
	if (GUI::isInDrawArea(p1)) {
		while (!pUI->GetLeftPointState(p2.x, p2.y)) {
			L->setPoint2(p2);
			pUI->DrawLine(L);
			pControl->getGraph()->Draw(pUI);
			pUI->CreateStatusBar(format("Point 1: ({}, {})    Point 2: ({}, {})", p1.x, p1.y, p2.x, p2.y));
			pUI->CreateDrawToolBar();
			Sleep(16);
			pUI->ClearDrawing();
		}
		pControl->getGraph()->Addshape(L);
	}
}
