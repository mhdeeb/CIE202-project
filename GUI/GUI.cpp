#include "GUI.h"

#include <sstream>

#include "../Shapes/Rect.h"
#include "../Shapes/Circle.h"
#include "../Shapes/square.h"
#include "../Shapes/Line.h"
#include "../Shapes/IrregPoly.h"
#include "../Shapes/RegPoly.h"
#include "../operations/opDelete.h"

GUI::GUI(controller* pCont) : pCont(pCont)
{
	//Initialize user interface parameters
	InterfaceMode = MODE_DRAW;
	DrawColor = BLACK;	//default Drawing color
	FillColor = GREEN;	//default Filling color
	Isfilled = false;
	MsgColor = BLACK;		//Messages color
	BkGrndColor = WHITE;	//Background color
	HighlightColor = MAGENTA;	//This color should NOT be used to draw shapes. use if for highlight only
	StatusBarColor = LIGHTSEAGREEN;
	PenWidth = 3;	//default width of the shapes frames
	perviousLeftButtonState = BUTTON_UP;
	width = 1300;
	height = 700;
	wx = 5;
	wy = 5;
	StatusBarHeight = 20;
	ToolBarHeight = 50;
	MenuIconWidth = 80;
	LoadDrawToolBar();
	//Create the output window
	pWind = CreateWind(width, height, wx, wy);
	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - PAINT ^ ^ PLAY - - - - - - - - - -");
	CreateDrawToolBar();
	PrintMessage("Welcome to Draw Mode!\nSelect an operation...");
}




//======================================================================================//
//								Input Functions										//
//======================================================================================//
bool GUI::GetPointClicked(int& x, int& y)
{
	char c;
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();
	while (GetLeftClick(x, y)) {
		if (GetKeyPress(c) == ESCAPE) {
			return false;
		}
		if (c == 'd')
			Delete(pCont).Execute();
		Sleep(16);
	}
	return true;
}

keytype GUI::GetKeyPress(char& c) const {
	return pWind->GetKeyPress(c);
}

bool GUI::GetLeftClick(int& x, int& y)
{
	buttonstate currentLeftButtonState = pWind->GetButtonState(LEFT_BUTTON, x, y), prev = perviousLeftButtonState;
	perviousLeftButtonState = currentLeftButtonState;
	return prev || !currentLeftButtonState;
}

void GUI::getMouseLocation(int& x, int& y)
{
	pWind->GetMouseCoord(x, y);
}

string GUI::GetSrting(string msg)
{
	string Label;
	char Key;
	keytype ktype;
	PrintMessage(msg);
	pWind->FlushKeyQueue();
	while (true)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)
			return "";
		if (Key == 13)
			return Label;
		if (Key == 8)
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		PrintMessage(Label, true);
	}
}

//This function reads the position where the user clicks to determine the desired operation
operationType GUI::GetUseroperation(int x, int y)
{
	if (InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		if (isInDrawArea({ x, y }))
			return DRAWING_AREA;
		else if (y >= 0 && y < ToolBarHeight)
		{
			//Check whick Menu icon was clicked
			//==> This assumes that menu icons are lined up horizontally <==
			int ClickedIconOrder = (x / MenuIconWidth);
			//Divide x coord of the point clicked by the menu icon width (int division)
			//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

			switch (ClickedIconOrder)
			{
			case ICON_RECT: return DRAW_RECT;
			case ICON_CIRC: return DRAW_CIRC;
			case ICON_SQUARE: return DRAW_SQUARE;
			case ICON_LINE: return DRAW_LINE;
			case ICON_TRIANGLE: return DRAW_TRIANGLE;
			case ICON_REG_POLY: return DRAW_REG_POLY;
			case ICON_IRREG_POLY: return DRAW_IRREG_POLY;
			case ICON_COLOR_PICKER: return DRAW_COLOR_PALETTE;
			case ICON_CHANGE_GENERAL_PEN: return CHNG_DRAW_CLR;
			case ICON_CHANGE_FILL: return CHNG_FILL_CLR;
			case ICON_PLAY_MODE: return TO_PLAY;
			case ICON_DELETE:return DEL;
			case ICON_EXIT: return EXIT;
			}
		}
		else if (DrawButtons[FILL_SWITCH]->isSelected({ x, y }))
			Isfilled = !Isfilled;
	}
	else	//GUI is in PLAY mode
	{
		/*TODO: perform checks similar to Draw mode checks above
		and return the correspoding operation*/
		return TO_PLAY;	//just for now. This should be updated
	}
	return EMPTY;
}
////////////////////////////////////////////////////



