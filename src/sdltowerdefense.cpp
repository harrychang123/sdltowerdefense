//============================================================================
// Name        : sdltowerdefense.cpp
// Authors     : Corey Ruda, Scott Wright, Doug Lowery
// Version     : 0.0.1
// Copyright   :
// Description : sdlTD Main File
//============================================================================

/* Include Files for sdlTD*/
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "functions.h"
#include "constants.h"

/* Namespaces */
using namespace std;

/*Global Variables*/

//Creep Array
SDL_Surface *creep[CREEP_DIRECTION][CREEP_FRAME];

//Event structure
SDL_Event event;

int main(int argc, char* args[]) {
	//Bool to hold if the user has quit or not
	bool quit = false;

	//Initialize
	if(init() == false)
		return 1;

	//Load the files
	if(load_files() == false)
		return 1;

	//The main loop.

	while(quit == false)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_Quit) //If the uses Xs out, set quit to true
				quit = true;
		}
	}

	clean_up();
	return 0;
}
