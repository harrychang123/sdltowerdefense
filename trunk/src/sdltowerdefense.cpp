//============================================================================
// Name        : sdltowerdefense.cpp
// Authors     : Corey Ruda, Scott Wright, Doug Lowery
// Version     : 0.0.1
// Copyright   :
// Description : sdlTD Main File
//============================================================================

/* Include Files for sdlTD*/
#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
//#include "SDL.h"
//#include "SDL_image.h"
//#include "SDL_ttf.h"
#include "functions.h"
#include "constants.h"

/* Namespaces */
using namespace std;

bool load_files();
bool init();
void clean_up();

/*Global Variables*/
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

//Creep Array
SDL_Surface *creep_sprites[CREEP_NUM][16];

//Event structure
SDL_Event event;

int main(int argc, char* args[]) {
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
		/**************************************************************************
		 EVENTS
		**************************************************************************/
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) //If the user Xs out, quit
				quit = true;
		}
		/***************************************************************************
		 LOGIC
		***************************************************************************/
		//TODO: Add Logic Code
		/***************************************************************************
		RENDERING
		***************************************************************************/
		//TODO: Add Rendering Code
		apply_surface(0, 0, background, screen);

		if(SDL_Flip(screen)==-1)
			return 1;
	}

	clean_up();
	return 0;
}

bool load_files()
{
	//TODO: Change this when he have files to load
    //Load the files needed for the program

	background = load_image("background.bmp");

	//load Creep #1
	SDL_Surface *tmpCreep = NULL;
	//TODO: Split this up into a 4x4 25px x 25px

    //font = TTF_OpenFont("lazy.ttf", 30);

    if(background == NULL)
        return false;

    //if(font == NULL)
        //return false;

    return true;
}

bool init()
{
    //Initialize all SDL subsystems
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return false;

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    if(screen == NULL)
        return false;

    if(TTF_Init() == -1)
        return false;

    SDL_WM_SetCaption(GAME_CAPTION.c_str(), NULL);
    return true;
}

void clean_up()
{//Delete all used surfaces
	SDL_FreeSurface(screen);
}
