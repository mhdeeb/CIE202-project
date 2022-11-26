#include "opAddCircle.h"
#include "../Shapes/Circle.h"

#include "../controller.h"

#include "../GUI/GUI.h"

opAddCircle::opAddCircle(controller* pCont) :operation(pCont)
{}
opAddCircle::~opAddCircle()
{}

//Execute the operation
void opAddCircle::Execute()
{
	Point center, rad;
	double radius;
	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("New Circle: Click at center");
	//Read center and store in point center
	pUI->GetPointClicked(center.x, center.y);

	string msg = "Center is at (" + to_string(center.x) + ", " + to_string(center.y) + " )";
	msg += " ... Click at radius end";
	pUI->PrintMessage(msg);
	//Read radius and store in point rad
	pUI->GetPointClicked(rad.x, rad.y);
	pUI->ClearStatusBar();

	//Preapre all circle parameters
	GfxInfo CircleGfxInfo;

	//get drawing, filling colors and pen width from the interface
	CircleGfxInfo.DrawClr = pUI->getCrntDrawColor();
	CircleGfxInfo.FillClr = pUI->getCrntFillColor();
	CircleGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	CircleGfxInfo.isFilled = false;	//default is not filled
	CircleGfxInfo.isSelected = false;	//defualt is not selected


	//Create a circle with the above parameters
	Circle* C = new Circle(center, sqrt(pow(rad.x - center.x, 2) + pow(rad.y - center.y, 2)), CircleGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the circle to the list of shapes
	pGr->Addshape(C);

}
