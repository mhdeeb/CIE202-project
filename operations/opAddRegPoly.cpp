#include "opAddRegPoly.h"
#include "../Shapes/RegPoly.h"
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
	int n = stoi(pUI->GetSrting());
	pUI->CreateStatusBar("Regular Polygon Selected: Click on graph to start drawing");
	pUI->GetPointClicked(p1.x, p1.y);
	if (GUI::isInDrawArea(p1)) {
		GfxInfo gfxInfo;
		gfxInfo.DrawClr = pUI->getCrntDrawColor();
		gfxInfo.FillClr = pUI->getCrntFillColor();
		gfxInfo.BorderWdth = pUI->getCrntPenWidth();
		gfxInfo.isFilled = pUI->getIsfilled();
		RegPoly* R = new RegPoly(gfxInfo);
		string msg = format("Point 1: ({:>4},{:>4})  ", p1.x, p1.y);
		pUI->CreateStatusBar(msg);
		Line l{ p1, p2, gfxInfo };
		pUI->storeImage();
		while (!pUI->GetLeftPointState(p2.x, p2.y)) {
			l.setPoint2(p2);
			l.Draw(pUI);
			pUI->CreateDrawToolBar();
			pUI->CreateStatusBar(msg + format("Point 2: ({:>4},{:>4})  Radius:{:4.1f}", p2.x, p2.y, p1.distance(p2)));
			Sleep(16);
			pUI->loadImage();
		}
		double r = p1.distance(p2);
		for (double theta = 0; theta < 2 * numbers::pi; theta += 2 * numbers::pi / n)
			R->addPoint({ int(r * cos(theta) + p1.x), int(r * sin(theta) + p1.y) });
		if (R->getSize() > 1)
			pControl->getGraph()->Addshape(R);
		else
			delete R;
	}
}


