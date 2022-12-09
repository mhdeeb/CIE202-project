#include "opColorPalette.h"

opColorPalette::opColorPalette(controller* pCont) : operation(pCont) {}

opColorPalette::~opColorPalette() {}

void opColorPalette::Execute()
{
	GUI* pUI = pControl->GetUI();
	color msgColor = pUI->getMsgColor();
	Point rad;
	pUI->PrintMessage("Color Palette selected: Click on a pixel to pick its color");
	pUI->getWindow()->DrawImage("images/util/Color_palette.jpg", pUI->getWindow()->GetWidth() - 316, 0, 300, 300);
	while (!pUI->GetLeftPointState(rad.x, rad.y)) {
		pUI->setMsgColor(pUI->getHoverColor(rad.x, rad.y));
		pUI->CreateStatusBar(pUI->getMsgColor().hex());
		Sleep(16);
	}
	pUI->setDrawColor(pUI->getHoverColor(rad.x, rad.y));
	pUI->ClearStatusBar();
	pUI->setMsgColor(msgColor);
}
