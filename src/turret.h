//Author: CoreyRuda, CPress.Scott
//Filename: turret.h
//This is the Turret Class

#ifndef TURRET_H
#define TURRET_H

class Turret
{
private:
	int x;           //This is the turrets x position
	int y;           //This is the turrets y position
	int cost;        //This is how much the turret costs
	int cost_upgrade;//This is how much it is to upgrade the tower
	int level;       //this is how upgraded the tower is
	int range;       //This is how far the turret can shoot, TODO: determine pixel per int
	int damage;      //How much damage the turret will do to a creep
	double cooldown; //This is how long the tower has to wait before shooting again

public:
	//Class Turret prototypes
	//Constructor
	Turret(int,int,int,int,int,int,double);

	//Get functions
	int get_cost();
	int get_range();
	int get_damage();
	double get_cooldown();
	int get_x();
	int get_y();
	int get_cost_upgrade();
	int get_level();

	//Set functions
	void set_cost(int);
	void set_range(int);
	void set_damage(int);
	void set_cooldown(double);
	void set_x(int);
	void set_y(int);
	void set_up_cost(int);
	void upgrade();
};

#endif /* TURRET_H */
