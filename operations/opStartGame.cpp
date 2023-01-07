#include "opStartGame.h"

opStartGame::opStartGame(controller* pCont): operation(pCont) {}

opStartGame::~opStartGame() = default;

bool opStartGame::Execute() {
	Graph const* graph = pControl->GetGraph();
	GUI* pUI = pControl->GetUI();
	graph->Hide(pUI);
	pUI->setScore(0);
	pUI->PrintMessage("Game Started!");

	if (pUI->getScore() == -1)
		pUI->PrintMessage("Click Play to start the game");
	else
		pUI->PrintMessage(format("Score: {}", pUI->getScore()));

	//if (pUI->getInterfaceMode() && pUI->getScore() != -1 && pSsh) {
	//	pSsh->Show();

	//	pUI->setScore(pUI->getScore() + 1);
	//	pUI->setScore(pUI->getScore() + 3);

	//	for (const shape* shape : graph->GetShapeList())
	//		if (shape->isHidden()) {
	//			graph->Refresh(pUI);
	//			return false;
	//		}
	//	graph->Refresh(pUI);
	//	pUI->Prompt(format("Congratulations!\n\nYour score is {}\n\nPress any key to exit", pUI->getScore()));
	//	return false;
	//} else {
	//	graph->Refresh(pUI);
	return false;
}