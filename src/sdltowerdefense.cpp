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
//#include "SDL.h"
//#include "SDL_image.h"
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
SDL_Rect creep_sprite_offsets[CREEP_NUM][16];
SDL_Surface *creep_sprites[CREEP_NUM];

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
{//Load the files needed for the program

	background = load_image("background.bmp");

	//TODO: Clean this up and make it work for more than 1 creep
	//load Creep #1
	SDL_Surface *tmpCreep = NULL;

	//TODO: Store creep spritesheet filenames in an array
	tmpCreep = load_image("creep1.bmp");
	creep_sprites[0] = tmpCreep;
	SDL_FreeSurface(tmpCreep);

	//Split this up into a 4x4 25px x 25px
	SDL_Rect tmpRect;
	int tmp_x=0, tmp_y=0;
	for(int i=0; i<4; i++)
	{//row
		tmp_x=i*25;
		for(int j=0; j<4; j++)
		{//col
			tmp_y=j*25;
			tmpRect.x=j;
			tmpRect.y=i;
			tmpRect.w=25;
			tmpRect.h=25;
			creep_sprite_offsets[0][j+4*i] = tmpRect;//Store the offsets in the array
		}
	}
    if(background == NULL)
        return false;
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

    SDL_WM_SetCaption(GAME_CAPTION.c_str(), NULL);
    return true;
}

void clean_up()
{//Delete all used surfaces
	SDL_FreeSurface(screen);
}
