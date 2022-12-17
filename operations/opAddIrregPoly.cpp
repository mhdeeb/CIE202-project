#include "opAddIrregPoly.h"

#include "../Shapes/IrregPoly.h"
#include "../Shapes/Circle.h"
#include "../Shapes/Line.h"

#include <format>

opAddIrregPoly::opAddIrregPoly(controller* pCont) :operation(pCont)
{}
opAddIrregPoly::~opAddIrregPoly()
{}

bool opAddIrregPoly::Execute()
{
	GUI* pUI = pControl->GetUI();
	Point p1, p2{ 0, 0 };
	char ch;
	while (true) {
		pUI->CreateStatusBar("Irregular Polygon Selected: Click on graph to start drawing");
		if (!pUI->GetPointClicked(p1.x, p1.y))return false;
		if (GUI::isInDrawArea(p1)) {
			GfxInfo gfxInfo;
			gfxInfo.DrawClr = pUI->getCrntDrawColor();
			gfxInfo.FillClr = pUI->getCrntFillColor();
			gfxInfo.BorderWdth = pUI->getCrntPenWidth();
			gfxInfo.isFilled = pUI->getIsfilled();
			IrregPoly* I = new IrregPoly(gfxInfo);
			I->addPoint(p1);
			string msg = format("Point   1: ({:>4},{:>4})  ", p1.x, p1.y);
			pUI->CreateStatusBar(msg);
			gfxInfo.DrawClr = LIGHTGRAY;
			Line l{ p1, p2, gfxInfo };
			Circle c{ p1, 12, gfxInfo };
			pUI->storeImage();
			while (true) {
				I->addPoint(p2);
				while (pUI->GetLeftClick(p2.x, p2.y)) {
					if (pUI->GetKeyPress(ch) == ESCAPE) {
						delete I;
						return false;
					}
					I->setPoint(p2, -1);
					l.setPoint2(p2);
					I->Draw(pUI);
					l.Draw(pUI);
					pUI->CreateDrawToolBar();
					pUI->CreateStatusBar(msg + format("Point{:>4}: ({:>4},{:>4})  ", I->getSize(), p2.x, p2.y));
					c.Draw(pUI);
					Sleep(16);
					pUI->loadImage();
				}
				if (p1.distance(p2) < 12) {
					I->removePoint(-1);
					break;
				}
				msg += format("Point{:>4}: ({:>4},{:>4})  ", I->getSize(), p2.x, p2.y);
				if (msg.length() > 96)
					msg = msg.substr(24);
				pUI->CreateStatusBar(msg);
			}
			if (I->getSize() > 1)
				pControl->getGraph()->Addshape(I);
			else
				delete I;
			pControl->getGraph()->Refresh(pUI);
		}
		else
			return true;
	}
}
