#include "opStartGame.h"
#include "../Shapes/Button.h"

opStartGame::opStartGame(controller* pCont): operation(pCont) {}

opStartGame::~opStartGame() = default;

bool opStartGame::Execute() {
	using namespace chrono;
	Graph const* graph = pControl->GetGraph();
	GUI* pUI = pControl->GetUI();
	graph->Hide(pUI);
	pUI->PrintMessage("Game Started!");
	vector<shape*>shapes = graph->GetShapeList();
	pUI->Clear();
	graph->Draw(pUI);
	int x;
	int y;
	int score = 0;
	int isComplete = false;
	int strikes = 0;
	int limit = 5;
	shape* selected = nullptr;
	Button exit{pUI, {50, pUI->getHeight() - 100}, "Exit"};
	while (!isComplete) {
		isComplete = true;
		bool leftDown = pUI->GetLeftClick(x, y);
		if (exit.isSelected({x, y})) {
			exit.SetSelected(true);
			if (leftDown) {
				isComplete = -1;
				break;
			}
		} else
			exit.SetSelected(false);
		for (auto shape : shapes) {
			if (shape->isHidden()) {
				if (shape->isSelected({x, y})) {
					shape->SetSelected(true);
					if (leftDown) {
						shape->Show();
						if (selected) {
							if (selected->signiture() == shape->signiture()) {
								score += 3;
							} else {
								shape->SetSelected(false);
								pUI->Clear(shape->GetCenter() - 55, shape->GetCenter() + 55);
								graph->Draw(pUI);
								time_t t = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() + 750;
								while (t - duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() > 0);
								score -= 1;
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
		Point p3{50, 200};
		string scoreMessage = format("Score: {}", score);
		string strikesCount = format("Strikes: {}\\{}", strikes, limit);
		string highScore = format("High Score: {}", pUI->getHighScore());
		pUI->Clear(p, p + Point((scoreMessage.size() + 1) * 10, 20));
		pUI->Clear(p2, p2 + Point((strikesCount.size() + 1) * 10, 20));
		pUI->Clear(p3, p3 + Point((highScore.size() + 1) * 10, 20));
		pUI->PrintMessage(scoreMessage, p);
		pUI->PrintMessage(strikesCount, p2);
		pUI->PrintMessage(highScore, p3);
		graph->Draw(pUI);
		exit.Draw();
		if (strikes == limit) {
			isComplete = 0;
			break;
		}
		Sleep(16);
	}
	for (auto shape : shapes)
		shape->SetSelected(false);
	if (isComplete == 0)
		pUI->Prompt(format("Game Over!\n\nYour score is {}\n\nPress any key to exit", score));
	else if (isComplete == 1)
		pUI->Prompt(format("Congratulations!\n\nYour score is {}\n\nPress any key to exit", score));
	graph->Show(pUI);
	if (score > pUI->getHighScore()) {
		pUI->setHighScore(score);
		pUI->Prompt(format("Congratulations!\n\nPersonal Best: {}\n\nPress any key to exit", score));
	}
	if (isComplete == 0)
		pUI->PrintMessage(format("Game Failed!\n\nYour score was {}", score));
	else if (isComplete == 1)
		pUI->PrintMessage(format("Game Completed!\n\nYour score was {}", score));
	else if (isComplete == -1)
		pUI->PrintMessage(format("Game Exited!\n\nYour score was {}", score));
	return false;
}