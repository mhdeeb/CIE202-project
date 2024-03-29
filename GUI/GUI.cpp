#include "GUI.h"

#include <sstream>
#include <fstream>

#include "../Shapes/Rect.h"
#include "../Shapes/Circle.h"
#include "../Shapes/square.h"
#include "../Shapes/Line.h"
#include "../Shapes/Triangle.h"
#include "../Shapes/IrregPoly.h"
#include "../Shapes/RegPoly.h"
#include "../Shapes/imageShape.h"
#include "../operations/opDelete.h"
#include "../operations/opRotate.h"
#include "../operations/opResize.h"
#include "../operations/opMove.h"
#include "../operations/opCopy.h"
#include "../operations/opPaste.h"
#include "../operations/opZoomIn.h"
#include "../operations/opZoomOut.h"
#include "../operations/opDuplicateGraph.h"
#include "../operations/opScramble.h"
#include "../operations/opToggleGroup.h"
#include "../operations/opPrompt.h"

GUI::GUI(controller* pCont): pCont(pCont) {
	//Initialize user interface parameters
	InterfaceMode = MODE_DRAW;
	DrawColor = BLACK;	//default Drawing color
	FillColor = GREEN;	//default Filling color
	Isfilled = false;
	MsgColor = BLACK;		//Messages color
	BkGrndColor = GREY;	//Background color
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
	LoadPlayToolBar();
	//Create the output window
	pWind = CreateWind(width, height, wx, wy);
	//Change the title
	pWind->ChangeTitle("PAINT");
	CreateDrawToolBar();
	PrintMessage("Welcome to Draw Mode!\n\nPress H for help");
}

//======================================================================================//
//								Input Functions										//
//======================================================================================//
bool GUI::GetPointClicked(int& x, int& y) {
	char c;
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();
	while (!GetLeftClick(x, y)) {
		if (keytype k = GetKeyPress(c)) {
			if (k == ESCAPE)
				return false;
			switch (c) {
			case 'd':
				Delete(pCont).Execute();
				break;
			case 'r':
				opRotate(pCont).Execute();
				break;
			case 's':
				opResize(pCont).Execute();
				break;
			case 'm':
				opMove(pCont).Execute();
				break;
			case 'c':
				opCopy(pCont).Execute();
				break;
			case 'p':
				opPaste(pCont).Execute();
				break;
			case '+':
				opZoomIn(pCont).Execute();
				break;
			case '-':
				opZoomOut(pCont).Execute();
				break;
			case 't':
				opToggleGroup(pCont).Execute();
				break;
			case 'b':
				pCont->GetGraph()->undo(this);
				break;
			case 'n':
				pCont->GetGraph()->redo(this);
				break;
			case 'h':
				ClearStatusMessage();
				displayHelp();
				break;
			default:
				break;
			}
		}
		Sleep(16);
		if (pWind->GetButtonState(RIGHT_BUTTON, x, y) == BUTTON_DOWN)
			return false;
	}
	return true;
}

bool GUI::GetPointClickedNoOp(int& x, int& y) {
	char c;
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();
	while (!GetLeftClick(x, y)) {
		if (ESCAPE == GetKeyPress(c) || pWind->GetButtonState(RIGHT_BUTTON, x, y) == BUTTON_DOWN)
			return false;
		Sleep(16);
	}
	return true;
}

keytype GUI::GetKeyPress(char& c) const {
	return pWind->GetKeyPress(c);
}

bool GUI::GetLeftClick(int& x, int& y) {
	buttonstate currentLeftButtonState = pWind->GetButtonState(LEFT_BUTTON, x, y);
	buttonstate prev = perviousLeftButtonState;
	perviousLeftButtonState = currentLeftButtonState;
	return !prev && currentLeftButtonState;
}

bool GUI::isMouseLeftDown(int& x, int& y) {
	return pWind->GetButtonState(LEFT_BUTTON, x, y);
}

void GUI::getMouseLocation(int& x, int& y) {
	pWind->GetMouseCoord(x, y);
}

Point GUI::getMousePosition() {
	int x;
	int y;
	pWind->GetMouseCoord(x, y);
	return {x, y};
}

