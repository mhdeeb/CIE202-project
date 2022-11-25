#include "opAddSquare.h"
#include "shapes\square.h"
#include "controller.h"
#include "GUI\GUI.h"
#include <Iostream>
using namespace std;

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

	pUI->PrintMessage("New Square: Click at the corner");
	//Read 1st corner and store in point P1
	pUI->GetPointClicked(P1.x, P1.y);

	string msg = "First corner is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	msg += " ... Click at any point to determine the side length of the square";
	pUI->PrintMessage(msg);
	//Read the point from wich we can calculate the side length of the square
	pUI->GetPointClicked(P2.x, P2.y);
	pUI->ClearStatusBar();

	//Preapre all Square parameters
	GfxInfo SquareGfxInfo;

	//get drawing, filling colors and pen width from the interface
	SquareGfxInfo.DrawClr = pUI->getCrntDrawColor();
	SquareGfxInfo.FillClr = pUI->getCrntFillColor();
	SquareGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	SquareGfxInfo.isFilled = false;	//default is not filled
	SquareGfxInfo.isSelected = false;	//defualt is not selected


	//Create a square with the above parameters
	square* R = new square(P1,P2, SquareGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the square to the list of shapes
	pGr->Addshape(R);

}
