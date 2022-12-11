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
	GfxInfo gfxInfo;
	gfxInfo.DrawClr = pUI->getCrntDrawColor();
	gfxInfo.FillClr = pUI->getCrntFillColor();
	gfxInfo.BorderWdth = pUI->getCrntPenWidth();
	gfxInfo.isFilled = false;
	Point rad;
	int x, y;
	Circle* C = new Circle( {}, {}, gfxInfo);
	pUI->PrintMessage("Circle Selected: Click on graph to start drawing");
	pUI->GetPointClicked(x, y);
	C->setOrigin({ x, y });
	while (!pUI->GetLeftPointState(rad.x, rad.y)) {
		C->setRadius(C->getOrigin().distance(rad));
		pUI->DrawCircle(C);
		pControl->getGraph()->Draw(pUI);
		pUI->CreateStatusBar(format("Point 1: ({}, {})    Point 2: ({}, {})    Radius: {:3.3f}", x, y, rad.x, rad.y, C->getRadius()));
		pUI->CreateDrawToolBar();
		Sleep(16);
		pUI->ClearDrawing();
	}
	pUI->ClearStatusBar();
	pControl->getGraph()->Addshape(C);
}