string GUI::GetString(const string& message) {
	string Label;
	string displayed;
	char Key;
	keytype ktype;

	int maxChar = 0;
	int nline = 0;
	stringstream ss(message);
	string line;
	while (getline(ss, line)) {
		nline++;
		maxChar = max(maxChar, (int)line.size());
	}

	const int charWidth = 10;
	const int marginx = 4;
	const int marginy = 4;
	const int charHeight = charWidth * 2;
	const int messageHeight = charHeight * nline;
	const int messageWidth = maxChar * charWidth;
	const int textInputHeight = charHeight + 2 * marginy;
	const int promptHeight = textInputHeight + messageHeight + messageWidth / 4;
	const int textInputWidth = messageWidth;
	const int promptWidth = messageWidth + 2 * marginx;
	const int textHeight = messageWidth - 2 * marginy;
	const int textWidth = messageWidth - 2 * marginx;
	const int centerY = height / 2;
	const int centerX = width / 2;
	const int promptY = centerY - promptHeight / 2;
	const int promptX = centerX - promptWidth / 2;
	const int messageY = promptY + marginy;
	const int messageX = promptX + marginx;
	const int textInputY = promptY + promptHeight - marginy - textInputHeight;
	const int textInputX = promptX + marginx;
	const int textY = textInputY + marginy;
	const int textX = textInputX + marginx;

	int caretY = textY;
	int caretX = textX;
	int caret = 0;
	int offset = 0;

	storeImage();

	while (true) {
		displayed = Label.substr(offset, maxChar - 1);

		pWind->SetPen(BLACK);
		pWind->SetBrush(GREY);
		pWind->DrawRectangle(promptX, promptY, promptX + promptWidth + 1, promptY + promptHeight + 1, FILLED, 10, 10);

		PrintMessage(message, {messageX, messageY});

		pWind->SetPen(BLACK);
		pWind->SetBrush(WHITE);
		pWind->DrawRectangle(textInputX, textInputY, textInputX + textInputWidth, textInputY + textInputHeight, FILLED, 10, 10);

		PrintMessage(displayed, {textX, textY});

		pWind->SetPen(BLACK);
		pWind->DrawLine(caretX, caretY, caretX, caretY + charHeight);

		pWind->FlushKeyQueue();

		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ARROW) {
			if (Key == 4) {
				caret--;
				if (caret == -1) {
					caret++;
					offset--;
					if (offset == -1)
						offset++;
				}
			} else if (Key == 6) {
				caret++;
				if (caret == displayed.size() + 1) {
					caret--;
					if (caret + 1 == maxChar) {
						offset++;
						if (offset + caret == Label.size() + 1) {
							offset--;
						}
					}
				}
			}
		} else if (Key == 8)
			if (Label.size() > 0) {
				Label.erase(Label.begin() + caret + offset - 1);
				caret--;
				if (caret == -1) {
					caret++;
					offset--;
					if (offset == -1)
						offset++;
				}
			} else
				Key = '\0';
		else if (ktype == ESCAPE) {
			loadImage();
			return "";
		} else if (Key == 13) {
			loadImage();
			return Label;
		} else {
			Label.insert(Label.begin() + caret + offset, Key);
			caret++;
			if (caret == maxChar) {
				caret--;
				offset++;
			}
		}
		caretX = caret * charWidth + textX;
		loadImage();
	}
}

bool GUI::Prompt(const string& message) {
	int maxChar = 0;
	int nline = 0;
	stringstream ss(message);
	string line;
	while (getline(ss, line)) {
		nline++;
		maxChar = max(maxChar, (int)line.size());
	}

	const int charWidth = 10;
	const int marginy = 20;
	const int marginx = 20;
	const int charHeight = charWidth * 2;
	const int messageHeight = charHeight * nline;
	const int messageWidth = maxChar * charWidth;
	const int promptHeight = messageHeight + 2 * marginy;
	const int promptWidth = messageWidth + 2 * marginx;
	const int centerY = height / 2;
	const int centerX = width / 2;
	const int promptY = centerY - promptHeight / 2;
	const int promptX = centerX - promptWidth / 2;
	const int messageY = promptY + marginy;
	const int messageX = promptX + marginx;

	storeImage();

	pWind->SetPen(BLACK, 2);
	pWind->SetBrush(GREY);
	pWind->DrawRectangle(promptX, promptY, promptX + promptWidth, promptY + promptHeight, FILLED, 10, 10);

	PrintMessage(message, {messageX, messageY});

	char Key;
	pWind->FlushKeyQueue();
	keytype t = pWind->WaitKeyPress(Key);
	loadImage();
	if (t == ESCAPE)
		return false;
	return true;
}

