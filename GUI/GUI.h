#pragma once

#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../DEFS.h"

#include <vector>

class shape;
class Rect;
class Circle;
class Square;
class Triangle;
class Line;
class IrregPoly;
class Graph;
class RegPoly;
class controller;

struct Point
{
	int x;
	int y;
	double distance(const Point& p2) const {
		return sqrt(pow(p2.x - x, 2) + pow(p2.y - y, 2));
	}
	string toString(string name) const {
		return format("{}: ({: >4}, {: >4})", name, x, y);
	}
	Point& scale(double factor) {
		x = int(round(x * factor));
		y = int(round(y * factor));
		return *this;
	}
	Point& translate(const Point & point) {
		x = x + point.x;
		y = y + point.y;
		return *this;
	}
	Point& rotate(double angle) {
		int tempx = x;
		x = int(round(x * cos(angle) - y * sin(angle)));
		y = int(round(tempx * sin(angle) + y * cos(angle)));
		return *this;
	}
	Point operator-() const {
		return Point{ -x, -y };
	}
	Point operator+(const Point & p) const {
		return { x + p.x, y + p.y };
	}
	Point operator-(const Point& p) const {
		return { x - p.x, y - p.y };
	}
	Point operator/(const Point& p) const {
		return { int(round(double(x) / p.x)), int(round(double(y) / p.y)) };
	}
	Point operator*(const Point& p) const {
		return { int(round(double(x) * p.x)), int(round(double(y) * p.y)) };
	}
	Point operator+(int i) const {
		return { x + i, y + i };
	}
	Point operator-(int i) const {
		return { x - i, y - i };
	}
	Point operator/(double i) const {
		return Point(int(round(x / i)), int(round(y / i)));
	}
	Point operator*(double i) const {
		return Point(int(round(x * i)), int(round(y * i)));
	}
};

struct GfxInfo	//Graphical info common for all shapes (you may add more members)
{
	color DrawClr = BLACK;		//Draw color of the shape
	color FillClr = BLACK;		//Fill color of the shape
	bool isFilled = false;		//shape Filled or not
	int BorderWdth = 1;			//Width of shape borders
	bool isSelected = false;	//true if the shape is selected.
};


class GUI
{
public:
	const enum GUI_MODE	//Graphical user interface mode
	{
		MODE_DRAW,		//Drawing mode (startup mode)
		MODE_PLAY		//Playing mode
	};

	const enum DrawMenuIcon //The icons of the Draw menu (you should add more icons)
	{
		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here
		ICON_RECT,			//Recangle icon in menu
		ICON_CIRC,			//Circle icon in menu
		ICON_SQUARE,		// Square icon menu 
		ICON_LINE,			//Line icon in menu
		ICON_TRIANGLE,
		ICON_REG_POLY,
		ICON_IRREG_POLY,
		ICON_COLOR_PICKER,
		ICON_CHANGE_GENERAL_PEN,
		ICON_CHANGE_FILL,
		ICON_DELETE,
		ICON_SAVE,
		ICON_LOAD,
		ICON_PLAY_MODE,
		ICON_EXIT,			//Exit icon

		DRAW_ICON_COUNT,	//no. of menu icons ==> This should be the last line in this enum
		ICON_COLOR_PALETTE,
		TOTAL_DRAW_ICON_COUNT,
	};

	const enum DrawButton {
		FILL_SWITCH,
		DRAW_BUTTONS_COUNT,
	};

	const enum PlayMenuIcon //The icons of the Play menu (you should add more icons)
	{
		ICON_HIDE,
		ICON_UNHIDE,
		ICON_MATCH,
		ICON_START_GAME,
		ICON_DRAW_MODE,
		ICON_EXIT2,


		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here

		//TODO: Add more icons names here

		PLAY_ICON_COUNT,		//no. of menu icons ==> This should be the last line in this enum
		TOTAL_PLAY_ICON_COUNT,
	};

private:
	int width,
		height,
		wx,
		wy,
		StatusBarHeight,
		ToolBarHeight,
		MenuIconWidth;
	GUI_MODE InterfaceMode;
	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	bool Isfilled;          // is the shape filled
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	color selectedColor;	//Selected color
	int PenWidth;			//width of the pen that draws shapes
	string statusMessage;
	buttonstate perviousLeftButtonState;
	image* DrawMenuIconImages[TOTAL_DRAW_ICON_COUNT]{};
	image* PlayMenuIconImages[TOTAL_PLAY_ICON_COUNT]{};
	shape* DrawButtons[DRAW_BUTTONS_COUNT]{};
	window* pWind;
	image storedImage;
	controller* pCont;
public:
	GUI(controller*);

	// Input Functions  ---------------------------
	bool GetPointClicked(int& x, int& y);
	keytype GetKeyPress(char& c) const;
	bool GetLeftClick(int&, int&);
	//Get coordinate where user clicks

	void getMouseLocation(int& x, int& y);

	string GetString(string prompt);	 //Returns a string entered by the user

	operationType GetUseroperation(int, int); //Read the user click and map to an operation

	// Output Functions  ---------------------------
	window* CreateWind(int, int, int, int) const;

	void LoadDrawToolBar();
	void LoadPlayToolBar();
	//creates the application window
	void CreateDrawToolBar();	//creates Draw mode toolbar & menu
	void CreatePlayToolBar();	//creates Play mode toolbar & menu
	void CreateStatusBar(string statusMessage);	//create the status bar
	void CreateStatusBar();
	void PrintMessage(string);

	void PrintMessage(string message, Point pos) const;

	void Clear() const;	//Clears the display
	void ClearStatusMessage();

	// -- shapes Drawing functions
	void DrawRect(const Rect*, int iWidth = 0, int iHeight = 0) const;		//Draw a rectangle
	void DrawSquare(const Square*) const;     // Draw square
	void DrawLine(const Line*) const;		//Draw a Line
	void DrawTriangle(const Triangle* triangle) const;
	void DrawCircle(const Circle*) const;  //Draw a circle
	void DrawIrregPoly(const IrregPoly*) const;
	void DrawRegPoly(const RegPoly*) const;
	///Make similar functions for drawing all other shapes.

	void ClearDrawing() const;

	int getWidth() const;
	int getHeight() const;
	color getCrntDrawColor() const;		//get current drwawing color
	color getCrntFillColor() const;		//get current filling color
	bool getIsfilled() const;
	int getCrntPenWidth() const;		//get current pen width
	color getMsgColor() const;			//get current message color
	color getSelectedColor() const;
	string getStatusMessage() const;	//get current message color
	int getStatusBarHeight() const;
	color getClickedColor(int&, int&);
	bool MouseDrag(int& x, int& y);
	color getHoverColor(int&, int&);
	window* getWindow() const;
	image* getImage(DrawMenuIcon) const;
	bool isInDrawArea(Point);
	shape* getDrawButton(DrawButton);

	void setDrawColor(color);
	void setFillColor(color, bool);
	void setHighlightColor(color);
	void setMsgColor(color);
	void setBkGrndColor(color);
	void setStatusBarColor(color);
	void setSelectedColor(color);
	void setIsFilled(bool);
	void setPenWidth(int);

	void setInterfaceModeToPlay();
	void setInterfaceModeToDraw();
	int getInterfaceMode() const;

	void storeImage();
	void loadImage();

	static shape* ParseShape(string line);

	~GUI();
};
