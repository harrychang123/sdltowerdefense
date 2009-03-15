//Author: CoreyRuda, CPress.Scott
//Filename: turret.cpp
//This is the Turret Class Functions
//TODO: Determine the max level that a tower can be upgraded to

#include "turret.h"

//Class Turret Constructor
Turret::Turret(int x_pos,int y_pos,int tcost,int cost_up,int trange,int tdamage,double tcooldown)
{
	//Initialize the class object
	x = x_pos;
	y = y_pos;
	cost = tcost;
	cost_upgrade = cost_up;
	range = trange;
	damage = tdamage;
	cooldown = tcooldown;
	level = 1;
}


/*****************************************************************************
Setter Functions
******************************************************************************/
void Turret::upgrade()
{
	//Set the level of the tower
	level += 1;
}

void Turret::set_up_cost(int num)
{
	//Set the cost to upgrade the tower
	cost_upgrade = num;
}

void Turret::set_y(int num)
{
	//Set the y value of the turret's position
	y = num;
}

void Turret::set_x(int num)
{
	//Set the x value of the turret's position
	x = num;
}

void Turret::set_cooldown(double num)
{
	//Set the cooldown of the tower
	cooldown = num;
}

void Turret::set_cost(int num)
{
	//Sets the cost of the tower
	cost = num;
}

void Turret::set_range(int num)
{
	//Sets the range of the tower
	//TODO: Determine how many pixels per int
	range = num;
}

void Turret::set_damage(int num)
{
	//Sets the damage the tower can do
	damage = num;
}

/*****************************************************************************
Getter Functions
******************************************************************************/

int Turret::get_cost()
{
	//Return the cost of the tower
	return cost;
}

int Turret::get_range()
{
	//Return the range of the tower
	return range;
}

int Turret::get_damage()
{
	//Return the damage of the tower
	return damage;
}

double Turret::get_cooldown()
{
	//Return the cooldown of the tower
	return cooldown;
}

int Turret::get_x()
{
	//Return the x position of the tower
	return x;
}

int Turret::get_y()
{
	//Return the y position of the turret
	return y;
}

int Turret::get_cost_upgrade()
{
	//Return the cost to upgrade the tower
	return cost_upgrade;
}

int Turret::get_level()
{
	//Returns the level of upgrade to the tower
	//TODO: Determine the max level a tower can be upgraded
	return level;
}

