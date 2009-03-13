/*
 * projectile.cpp
 *
 *  Created on: Mar 12, 2009
 *      Author: scott
 */

#include "projectile.h"

int Projectile::get_x()
{
	return x;
}

int Projectile::get_y()
{
	return y;
}

int Projectile::get_speed()
{
	return speed;
}

int Projectile::get_parent()
{
	return parent_tower;
}

int Projectile::get_type()
{
	return type;
}

int Projectile::get_damage()
{
	return damage;
}

int Projectile::get_splash_damage()
{
	return splash_damage;
}

int Projectile::get_splash_range()
{
	return splash_range;
}

int Projectile::get_target()
{
	return target;
}

void Projectile::set_x(int a)
{
	x = a;
}

void Projectile::set_y(int a)
{
	y = a;
}

void Projectile::set_speed(int a)
{
	speed = a;
}

void Projectile::set_parent(int a)
{
	parent_tower = a;
}

void Projectile::set_type(int a)
{
	type = a;
}

void Projectile::set_damage(int a)
{
	damage = a;
}

void Projectile::set_splash_damage(int a)
{
	splash_damage = a;
}
void Projectile::set_splash_range(int a)
{
	splash_range = a;
}

void Projectile::set_target(int a)
{
	target = a;
}

void Projectile::set_ptr(Creep* a)
{
	ptr_target = a;
}

void Projectile::move()
{//Moves the projectile towards the target
	int tar_x=0, tar_y=0; //target position
	tar_x = ptr_target->get_x();
	tar_y = ptr_target->get_y();

	//make a unit vector

}
