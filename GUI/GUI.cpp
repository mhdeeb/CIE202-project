#include "GUI.h"

#include "../Shapes/Rect.h"
#include "../Shapes/Circle.h"
#include "../Shapes/square.h"
#include "../Shapes/Line.h"
#include "../Shapes/IrregPoly.h"

GUI::GUI()
{
	//Initialize user interface parameters
	InterfaceMode = MODE_DRAW;
	DrawColor = BLACK;	//default Drawing color
	FillColor = GREEN;	//default Filling color
	MsgColor = BLACK;		//Messages color
	BkGrndColor = WHITE;	//Background color
	HighlightColor = MAGENTA;	//This color should NOT be used to draw shapes. use if for highlight only
	StatusBarColor = LIGHTSEAGREEN;
	PenWidth = 3;	//default width of the shapes frames
	perviousLeftButtonState = BUTTON_UP;
	LoadDrawToolBar();
	//Create the output window
	pWind = CreateWind(width, height, wx, wy);
	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - PAINT ^ ^ PLAY - - - - - - - - - -");
	CreateDrawToolBar();
	CreateStatusBar("Welcome to Paint Mode!");
}




//======================================================================================//
//								Input Functions										//
//======================================================================================//
void GUI::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

buttonstate GUI::GetLeftPointState(int& x, int& y) const
{
	return pWind->GetButtonState(LEFT_BUTTON, x, y);
}

bool GUI::GetLeftClick(int& x, int& y)
{

	buttonstate currentLeftButtonState = pWind->GetButtonState(LEFT_BUTTON, x, y), prev = perviousLeftButtonState;
	perviousLeftButtonState = currentLeftButtonState;
	return prev || !currentLeftButtonState;
}

Point GUI::getMouseLocation()
{
	int x, y;
	pWind->GetMouseCoord(x, y);
	return Point(x, y);
}

string GUI::GetSrting()
{
	string Label;
	char Key;
	keytype ktype;
	PrintMessage("Taking input...");
	pWind->FlushKeyQueue();
	while (true)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13) { //ENTER key is pressed
			PrintMessage("Input Saved!");
			return Label;
		}
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired operation
operationType GUI::GetUseroperation(int x, int y) const
{
	if (InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < ToolBarHeight)
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
			case ICON_EXIT: return EXIT;
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= ToolBarHeight && y < height - StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		/*TODO: perform checks similar to Draw mode checks above
		and return the correspoding operation*/
		return TO_PLAY;	//just for now. This should be updated
	}

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
void GUI::CreateStatusBar(string statusMessage, Rect textInput) const
{
	Point c1 = textInput.getC1(), c2 = textInput.getC2();
	GfxInfo gfxInfo = textInput.getGfxInfo();
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);
	pWind->SetPen(gfxInfo.DrawClr, gfxInfo.BorderWdth);
	pWind->SetBrush(gfxInfo.FillClr);
	pWind->DrawRectangle(c1.x, c1.y, c2.x, c2.y);
	pWind->SetPen(MsgColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, height - (int)(0.9 * StatusBarHeight), statusMessage);
}

void GUI::CreateStatusBar(string statusMessage) const
{
	CreateStatusBar(statusMessage, {});
}

void GUI::CreateStatusBar() const
{
	CreateStatusBar(statusMessage, {});
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar()
{
	//Clear Status bar message
	statusMessage = "";
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
	MenuIconImages[ICON_COLOR_PICKER] = new image("images/MenuIcons/Menu_Color_Picker.jpg");
	MenuIconImages[ICON_EXIT] = new image("images/MenuIcons/Menu_Exit.jpg");
	MenuIconImages[ICON_PLACE_HOLDER] = new image("images/MenuIcons/Placeholder.jpg");
	MenuIconImages[ICON_COLOR_PALETTE] = new image("images/util/Color_palette.jpg");
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
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);
	pWind->DrawRectangle(DRAW_ICON_COUNT * MenuIconWidth, 0, width, ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::PrintMessage(string msg) //Prints a message on status bar
{
	statusMessage = msg;
	if (color::isHexColor(msg))	//Preview written color
	{
		GfxInfo r;
		r.FillClr = WHITE;
		Rect rect = Rect({ 10, height - StatusBarHeight + 10 }, { 90, height - StatusBarHeight + 50 }, r);
		DrawRect(&rect);
		color msgColor = getMsgColor();
		setMsgColor(msg);
		CreateStatusBar(msg);
		setMsgColor(msgColor);
	}
	else
		CreateStatusBar(msg);
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

window* GUI::getWindow() const
{
	return pWind;
}

image* GUI::getImage(DrawMenuIcon icon) const
{
	return MenuIconImages[icon];
}

bool GUI::isInDrawArea(Point p) {
	return (p.y < ToolBarHeight&& p.x >(width - DRAW_ICON_COUNT * MenuIconWidth)) || p.y > ToolBarHeight;
}

void GUI::setDrawColor(color drawColor)
{
	DrawColor = drawColor;
}

void GUI::setFillColor(color fillColor)
{
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

void GUI::setPaletteColor(color paletteColor)
{
	PaletteColor = paletteColor;
}

void GUI::setPenWidth(int penWidth)
{
	PenWidth = penWidth;
}

void GUI::storeImage()
{
	pWind->StoreImage(storedImage, 0, 0, width, height - StatusBarHeight);
}

void GUI::loadImage()
{
	pWind->DrawImage(storedImage, 0, 0, width, height - StatusBarHeight);
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

	pWind->DrawCircle(origin.x, origin.y, circle->getRadius(), style);
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

	drawstyle style;
	if (gfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(gfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawLine(p1.x, p1.y, p2.x, p2.y, style);
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
	for (int i = 0; i < ICON_COUNT; ++i)
		delete MenuIconImages[i];
}
