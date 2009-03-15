/*
 * functions.cpp
 *
 *  Created on: Mar 9, 2009
 *      Author: CPress.Scott
 */

#ifndef _WIN32
	#include "SDL/SDL.h"
	#include "SDL/SDL_image.h"
#else
	#include "SDL.h"
	#include "SDL_image.h"
#endif

#include <string>
#include <sstream>
#include "functions.h"
#include "constants.h"
#include <math.h>

Point::Point()
{
	x=0;
	y=0;
	useful=true;
}

Point::Point(int a, int b)
{
	x = a;
	y = b;
	useful=true;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
	//Applies the source surface to the destination surface

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

Point check_click(int x, int y)
{//Checks to see if the user clicked on anything.  If they did, return an action code
	//Check so see if we clicked in the grid
	Point tmp;
	tmp = clicked_grid(x, y);
	if(tmp.useful)
	{
		return tmp;//User clicked the grid
	} else {
		//user did not click the grid
		Point crap(-1,-1);
		crap.useful=false;
		return crap;
	}
}

Point clicked_grid(int x, int y)
{//If user clicked a cell in the grid, returns the top left coords of that cell. Otherwise, useful=false
	for(int a=1; a<= NUM_ROWS; a++)
	{
		for(int b=1; b<=NUM_COLUMNS; b++)
		{
			if(x>=1+26*(b-1) && x<=25+26*(b-1) && y>=1+26*(a-1) && y<=25+26*(a-1))//I hate this formula >_<
			{//User clicked in square a,b (row,col)
				//Return the top left corner of this cell
				Point tmp(1+26*(b-1), 1+26*(a-1));
				return tmp;
			}
		}
	}
	Point tmp;
	tmp.useful = false;
	return tmp;
}

double distance(int x2, int x1, int y2, int y1)
{
	return sqrt(pow(x2-x1, 2)+pow(y2-y1, 2));
}

double distance(double x2, double x1, double y2, double y1)
{
	return sqrt(pow(x2-x1, 2)+pow(y2-y1, 2));
}


