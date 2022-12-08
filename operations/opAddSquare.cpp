#include "opAddSquare.h"

#include "../Shapes/Square.h"
#include "../Shapes/Circle.h"

opAddSquare::opAddSquare(controller* pCont) :operation(pCont)
{}
opAddSquare::~opAddSquare()
{}

//Execute the operation
void opAddSquare::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	//Preapre all Square parameters
	GfxInfo gfxInfo;

	//get drawing, filling colors and pen width from the interface
	gfxInfo.DrawClr = pUI->getCrntDrawColor();
	gfxInfo.FillClr = pUI->getCrntFillColor();
	gfxInfo.BorderWdth = pUI->getCrntPenWidth();
	gfxInfo.isFilled = false;	//default is not filled
	gfxInfo.isSelected = false;	//defualt is not selected

	pUI->PrintMessage("New Square: Click at the corner");
	//Read 1st corner and store in point P1
	pUI->GetPointClicked(P1.x, P1.y);
	Circle circ = Circle({ P1.x , P1.y }, 10, gfxInfo);
	pUI->DrawCircle(&circ);
	string msg = "First corner is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	msg += " ... Click at any point to determine the diagonal of the square";
	pUI->PrintMessage(msg);
	//Read the point from wich we can calculate the diagonal of the square
	pUI->GetPointClicked(P2.x, P2.y);
	pUI->ClearStatusBar();

	//Create a square with the above parameters
	Square* R = new Square(P1, P2, gfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the square to the list of shapes
	pGr->Addshape(R);

}
