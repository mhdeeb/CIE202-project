#include "GUI.h"

#include <sstream>
#include <filesystem>

#include "../Shapes/Rect.h"
#include "../Shapes/Circle.h"
#include "../Shapes/square.h"
#include "../Shapes/Line.h"
#include "../Shapes/Triangle.h"
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
	PrintMessage("Welcome to Draw Mode!\n\nSelect an operation.\n\nPress esc to cancel operations.");
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

string GUI::GetSrting(string message)
{
	string Label, displayed;
	char Key;
	keytype ktype;
	const int
		charWidth = 10,
		marginx = 4,
		marginy = 4,
		charHeight = charWidth * 2,
		messageHeight = charHeight,
		messageWidth = message.size() * charWidth,
		textInputHeight = charHeight + 2 * marginy,
		promptHeight = textInputHeight + messageWidth / 4,
		textInputWidth = messageWidth,
		promptWidth = messageWidth + 2 * marginx,
		textHeight = messageWidth - 2 * marginy,
		textWidth = messageWidth - 2 * marginx,
		centerY = height / 2,
		centerX = width / 2,
		promptY = centerY - promptHeight / 2,
		promptX = centerX - promptWidth / 2,
		messageY = promptY + marginy,
		messageX = promptX + marginx,
		textInputY = promptY + promptHeight - marginy - textInputHeight,
		textInputX = promptX + marginx,
		textY = textInputY + marginy,
		textX = textInputX + marginx;
	int cursorY = textY,
		cursorX = textX,
		cursor = 0,
		offset = 0;

	storeImage();

	while (true)
	{
		displayed = Label.substr(offset, message.size() - 1);

		pWind->SetPen(BLACK);
		pWind->SetBrush(GREY);
		pWind->DrawRectangle(promptX, promptY, promptX + promptWidth + 1, promptY + promptHeight + 1, FILLED, 10, 10);

		PrintMessage(message, { messageX, messageY });

		pWind->SetPen(BLACK);
		pWind->SetBrush(WHITE);
		pWind->DrawRectangle(textInputX, textInputY, textInputX + textInputWidth, textInputY + textInputHeight, FILLED, 10, 10);


		PrintMessage(displayed, { textX, textY });

		pWind->SetPen(BLACK);
		pWind->DrawLine(cursorX, cursorY, cursorX, cursorY + charHeight);

		pWind->FlushKeyQueue();

		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ARROW) {
			if (Key == 4) {
				cursor--;
				if (cursor == -1) {
					cursor++;
					offset--;
					if (offset == -1)
						offset++;
				}
			}
			else if (Key == 6) {
				cursor++;
				if (cursor == displayed.size() + 1) {
					cursor--;
					offset++;
					if (offset == Label.size() - message.size()) {
						offset--;
					}
				}
			}
		}
		else if (Key == 8)
			if (Label.size() > 0 && cursor) {
				Label.erase(Label.begin() + cursor + offset - 1);
				cursor--;
				if (cursor == -1) {
					cursor++;
					offset--;
					if (offset == -1)
						offset++;
				}
			}
			else
				Key = '\0';
		else if (ktype == ESCAPE) {
			loadImage();
			return "";
		}
		else if (Key == 13) {
			loadImage();
			return Label;
		}
		else {
			Label.insert(Label.begin() + cursor + offset, Key);
			cursor++;
			if (cursor == message.size()) {
				cursor--;
				offset++;
			}
		}
		cursorX = cursor * charWidth + textX;
		loadImage();
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
			case ICON_DELETE:return DEL;
			case ICON_SAVE:return SAVE;
			case ICON_LOAD:return LOAD;
			case ICON_PLAY_MODE: return TO_PLAY;
			case ICON_EXIT: return EXIT;
			}
		}
		else if (DrawButtons[FILL_SWITCH]->isSelected({ x, y }))
			Isfilled = !Isfilled;
	}


	else if (InterfaceMode == MODE_PLAY)	//GUI is in PLAY mode
	{
		if (y >= 0 && y < ToolBarHeight) {
			//Check whick Menu icon was clicked
			 //==> This assumes that menu icons are lined up horizontally <==
			int ClickedIconOrder = (x / MenuIconWidth);
			//Divide x coord of the point clicked by the menu icon width (int division)
			//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

			switch (ClickedIconOrder)
			{
			case ICON_HIDE: return HIDE;
			case ICON_UNHIDE: return UNHIDE;
			case ICON_MATCH: return MATCH;
			case ICON_START_GAME: return START_GAME;
			case ICON_DRAW_MODE: return TO_DRAW;
			case ICON_EXIT2: return EXIT;

			}
		}
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
void GUI::CreateStatusBar(string statusMessage)
{
	int prevn = (getStatusBarHeight() - 5) / StatusBarHeight;
	this->statusMessage = statusMessage;
	if (prevn * StatusBarHeight > getStatusBarHeight()) {
		pWind->SetPen(BkGrndColor, 1);
		pWind->SetBrush(BkGrndColor);
		pWind->DrawRectangle(0, height - prevn * StatusBarHeight - 5, width - 12, height, FILLED, 15, 15);
	}

	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - getStatusBarHeight(), width - 12, height, FILLED, 15, 15);

	color msgColor = MsgColor;
	if (color::isHexColor(statusMessage))
		setMsgColor(statusMessage);

	int n = count(statusMessage.cbegin(), statusMessage.cend(), '\n') + 2, i = 0;
	stringstream ss(statusMessage);
	string line;
	while (getline(ss, line))
		PrintMessage(line, { 10, height - StatusBarHeight * (n - i++) });

	setMsgColor(msgColor);

	Circle* c = (Circle*)DrawButtons[FILL_SWITCH];
	c->setDrawColor(DrawColor);
	c->setFillColor(FillColor, Isfilled);
	DrawCircle(c);
}

