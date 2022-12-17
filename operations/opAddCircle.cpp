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
	Point p1, p2{ 0, 0 };
	char c;
	while (true) {
		pUI->CreateStatusBar("Circle Selected: Click on graph to start drawing");
		if (!pUI->GetPointClicked(p1.x, p1.y))return false;
		if (GUI::isInDrawArea(p1)) {
			pUI->storeImage();
			GfxInfo gfxInfo;
			gfxInfo.DrawClr = pUI->getCrntDrawColor();
			gfxInfo.FillClr = pUI->getCrntFillColor();
			gfxInfo.BorderWdth = pUI->getCrntPenWidth();
			gfxInfo.isFilled = pUI->getIsfilled();
			Circle* C = new Circle(p1, 0, gfxInfo);
			while (pUI->GetLeftClick(p2.x, p2.y)) {
				if (pUI->GetKeyPress(c) == ESCAPE) {
					delete C;
					return false;
				}
				C->setRadius(C->getOrigin().distance(p2));
				C->Draw(pUI);
				pUI->CreateDrawToolBar();
				pUI->CreateStatusBar(format("Point 1: ({}, {})    Point 2: ({}, {})    Radius: {:3.3f}", p1.x, p1.y, p2.x, p2.y, C->getRadius()));
				Sleep(16);
				pUI->loadImage();
			}
			pControl->getGraph()->Addshape(C);
			pControl->getGraph()->Refresh(pUI);
		}
		else
			return true;
	}
}
