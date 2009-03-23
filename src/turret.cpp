//Author: CoreyRuda, CPress.Scott
//Filename: turret.cpp
//This is the Turret Class Functions
//TODO: Determine the max level that a tower can be upgraded to

#include "turret.h"
#include "constants.h"
#include "functions.h"

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
	splash_damage = 0;
	splash_range = 0;
	projectile_speed = 0;
}

Turret::Turret()
{
	//Don't use this
	x = 0;
	y = 0;
	cost = 0;
	cost_upgrade = 0;
	range = 0;
	damage = 0;
	cooldown = 0;
	level = 1;
	splash_damage = 0;
	splash_range = 0;
	projectile_speed = 0;
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

void Turret::set_type(int num)
{
	//Sets the type of tower
	type = num;
}

void Turret::set_range(int num)
{
	//Sets the range of the tower
	//TODO: Determine how many pixels per int
	range = num;
}

void Turret::set_pspeed(double num)
{
	//Sets the speed of projectiles launched by this turret
	projectile_speed = num;
}

void Turret::set_damage(int num)
{
	//Sets the damage the tower can do
	damage = num;
}

void Turret::set_splash_damage(int num)
{
	//Sets the amount of splash damage (0 if no splash)
	splash_damage = num;
}

void Turret::set_splash_range(int num)
{
	//Sets the range of the splash damage
	splash_range = num;
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

int Turret::get_type()
{
	//Returns the type of the tower
	return type;
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

int Turret::get_splash_damage()
{
	//Returns the amount of splash damage
	return splash_damage;
}

int Turret::get_splash_range()
{
	//Returns the range of the splash damage
	return splash_range;
}

double Turret::get_pspeed()
{
	//Returns the speed of projectiles launched by this turret
	return projectile_speed;
}

bool Turret::in_range(Creep* param)
{
	//Returns true if the creep is in the tower's range
	if(sqrt(pow(param->get_x()-x, 2)+pow(param->get_y()-y, 2)) <= range)


		return true;	//In range
	return false;		//Not in range
}

bool Turret::cooldown_is_up()
{
	//Returns true if the cooldown is up
	if(cooldown_remaining>=0.0)
	{
		return false;
	} else {
		cooldown_remaining = cooldown;
		return true;
	}
}

void Turret::update_cooldown()
{
	//Updates the cooldown_remaining
	cooldown_remaining-=1000.0/FRAMES_PER_SECOND;
}