void GUI::CreateStatusBar() {
	CreateStatusBar(statusMessage);
}

void GUI::PrintMessage(string statusMessage)
{
	CreateStatusBar(statusMessage);
}

void GUI::PrintMessage(string message, Point pos) const
{
	pWind->SetPen(MsgColor, 50);
	pWind->SetFont(StatusBarHeight, PLAIN, BY_NAME, "Courier New");
	pWind->DrawString(pos.x, pos.y, message);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusMessage()
{
	PrintMessage("");
}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::LoadDrawToolBar() {
	DrawMenuIconImages[ICON_RECT] = new image("images/MenuIcons/Menu_Rect.jpg");
	DrawMenuIconImages[ICON_CIRC] = new image("images/MenuIcons/Menu_Circle.jpg");
	DrawMenuIconImages[ICON_SQUARE] = new image("images/MenuIcons/Menu_Square.jpg");
	DrawMenuIconImages[ICON_LINE] = new image("images/MenuIcons/Menu_Line.jpg");
	DrawMenuIconImages[ICON_TRIANGLE] = new image("images/MenuIcons/Menu_Triangle.jpg");
	DrawMenuIconImages[ICON_REG_POLY] = new image("images/MenuIcons/Menu_Regular_Polygon.jpg");
	DrawMenuIconImages[ICON_IRREG_POLY] = new image("images/MenuIcons/Menu_Irregular_Polygon.jpg");
	DrawMenuIconImages[ICON_COLOR_PICKER] = new image("images/MenuIcons/Menu_Color_Pick.jpg");
	DrawMenuIconImages[ICON_CHANGE_GENERAL_PEN] = new image("images/MenuIcons/Menu_PenCol.jpg");
	DrawMenuIconImages[ICON_CHANGE_FILL] = new image("images/MenuIcons/Menu_FillCol.jpg");
	DrawMenuIconImages[ICON_DELETE] = new image("images/MenuIcons/Menu_Delete.jpg");
	DrawMenuIconImages[ICON_SAVE] = new image("images/MenuIcons/Menu_Save.jpg");
	DrawMenuIconImages[ICON_LOAD] = new image("images/MenuIcons/Menu_Load.jpg");
	DrawMenuIconImages[ICON_PLAY_MODE] = new image("images/MenuIcons/Menu_Play.jpg");
	DrawMenuIconImages[ICON_EXIT] = new image("images/MenuIcons/Menu_Exit.jpg");
	DrawMenuIconImages[ICON_COLOR_PALETTE] = new image("images/util/Color_palette.jpg");
	DrawButtons[FILL_SWITCH] = new Circle{ {width - 30, height - 30}, 10, {DrawColor, FillColor, Isfilled, PenWidth } };
}
void GUI::CreateDrawToolBar()
{
	for (int i = 0; i < DRAW_ICON_COUNT; i++)
		pWind->DrawImage(DrawMenuIconImages[i], i * MenuIconWidth, 0, MenuIconWidth, ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::LoadPlayToolBar() {
	PlayMenuIconImages[ICON_HIDE] = new image("images/PlayMode/Menu_Hide.jpg");
	PlayMenuIconImages[ICON_UNHIDE] = new image("images/PlayMode/Menu_Unhide.jpg");
	PlayMenuIconImages[ICON_MATCH] = new image("images/PlayMode/Menu_Match.jpg");
	PlayMenuIconImages[ICON_START_GAME] = new image("images/PlayMode/Menu_Play.jpg");
	PlayMenuIconImages[ICON_DRAW_MODE] = new image("images/PlayMode/Menu_Draw_Mode.jpg");
	PlayMenuIconImages[ICON_EXIT2] = new image("images/MenuIcons/Menu_Exit.jpg");
	DrawButtons[FILL_SWITCH] = new Circle{ {width - 30, height - StatusBarHeight + 18}, 10, {DrawColor, FillColor, Isfilled, PenWidth } };
}
void GUI::CreatePlayToolBar()
{
	for (int i = 0; i < PLAY_ICON_COUNT; i++)
		pWind->DrawImage(PlayMenuIconImages[i], i * MenuIconWidth, 0, MenuIconWidth, ToolBarHeight);
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
int GUI::getWidth() const
{
	return width;
}
int GUI::getHeight() const
{
	return height;
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
	return DrawMenuIconImages[icon];
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

void GUI::setInterfaceModeToPlay() {
	InterfaceMode = MODE_PLAY;
}
void GUI::setInterfaceModeToDraw() {
	InterfaceMode = MODE_DRAW;
}

int GUI::getInterfaceMode() const {
	return InterfaceMode;
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

void GUI::DrawTriangle(const Triangle* triangle) const
{
	color DrawingClr;
	GfxInfo gfxInfo = triangle->getGfxInfo();
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

	pWind->DrawTriangle(triangle->getPoint(0).x, triangle->getPoint(0).y, triangle->getPoint(1).x, triangle->getPoint(1).y, triangle->getPoint(2).x, triangle->getPoint(2).y, style);

}
//////////////////////////////////////////////////////////////////////////////////////////

shape* GUI::ParseShape(string line) {
	stringstream ss(line);
	string type, rest;
	ss >> type;
	getline(ss, rest);
	getline(ss, rest);
	shapeType t;
	shape* sh;
	for (int i = 0; i < shapesCount; ++i)
		if (ShapesArray[i] == type)
			t = (shapeType)i;
	switch (t) {
	case RECTANGLE:
		sh = Rect::Load(rest);
		break;
	case CIRCLE:
		sh = Circle::Load(rest);
		break;
	case SQUARE:
		sh = Square::Load(rest);;
		break;
	case LINE:
		sh = Line::Load(rest);
		break;
	case TRIANGLE:
		sh = Triangle::Load(rest);
		break;
	case REGULAR_POLYGON:
		sh = RegPoly::Load(rest);
		break;
	case IRREGULAR_POLYGON:
		sh = IrregPoly::Load(rest);
		break;
	}
	return sh;
}

GUI::~GUI()
{
	delete pWind;
	for (int i = 0; i < TOTAL_DRAW_ICON_COUNT; ++i)
		delete DrawMenuIconImages[i];
	for (int i = 0; i < DRAW_BUTTONS_COUNT; ++i)
		delete DrawButtons[i];
	for (int i = 0; i < TOTAL_PLAY_ICON_COUNT; ++i)
		delete PlayMenuIconImages[i];
}
