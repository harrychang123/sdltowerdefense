/*
 * projectile.h
 *
 *  Created on: Mar 12, 2009
 *      Author: scott
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "creep.h"

class Projectile
{
	int x;					//x position
	int y;					//y position
	int speed;				//Projectile's speed
	int parent_tower;		//The ID of the tower that launched this projectile
	int type;				//The type of projectile
	int damage;				//Amount of damage done to target
	int splash_damage;		//Splash damage done to any targets in splash_range radius
	int splash_range;		//Radius around the projectile's intended target where any other targets inside take damage
	int target;				//Creep ID
	Creep *ptr_target;		//Pointer to target

public:
	Projectile();
	int get_x();
	int get_y();
	int get_speed();
	int get_parent();
	int get_type();
	int get_damage();
	int get_splash_damage();
	int get_splash_range();
	int get_target();

	void set_x(int);
	void set_y(int);
	void set_speed(int);
	void set_parent(int);
	void set_type(int);
	void set_damage(int);
	void set_splash_damage(int);
	void set_splash_range(int);
	void set_target(int);
	void set_ptr(Creep*);
	void move();
};

#endif /* PROJECTILE_H_ */
