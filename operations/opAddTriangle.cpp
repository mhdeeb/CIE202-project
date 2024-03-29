#include "opAddTriangle.h"
#include "../shapes/Triangle.h"

#include "../controller.h"

#include "../GUI/GUI.h"

opAddTri::opAddTri(controller* pCont):operation(pCont) {}
opAddTri::~opAddTri() {}

bool opAddTri::Execute() {
	Point p1{0, 0};
	Point p2{0, 0};
	GUI* pUI = pControl->GetUI();
	char c;
	while (true) {
		pUI->PrintMessage("New Triangle: Click at first point");
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
			string msg = format("Point  1: ({: >4},{: >4})  ", p1.x, p1.y);
			Triangle* T = new Triangle(gfxInfo);
			T->addPoint(p1);
			for (int i = 0; i < 2; ++i) {
				T->addPoint(p2);
				while (!pUI->GetLeftClick(p2.x, p2.y)) {
					if (pUI->GetKeyPress(c) == ESCAPE) {
						delete T;
						pUI->ClearStatusMessage();
						return false;
					}
					T->setPoint(p2, -1);
					T->Draw(pUI);
					pUI->CreateDrawToolBar();
					pUI->PrintMessage(msg + format("Point{: >4}: ({: >4}, {: >4})  ", T->getSize(), p2.x, p2.y));
					Sleep(16);
					pUI->loadImage();
				}
				msg += format("Point {: >4}: ({: >4}, {: >4})  ", T->getSize(), p2.x, p2.y);
			}
			if (p1.distance(T->getPoint(1)) == 0 && p2.distance(T->getPoint(1))) {
				delete T;
				continue;
			}
			pControl->GetGraph()->Addshape(T, pUI);
			pControl->GetGraph()->Refresh(pUI);
		} else {
			pUI->ClearStatusMessage();
			return true;
		}
	}
}