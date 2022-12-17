#include "opAddSquare.h"

#include "../Shapes/Square.h"

#include <format>

opAddSquare::opAddSquare(controller* pCont) :operation(pCont)
{}
opAddSquare::~opAddSquare()
{}

bool opAddSquare::Execute()
{
	GUI* pUI = pControl->GetUI();
	Point p1, p2{ 0, 0 };
	char c;
	while (true) {
		pUI->CreateStatusBar("Square Selected: Click on graph to start drawing");
		if (!pUI->GetPointClicked(p1.x, p1.y))return false;
		if (GUI::isInDrawArea(p1)) {
			pUI->storeImage();
			GfxInfo gfxInfo;
			gfxInfo.DrawClr = pUI->getCrntDrawColor();
			gfxInfo.FillClr = pUI->getCrntFillColor();
			gfxInfo.BorderWdth = pUI->getCrntPenWidth();
			gfxInfo.isFilled = pUI->getIsfilled();
			Square* S = new Square(p1, p2, gfxInfo);
			while (pUI->GetLeftClick(p2.x, p2.y)) {
				if (pUI->GetKeyPress(c) == ESCAPE) {
					delete S;
					return false;
				}
				S->setC2(p2);
				S->Draw(pUI);
				pUI->CreateDrawToolBar();
				pUI->CreateStatusBar(format("Point 1: ({}, {})    Point 2: ({}, {})", p1.x, p1.y, p2.x, p2.y));
				Sleep(16);
				pUI->loadImage();
			}
			pControl->getGraph()->Addshape(S);
			pControl->getGraph()->Refresh(pUI);
		}
		else
			return true;
	}
}
