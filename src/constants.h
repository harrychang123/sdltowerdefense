/*
 * constants.h
 *
 *  Created on: Mar 9, 2009
 *      Author: CPress.Scott, CoreyRuda
 */
//TODO: Add Nessecarry Game Stats as needed to enum GameStates
//TODO: Change all CREEP_NUM to a set number

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>

/*Global Variables*/
const int SCREEN_WIDTH     = 660;
const int SCREEN_HEIGHT    = 469;
const int SCREEN_BPP       = 32;
const int NUM_ROWS         = 18;
const int NUM_COLUMNS      = 24;
const int CREEP_NUM        = 4;
const int TURRET_NUM 	   = 1;
const std::string GAME_CAPTION = "SDL Tower Defense";
const int WAIT             =  10;

//Creep Pixel Determinations
const int CREEP_WIDTH      = 25;
const int CREEP_HEIGHT     = 25;
const int CREEP_NORTH      = 0;
const int CREEP_EAST       = 1;
const int CREEP_SOUTH      = 2;
const int CREEP_WEST       = 3;

//Constants that affect the creep
const bool CREEP_SLOWED     = true;

//Slow Movement constants
const int SLOW_MOVE        = 1;
const int SLOW_COOLDOWN    = 3;

//Maximun number of frames - 1 to wait before animation a creep
const int MOVE_SCALE       = 10;

//Frams per second
const int FRAMES_PER_SECOND = 30;

//Game State Constants
enum GameStates
{
	STATE_NULL,
	STATE_EXIT,
	STATE_MENU,
	STATE_GAMEPLAY,
	STATE_PAUSED
};

#endif /* CONSTANTS_H_ */
