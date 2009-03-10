//============================================================================
// Name        : sdltowerdefense.cpp
// Authors     : Corey Ruda, Scott Wright, Doug Lowery
// Version     : 0.0.1
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

/* Include Files for sdlTD*/
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

/* Namespaces */
using namespace std;

/*Global Variables*/

//The Screen's Dimensions
//TODO: Put into a constant header
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;

//Surface variable
SDL_Surface *screen = NULL;

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
