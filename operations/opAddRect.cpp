#include "opAddRect.h"

#include "../Shapes/Rect.h"

#include <format>

opAddRect::opAddRect(controller* pCont) :operation(pCont)
{}
opAddRect::~opAddRect()
{}

void opAddRect::Execute()
{
	GUI* pUI = pControl->GetUI();
	GfxInfo gfxInfo;
	gfxInfo.DrawClr = pUI->getCrntDrawColor();
	gfxInfo.FillClr = pUI->getCrntFillColor();
	gfxInfo.BorderWdth = pUI->getCrntPenWidth();
	gfxInfo.isFilled = false;
	Point p1, p2{ 0, 0 };
	pUI->CreateStatusBar("Rectangle Selected: Click on graph to start drawing");
	pUI->GetPointClicked(p1.x, p1.y);
	if (GUI::isInDrawArea(p1)) {
		Rect* R = new Rect(p1, p2, gfxInfo);
		while (!pUI->GetLeftPointState(p2.x, p2.y)) {
			R->setC2(p2);
			pUI->DrawRect(R);
			pControl->getGraph()->Draw(pUI);
			pUI->CreateStatusBar(format("Point 1: ({}, {})    Point 2: ({}, {})", p1.x, p1.y, p2.x, p2.y));
			pUI->CreateDrawToolBar();
			Sleep(16);
			pUI->ClearDrawing();
		}
		pControl->getGraph()->Addshape(R);
	}
}
