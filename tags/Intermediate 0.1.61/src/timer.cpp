/*
 * Author: Corey Ruda
 * Filename: timer.cpp
 *
 * This is the source file for the Timer class
 */

#include "timer.h"
#ifndef _WIN32
	#include "SDL/SDL.h"
	#include "SDL/SDL_image.h"
#else
	#include "SDL.h"
	#include "SDL_image.h"
#endif

/***************************************************
The Constructor
***************************************************/
Timer::Timer()
{
	//initialize the variables
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

/****************************************************
Setter Functions
****************************************************/
void Timer::start()
{
	//Starts the timer
	started = true;

	//Unpause the timer
	paused = false;

	//Get the ticks
	startTicks = SDL_GetTicks();
}

void Timer::stop()
{
	//Stop the timer
	started = false;

	//Unpause the timer
	paused = false;
}

int Timer::get_ticks()
{
	//Return the ticks depending on the timer's state
	if(started == true)
	{
		//Check to see if the timer is paused
		if(paused == true)
		{
			//Return the number of ticks when it timer was paused
			return pausedTicks;
		}

		else
		{
			//Return the current time minus the start time
			return SDL_GetTicks() - startTicks;
		}
	}

	//The timer isnt running
	return 0;

}

void Timer::pause()
{
	//Determine if the timer is running and isnt paused
	if(started == true && paused == false)
	{
		//Pause the timer and get the time from when it was paused
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::unpause()
{
	//Check to see if the timer is paused
	if(paused)
	{
		//Unpause the timer
		paused = false;

		//Reset the ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		//Reset paused ticks
		pausedTicks = 0;
	}
}

/********************************************************************
Getter Functions
********************************************************************/
bool Timer::is_paused()
{
	//Return the paused variable
	return paused;
}

bool Timer::is_started()
{
	return started;
}
