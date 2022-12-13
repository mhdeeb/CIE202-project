#include "opAddCircle.h"

#include "../Shapes/Circle.h"

#include <format>

opAddCircle::opAddCircle(controller* pCont) :operation(pCont)
{}
opAddCircle::~opAddCircle()
{}

void opAddCircle::Execute()
{
	GUI* pUI = pControl->GetUI();
	Point p1, p2{ 0, 0 };
	pUI->CreateStatusBar("Circle Selected: Click on graph to start drawing");
	pUI->GetPointClicked(p1.x, p1.y);
	if (GUI::isInDrawArea(p1)) {
		pUI->storeImage();
		GfxInfo gfxInfo;
		gfxInfo.DrawClr = pUI->getCrntDrawColor();
		gfxInfo.FillClr = pUI->getCrntFillColor();
		gfxInfo.BorderWdth = pUI->getCrntPenWidth();
		gfxInfo.isFilled = false;
		Circle* C = new Circle(p1, 0, gfxInfo);
		while (!pUI->GetLeftPointState(p2.x, p2.y)) {
			C->setRadius(C->getOrigin().distance(p2));
			C->Draw(pUI);
			pUI->CreateDrawToolBar();
			pUI->CreateStatusBar(format("Point 1: ({}, {})    Point 2: ({}, {})    Radius: {:3.3f}", p1.x, p1.y, p2.x, p2.y, C->getRadius()));
			Sleep(16);
			pUI->loadImage();
		}
		pControl->getGraph()->Addshape(C);
	}
}
