/*
 * button.cpp
 *
 *  Created on: Mar 22, 2009
 *      Author: scott
 */

#ifndef _WIN32
	#include "SDL/SDL.h"
	#include "SDL/SDL_image.h"
#else
	#include "SDL.h"
	#include "SDL_image.h"
#endif

#include "button.h"

Button::Button()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	down = 0;
	image = NULL;
	image_highlight = NULL;
	image_down = NULL;
}

Button::Button(int px, int py, int pw, int ph, SDL_Surface *pimage, SDL_Surface *pimage_highlight, SDL_Surface *pimage_down)
{
	x = px;
	y = py;
	w = pw;
	h = ph;
	down = 0;
	image = pimage;
	image_highlight = pimage_highlight;
	image_down = pimage_down;
}

int Button::get_x()
{
	return x;
}

int Button::get_y()
{
	return y;
}

int Button::get_w()
{
	return w;
}

int Button::get_h()
{
	return h;
}

int Button::is_down()
{
	return down;
}

bool Button::is_button(int px, int py)
{
	//Returns true if the coords are inside of or on the button
	if(px>=x && px<=x+w && py>=y && py<=y+h)
	{//it is inside/on
		return true;
	}
	return false;
}

void Button::set_x(int param)
{
	x = param;
}

void Button::set_y(int param)
{
	y = param;
}

void Button::set_w(int param)
{
	w = param;
}

void Button::set_h(int param)
{
	h = param;
}

void Button::set_down()
{
	down = 2;
}

void Button::set_highlight()
{
	down = 1;
}

void Button::set_up()
{
	down = 0;
}

void Button::set_center(int param_x, int param_y)
{
	//Positions the button so that the center is at param_x, param_y
	x = param_x - w/2;
	y = param_y - h/2;
}
