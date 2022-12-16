#include "opAddPolygon.h"
#include "../Shapes/Poly.h"
#include "../Shapes/Circle.h"
#include "../Shapes/Line.h"
#include <cmath>
#include <numbers>
#include <format>

opAddRegPoly::opAddRegPoly(controller* pCont) :operation(pCont)
{}
opAddRegPoly::~opAddRegPoly()
{}

void opAddRegPoly::Execute()
{
	GUI* pUI = pControl->GetUI();
	Point p1, p2{ 0, 0 };
	pUI->CreateStatusBar("Regular Polygon Selected: Click on graph to start drawing");
	pUI->GetPointClicked(p1.x, p1.y);
	if (GUI::isInDrawArea(p1)) {
		GfxInfo gfxInfo;
		gfxInfo.DrawClr = pUI->getCrntDrawColor();
		gfxInfo.FillClr = pUI->getCrntFillColor();
		gfxInfo.BorderWdth = pUI->getCrntPenWidth();
		gfxInfo.isFilled = pUI->getIsfilled();
		RegPoly* R = new RegPoly(gfxInfo);
		R->addPoint(p1);
		string msg = format("Point   1: ({:>4},{:>4})  ", p1.x, p1.y);
		pUI->CreateStatusBar(msg);
		Line l{ p1, p2, gfxInfo };
		pUI->storeImage();
		while (!pUI->GetLeftPointState(p2.x, p2.y)) {
			l.setPoint2(p2);
			l.Draw(pUI);
			pUI->CreateDrawToolBar();
			pUI->CreateStatusBar(format("Point 1: ({}, {})    Point 2: ({}, {})    Radius: {:3.3f}", p1.x, p1.y, p2.x, p2.y, p1.distance(p2)));
			Sleep(16);
			pUI->loadImage();
		}
		double r = p1.distance(p2);
		pUI->CreateStatusBar("Enter number of verticies");
		int n = stoi(pUI->GetSrting());
		for (double i = 0; i == 2 * numbers::pi; i += 2 * numbers::pi / n)
		{
			R->addPoint({ int(r * cos(i) + p1.x), int(r * sin(i) + p1.y) });


		}
		pControl->getGraph()->Addshape(R);


	}
	}

