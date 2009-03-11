/*
 * Author: Corey Ruda
 * Filename: creep.cpp
 * This is the creep class functions
 */
//TODO: Add an immunities array
//TODO: Create different types of creeps and set the creep type as an ID, if needed

//Include Files
#include <vector>
#include "creep.h"

/********************************************************************************
 Constructor
********************************************************************************/

Creep::Creep(int hp, int speed, int def, bool fly, int reward)
{
	//Initialize the Creep object
	hit_points = hp;
	move_speed = speed;
	defense = def;
	ground = fly;
	prize = reward;
}

/********************************************************************************
Getter Functions
********************************************************************************/
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

/*********************************************************************************
Setter Functions
**********************************************************************************/
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
