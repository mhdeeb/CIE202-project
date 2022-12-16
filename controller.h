#pragma once

#include "Shapes/Graph.h"

class operation;

//Main class that manages everything in the application.
class controller
{

	Graph* pGraph;	//pointe to the grapg
	GUI* pGUI;		//Pointer to UI class


public:
	controller();
	~controller();

	// -- operation-Related Functions
	//Reads the input command from the user and returns the corresponding operation type
	operationType GetUseroperation(int, int) const;
	operation* createOperation(operationType); //Creates an operation
	void Run();

	Graph* getGraph() const;

	// -- Interface Management Functions
	GUI* GetUI() const; //Return pointer to the UI
	void UpdateInterface() const;	//Redraws all the drawing window	

};
