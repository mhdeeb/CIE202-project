#include "SwitchToPlayMode.h"

SwitchToPlayMode::SwitchToPlayMode(controller* pCont) :operation(pCont)
{}
SwitchToPlayMode::~SwitchToPlayMode()
{}
bool SwitchToPlayMode::Execute() {
	GUI* pUI = pControl->GetUI();
	pUI->setInterfaceModeToPlay();
	pUI->Clear();
	pUI->LoadPlayToolBar();
	pUI->CreatePlayToolBar();
	return false;
}