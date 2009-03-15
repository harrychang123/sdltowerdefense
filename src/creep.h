//Author: CoreyRuda, CPress.Scott
//Filename: creep.h
//This is the creep class

#ifndef CREEP_H
#define CREEP_H

#ifndef _WIN32
	#include "SDL/SDL.h"
	#include "SDL/SDL_image.h"
#else
	#include "SDL.h"
	#include "SDL_image.h"
#endif

class Creep
{
private:
	int hit_points; //How much damage a creep can take
	int creep_type; //Type of Creep
	int move_speed; //How many pixels the creep can move per render
	int cooldown;   //How many frames the creep has to wait before moving
	int defense;    //How much damage is reduced from tower damage
	bool ground;    //Is the creep a ground unit or air unit
	bool dead;		//true if the creep is dead
	int prize;      //How much the creep gives when killed
	int xpos;       //X position of the creep
	int ypos;       //Y position of the creep
	int frame;      //What frame of animation the creep is on
	int creep_id;   //The Creeps ID
	int face;       //This is the direction the creep is facing
	bool slowed;      //Determines if the creep is slowed or not

public:
	//Class Constructor
	Creep(int,int,int,int,int,int,bool,int);

	//Getter function prototypes
	int get_hp();
	int get_move();
	int get_defense();
	int get_prize();
	int get_type();
	bool get_ground();
	bool is_dead();
	int get_x();
	int get_y();
	int get_frame();
	int get_cooldown();
	int get_id();

	//Setter Function prototypes
	void set_hp(int);
	void set_move(int);
	void set_defense(int);
	void set_prize(int);
	void set_type(int);
	void set_ground(bool);
	void set_x(int);
	void set_y(int);
	void set_cooldown(int);
	void die();

	//Member Functions
	void move(int);
	void show(int,int,SDL_Surface*,SDL_Surface*,SDL_Rect*);
	void slow();

};
#endif /*CREEP_H*/
