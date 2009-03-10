//Author: Corey Ruda
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
void upgrade()
{
	//Set the level of the tower
	level += 1;
}

void set_up_cost(int num)
{
	//Set the cost to upgrade the tower
	cost_upgrade = num;
}

void set_y(int num)
{
	//Set the y value of the turret's position
	y = num;
}

void set_x(int num)
{
	//Set the x value of the turret's position
	x = num;
}

void set_cooldown(double num)
{
	//Set the cooldown of the tower
	cooldown = num;
}

void set_cost(int num)
{
	//Sets the cost of the tower
	cost = num;
}

void set_range(int num)
{
	//Sets the range of the tower
	//TODO: Determine how many pixels per int
	range = num;
}

void set_damage(int num)
{
	//Sets the damage the tower can do
	damage = num;
}

/*****************************************************************************
Getter Functions
******************************************************************************/

int get_cost()
{
	//Return the cost of the tower
	return cost;
}

int get_range()
{
	//Return the range of the tower
	return range;
}

int get_damage()
{
	//Return the damage of the tower
	return damage;
}

double get_cooldown()
{
	//Return the cooldown of the tower
	return cooldown;
}

int get_x()
{
	//Return the x position of the tower
	return x;
}

int get_y()
{
	//Return the y position of the turret
	return y;
}

int get_cost_upgrade()
{
	//Return the cost to upgrade the tower
	return cost_upgrade;
}

int get_level()
{
	//Returns the level of upgrade to the tower
	//TODO: Determine the max level a tower can be upgraded
	return level;
}
