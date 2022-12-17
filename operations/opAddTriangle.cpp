#include "opAddTriangle.h"
#include "..\shapes\Triangle.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opAddTri::opAddTri(controller* pCont) :operation(pCont)
{}
opAddTri::~opAddTri()
{}

bool opAddTri::Execute()
{
	Point p1, p2{ 0, 0 };
	GUI* pUI = pControl->GetUI();
	char c;
	while (true) {
		pUI->PrintMessage("New Triangle: Click at first point");
		if (!pUI->GetPointClicked(p1.x, p1.y))return false;
		if (GUI::isInDrawArea(p1)) {
			pUI->storeImage();
			GfxInfo gfxInfo;
			gfxInfo.DrawClr = pUI->getCrntDrawColor();
			gfxInfo.FillClr = pUI->getCrntFillColor();
			gfxInfo.BorderWdth = pUI->getCrntPenWidth();
			gfxInfo.isFilled = pUI->getIsfilled();
			string msg = format("Point  1: ({:>4},{:>4})  ", p1.x, p1.y);
			Triangle* T = new Triangle(gfxInfo);
			T->addPoint(p1);
			for (int i = 0; i < 2; ++i)
			{
				T->addPoint(p2);
				while (pUI->GetLeftClick(p2.x, p2.y)) {
					if (pUI->GetKeyPress(c) == ESCAPE) {
						delete T;
						return false;
					}
					T->setPoint(p2, -1);
					T->Draw(pUI);
					pUI->CreateDrawToolBar();
					pUI->CreateStatusBar(msg + format("Point{:>3}: ({:>4},{:>4})  ", T->getSize(), p2.x, p2.y));
					Sleep(16);
					pUI->loadImage();
				}
				msg += format("Point {:>3}: ({:>4},{:>4})  ", T->getSize(), p2.x, p2.y);
			}
			pControl->getGraph()->Addshape(T);
			pControl->getGraph()->Refresh(pUI);
		}
		else
			return true;;
	}
}
