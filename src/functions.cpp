/*
 * functions.cpp
 *
 *  Created on: Mar 9, 2009
 *      Author: CPress.Scott
 */

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <sstream>
#include "functions.h"

void clean_up()
{//Delete all used surfaces
	SDL_FreeSurface(screen);
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{//Applies the source surface to the destination surface
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface(source, clip, destination, &offset);
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{//Applies the source surface to the destination surface
    //Blit
    SDL_BlitSurface(source, clip, destination, &offset);
}

std::string intToStr(int a)
{//Converts an int to a string
	std::stringstream out;
	out << a;
	return out.str();
}

SDL_Surface *load_image(std::string filename)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load(filename.c_str());

    //TODO: Catch exception where loadedimage==NULL
    if(loadedImage != NULL)
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat(loadedImage);

        //Free the old surface
        SDL_FreeSurface(loadedImage);

        //If the surface was optimized
        if(optimizedImage != NULL)
        {
            //Color key surface
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));
        }
    }

    //Return the optimized surface
    return optimizedImage;
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

    SDL_WM_SetCaption("SDL Tower Defense", NULL);
    return true;
}

bool load_files()
{
	//TODO: Change this when he have files to load
    //Load the files needed for the program
    /*
	background = load_image("background_big.png");

    font = TTF_OpenFont("lazy.ttf", 30);

    if(background == NULL)
        return false;

    if(font == NULL)
        return false;
    */
    return true;
}
