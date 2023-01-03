#include "opAddRegPoly.h"
#include "opPrompt.h"
#include "../Shapes/RegPoly.h"
#include "../Shapes/Circle.h"
#include "../Shapes/Line.h"
#include <cmath>
#include <format>

opAddRegPoly::opAddRegPoly(controller* pCont):operation(pCont) {}
opAddRegPoly::~opAddRegPoly() = default;

bool opAddRegPoly::Execute() {
	GUI* pUI = pControl->GetUI();
	Point p1;
	Point p2{0, 0};
	string s;
	char c;
	auto prompt = opPrompt(pControl, "Enter no of vertices(more than 1)");
	prompt.Execute();
	s = prompt.response();
	if (s.empty() || !std::ranges::all_of(s.begin(), s.end(), ::isdigit) || std::stoi(s) < 2) {
		pUI->PrintMessage("Error, bad argument: Select another operation");
		return false;
	}
	int n = std::stoi(s);
	while (true) {
		pUI->PrintMessage("Regular Polygon Selected: Click on graph to start drawing");
		if (!pUI->GetPointClicked(p1.x, p1.y)) {
			pUI->ClearStatusMessage();
			return false;
		}
		if (pUI->isInDrawArea(p1)) {
			GfxInfo gfxInfo;
			gfxInfo.DrawClr = pUI->getCrntDrawColor();
			gfxInfo.FillClr = pUI->getCrntFillColor();
			gfxInfo.BorderWdth = pUI->getCrntPenWidth();
			gfxInfo.isFilled = pUI->getIsfilled();
			RegPoly* R = new RegPoly(p1, n, gfxInfo);
			double radius = 0;
			pUI->storeImage();
			while (pUI->MouseDrag(p2.x, p2.y)) {
				if (pUI->GetKeyPress(c) == ESCAPE) {
					delete R;
					pUI->ClearStatusMessage();
					return false;
				}
				radius = p1.distance(p2);
				R->update(p1, radius);
				R->Draw(pUI);
				pUI->CreateDrawToolBar();
				pUI->PrintMessage(format("Point 1: ({: >4}, {: >4})  Point 2: ({: >4}, {: >4})  Radius: {:4.1f}", p1.x, p1.y, p2.x, p2.y, radius));
				Sleep(16);
				pUI->loadImage();
			}
			if (radius == 0) {
				delete R;
				continue;
			}
			pControl->GetGraph()->Addshape(R);
			pControl->GetGraph()->Refresh(pUI);
		} else {
			pUI->ClearStatusMessage();
			return true;
		}
	}
}