//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(BkGrndColor);
	pW->SetPen(BkGrndColor, 1);
	pW->DrawRectangle(0, 0, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::PrintMessage(string statusMessage, bool isTextInput)
{
	this->statusMessage = statusMessage;
	if (isTextInput && !statusMessage.size())
		statusMessage = "Enter Input: ";
	color msgColor = MsgColor;
	if (color::isHexColor(statusMessage))
		setMsgColor(statusMessage);
	stringstream ss(statusMessage);
	string line;
	bool adaptiveResize = statusMessage.size() > 3;
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - getStatusBarHeight(), width - 12, height, FILLED, 20, 20);
	if (isTextInput) {
		pWind->SetPen(BLACK, 2);
		pWind->SetBrush(WHITE);
		pWind->DrawRectangle(5, height - getStatusBarHeight(), (adaptiveResize) ? 11 * (statusMessage.size() + 1) : 49, height - 20, FILLED, 20, 20);
	}
	pWind->SetPen(msgColor, 50);
	int n = count(statusMessage.cbegin(), statusMessage.cend(), '\n') + 2, i = 0;
	while (getline(ss, line)) {
		pWind->SetFont(StatusBarHeight, PLAIN, BY_NAME, "Courier New");
		pWind->DrawString(10, height - StatusBarHeight * (n - i++), line);
	}
	Circle* c = (Circle*)DrawButtons[FILL_SWITCH];
	c->setDrawColor(DrawColor);
	c->setFillColor(FillColor, Isfilled);
	DrawCircle(c);
	setMsgColor(msgColor);
}

void GUI::PrintMessage(string statusMessage)
{
	PrintMessage(statusMessage, false);
}

