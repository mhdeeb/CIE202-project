#include "opAddIrregPoly.h"

#include "../Shapes/IrregPoly.h"
#include "../Shapes/Circle.h"
#include "../Shapes/Line.h"

#include <format>

opAddIrregPoly::opAddIrregPoly(controller* pCont) :operation(pCont)
{}
opAddIrregPoly::~opAddIrregPoly()
{}

void opAddIrregPoly::Execute()
{
	GUI* pUI = pControl->GetUI();
	GfxInfo gfxInfo;
	gfxInfo.DrawClr = pUI->getCrntDrawColor();
	gfxInfo.FillClr = pUI->getCrntFillColor();
	gfxInfo.BorderWdth = pUI->getCrntPenWidth();
	gfxInfo.isFilled = false;
	Point rad;
	int x, y;
	IrregPoly* I = new IrregPoly(gfxInfo);
	pUI->PrintMessage("Irregular Polygon Selected: Click on graph to start drawing");
	pUI->GetPointClicked(x, y);
	I->addPoint({ x, y });
	string msg = format("Point 1: ({}, {})  ", I->getPoint(-1).x, I->getPoint(-1).y);
	pUI->CreateStatusBar(msg);
	Circle C{ I->getPoint(0), 12, gfxInfo };
	while (true) {
		while (pUI->GetLeftClick(rad.x, rad.y)) {
			pControl->getGraph()->Draw(pUI);
			for (int i = 0; i < I->getSize() - 1; ++i) {
				Line l{ I->getPoint(i), I->getPoint(i + 1), gfxInfo };
				pUI->DrawLine(&l);
			}
			Line l2{ I->getPoint(-1), rad, gfxInfo };
			pUI->DrawLine(&l2);
			pUI->CreateStatusBar(msg + format("Point {}: ({}, {})  ", I->getSize() + 1, rad.x, rad.y));
			pUI->DrawCircle(&C);
			Sleep(16);
			pUI->Clear();
		}
		if (I->getPoint(0).distance(rad) < 12)
			break;
		I->addPoint(rad);
		msg += format("Point {}: ({}, {})  ", I->getSize(), I->getPoint(-1).x, I->getPoint(-1).y);
		pUI->CreateStatusBar(msg);
	}
	pUI->ClearStatusBar();
	pControl->getGraph()->Addshape(I);
}
