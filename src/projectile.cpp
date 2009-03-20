/*
 * projectile.cpp
 *
 *  Created on: Mar 12, 2009
 *      Author: CPress.Scott
 */

#include "projectile.h"
#include "functions.h"
#include "creep.h"

Projectile::Projectile()
{
	x=0;
	y=0;
	speed=0;
	parent_tower=0;
	type=0;
	damage=0;
	splash_damage=0;
	splash_range=0;
	disabled=false;
	ptr_target=NULL;
	accelerate=false;
}

Projectile::Projectile(double px, double py, double pspeed, Creep* ptarget)
{
	x = px;
	y = py;
	ptr_target = ptarget;
	speed = pspeed;
	parent_tower=0;
	type=0;
	damage=0;
	splash_damage=0;
	splash_range=0;
	accelerate=false;
	disabled=false;
}

Projectile::Projectile(int px, int py, double pspeed, Creep* ptarget)
{
	x = (double)px;
	y = (double)py;
	ptr_target = ptarget;
	speed = pspeed;
	parent_tower=0;
	type=0;
	damage=0;
	splash_damage=0;
	splash_range=0;
	accelerate=false;
	disabled=false;
}

int Projectile::get_x()
{
	//Returns the current x position
	return (int)x;
}

int Projectile::get_y()
{
	//Returns the current y position
	return (int)y;
}

double Projectile::get_speed()
{
	//Returns the current speed
	return speed;
}

int Projectile::get_parent()
{
	//Returns the ID of the parent tower
	return parent_tower;
}

int Projectile::get_type()
{
	//Returns the type of projectile
	return type;
}

int Projectile::get_damage()
{
	//Returns the damage
	return damage;
}

int Projectile::get_splash_damage()
{
	//Returns the splash damage
	return splash_damage;
}

int Projectile::get_splash_range()
{
	//Returns the splash range
	return splash_range;
}

Creep* Projectile::get_target()
{
	//Returns the creep_id of the target
	return ptr_target;
}

bool Projectile::does_accelerate()
{
	//Returns true if the projectile accelerates as it moves
	return accelerate;
}

void Projectile::set_x(int a)
{
	//Sets the x position
	x = (double)a;
}

void Projectile::set_y(int a)
{
	//Sets the y position
	y = (double)a;
}

void Projectile::set_speed(double a)
{
	//Sets the current speed
	speed = a;
}

void Projectile::set_parent(int a)
{
	//Sets the parent tower ID
	parent_tower = a;
}

void Projectile::set_type(int a)
{
	//Sets the type of projectile
	type = a;
}

void Projectile::set_damage(int a)
{
	//Sets the damage
	damage = a;
}

void Projectile::set_splash_damage(int a)
{
	//Sets the splash damage
	splash_damage = a;
}
void Projectile::set_splash_range(int a)
{
	//Sets the splash range
	splash_range = a;
}

void Projectile::set_accelerate(bool param)
{
	//Sets the accelerate value (whether or not projectile accelerates)
	accelerate = param;
}

void Projectile::set_ptr(Creep* a)
{
	//Sets the pointer that points to the target Creep
	ptr_target = a;
}

void Projectile::set_target_id(int param)
{
	//Sets the creep_id of the target
	target_id = param;
}

void Projectile::collide()
{
	//Collide with the target
	if(!is_disabled())
	{
		if(ptr_target->is_dead())
		{//target is already dead, do nothing
			disable();
		} else {
			//TODO: Add Splash Damage
			ptr_target->set_hp(ptr_target->get_hp()-damage);
			if(ptr_target->get_hp() <= 0)
			{
				ptr_target->die();
			}
			disable();
		}
	}
}

void Projectile::move()
{
	//Moves the projectile towards the target
	if(!is_disabled())
	{
		if(!ptr_target->is_dead())
		{
			int tar_x=0, tar_y=0; 		//target position
			double unit_x=0, unit_y=0; 	//unit vector x, y (A unit vector is a vector of length 1.0)
			double dist = 0.0;

			tar_x = ptr_target->get_x()+10;
			tar_y = ptr_target->get_y()+10;

			//make a unit vector
			dist = distance(tar_x, x, tar_y, y);
			unit_x = (tar_x - x) / dist;
			unit_y = (tar_y - y) / dist;

			//If we're supposed to accelerate
			//TODO: Tweak the acceleration rate (possibly make a variable to hold the rate)
			if(accelerate)
				speed *= 1.05;

			if(dist<=speed)
			{//Projectile should collide with the creep on this frame
				x = tar_x;
				y = tar_y;
				collide();
			} else {
				//Projectile will not collide with the creep on this frame
				//multiply unit vector by projectile's speed
				unit_x *= speed;	//if the speed is 5, then the projectile moves 5 units total
				unit_y *= speed;
				x += unit_x;
				y += unit_y;
			}
		} else {
			disable();
		}
	}
}

void Projectile::disable()
{
	//Disables the projectile
	disabled = true;
	ptr_target = NULL;
}

bool Projectile::is_disabled()
{
	//Returns true if the projectile is disabled
	if(!disabled)
	{
		//Check to see if our target is still in the creep array
		if(!creep_in_array(target_id))
		{
			disabled = true;
			ptr_target = NULL;
			return disabled;
		}
		if(ptr_target->get_hp() <= 0)
		{
			ptr_target->die();
		}
		if(ptr_target->is_dead())
		{
			disabled = true;
			ptr_target = NULL;
		}
	}
	return disabled;
}
