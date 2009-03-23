/*
 * button.h
 *
 *  Created on: Mar 22, 2009
 *      Author: scott
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#ifndef _WIN32
	#include "SDL/SDL.h"
	#include "SDL/SDL_image.h"
#else
	#include "SDL.h"
	#include "SDL_image.h"
#endif


class Button
{
private:
	int x;
	int y;
	int w;
	int h;
	int down;

public:
	SDL_Surface *image;
	SDL_Surface *image_down;
	SDL_Surface *image_highlight;

	Button();
	Button(int, int, int, int, SDL_Surface*, SDL_Surface*, SDL_Surface*);//x, y, w, h, image, image highlight, image down
	int get_x();
	int get_y();
	int get_w();
	int get_h();
	int is_down();//0=up, 1=highlight, 2=down
	bool is_button(int, int);
	void set_x(int);
	void set_y(int);
	void set_w(int);
	void set_h(int);
	void set_down();
	void set_up();
	void set_highlight();
	void set_center(int, int);
};

#endif /* BUTTON_H_ */
