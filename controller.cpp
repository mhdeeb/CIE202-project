#include "controller.h"
#include "operations/opAddTriangle.h"
#include "operations/opAddRect.h"
#include "operations/opAddCircle.h"
#include "operations/opAddSquare.h"
#include "operations/opAddLine.h"
#include "operations/opAddIrregPoly.h"
#include "operations/opColorPalette.h"
#include "operations/opSelect.h"
#include "operations/opExit.h"
#include "operations/opChangeGpenCol.h"
#include "operations/opChangeGfillCol.h"

//Constructor
controller::controller()
{
	pGraph = new Graph;
	pGUI = new GUI;	//Create GUI object
	isRunning = true;
}

//==================================================================================//
//								operations-Related Functions							//
//==================================================================================//
operationType controller::GetUseroperation(int x, int y) const
{
	//Ask the input to get the operation from the user.
	return pGUI->GetUseroperation(x, y);
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an operation and executes it
operation* controller::createOperation(operationType OpType)
{
	operation* pOp = nullptr;

	//According to operation Type, create the corresponding operation object
	switch (OpType)
	{
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
		break;
	case DRAW_IRREG_POLY:
		pOp = new opAddIrregPoly(this);
		break;
	case DRAW_COLOR_PALETTE:
		pOp = new opColorPalette(this);
		break;
	case CHNG_DRAW_CLR:
		pOp = new opChangeGpenCol(this);
		break;
	case CHNG_FILL_CLR:
		pOp = new opChangeGfillCol(this);
		break;
	case EXIT:
		pOp = new opExit(this);
		break;
	case STATUS:	//a click on the status bar ==> no operation
		break;
	case DRAWING_AREA:
		pOp = new Select(this);
		break;	
	}
	return pOp;

}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all shapes on the user interface
void controller::UpdateInterface() const
{
	pGraph->Refresh(pGUI);
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the UI
GUI* controller::GetUI() const
{
	return pGUI;
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the Graph
Graph* controller::getGraph() const
{
	return pGraph;
}



//Destructor
controller::~controller()
{
	delete pGUI;
	delete pGraph;
}



//==================================================================================//
//							Run function											//
//==================================================================================//
void controller::Run()
{
	operationType OpType;
	int x, y;
	do
	{
		//1. Ask the GUI to read the required operation from the user
		pGUI->PrintMessage("Select an operation");
		pGUI->getWindow()->WaitMouseClick(x, y);	//Get the coordinates of the user click
		OpType = GetUseroperation(x, y);

		//2. Create an operation coresspondingly
		operation* pOpr = createOperation(OpType);

		//3. Execute the created operation
		if (pOpr)
		{
			pOpr->Execute();
			delete pOpr;
			pOpr = nullptr;
		}
		UpdateInterface();
	} while (isRunning);
}

void controller::close() {
	isRunning = false;
}