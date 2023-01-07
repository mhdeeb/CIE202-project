#include "controller.h"
#include "operations/opAddTriangle.h"
#include "operations/opAddRect.h"
#include "operations/opAddCircle.h"
#include "operations/opAddSquare.h"
#include "operations/opAddLine.h"
#include "operations/opAddIrregPoly.h"
#include "operations/opColorPalette.h"
#include "operations/opSelect.h"
#include "operations/opSave.h"
#include "operations/opLoad.h"
#include "operations/opExit.h"
#include "operations/opChangeGpenCol.h"
#include "operations/opChangeGfillCol.h"
#include "operations/opDelete.h"
#include "operations/opAddRegPoly.h"
#include "operations/SwitchToPlayMode.h"
#include "operations/SwitchToDrawMode.h"
#include "operations/opAddImageShape.h"
#include "operations/noOp.h"
#include "operations/opStartGame.h"
#include "operations/opRestartGame.h"

//Constructor
controller::controller() {
	pGraph = new Graph;
	pGUI = new GUI(this);	//Create GUI object
	isRunning = true;
}

//==================================================================================//
//								operations-Related Functions							//
//==================================================================================//
operationType controller::GetUseroperation(int x, int y) const {
	//Ask the input to get the operation from the user.
	return pGUI->GetUseroperation(x, y);
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an operation and executes it
operation* controller::createOperation(operationType OpType) {
	operation* pOp = nullptr;

	//According to operation Type, create the corresponding operation object
	if (!pGUI->getInterfaceMode()) {
		switch (OpType) {
		case DRAW_RECT:
			pOp = new opAddRect(this);
			break;
		case DRAW_CIRC:
			pOp = new opAddCircle(this);
			break;
		case DRAW_SQUARE:
			pOp = new opAddSquare(this);
			break;
		case DRAW_LINE:
			pOp = new opAddLine(this);
			break;
		case DRAW_TRIANGLE:
			pOp = new opAddTri(this);
			break;
		case DRAW_REG_POLY:
			pOp = new opAddRegPoly(this);
			break;
		case DRAW_IRREG_POLY:
			pOp = new opAddIrregPoly(this);
			break;
		case DRAW_COLOR_PALETTE:
			pOp = new opColorPalette(this, false);
			break;
		case DRAW_IMAGE:
			pOp = new opAddImageShape(this);
			break;
		case CHNG_DRAW_CLR:
			pOp = new opChangeGpenCol(this);
			break;
		case CHNG_FILL_CLR:
			pOp = new opChangeGfillCol(this);
			break;
		case DEL:
			pOp = new Delete(this);
			break;
		case SAVE:
			pOp = new opSave(this);
			break;
		case LOAD:
			pOp = new opLoad(this);
			break;
		case TO_PLAY:
			pOp = new SwitchToPlayMode(this);  // this operation is supposed to Clear the draw toolbar and draw the play toolbar
			break;
		case EXIT:
			pOp = new opExit(this);
			break;
		case STATUS:	//a click on the status bar ==> no operation
			break;
		default:
			pOp = new Select(this);
			break;
		}
	} else {
		switch (OpType) {
		case RESTART:
			pOp = new opRestartGame(this);
			break;
		case START_GAME:
			pOp = new opStartGame(this);
			break;
		case TO_DRAW:
			pOp = new SwitchToDrawMode(this);  // this operation is supposed to Clear the Play toolbar and draw the Draw toolbar
			break;
		case EXIT:
			pOp = new opExit(this);
			break;
		case STATUS:	//a click on the status bar ==> no operation
			break;
		default:
			pOp = new Select(this);
			break;
		}
	}
	if (!pOp)
		pOp = new noOp(this);	//No valid operation: create a dummy operation for noAction
	return pOp;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all shapes on the user interface
void controller::UpdateInterface() const {
	pGraph->Refresh(pGUI);
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the UI
GUI* controller::GetUI() const {
	return pGUI;
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the Graph
Graph* controller::GetGraph() const {
	return pGraph;
}

//Destructor
controller::~controller() {
	delete pGUI;
	delete pGraph;
}

//==================================================================================//
//							Run function											//
//==================================================================================//
void controller::Run() {
	operationType OpType;
	int x;
	int y;
	bool skipInput = false;
	pGraph->Load("save/Example_gf.txt", pGUI);
	do {
		if (pGUI->getInterfaceMode()) {
			pGUI->GetPointClickedNoOp(x, y);
		} else {
			if (!skipInput)
				while (!pGUI->GetPointClicked(x, y));
			else
				pGUI->getMouseLocation(x, y);
		}
		OpType = GetUseroperation(x, y);
		pGUI->getWindow()->FlushKeyQueue();
		operation* pOpr = createOperation(OpType);
		if (!(dynamic_cast<opChangeGfillCol*>(pOpr) || dynamic_cast<opChangeGpenCol*>(pOpr) || dynamic_cast<opColorPalette*>(pOpr)))
			pGraph->updateSelectedShapes(pGUI);
		UpdateInterface();

		if (pOpr) {
			skipInput = pOpr->Execute();
			delete pOpr;
			pOpr = nullptr;
		}
	} while (isRunning);
}

void controller::close() {
	isRunning = false;
}