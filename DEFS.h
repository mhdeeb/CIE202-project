#ifndef DEFS_H
#define DEFS_H

//This file contais some global constants and definitions to be used in the project.
enum operationType //The operations supported (you can add more if needed)
{
	DRAW_LINE,		//Draw Line
	DRAW_RECT,		//Draw Rectangle
	DRAW_SQUARE,    //Draw Square
	DRAW_TRIANGLE,  //Draw Triangle
	DRAW_CIRC,		//Draw Circle
	DRAW_REG_POLY,  //Draw Regular Polygon
	DRAW_IRREG_POLY,//Draw Irregular Polygon
	DRAW_IMAGE,		//Draw Image
	DRAW_COLOR_PALETTE,
	CHNG_DRAW_CLR,	//Change the drawing color
	CHNG_FILL_CLR,	//Change the filling color
	CHNG_BK_CLR,	//Change background color

	DEL,			//Delete a shape(s)
	MOVE,			//Move a shape(s)
	RESIZE,			//Resize a shape(s)
	ROTATE,			//Rotate a shape(s)
	SEND_BACK,		//Send a shape to the back of all shapes
	BRNG_FRNT,		//Bring a shape to the front of all shapes
	SAVE,			//Save the whole graph to a file
	LOAD,			//Load a graph from a file
	EXIT,			//Exit the application

	WINDOW_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar
	EMPTY,			//A click on empty place in the toolbar

	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY,			//Switch interface to Play mode

	RESTART,
	START_GAME,
};

const color ColorsArray[]{
	RED,
	GREEN,
	BLUE,
	ORANGE,
	YELLOW,
	PURPLE,
	WHITE,
};

#endif
