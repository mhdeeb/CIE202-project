#include "opAddRegPoly.h"
#include "../Shapes/RegPoly.h"
#include "../Shapes/Circle.h"
#include "../Shapes/Line.h"
#include <cmath>
#include <format>

opAddRegPoly::opAddRegPoly(controller* pCont) :operation(pCont)
{}
opAddRegPoly::~opAddRegPoly()
{}

void opAddRegPoly::Execute()
{
	GUI* pUI = pControl->GetUI();
	Point p1, p2{ 0, 0 };
	int n;
	while ((n = stoi(pUI->GetSrting("Enter no of vertices(more than 1): "))) < 2);
	pUI->CreateStatusBar("Regular Polygon Selected: Click on graph to start drawing");
	pUI->GetPointClicked(p1.x, p1.y);
	if (GUI::isInDrawArea(p1)) {
		GfxInfo gfxInfo;
		gfxInfo.DrawClr = pUI->getCrntDrawColor();
		gfxInfo.FillClr = pUI->getCrntFillColor();
		gfxInfo.BorderWdth = pUI->getCrntPenWidth();
		gfxInfo.isFilled = pUI->getIsfilled();
		RegPoly* R = new RegPoly(p1, n, gfxInfo);
		double radius = 0;
		pUI->storeImage();
		while (!pUI->GetLeftPointState(p2.x, p2.y)) {
			radius = p1.distance(p2);
			R->update(p1, radius);
			R->Draw(pUI);
			pUI->CreateDrawToolBar();
			pUI->CreateStatusBar(format("Point 1: ({:>4},{:>4})  Point 2: ({:>4},{:>4})  Radius:{:4.1f}", p1.x, p1.y, p2.x, p2.y, radius));
			Sleep(16);
			pUI->loadImage();
		}
		pControl->getGraph()->Addshape(R);
	}
}
