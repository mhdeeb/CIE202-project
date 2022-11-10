#include "controller.h"


int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);		// Hide Console terminal
	//Create an object of controller
	controller Control;

	Control.Run();

	
	return 0;
}