void GUI::PrintMessage()
{
	PrintMessage(statusMessage, false);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusMessage()
{
	statusMessage = "";
	PrintMessage();
}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::LoadDrawToolBar() {
	MenuIconImages[ICON_RECT] = new image("images/MenuIcons/Menu_Rectangle.jpg");
	MenuIconImages[ICON_CIRC] = new image("images/MenuIcons/Menu_Circle.jpg");
	MenuIconImages[ICON_SQUARE] = new image("images/MenuIcons/Menu_Square.jpg");
	MenuIconImages[ICON_LINE] = new image("images/MenuIcons/Menu_Line.jpg");
	MenuIconImages[ICON_TRIANGLE] = new image("images/MenuIcons/Menu_Triangle.jpg");
	MenuIconImages[ICON_REG_POLY] = new image("images/MenuIcons/Menu_Regular_Polygon.jpg");
	MenuIconImages[ICON_IRREG_POLY] = new image("images/MenuIcons/Menu_Irregular_Polygon.jpg");
	MenuIconImages[ICON_COLOR_PICKER] = new image("images/MenuIcons/Menu_Color_Pick.jpg");
	MenuIconImages[ICON_CHANGE_GENERAL_PEN] = new image("images/MenuIcons/Menu_PenCol.jpg");
	MenuIconImages[ICON_CHANGE_FILL] = new image("images/MenuIcons/Menu_FillCol.jpg");
	MenuIconImages[ICON_PLAY_MODE] = new image("images/MenuIcons/Menu_Delete.jpg");
	MenuIconImages[ICON_DELETE] = new image("images/MenuIcons/Menu_Delete.jpg");
	MenuIconImages[ICON_EXIT] = new image("images/MenuIcons/Menu_Exit.jpg");
	MenuIconImages[ICON_PLACE_HOLDER] = new image("images/MenuIcons/Placeholder.jpg");
	MenuIconImages[ICON_COLOR_PALETTE] = new image("images/util/Color_palette.jpg");
	DrawButtons[FILL_SWITCH] = new Circle{ {width - 30, height - 30}, 10, {DrawColor, FillColor, Isfilled, PenWidth } };
}
void GUI::CreateDrawToolBar()
{
	InterfaceMode = MODE_DRAW;
	for (int i = 0; i < DRAW_ICON_COUNT; i++)
		pWind->DrawImage((MenuIconImages[i]) ? MenuIconImages[i] : MenuIconImages[ICON_PLACE_HOLDER], i * MenuIconWidth, 0, MenuIconWidth, ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar()
{
	InterfaceMode = MODE_PLAY;
	for (int i = 0; i < PLAY_ICON_COUNT; i++)
		pWind->DrawImage((MenuIconImages[i]) ? MenuIconImages[i] : MenuIconImages[ICON_PLACE_HOLDER], i * MenuIconWidth, 0, MenuIconWidth, ToolBarHeight);
	///TODO: write code to create Play mode menu
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::Clear() const
{
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, 0, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawing() const
{
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - getStatusBarHeight());
	pWind->DrawRectangle(DRAW_ICON_COUNT * MenuIconWidth, 0, width, ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drwawing color
{
	return DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{
	return FillColor;
}
bool GUI::getIsfilled() const {
	return Isfilled;
}
//////////////////////////////////////////////////////////////////////////////////////////

int GUI::getCrntPenWidth() const		//get current pen width
{
	return PenWidth;
}

color GUI::getMsgColor() const
{
	return MsgColor;
}

string GUI::getStatusMessage() const
{
	return statusMessage;
}

int GUI::getStatusBarHeight() const
{
	int n = count(statusMessage.cbegin(), statusMessage.cend(), '\n') + 2;
	return StatusBarHeight * n + 5;
}

color GUI::getClickedColor(int& x, int& y)
{
	pWind->WaitMouseClick(x, y);
	return pWind->GetColor(x, y);
}

color GUI::getHoverColor(int& x, int& y)
{
	pWind->GetMouseCoord(x, y);
	return pWind->GetColor(x, y);
}
color GUI::getSelectedColor() const {
	return selectedColor;
}

window* GUI::getWindow() const
{
	return pWind;
}

image* GUI::getImage(DrawMenuIcon icon) const
{
	return MenuIconImages[icon];
}

bool GUI::isInDrawArea(Point p) {
	return  height - getStatusBarHeight() > p.y && (p.y > ToolBarHeight || p.x > DRAW_ICON_COUNT * MenuIconWidth);
}

shape* GUI::getDrawButton(DrawButton button)
{
	return DrawButtons[button];
}

void GUI::setDrawColor(color drawColor)
{
	DrawColor = drawColor;
}

void GUI::setFillColor(color fillColor, bool isFilled = true)
{
	Isfilled = isFilled;
	FillColor = fillColor;
}

void GUI::setHighlightColor(color highlightColor)
{
	HighlightColor = highlightColor;
}

void GUI::setMsgColor(color msgColor)
{
	MsgColor = msgColor;
}

void GUI::setBkGrndColor(color bkGrndColor)
{
	BkGrndColor = bkGrndColor;
}

void GUI::setStatusBarColor(color statusBarColor)
{
	StatusBarColor = statusBarColor;
}

void GUI::setSelectedColor(color paletteColor)
{
	selectedColor = paletteColor;
}

void GUI::setIsFilled(bool b)
{
	Isfilled = b;
}

void GUI::setPenWidth(int penWidth)
{
	PenWidth = penWidth;
}

void GUI::storeImage()
{
	pWind->StoreImage(storedImage, 0, 0, width, height - getStatusBarHeight());
}

void GUI::loadImage()
{
	pWind->DrawImage(storedImage, 0, 0, width, height - getStatusBarHeight());
}

//======================================================================================//
//								shapes Drawing Functions								//
//======================================================================================//

void GUI::DrawRect(const Rect* rect) const
{
	color DrawingClr;
	GfxInfo gfxInfo = rect->getGfxInfo();
	Point c1 = rect->getC1(), c2 = rect->getC2();
	if (gfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = gfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, gfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (rect->getGfxInfo().isFilled)
	{
		style = FILLED;
		pWind->SetBrush(rect->getGfxInfo().FillClr);
	}
	else
		style = FRAME;
	pWind->DrawRectangle(c1.x, c1.y, c2.x, c2.y, style);
}

void GUI::DrawSquare(const Square* Square) const
{
	color DrawingClr;
	GfxInfo gfxInfo = Square->getGfxInfo();
	Point c1 = Square->getC1(), c2 = Square->getC2();
	if (gfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = gfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, gfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (Square->getGfxInfo().isFilled)
	{
		style = FILLED;
		pWind->SetBrush(Square->getGfxInfo().FillClr);
	}
	else
		style = FRAME;
	pWind->DrawRectangle(c1.x, c1.y, c2.x, c2.y, style);
}

void GUI::DrawCircle(const Circle* circle) const
{
	color DrawingClr;
	Point origin = circle->getOrigin();
	GfxInfo gfxInfo = circle->getGfxInfo();
	if (gfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = gfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, gfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (gfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(gfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawCircle(origin.x, origin.y, (int)circle->getRadius(), style);
}

void GUI::DrawIrregPoly(const IrregPoly* irrePoly) const
{
	color DrawingClr;
	GfxInfo gfxInfo = irrePoly->getGfxInfo();
	if (gfxInfo.isSelected)
		DrawingClr = HighlightColor;
	else
		DrawingClr = gfxInfo.DrawClr;
	pWind->SetPen(DrawingClr, gfxInfo.BorderWdth);
	drawstyle style;
	if (gfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(gfxInfo.FillClr);
	}
	else
		style = FRAME;
	pWind->DrawPolygon(irrePoly->getXpoints(), irrePoly->getYpoints(), irrePoly->getSize(), style);
}



void GUI::DrawRegPoly(const RegPoly* RegPoly) const
{
	DrawIrregPoly(RegPoly);
}
void GUI::DrawLine(const Line* line) const
{
	color DrawingClr;
	GfxInfo gfxInfo = line->getGfxInfo();
	Point p1 = line->getPoint1(), p2 = line->getPoint2();
	if (gfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = gfxInfo.DrawClr;
	pWind->SetPen(DrawingClr, gfxInfo.BorderWdth);	//Set Drawing color & width
	pWind->DrawLine(p1.x, p1.y, p2.x, p2.y, FRAME);
}

void GUI::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo) const
{
	color DrawingClr;
	if (TriGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = TriGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, TriGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (TriGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);

}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
	for (int i = 0; i < ICON_COUNT; ++i)
		delete MenuIconImages[i];
	for (int i = 0; i < DRAW_BUTTONS_COUNT; ++i)
		delete DrawButtons[i];
}
