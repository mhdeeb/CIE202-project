#include "opAddRect.h"

#include "../Shapes/Rect.h"

#include <format>

opAddRect::opAddRect(controller* pCont) :operation(pCont)
{}
opAddRect::~opAddRect()
{}

bool opAddRect::Execute()
{
	GUI* pUI = pControl->GetUI();
	Point p1, p2{ 0, 0 };
	char c;
	while (true) {
		pUI->PrintMessage("Rectangle Selected: Click on graph to start drawing");
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
			gfxInfo.isFilled = pUI->getIsfilled();
			Rect* R = new Rect(p1, p2, gfxInfo);
			while (pUI->MouseDrag(p2.x, p2.y)) {
				if (pUI->GetKeyPress(c) == ESCAPE) {
					delete R;
					pUI->ClearStatusMessage();
					return false;
				}
				R->setC2(p2);
				R->Draw(pUI);
				pUI->CreateDrawToolBar();
				pUI->PrintMessage(format("Point 1: ({: >4}, {: >4})    Point 2: ({: >4}, {: >4})", p1.x, p1.y, p2.x, p2.y));
				Sleep(16);
				pUI->loadImage();
			}
			if (p1.distance(p2) == 0) {
				delete R;
				continue;
			}
			pControl->GetGraph()->Addshape(R);
			pControl->GetGraph()->Refresh(pUI);
		}
		else {
			pUI->ClearStatusMessage();
			return true;
		}
	}
}
