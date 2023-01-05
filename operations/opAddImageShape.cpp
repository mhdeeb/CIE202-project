#include "opAddImageShape.h"
#include "opPrompt.h"

#include "../Shapes/imageShape.h"

#include <format>

opAddImageShape::opAddImageShape(controller* pCont):operation(pCont) {}
opAddImageShape::~opAddImageShape() = default;

bool opAddImageShape::Execute() {
	GUI* pUI = pControl->GetUI();
	Point p1{0, 0};
	Point p2{0, 0};
	char c;
	auto [response, files] = pUI->fileSelect("images/", ".jpg");
	if (response == "")
		return false;

	if (!files.contains(response)) {
		pUI->PrintMessage("Image wasn't loaded: bad input");
		return false;
	}

	pUI->PrintMessage("Image Selected: Drag on graph to create it");
	if (!pUI->GetPointClicked(p1.x, p1.y)) {
		pUI->ClearStatusMessage();
		return false;
	}
	if (pUI->isInDrawArea(p1)) {
		pUI->storeImage();
		imageShape* I = new imageShape(p1, p2, files[response].generic_string());
		while (pUI->MouseDrag(p2.x, p2.y)) {
			if (pUI->GetKeyPress(c) == ESCAPE) {
				delete I;
				pUI->ClearStatusMessage();
				return false;
			}
			I->setC2(p2);
			I->Draw(pUI);
			pUI->CreateDrawToolBar();
			pUI->PrintMessage(format("Point 1: ({: >4}, {: >4})    Point 2: ({: >4}, {: >4})", p1.x, p1.y, p2.x, p2.y));
			Sleep(16);
			pUI->loadImage();
		}
		if (p1.distance(p2) == 0) {
			delete I;
			return false;
		}
		pControl->GetGraph()->Addshape(I);
		pControl->GetGraph()->Refresh(pUI);
	} else {
		pUI->ClearStatusMessage();
		return true;
	}
	return false;
}