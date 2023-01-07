#include "opStartGame.h"
#include "../Shapes/Button.h"

opStartGame::opStartGame(controller* pCont): operation(pCont) {}

opStartGame::~opStartGame() = default;

bool opStartGame::Execute() {
	Graph* graph = pControl->GetGraph();
	GUI* pUI = pControl->GetUI();
	graph->Hide(pUI);
	pUI->setScore(0);
	pUI->PrintMessage("Game Started!");
	vector<shape*>shapes = graph->GetShapeList();
	pUI->Clear();
	graph->Draw(pUI);
	int x;
	int y;
	int isComplete = false;
	int strikes = 0;
	int limit = 5;
	shape* selected = nullptr;
	Button exit{pUI, {50, pUI->getHeight() - 100}, "Exit"};
	while (!isComplete) {
		isComplete = true;
		bool leftDown = pUI->GetLeftClick(x, y);
		if (leftDown && exit.isSelected({x, y})) {
			isComplete = -1;
			break;
		}
		for (auto shape : shapes) {
			if (shape->isHidden()) {
				if (shape->isSelected({x, y})) {
					shape->SetSelected(true);
					if (leftDown) {
						shape->Show();
						if (selected) {
							if (selected->signiture() == shape->signiture()) {
								pUI->setScore(pUI->getScore() + 3);
							} else {
								pUI->setScore(pUI->getScore() - 1);
								shape->Hide();
								selected->Hide();
								pUI->Clear(selected->GetCenter() - 55, selected->GetCenter() + 55);
								if (++strikes == limit)
									break;
							}
							selected = nullptr;
						} else
							selected = shape;
						pUI->Clear(shape->GetCenter() - 55, shape->GetCenter() + 55);
					}
				} else
					shape->SetSelected(false);
				isComplete = false;
			} else
				shape->SetSelected(false);
		}
		Point p{50, 100};
		Point p2{50, 150};
		string score = format("Score: {}", pUI->getScore());
		string strikesCount = format("Strikes: {}\\{}", strikes, limit);
		pUI->Clear(p, p + Point(score.size() * 10 + 2, 20));
		pUI->Clear(p2, p2 + Point(strikesCount.size() * 10 + 2, 20));
		pUI->PrintMessage(score, p);
		pUI->PrintMessage(strikesCount, p2);
		graph->Draw(pUI);
		exit.Draw();
		if (strikes == limit) {
			isComplete = 0;
			break;
		}
		Sleep(16);
	}
	if (!isComplete)
		pUI->Prompt(format("Game Over!\n\nYour score is {}\n\nPress any key to exit", pUI->getScore()));
	else if (isComplete == 1)
		pUI->Prompt(format("Congratulations!\n\nYour score is {}\n\nPress any key to exit", pUI->getScore()));
	pUI->PrintMessage("Game Completed!");
	graph->Show(pUI);
	return false;
}