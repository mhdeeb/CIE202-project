#pragma once

#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../DEFS.h"

#include <vector>

class shape;
class Rect;
class Circle;
class Square;
class Line;
class IrregPoly;
class Graph;
class RegPoly;
class controller;

inline const int width = 1300, height = 700,
wx = 5, wy = 5,
StatusBarHeight = 50, ToolBarHeight = 50,
MenuIconWidth = 80;

struct Point
{
	int x, y;
	int& getX() {
		return x;
	}
	int& getY() {
		return y;
	}
	double distance(const Point& p2) {
		return sqrt(pow(p2.x - x, 2) + pow(p2.y - y, 2));
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
		ICON_EXIT,			//Exit icon

		DRAW_ICON_COUNT,	//no. of menu icons ==> This should be the last line in this enum
		ICON_PLACE_HOLDER,
		ICON_COLOR_PALETTE,
		ICON_COUNT,
	};

	const enum DrawButton {
		FILL_SWITCH,
		DRAW_BUTTONS_COUNT,
	};

	const enum PlayMenuIcon //The icons of the Play menu (you should add more icons)
	{
		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here

		//TODO: Add more icons names here

		PLAY_ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum

	};

private:
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
	image* MenuIconImages[ICON_COUNT]{};
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

	void getMouseLocation(int &x, int &y);

	string GetSrting(string msg="Taking Input...");	 //Returns a string entered by the user
	operationType GetUseroperation(int, int); //Read the user click and map to an operation

	// Output Functions  ---------------------------
	window* CreateWind(int, int, int, int) const;
	void LoadDrawToolBar();
	//creates the application window
	void CreateDrawToolBar();	//creates Draw mode toolbar & menu
	void CreatePlayToolBar();	//creates Play mode toolbar & menu
	void CreateStatusBar(string, Rect) const;	//create the status bar
	void CreateStatusBar(string) const;
	void CreateStatusBar() const;

	void Clear() const;	//Clears the display
	void ClearStatusBar();

	// -- shapes Drawing functions
	void DrawRect(const Rect*) const;		//Draw a rectangle
	void DrawSquare(const Square*) const;     // Draw square
	void DrawLine(const Line*) const;		//Draw a Line
	void DrawCircle(const Circle*) const;  //Draw a circle
	void DrawIrregPoly(const IrregPoly*) const;
	void DrawRegPoly(const RegPoly*) const;
	void DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo) const;
	///Make similar functions for drawing all other shapes.

	void ClearDrawing() const;

	void PrintMessage(string msg); //Print a message on Status bar

	color getCrntDrawColor() const;		//get current drwawing color
	color getCrntFillColor() const;		//get current filling color
	bool getIsfilled() const;
	int getCrntPenWidth() const;		//get current pen width
	color getMsgColor() const;			//get current message color
	color getSelectedColor() const;
	string getStatusMessage() const;	//get current message color
	color getClickedColor(int&, int&);
	color getHoverColor(int&, int &);
	window* getWindow() const;
	image* getImage(DrawMenuIcon) const;
	static bool isInDrawArea(Point);
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
	void storeImage();
	void loadImage();

	~GUI();
};
