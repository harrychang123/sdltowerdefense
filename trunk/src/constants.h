/*
 * constants.h
 *
 *  Created on: Mar 9, 2009
 *      Author: CPress.Scott
 */
//TODO: Add Nessecarry Game Stats as needed to enum GameStates
//TODO: Change all CREEP_NUM to a set number

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

/*Global Variables*/
const int SCREEN_WIDTH     = 640;
const int SCREEN_HEIGHT    = 480;
const int SCREEN_BPP       = 32;
const int CREEP_NUM        = 1;

//Game State Constants
enum GameStates
{
	STATE_NULL,
	STATE_INIT,
	STATE_EXIT,
	STATE_MENU,
	STATE_PLAYING,
	STATE_PAUSED
};

//The screen
SDL_Surface *screen = NULL;

#endif /* CONSTANTS_H_ */
