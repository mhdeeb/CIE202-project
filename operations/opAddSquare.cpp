#include "opAddSquare.h"

#include "../Shapes/Square.h"

#include <format>

opAddSquare::opAddSquare(controller* pCont):operation(pCont) {}
opAddSquare::~opAddSquare() = default;

bool opAddSquare::Execute() {
	GUI* pUI = pControl->GetUI();
	Point p1{0, 0};
	Point p2{0, 0};
	char c;
	while (true) {
		pUI->PrintMessage("Square Selected: Drag on graph to create it");
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
			Square* S = new Square(p1, p2, gfxInfo);
			while (pUI->MouseDrag(p2.x, p2.y)) {
				if (pUI->GetKeyPress(c) == ESCAPE) {
					delete S;
					pUI->ClearStatusMessage();
					return false;
				}
				S->setC2(p2);
				S->Draw(pUI);
				pUI->CreateDrawToolBar();
				pUI->PrintMessage(format("Point 1: ({: >4}, {: >4})    Point 2: ({: >4}, {: >4})", p1.x, p1.y, p2.x, p2.y));
				Sleep(16);
				pUI->loadImage();
			}
			if (p1.distance(p2) == 0) {
				delete S;
				continue;
			}
			pControl->GetGraph()->Addshape(S, pUI);
			pControl->GetGraph()->Refresh(pUI);
		} else {
			pUI->ClearStatusMessage();
			return true;
		}
	}
}