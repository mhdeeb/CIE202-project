#include "opColorPalette.h"

opColorPalette::opColorPalette(controller* pCont, bool lockScreen) : operation(pCont), lockScreen(lockScreen) {}

opColorPalette::~opColorPalette() = default;

bool opColorPalette::Execute()
{
	GUI* pUI = pControl->GetUI();
	color msgColor = pUI->getMsgColor();
	Point p;
	char c;
	int x = pUI->getWindow()->GetWidth() - 314;
	int y = 50;
	int side = 300;
	pUI->getWindow()->DrawImage(pUI->getImage(GUI::ICON_COLOR_PALETTE), x, y, side, side);
	while (pUI->GetLeftClick(p.x, p.y) || !(x <= p.x && p.x <= x + side && y <= p.y && p.y <= y + side) && lockScreen) {
		if (pUI->GetKeyPress(c) == ESCAPE) {
			pUI->ClearStatusMessage();
			return false;
		}
		pUI->setMsgColor(pUI->getHoverColor(p.x, p.y));
		pUI->PrintMessage(pUI->getMsgColor().hex());
		Sleep(16);
	}
	pUI->setMsgColor(msgColor);
	pUI->ClearStatusMessage();
	pUI->setSelectedColor(pUI->getHoverColor(p.x, p.y));
	return false;
}
