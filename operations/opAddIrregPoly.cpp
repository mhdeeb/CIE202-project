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
	Point p1, p2{ 0, 0 };
	IrregPoly* I = new IrregPoly(gfxInfo);
	pUI->CreateStatusBar("Irregular Polygon Selected: Click on graph to start drawing");
	pUI->GetPointClicked(p1.x, p1.y);
	if (GUI::isInDrawArea(p1)) {
		I->addPoint(p1);
		string msg = format("Point 1: ({}, {})  ", p1.x, p1.y);
		pUI->CreateStatusBar(msg);
		Circle C{ p1, 12, gfxInfo };
		while (true) {
			while (pUI->GetLeftClick(p2.x, p2.y)) {
				pControl->getGraph()->Draw(pUI);
				for (int i = 0; i < I->getSize() - 1; ++i) {
					Line l{ I->getPoint(i), I->getPoint(i + 1), gfxInfo };
					pUI->DrawLine(&l);
				}
				Line l2{ I->getPoint(-1), p2, gfxInfo };
				pUI->DrawLine(&l2);
				pUI->CreateStatusBar(msg + format("Point {}: ({}, {})  ", I->getSize() + 1, p2.x, p2.y));
				pUI->DrawCircle(&C);
				pUI->CreateDrawToolBar();
				Sleep(16);
				pUI->ClearDrawing();
			}
			if (p1.distance(p2) < 12)
				break;
			I->addPoint(p2);
			msg += format("Point {}: ({}, {})  ", I->getSize(), p2.x, p2.y);
			pUI->CreateStatusBar(msg);
		}
		pControl->getGraph()->Addshape(I);
	}
}
