//Author: CoreyRuda, CPress.Scott
//Filename: turret.h
//This is the Turret Class

#ifndef TURRET_H
#define TURRET_H

#include "creep.h"
#include <math.h>

class Turret
{
private:
	int x;           //This is the turrets x position
	int y;           //This is the turrets y position
	int cost;        //This is how much the turret costs
	int cost_upgrade;//This is how much it is to upgrade the tower
	int level;       //this is how upgraded the tower is
	int type;		 //The type of tower
	int range;       //This is how far the turret can shoot, TODO: determine pixel per int
	int damage;      //How much damage the turret will do to a creep
	int splash_damage;//How much splash damage the turret does
	int splash_range;//The range of the splash
	bool accelerate; //Do the turret's projectiles accelerate?
	double projectile_speed; //The speed of projectiles launched by this turret
	double cooldown_remaining;	//This is how much time the cooldown has remaining
	double cooldown; //This is how long the tower has to wait before shooting again

public:
	//Class Turret prototypes
	//Constructor
	Turret(int,int,int,int,int,int,double);
	Turret();

	//Get functions
	int get_cost();
	int get_range();
	int get_damage();
	double get_cooldown();
	double get_pspeed();
	int get_x();
	int get_y();
	int get_cost_upgrade();
	int get_level();
	int get_type();
	int get_splash_damage();
	int get_splash_range();
	bool does_accelerate();

	//Set functions
	void set_cost(int);
	void set_range(int);
	void set_damage(int);
	void set_cooldown(double);
	void set_pspeed(double);
	void set_type(int);
	void set_x(int);
	void set_y(int);
	void set_up_cost(int);
	void set_splash_damage(int);
	void set_splash_range(int);
	void set_accelerate(bool);

	//Functions
	void upgrade();
	void update_cooldown();
	bool in_range(Creep*);
	bool cooldown_is_up();	//Returns true if the cooldown is up
};

#endif /* TURRET_H */
