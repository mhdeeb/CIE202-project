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
	Point p1, p2{ 0, 0 };
	pUI->CreateStatusBar("Line Selected: Click on graph to start drawing");
	pUI->GetPointClicked(p1.x, p1.y);
	if (GUI::isInDrawArea(p1)) {
		pUI->storeImage();
		GfxInfo gfxInfo;
		gfxInfo.DrawClr = pUI->getCrntDrawColor();
		gfxInfo.FillClr = pUI->getCrntFillColor();
		gfxInfo.BorderWdth = pUI->getCrntPenWidth();
		Line* L = new Line(p1, p2, gfxInfo);
		while (!pUI->GetLeftPointState(p2.x, p2.y)) {
			L->setPoint2(p2);
			L->Draw(pUI);
			pUI->CreateDrawToolBar();
			pUI->CreateStatusBar(format("Point 1: ({}, {})    Point 2: ({}, {})", p1.x, p1.y, p2.x, p2.y));
			Sleep(16);
			pUI->loadImage();
		}
		pControl->getGraph()->Addshape(L);
	}
}
