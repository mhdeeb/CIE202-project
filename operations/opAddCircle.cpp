#include "opAddCircle.h"

#include "../Shapes/Circle.h"

#include <format>

opAddCircle::opAddCircle(controller* pCont) :operation(pCont)
{}
opAddCircle::~opAddCircle()
{}

bool opAddCircle::Execute()
{
	GUI* pUI = pControl->GetUI();
	Point p1;
	Point p2{ 0, 0 };
	char c;
	while (true) {
		pUI->PrintMessage("Circle Selected: Click on graph to start drawing");
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
			Circle* C = new Circle(p1, 0, gfxInfo);
			while (pUI->MouseDrag(p2.x, p2.y)) {
				if (pUI->GetKeyPress(c) == ESCAPE) {
					delete C;
					pUI->ClearStatusMessage();
					return false;
				}
				C->setRadius(C->getOrigin().distance(p2));
				C->Draw(pUI);
				pUI->CreateDrawToolBar();
				pUI->PrintMessage(format("Point 1: ({: >4}, {: >4})    Point 2: ({: >4}, {: >4})    Radius: {:3.3f}", p1.x, p1.y, p2.x, p2.y, C->getRadius()));
				Sleep(16);
				pUI->loadImage();
			}
			if (p1.distance(p2) == 0) {
				delete C;
				continue;
			}
			pControl->GetGraph()->Addshape(C);
			pControl->GetGraph()->Refresh(pUI);
		}
		else {
			pUI->ClearStatusMessage();
			return true;
		}
	}
}