//This function reads the position where the user clicks to determine the desired operation
operationType GUI::GetUseroperation(int x, int y) {
	if (InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		if (isInDrawArea({x, y})) {
			return WINDOW_AREA;
		} else if (y >= 0 && y < ToolBarHeight) {
			//Check whick Menu icon was clicked
			//==> This assumes that menu icons are lined up horizontally <==
			int ClickedIconOrder = (x / MenuIconWidth);
			//Divide x coord of the point clicked by the menu icon width (int division)
			//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

			switch (ClickedIconOrder) {
			case ICON_RECT: return DRAW_RECT;
			case ICON_CIRC: return DRAW_CIRC;
			case ICON_SQUARE: return DRAW_SQUARE;
			case ICON_LINE: return DRAW_LINE;
			case ICON_TRIANGLE: return DRAW_TRIANGLE;
			case ICON_REG_POLY: return DRAW_REG_POLY;
			case ICON_IRREG_POLY: return DRAW_IRREG_POLY;
			case ICON_COLOR_PICKER: return DRAW_COLOR_PALETTE;
			case ICON_CHANGE_GENERAL_PEN: return CHNG_DRAW_CLR;
			case ICON_IMAGE: return DRAW_IMAGE;
			case ICON_CHANGE_FILL: return CHNG_FILL_CLR;
			case ICON_DELETE:return DEL;
			case ICON_SAVE:return SAVE;
			case ICON_LOAD:return LOAD;
			case ICON_PLAY_MODE: return TO_PLAY;
			case ICON_EXIT: return EXIT;
			}
		} else if (DrawButtons[FILL_SWITCH]->isSelected({x, y})) {
			Isfilled = !Isfilled;
			vector<shape*> selectedShapes = pCont->GetGraph()->getSelectedShapes();
			for (shape* selectedShape : selectedShapes)
				if (selectedShape)
					selectedShape->setFillColor(selectedShape->getGfxInfo().FillClr, Isfilled);
		} else if (DrawButtons[GROUP_CYCLE]->isSelected({x, y})) {
			gid = ++gid % gcount;
			DrawButtons[GROUP_CYCLE]->setFillColor(ColorsArray[gid], true);
			for (shape* pShape : pCont->GetGraph()->GetShapeList())
				if (pShape->getId() == gid)
					pShape->SetSelected(true);
		}
	}

	else if (InterfaceMode == MODE_PLAY)	//GUI is in PLAY mode
	{
		if (isInDrawArea({x, y})) {
			return WINDOW_AREA;
		} if (y >= 0 && y < ToolBarHeight) {
			//Check whick Menu icon was clicked
			 //==> This assumes that menu icons are lined up horizontally <==
			int ClickedIconOrder = (x / MenuIconWidth);
			//Divide x coord of the point clicked by the menu icon width (int division)
			//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

			switch (ClickedIconOrder) {
			case ICON_START_GAME: return START_GAME;
			case ICON_RESTART_GAME: return RESTART;
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

window* GUI::CreateWind(int w, int h, int x, int y) const {
	window* pW = new window(w, h, x, y);
	pW->SetBrush(BkGrndColor);
	pW->SetPen(BkGrndColor, 1);
	pW->DrawRectangle(0, 0, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar(string statusMessage) {
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

	PrintMessage(statusMessage, {10, height - getStatusBarHeight()});

	setMsgColor(msgColor);
	if (getInterfaceMode() == MODE_DRAW) {
		Circle* c = (Circle*)DrawButtons[FILL_SWITCH];
		c->setDrawColor(DrawColor);
		c->setFillColor(FillColor, Isfilled);
		DrawCircle(c);
		if (pCont->GetGraph()->getGroupPreview()) {
			c = (Circle*)DrawButtons[GROUP_CYCLE];
			DrawCircle(c);
			pWind->SetPen(unsigned char(gid + 1));
			pWind->DrawString(int(c->getOrigin().x - c->getRadius() / 2), int(c->getOrigin().y - c->getRadius() + 1), to_string(gid));
		}
	}
}

void GUI::CreateStatusBar() {
	CreateStatusBar(statusMessage);
}

void GUI::PrintMessage(string statusMessage) {
	CreateStatusBar(statusMessage);
}

void GUI::PrintMessage(string message, Point pos) const {
	pWind->SetPen(MsgColor, 50);
	pWind->SetFont(StatusBarHeight, PLAIN, BY_NAME, "Courier New");
	stringstream ss(message);
	string line;
	int i = 0;
	while (getline(ss, line)) {
		pWind->DrawString(pos.x, pos.y + i++ * StatusBarHeight + 2, line);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusMessage() {
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
	DrawMenuIconImages[ICON_COLOR_PICKER] = new image("images/MenuIcons/Menu_Color_Picker.jpg");
	DrawMenuIconImages[ICON_CHANGE_GENERAL_PEN] = new image("images/MenuIcons/Menu_PenCol.jpg");
	DrawMenuIconImages[ICON_CHANGE_FILL] = new image("images/MenuIcons/Menu_FillCol.jpg");
	DrawMenuIconImages[ICON_DELETE] = new image("images/MenuIcons/Menu_Delete.jpg");
	DrawMenuIconImages[ICON_SAVE] = new image("images/MenuIcons/Menu_Save.jpg");
	DrawMenuIconImages[ICON_LOAD] = new image("images/MenuIcons/Menu_Load.jpg");
	DrawMenuIconImages[ICON_PLAY_MODE] = new image("images/MenuIcons/Menu_Play.jpg");
	DrawMenuIconImages[ICON_EXIT] = new image("images/MenuIcons/Menu_Exit.jpg");
	DrawMenuIconImages[ICON_IMAGE] = new image("images/MenuIcons/Menu_Image.jpg");
	DrawMenuIconImages[ICON_COLOR_PALETTE] = new image("images/util/Color_palette.jpg");
	DrawButtons[FILL_SWITCH] = new Circle{{width - 30, height - 30}, 10, {DrawColor, FillColor, Isfilled, 2 }};
	DrawButtons[GROUP_CYCLE] = new Circle{{width - 55, height - 30}, 10, {BLACK, ColorsArray[gid], true, 2 }};
}
void GUI::CreateDrawToolBar() {
	for (int i = 0; i < DRAW_ICON_COUNT; i++)
		pWind->DrawImage(DrawMenuIconImages[i], i * MenuIconWidth, 0, MenuIconWidth, ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::LoadPlayToolBar() {
	PlayMenuIconImages[ICON_START_GAME] = new image("images/PlayMode/Menu_Play.jpg");
	PlayMenuIconImages[ICON_DRAW_MODE] = new image("images/PlayMode/Menu_Draw_Mode.jpg");
	PlayMenuIconImages[ICON_EXIT2] = new image("images/MenuIcons/Menu_Exit.jpg");
	PlayMenuIconImages[ICON_RESTART_GAME] = new image("images/PlayMode/Menu_Restart.jpg");
}
void GUI::CreatePlayToolBar() {
	for (int i = 0; i < PLAY_ICON_COUNT; i++)
		pWind->DrawImage(PlayMenuIconImages[i], i * MenuIconWidth, 0, MenuIconWidth, ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::Clear() const {
	Clear({0, 0}, {width, height});
}

void GUI::Clear(Point p1, Point p2) const {
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(p1.x, p1.y, p2.x, p2.y);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawing() const {
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - getStatusBarHeight());
	pWind->DrawRectangle(DRAW_ICON_COUNT * MenuIconWidth, 0, width, ToolBarHeight);
}
int GUI::getWidth() const {
	return width;
}
int GUI::getHeight() const {
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

color GUI::getMsgColor() const {
	return MsgColor;
}

string GUI::getStatusMessage() const {
	return statusMessage;
}

int GUI::getStatusBarHeight() const {
	int n = std::ranges::count(statusMessage.cbegin(), statusMessage.cend(), '\n') + 2;
	return StatusBarHeight * n + 5;
}

color GUI::getClickedColor(int& x, int& y) {
	pWind->WaitMouseClick(x, y);
	return pWind->GetColor(x, y);
}

bool GUI::MouseDrag(int& x, int& y) {
	return pWind->GetButtonState(LEFT_BUTTON, x, y);
}

color GUI::getHoverColor(int& x, int& y) {
	pWind->GetMouseCoord(x, y);
	return pWind->GetColor(x, y);
}
color GUI::getSelectedColor() const {
	return selectedColor;
}

window* GUI::getWindow() const {
	return pWind;
}

image* GUI::getImage(DrawMenuIcon icon) const {
	return DrawMenuIconImages[icon];
}

bool GUI::isInDrawArea(Point p) {
	return  height - getStatusBarHeight() > p.y && (p.y > ToolBarHeight || p.x > DRAW_ICON_COUNT * MenuIconWidth);
}

shape* GUI::getDrawButton(DrawButton button) {
	return DrawButtons[button];
}

int GUI::getGid() const {
	return gid;
}

void GUI::setDrawColor(color drawColor) {
	DrawColor = drawColor;
	pCont->GetGraph()->updateHistory(this);
}

void GUI::setFillColor(color fillColor, bool isFilled = true) {
	Isfilled = isFilled;
	FillColor = fillColor;
	pCont->GetGraph()->updateHistory(this);
}

void GUI::setHighlightColor(color highlightColor) {
	HighlightColor = highlightColor;
}

void GUI::setMsgColor(color msgColor) {
	MsgColor = msgColor;
}

void GUI::setBkGrndColor(color bkGrndColor) {
	BkGrndColor = bkGrndColor;
}

void GUI::setStatusBarColor(color statusBarColor) {
	StatusBarColor = statusBarColor;
}

void GUI::setSelectedColor(color paletteColor) {
	selectedColor = paletteColor;
}

void GUI::setPenWidth(int penWidth) {
	PenWidth = penWidth;
	pCont->GetGraph()->updateHistory(pCont->GetUI());
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

void GUI::storeImage() {
	pWind->StoreImage(storedImage, 0, 0, unsigned short(width), unsigned short(height - getStatusBarHeight()));
}

void GUI::loadImage() {
	pWind->DrawImage(storedImage, 0, 0, width, height - getStatusBarHeight());
}

void GUI::setHighScore(int highscore) {
	this->highscore = highscore;
}

int GUI::getHighScore() const {
	return highscore;
}

//======================================================================================//
//								shapes Drawing Functions								//
//======================================================================================//

void GUI::DrawRect(const Rect* rect, int iWidth, int iHeight) const {
	if (rect->isHidden()) {
		auto [x1, y1] = rect->GetCenter() - 51;
		auto [x2, y2] = rect->GetCenter() + 51;
		pWind->SetPen(rect->IsSelected() ? HighlightColor : BLACK, 3);
		pWind->SetBrush(WHITE);
		pWind->DrawRectangle(x1, y1, x2, y2, FILLED, iWidth, iHeight);
		return;
	}
	color DrawingClr;
	GfxInfo gfxInfo = rect->getGfxInfo();
	Point c1 = rect->getC1();
	Point c2 = rect->getC2();
	if (gfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = gfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, gfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (rect->getGfxInfo().isFilled) {
		style = FILLED;
		pWind->SetBrush(rect->getGfxInfo().FillClr);
	} else
		style = FRAME;
	pWind->DrawRectangle(c1.x, c1.y, c2.x, c2.y, style, iWidth, iHeight);
}

void GUI::DrawCircle(const Circle* circle) const {
	if (circle->isHidden()) {
		auto [x1, y1] = circle->GetCenter() - 51;
		auto [x2, y2] = circle->GetCenter() + 51;
		pWind->SetPen(circle->IsSelected() ? HighlightColor : BLACK, 3);
		pWind->SetBrush(WHITE);
		pWind->DrawRectangle(x1, y1, x2, y2, FILLED);
		return;
	}
	color DrawingClr;
	Point origin = circle->getOrigin();
	GfxInfo gfxInfo = circle->getGfxInfo();
	if (gfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = gfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, gfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (gfxInfo.isFilled) {
		style = FILLED;
		pWind->SetBrush(gfxInfo.FillClr);
	} else
		style = FRAME;

	pWind->DrawCircle(origin.x, origin.y, (int)circle->getRadius(), style);
}

void GUI::DrawIrregPoly(const IrregPoly* irrePoly) const {
	if (irrePoly->isHidden()) {
		auto [x1, y1] = irrePoly->GetCenter() - 51;
		auto [x2, y2] = irrePoly->GetCenter() + 51;
		pWind->SetPen(irrePoly->IsSelected() ? HighlightColor : BLACK, 3);
		pWind->SetBrush(WHITE);
		pWind->DrawRectangle(x1, y1, x2, y2, FILLED);
		return;
	}
	color DrawingClr;
	GfxInfo gfxInfo = irrePoly->getGfxInfo();
	if (gfxInfo.isSelected)
		DrawingClr = HighlightColor;
	else
		DrawingClr = gfxInfo.DrawClr;
	pWind->SetPen(DrawingClr, gfxInfo.BorderWdth);
	drawstyle style;
	if (gfxInfo.isFilled) {
		style = FILLED;
		pWind->SetBrush(gfxInfo.FillClr);
	} else
		style = FRAME;
	pWind->DrawPolygon(irrePoly->getXpoints(), irrePoly->getYpoints(), irrePoly->getSize(), style);
}

void GUI::DrawRegPoly(const RegPoly* RegPoly) const {
	DrawIrregPoly(RegPoly);
}

void GUI::displayHelp() {
	ifstream help;
	help.open("help.txt");
	bool response = true;
	string msg;
	while (getline(help, msg, ';') && response)
		if (!ranges::all_of(msg.begin(), msg.end(), ::isspace))
			response = Prompt(msg);
	help.close();
}

void GUI::DrawLine(const Line* line) const {
	if (line->isHidden()) {
		auto [x1, y1] = line->GetCenter() - 51;
		auto [x2, y2] = line->GetCenter() + 51;
		pWind->SetPen(line->IsSelected() ? HighlightColor : BLACK, 3);
		pWind->SetBrush(WHITE);
		pWind->DrawRectangle(x1, y1, x2, y2, FILLED);
		return;
	}
	color DrawingClr;
	GfxInfo gfxInfo = line->getGfxInfo();
	Point p1 = line->getPoint1();
	Point p2 = line->getPoint2();
	if (gfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = gfxInfo.DrawClr;
	pWind->SetPen(DrawingClr, gfxInfo.BorderWdth);	//Set Drawing color & width
	pWind->DrawLine(p1.x, p1.y, p2.x, p2.y, FRAME);
}

void GUI::DrawImage(const image* imgThis, const int iX, const int iY, const int iWidth, const int iHeight) const {
	pWind->DrawImage(imgThis, iX, iY, iWidth, iHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

shape* GUI::ParseShape(const string& line) {
	stringstream ss(line);
	string type;
	string rest;
	ss >> type;
	ss >> ws;
	getline(ss, rest);
	shape* sh = nullptr;
	if (type == "RECTANGLE")
		sh = Rect::Load(rest);
	else if (type == "CIRCLE")
		sh = Circle::Load(rest);
	else if (type == "SQUARE")
		sh = Square::Load(rest);
	else if (type == "LINE")
		sh = Line::Load(rest);
	else if (type == "TRIANGLE")
		sh = Triangle::Load(rest);
	else if (type == "REGULAR_POLYGON")
		sh = RegPoly::Load(rest);
	else if (type == "IRREGULAR_POLYGON")
		sh = IrregPoly::Load(rest);
	else if (type == "IMAGE")
		sh = imageShape::Load(rest);
	return sh;
}

GUI::~GUI() {
	delete pWind;
	for (int i = 0; i < TOTAL_DRAW_ICON_COUNT; ++i)
		delete DrawMenuIconImages[i];
	for (int i = 0; i < DRAW_BUTTONS_COUNT; ++i)
		delete DrawButtons[i];
	for (int i = 0; i < PLAY_ICON_COUNT; ++i)
		delete PlayMenuIconImages[i];
}

pair<string, map<string, filesystem::path>> GUI::fileSelect(const string& directory, const string& postfix) {
	stringstream ss;
	ss << "Select from " << directory << "\n\n";

	int i = 0;

	string filename;
	map<string, filesystem::path> files;
	for (const auto& save : filesystem::directory_iterator(directory))
		if ((filename = save.path().filename().string()).ends_with(postfix)) {
			files[to_string(i)] = save.path();
			ss << format("({}) {}\n", i, filename.substr(0, filename.size() - 4));
			i++;
		}

	auto prompt = opPrompt(pCont, ss.str());
	prompt.Execute();
	return pair(prompt.response(), files);
}