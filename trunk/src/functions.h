/*
 * functions.h
 *
 *  Created on: Mar 9, 2009
 *      Author: CPress.Scott
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "SDL/SDL.h"
//#include "SDL.h"
#include <string>

std::string intToStr(int);
SDL_Surface* load_image(std::string);
void apply_surface(int, int, SDL_Surface*, SDL_Surface*, SDL_Rect*);
void apply_surface(int, int, SDL_Surface*, SDL_Surface*);

class Point
{//Simple class to hold coordinates
public:
	int x, y;
	bool useful;//for returning 'bad' coordinates
	Point();
	Point(int, int);

};


Point clicked_grid(int, int);
Point check_click(int, int);


#endif /* FUNCTIONS_H_ */
