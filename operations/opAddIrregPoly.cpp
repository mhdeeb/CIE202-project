//#include "opAddIrregPoly.h"
//
//#include "../Shapes/IrregPoly.h"
//#include "../Shapes/Circle.h"
//#include "../Shapes/Line.h"
//
//opAddIrregPoly::opAddIrregPoly(controller* pCont) :operation(pCont)
//{}
//opAddIrregPoly::~opAddIrregPoly()
//{}
//
//
//void opAddIrregPoly::Execute()
//{
//	vector<int> xpoints, ypoints;
//	int px, py;
//	GUI* pUI = pControl->GetUI();
//	pUI->PrintMessage("New Irregular Polygon: Click to add points");
//	GfxInfo gfxInfo;
//	gfxInfo.DrawClr = pUI->getCrntDrawColor();
//	gfxInfo.FillClr = pUI->getCrntFillColor();
//	gfxInfo.BorderWdth = pUI->getCrntPenWidth();
//	gfxInfo.isFilled = false;
//	gfxInfo.isSelected = false;
//	pUI->GetPointClicked(px, py);
//	Circle circ = Circle({ px , py }, 10, gfxInfo);
//	pUI->DrawCircle(&circ);
//	xpoints.push_back(px);
//	ypoints.push_back(py);
//	string msg = "Click on first point to complete the shape: p" + to_string(xpoints.size()) + "(" + to_string(px) + ", " + to_string(py) + ") ";
//	pUI->PrintMessage(msg);
//	pUI->GetPointClicked(px, py);
//	while (sqrt(pow(xpoints[0] - px, 2) + pow(ypoints[0] - py, 2)) > 10) {
//		circ = Circle({ px , py }, 10, gfxInfo);
//		pUI->DrawCircle(&circ);
//		Line line = Line({ xpoints[xpoints.size() - 1], ypoints[ypoints.size() - 1] }, { px, py }, gfxInfo);
//		pUI->DrawLine(&line);
//		xpoints.push_back(px);
//		ypoints.push_back(py);
//		msg += "p" + to_string(xpoints.size()) + "(" + to_string(px) + ", " + to_string(py) + ") ";
//		pUI->PrintMessage(msg);
//		pUI->GetPointClicked(px, py);
//	};
//	pUI->ClearStatusBar();
//
//	IrregPoly* R = new IrregPoly(xpoints, ypoints, gfxInfo);
//	Graph* pGr = pControl->getGraph();
//	pGr->Addshape(R);
//}
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
			pUI->CreateStatusBar(msg);
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
