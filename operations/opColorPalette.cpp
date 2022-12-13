#include "opColorPalette.h"

opColorPalette::opColorPalette(controller* pCont) : operation(pCont) {}

opColorPalette::~opColorPalette() {}

void opColorPalette::Execute()
{
	GUI* pUI = pControl->GetUI();
	color msgColor = pUI->getMsgColor();
	Point p;
	pUI->getWindow()->DrawImage(pUI->getImage(GUI::ICON_COLOR_PALETTE), pUI->getWindow()->GetWidth() - 316, 2, 300, 300);
	while (!pUI->GetLeftPointState(p.x, p.y)) {
		pUI->setMsgColor(pUI->getHoverColor(p.x, p.y));
		pUI->CreateStatusBar(pUI->getMsgColor().hex());
		Sleep(16);
	}
	pUI->setSelectedColor(pUI->getHoverColor(p.x, p.y));
	pUI->setMsgColor(msgColor);
}
