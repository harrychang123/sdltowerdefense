/*
 * functions.cpp
 *
 *  Created on: Mar 9, 2009
 *      Author: CPress.Scott
 */

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
/*
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
*/
#include <string>
#include <sstream>
#include "functions.h"
#include "constants.h"

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{//Applies the source surface to the destination surface
    //Holds offsets
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface(source, clip, destination, &offset);
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{//Applies the source surface to the destination surface
    //Blit
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
    SDL_BlitSurface(source, NULL, destination, &offset);
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

SDL_Surface *optimize_image(SDL_Surface* source)
{
	SDL_Surface *optimizedImage = NULL;
	optimizedImage = SDL_DisplayFormat(source);
	SDL_FreeSurface(source);

	if(optimizedImage!=NULL)
	{
		//Color key surface
		SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));
	}

	return optimizedImage;
}


