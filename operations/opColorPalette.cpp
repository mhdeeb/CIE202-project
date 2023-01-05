#include "opColorPalette.h"
#include "../Shapes/Rect.h"

opColorPalette::opColorPalette(controller* pCont, bool lockScreen): operation(pCont), lockScreen(lockScreen) {}

opColorPalette::~opColorPalette() = default;

bool opColorPalette::Execute() {
	GUI* pUI = pControl->GetUI();
	color msgColor = pUI->getMsgColor();
	Point p;
	char c;
	int x = pUI->getWindow()->GetWidth() - 320;
	int y = 100;
	int side = 300;
	Rect border{{ x - 3, y - 3 }, {x + side + 3, y + side + 3 }, { BLACK, WHITE, false, 5, false }};
	Rect border2{{ x - 4, y - 4 }, {x + side + 4, y + side + 4 }, { GREY, WHITE, false, 5, false }};
	pUI->DrawRect(&border2, 5, 5);
	pUI->getWindow()->DrawImage(pUI->getImage(GUI::ICON_COLOR_PALETTE), x, y, side, side);
	pUI->DrawRect(&border, 5, 5);
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
	pControl->GetGraph()->Refresh(pUI);
	return false;
}