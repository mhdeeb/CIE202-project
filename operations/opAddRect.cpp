#include "opAddRect.h"

#include "../Shapes/Rect.h"
#include "../Shapes/Circle.h"

opAddRect::opAddRect(controller* pCont) :operation(pCont)
{}
opAddRect::~opAddRect()
{}

//Execute the operation
void opAddRect::Execute()
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

	pUI->PrintMessage("New Rectangle: Click at first corner");
	//Read 1st corner and store in point P1
	pUI->GetPointClicked(P1.x, P1.y);
	Circle circ = Circle({ P1.x , P1.y }, 10, gfxInfo);
	pUI->DrawCircle(&circ);
	string msg = "First corner is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	msg += " ... Click at second corner";
	pUI->PrintMessage(msg);
	//Read 2nd corner and store in point P2
	pUI->GetPointClicked(P2.x, P2.y);
	pUI->ClearStatusBar();


	//Create a rectangle with the above parameters
	Rect* R = new Rect(P1, P2, gfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the rectangle to the list of shapes
	pGr->Addshape(R);

}
