//Author: Corey Ruda
//Filename: creep.h
//This is the creep class

#ifndef CREEP_H
#define CREEP_H

class Creep
{
private:
	int hit_points; //How much damage a creep can take
	int creep_type; //Type of Creep
	int move_speed; //How fast the creep moves
	int defense;    //How much damage is reduced from tower damage
	bool ground;    //Is the creep a ground unit or air unit
	int prize;      //How much the creep gives when killed

public:
	//Class Constructor
	Creep(int,int,int,bool,int);

	//Getter function prototypes
	int get_hp();
	int get_move();
	int get_defense();
	int get_prize();
	int get_type();
	bool get_ground();

	//Setter Function prototypes
	void set_hp(int);
	void set_move(int);
	void set_defense(int);
	void set_prize(int);
	void set_type(int);
	void set_ground(bool);

};
#endif /*CREEP_H*/
