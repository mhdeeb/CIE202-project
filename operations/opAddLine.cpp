#include "opAddLine.h"

#include "../Shapes/Line.h"

#include <format>

opAddLine::opAddLine(controller* pCont) :operation(pCont)
{}
opAddLine::~opAddLine()
{}

bool opAddLine::Execute()
{
	GUI* pUI = pControl->GetUI();
	Point p1, p2{ 0, 0 };
	char c;
	while (true) {
		pUI->PrintMessage("Line Selected: Click on graph to start drawing");
		if (!pUI->GetPointClicked(p1.x, p1.y)) {
			pUI->ClearStatusMessage();
			return false;
		}
		if (pUI->isInDrawArea(p1)) {
			pUI->storeImage();
			GfxInfo gfxInfo;
			gfxInfo.DrawClr = pUI->getCrntDrawColor();
			gfxInfo.FillClr = pUI->getCrntFillColor();
			gfxInfo.BorderWdth = pUI->getCrntPenWidth();
			Line* L = new Line(p1, p2, gfxInfo);
			while (pUI->MouseDrag(p2.x, p2.y)) {
				if (pUI->GetKeyPress(c) == ESCAPE) {
					delete L;
					pUI->ClearStatusMessage();
					return false;
				}
				L->setPoint2(p2);
				L->Draw(pUI);
				pUI->CreateDrawToolBar();
				pUI->PrintMessage(format("Point 1: ({: >4}, {: >4})    Point 2: ({: >4}, {: >4})", p1.x, p1.y, p2.x, p2.y));
				Sleep(16);
				pUI->loadImage();
			}
			pControl->GetGraph()->Addshape(L);
			pControl->GetGraph()->Refresh(pUI);
		}
		else {
			pUI->ClearStatusMessage();
			return true;
		}
	}
}
