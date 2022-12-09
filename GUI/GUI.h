#pragma once

#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../DEFS.h"

#include <vector>

class Rect;
class Circle;
class Square;
class Line;
class IrregPoly;

struct Point
{
	int x, y;
};

struct GfxInfo	//Graphical info common for all shapes (you may add more members)
{
	color DrawClr = BLACK;	//Draw color of the shape
	color FillClr = BLACK;	//Fill color of the shape
	bool isFilled = true;	//shape Filled or not
	int BorderWdth = 1;	//Width of shape borders
	bool isSelected = false;	//true if the shape is selected.
};


class GUI
{
	enum GUI_MODE	//Graphical user interface mode
	{
		MODE_DRAW,	//Drawing mode (startup mode)
		MODE_PLAY	//Playing mode
	};

	enum DrawMenuIcon //The icons of the Draw menu (you should add more icons)
	{
		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here
		ICON_RECT,		//Recangle icon in menu
		ICON_CIRC,		//Circle icon in menu
		ICON_SQUARE,    // Square icon menu 

		ICON_LINE,      //Line icon in menu
		ICON_TRIANGLE,
		ICON_REG_POLY,
		ICON_IRREG_POLY,
		ICON_COLOR_PALETTE,
		//TODO: Add more icons names here

		ICON_EXIT,		//Exit icon

		DRAW_ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum

	};

	enum PlayMenuIcon //The icons of the Play menu (you should add more icons)
	{
		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here

		//TODO: Add more icons names here

		PLAY_ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum

	};


	GUI_MODE InterfaceMode;

	int	width, height,	//Window width and height
		wx, wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuIconWidth;		//Width of each icon in toolbar menu


	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	color PaletteColor;		//Select Palette color
	int PenWidth;			//width of the pen that draws shapes
	string statusMessage;



	window* pWind;

public:

	GUI();

	// Input Functions  ---------------------------
	void GetPointClicked(int& x, int& y) const;//Get coordinate where user clicks
	string GetSrting();	 //Returns a string entered by the user
	operationType GetUseroperation() const; //Read the user click and map to an operation

	// Output Functions  ---------------------------
	window* CreateWind(int, int, int, int) const; //creates the application window
	void CreateDrawToolBar();	//creates Draw mode toolbar & menu
	void CreatePlayToolBar();	//creates Play mode toolbar & menu
	void CreateStatusBar(string, Rect) const;	//create the status bar
	void CreateStatusBar(string) const;
	void CreateStatusBar() const;

	void Clear() const;	//Clears the display
	void ClearStatusBar();

	// -- shapes Drawing functions
	void DrawRect(const Rect *) const;		//Draw a rectangle
	void DrawLine(const Line *) const;		//Draw a Line
	void DrawCircle(const Circle *) const;  //Draw a circle
	void DrawIrregPoly(const IrregPoly *) const;

	///Make similar functions for drawing all other shapes.

	void PrintMessage(string msg); //Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;	//get current pen width
	color getMsgColor() const;	//get current message color
	string getStatusMessage() const;	//get current message color
	window* getWindow() const;
	buttonstate GetLeftPointState(int&, int&);
	color getHoverColor(int& x, int& y);

	void setDrawColor(color);
	void setFillColor(color);
	void setHighlightColor(color);
	void setMsgColor(color);
	void setBkGrndColor(color);
	void setStatusBarColor(color);
	void setPaletteColor(color);
	void setPenWidth(int);


	~GUI();
};
