/*
 * projectile.h
 *
 *  Created on: Mar 12, 2009
 *      Author: CPress.Scott
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "creep.h"

class Projectile
{
	int x;					//x position
	int y;					//y position
	double speed;			//Projectile's speed
	int parent_tower;		//The ID of the tower that launched this projectile
	int type;				//The type of projectile
	int damage;				//Amount of damage done to target
	int splash_damage;		//Splash damage done to any targets in splash_range radius
	int splash_range;		//Radius around the projectile's intended target where any other targets inside take damage
	bool disabled;			//True if this projectile is disabled (will be removed from array in main on next loop)
	bool accelerate;		//True if this projectile should accelerate while moving
	Creep *ptr_target;		//Pointer to target

public:
	Projectile();						//Standard constructor.  We probably won't use this.
	Projectile(int, int, double, Creep*);  			//Our custom constructor for Projectiles
	Projectile(double, double, double, Creep*);  	//Our custom constructor for Projectiles (preferred)
	int get_x();						//Returns the x position
	int get_y();						//Returns the y position
	double get_speed();					//Returns the current speed of the projectile
	int get_parent();					//Returns the ID of the tower that launched this projectile
	int get_type();						//Returns the type of tower
	int get_damage();					//Returns the amount of regular damage
	int get_splash_damage();			//Returns the amount of splash damage
	int get_splash_range();				//Returns the splash range of the projectile
	int get_target();					//return the creep_id of the target
	bool is_disabled();					//Is the projectile disabled?
	bool does_accelerate();				//Does the projectile accelerate as it moves?

	void set_x(int);					//Sets the x position
	void set_y(int);					//Sets the y position
	void set_speed(double);				//Sets the speed
	void set_parent(int);				//Sets the ID of the parent tower
	void set_type(int);					//Sets the type of projectile
	void set_damage(int);				//Sets the normal damage
	void set_splash_damage(int);		//Sets the splash damage
	void set_splash_range(int);			//Sets the splash range
	void set_ptr(Creep*);				//Sets the pointer to the target creep
	void set_accelerate(bool);			//Sets whether or not projectile accelerates
	void collide();						//Collide with target creep
	void move();						//Move the creep (and do everything else moving related)
	void disable();						//Disable this projectile (will cause it to be removed from projectiles array in main)
};

#endif /* PROJECTILE_H_ */
