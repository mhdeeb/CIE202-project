#include "controller.h"

int main()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);	// Toggle Console terminal
	controller Control;
	Control.Run();
}
