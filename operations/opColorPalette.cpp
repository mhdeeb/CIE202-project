#include "opColorPalette.h"

opColorPalette::opColorPalette(controller* pCont) : operation(pCont) {}

opColorPalette::~opColorPalette() {}

bool opColorPalette::Execute()
{
	GUI* pUI = pControl->GetUI();
	color msgColor = pUI->getMsgColor();
	Point p;
	char c;
	int x = pUI->getWindow()->GetWidth() - 316, y = 2, side = 300;
	pUI->getWindow()->DrawImage(pUI->getImage(GUI::ICON_COLOR_PALETTE), x, y, side, side);
	while (pUI->GetLeftClick(p.x, p.y)) {
		if (pUI->GetKeyPress(c) == ESCAPE) {
			pUI->ClearStatusMessage();
			return false;
		}
		pUI->setMsgColor(pUI->getHoverColor(p.x, p.y));
		pUI->PrintMessage(pUI->getMsgColor().hex());
		Sleep(16);
	}
	if(x <= p.x && p.x <= x + side && y <= p.y && p.y <= y + side)
		pUI->setSelectedColor(pUI->getHoverColor(p.x, p.y));
	pUI->setMsgColor(msgColor);
	pUI->ClearStatusMessage();
	return false;
}
