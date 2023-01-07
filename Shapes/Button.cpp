#include "Button.h"

Button::Button(GUI* pUI, Point position, const string& text): Rect(position, position + Point((text.size() + 1) * 10, 24), {BLACK, WHITE, true, 3}, 5, 5), pUI(pUI), text(text) {}

void Button::Draw() const {
	Rect::Draw(pUI);
	pUI->PrintMessage(text, p1 + Point(5, 0));
}