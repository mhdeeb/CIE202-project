#include "SwitchToDrawMode.h"

SwitchToDrawMode::SwitchToDrawMode(controller* pCont):operation(pCont) {}
SwitchToDrawMode::~SwitchToDrawMode() {}
bool SwitchToDrawMode::Execute() {
	GUI* pUI = pControl->GetUI();
	pUI->setInterfaceModeToDraw();
	pUI->Clear();
	pUI->LoadDrawToolBar();
	pUI->CreateDrawToolBar();
	return false;
}