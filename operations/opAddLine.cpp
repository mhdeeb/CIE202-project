#include "opAddLine.h"

#include "../Shapes/Line.h"
#include "../Shapes/Circle.h"

opAddLine::opAddLine(controller* pCont) :operation(pCont)
{}
opAddLine::~opAddLine()
{}

//Execute the operation
void opAddLine::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	//Preapre all rectangle parameters
	GfxInfo gfxInfo;

	//get drawing, filling colors and pen width from the interface
	gfxInfo.DrawClr = pUI->getCrntDrawColor();
	gfxInfo.FillClr = pUI->getCrntFillColor();
	gfxInfo.BorderWdth = pUI->getCrntPenWidth();
	gfxInfo.isFilled = false;	//default is not filled
	gfxInfo.isSelected = false;	//defualt is not selected

	pUI->PrintMessage("New Line: Click at first Line");
	//Read 1st Line and store in point P1
	pUI->GetPointClicked(P1.x, P1.y);
	Circle circ = Circle({ P1.x , P1.y }, 10, gfxInfo);
	pUI->DrawCircle(&circ);
	string msg = "First Point is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	msg += " ... Click at second corner";
	pUI->PrintMessage(msg);
	//Read 2nd Point and store in point P2
	pUI->GetPointClicked(P2.x, P2.y);
	pUI->ClearStatusBar();

	//Create a rectangle with the above parameters
	Line* R = new Line(P1, P2, gfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the Line to the list of shapes
	pGr->Addshape(R);

}
