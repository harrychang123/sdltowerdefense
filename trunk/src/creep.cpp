/*
 * Author: CoreyRuda, CPress.Scott
 * Filename: creep.cpp
 * This is the creep class functions
 */
//TODO: Add an immunities array
//TODO: Create different types of creeps and set the creep type as an ID, if needed

//Include Files
#include <vector>
#include "creep.h"
#include "functions.h"
#include "constants.h"

//Creep Next Num
int creep_next_num = 0;

/********************************************************************************
 Constructor
********************************************************************************/

Creep::Creep(int x,int y,int hp, int speed, int cd,int def, bool fly, int reward)
{
	//Initialize the Creep object
	hit_points = hp;
	move_speed = speed;
	defense = def;
	ground = fly;
	prize = reward;
	xpos = x;
	ypos = y;
	frame = 0;
	creep_id = creep_next_num;
	creep_next_num ++;
	cooldown = cd;
	slowed = false;
	dead = false;
}

/********************************************************************************
Getter Functions
********************************************************************************/
int Creep::get_cooldown()
{
	//Returns the creeps cooldown
	return cooldown;
}

int Creep::get_hp()
{
	//Return the value of Hit Points
	return hit_points;
}

int Creep::get_move()
{
	//Return the value of movespeed
	return move_speed;
}

int Creep::get_defense()
{
	//Return the value of defense
	return defense;
}

int Creep::get_prize()
{
	//Return the value of prize
	return prize;
}

int Creep::get_type()
{
	//Return the value of creep_type
	return creep_type;
}

bool Creep::get_ground()
{
	//Return the value ot ground
	return ground;
}

int Creep::get_x()
{
	//Returns the xposition
	return xpos;
}

int Creep::get_y()
{
	//Retuns the y position
	return ypos;
}

int Creep::get_frame()
{
	//Returns the current frame that the creep is on
	return frame;
}

int Creep::get_id()
{
	//Returns the creep_id
	return creep_id;
}
/*********************************************************************************
Setter Functions
**********************************************************************************/
void Creep::set_cooldown(int num)
{
	//Changes the creeps cooldown
	cooldown = num;
}

void Creep::set_hp(int num)
{
	//Set HP
	hit_points = num;
}

void Creep::set_move(int num)
{
	//Set the move speed of the creep
	move_speed = num;
}

void Creep::set_defense(int num)
{
	//Set the defense of the creep
	defense = num;
}

void Creep::set_prize(int num)
{
	//Set the prize of the creep
	prize = num;
}

void Creep::set_type(int num)
{
	//Set the creep_type of the creep
	creep_type = num;
}

void Creep::set_ground(bool value)
{
	//Set the ground to true or false
	ground = value;
}

void Creep::set_x(int num)
{
	//Sets the x position of the creep
	xpos = num;
}

void Creep::set_y(int num)
{
	//Sets the y position of the creep
	ypos = num;
}

/****************************************************************************************
Member Functions
****************************************************************************************/

void Creep::move(int state)
{
	//TODO: Finish direction detection and set up movements for corresponding directions
	//Determine the direction the creep is moving

	//Frame Setting controller
	//Determines how many frames it has been since the creep last moved
	static int rate = 0;

	//If adding a frame wont go over, add one to the frame. otherwise, reset
	//This is when the creep is healthy
	switch(state)
	case CREEP_NORTH:
	{
		if(rate == (MOVE_SCALE - get_cooldown()))
		{
			if((frame+1) > 3)
			{
				frame = 0;
				set_y(get_y() - get_move());
			}
			else
			{
				frame ++;
				rate = 0;
				set_y(get_y() - get_move());
			}
		}
		else
		{
			rate ++;
			break;
		}

		break;
	case CREEP_EAST:
		if((frame > 3) && ((frame+1) < 7))
		{
			frame ++;
			set_x(get_x()+get_move());
			set_y(get_y());
		}
		else
		{
			frame = 4;
		}
		break;
	}
}

void Creep::show(int xpos,int ypos,SDL_Surface* source,SDL_Surface* destination,SDL_Rect* sprite)
{
	//Renders the creep to the screen
	apply_surface(xpos,ypos,source,destination,sprite);
}

void Creep::slow()
{
	//This changes the creeps state
	slowed = (!slowed);
}

void Creep::die()
{
	//Kills the creep
	//TODO: Remove the creep from the array in main.
	hit_points = 0;
	dead = true;
}

bool Creep::is_dead()
{
	return dead;
}
