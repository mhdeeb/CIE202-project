#pragma once
#include "Rect.h"
class Button: public Rect {
private:
	GUI* pUI;
	string text;
public:
	Button(GUI* pUI, Point position, const string& text);
	void Draw() const;
};
