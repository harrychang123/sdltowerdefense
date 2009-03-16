//============================================================================
// Name        : sdltowerdefense.cpp
// Authors     : CoreyRuda, CPress.Scott
// Version     : 0.0.1
// Copyright   :
// Description : sdlTD Main File
//============================================================================

#ifndef _WIN32
	#include "SDL/SDL.h"
	#include "SDL/SDL_image.h"
#else
	#include "SDL.h"
	#include "SDL_image.h"
#endif

/* Include Files for sdlTD*/
#include <iostream>
#include <vector>
#include "functions.h"
#include "constants.h"
#include "turret.h"
#include "creep.h"
#include "timer.h"
#include "projectile.h"

/* Namespaces */
using namespace std;

//Function Prototypes
bool load_files();
bool init();
void clean_up();
void creep_clips();
void set_creep_clip(int,int,int);

/*Global Variables*/
//The Screens pointers
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *sidebar = NULL;
SDL_Surface *blank_surface = NULL;//used for creating 25x25 sprite blits (formats surface)

//Creep Arrays
SDL_Rect creep_sprite_offsets[CREEP_NUM][16];
SDL_Surface *creep_sprites[CREEP_NUM];
vector<Creep> creeps;

//Turret Array
SDL_Surface *turret_sprites[TURRET_NUM][3];
SDL_Surface *turret_projectiles[TURRET_NUM];
vector<Turret> turrets;
vector<Projectile> projectiles;

//FPS Regulator
Timer fps;

//Event structure
SDL_Event event;

int main(int argc, char* args[]) {
	bool quit = false;

	//Initialize
	if(init() == false)
		return 1;

	//Load the files
	if(load_files() == false)
		return 1;

	//Set the creeps clips
	creep_clips();

	//Initialize test objects
	//int x_pos,int y_pos,int tcost,int cost_up,int trange,int tdamage,double tcooldown
	Turret tmp(365, 157, 50, 0, 275, 1, 250.0);
	Creep ctmp(261,442, 30, 2,5, 0, false, 3);
	creeps.push_back(ctmp);
	turrets.push_back(tmp);

	//Set default direction
	int direction = CREEP_NORTH;

	//The main loop.
	while(quit == false)
	{
		//Starts FPS management
		fps.start();

		/**************************************************************************
		 EVENTS
		*************************************************************************/
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) //If the user Xs out, quit
				quit = true;
			//If a mouse button was pressed
			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				//If the left mouse button was pressed
				if(event.button.button == SDL_BUTTON_LEFT)
				{//Get the mouse offsets
					Point action;
					action = check_click(event.button.x, event.button.y);

					//TODO: Fix how a creep is slowed down
					//Testing Creep Slowed
					//creeps.at(0).slow();


					cout << action.x << " " << action.y  << " " << endl;//Outputs coords to screen!

					/*TODO: Check to see if any towers are here, or if we are placing a
					        tower.  Offload this to a function. */

				}
			}
			if(event.type == SDL_MOUSEMOTION)
			{
				//TODO: Take this out.  It is temporary to test projectiles (Creates a projectile at mouse everytime it moves)
				Projectile tmp_proj(event.motion.x, event.motion.y, 1.0, &creeps.at(0));
				tmp_proj.set_damage(1);
				projectiles.push_back(tmp_proj);

			}
		}
		/***************************************************************************
		 LOGIC
		***************************************************************************/
		//TODO: Add Logic Code

		for(int i=0; i < (signed int)creeps.size(); i++)
			creeps.at(i).move(direction);//calls the add_frame function in Creeps

		//Move the projectiles
		if(projectiles.size()>=1)//Out-of-bounds error if we don't check the size
		{
			for(int proj=0; proj < (signed int) projectiles.size(); proj++)
			{
				if(projectiles.at(proj).is_disabled())
				{
					//Delete this projectile
					projectiles.erase(projectiles.begin() + proj);
				} else {
					projectiles.at(proj).move();
				}
			}
		}

		if(creeps.size()>=1)
		{
			if(turrets.size()>=1)
			{
				for(int l_t=0; l_t<(signed int)turrets.size(); l_t++)
				{//Loops through turrets
					for(int l_c=0; l_c<(signed int)creeps.size(); l_c++)
					{//Loops through creeps
						if(turrets.at(l_t).in_range(&creeps.at(l_c)))
						{//Creep is in range of this tower
							//Fire a projectile!
							if(turrets.at(l_t).cooldown_is_up())
							{//If the cooldown is up
								Projectile tmp_proj(turrets.at(l_t).get_x()+10, turrets.at(l_t).get_y()+10, 12.0, &creeps.at(l_c));
								tmp_proj.set_damage(1);
								projectiles.push_back(tmp_proj);
							}
						}
					}
				}
			}
		}

		/***************************************************************************
		RENDERING
		***************************************************************************/
		//TODO: Add Rendering Code
		apply_surface(0, 0, background, screen);

		for(int i=0; i<(signed int)turrets.size(); i++)
		{
			apply_surface(turrets.at(i).get_x(), turrets.at(i).get_y(), turret_sprites[0][0], screen);
		}

		//Loops through each creep in the creep vector and renders it
		//TODO:Figure out why i cant add more then one creep on screen
		for(int i = 0; i < (signed int)creeps.size();i++)
		{
			creeps.at(i).show(creeps.at(i).get_x(),creeps.at(i).get_y(),creep_sprites[i],screen,&creep_sprite_offsets[i][creeps.at(i).get_frame()]);
			if(creeps.at(i).get_y() < -24)
			{
				creeps.at(i).set_y(SCREEN_HEIGHT);
			}
		}

		//Draw the projectiles
		if(projectiles.size()>=1)//Out-of-bounds error if we don't check the size of the array
		{
			for(int pr=0; pr < (signed int) projectiles.size(); pr++)
			{
				//If not disabled
				if(!projectiles.at(pr).is_disabled())
					apply_surface(projectiles.at(pr).get_x(), projectiles.at(pr).get_y(), turret_projectiles[projectiles.at(pr).get_type()], screen);
			}
		}

		//Draw the sidebar last
		apply_surface(SCREEN_WIDTH-35, 0, sidebar, screen);

		//Update the screen.
		if(SDL_Flip(screen)==-1)
			return 1;

		//Regulate the Frames Per SEcond(FPS = 30 Cap)
		if((fps.get_ticks() < 1000 / FRAMES_PER_SECOND))
		{
			//Delay the frames
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
		}
	}

	clean_up();
	return 0;
}

bool load_files()
{//Load the files needed for the program

	background = load_image("background.bmp");
	sidebar = load_image("sidebar.bmp");


	//load the first turret
	blank_surface = load_image("blank.bmp");
	turret_sprites[0][0] = load_image("turret1.bmp");

	//This loop loads the turret sprite sheet, and then loads each sprite into the turret_sprites array
	SDL_Surface *turret_sprite_sheet = NULL;
	turret_sprite_sheet = load_image("turret_sprite.bmp");
	for(int a=0; a<TURRET_NUM; a++)
	{
		for(int b=0; b<3; b++)
		{
			SDL_Surface *tmp = NULL;
			SDL_Rect myRect;
			myRect.x=b*25;
			myRect.y=a*25;
			myRect.h=25;
			myRect.w=25;
			tmp = blank_surface;//make it 25x25, and formatted.
			apply_surface(0, 0, turret_sprite_sheet, turret_sprites[a][b], &myRect);
		}
	}


	turret_projectiles[0] = load_image("turret1_projectile.bmp");


	//TODO: Clean this up and make it work for more than 1 creep
	//load Creep #1
	//TODO: Store creep spritesheet filenames in an array
		creep_sprites[0] = load_image("creep1.bmp");

	//Split this up into a 4x4 25px x 25px
	SDL_Rect tmpRect;
	int tmp_x=0, tmp_y=0;
	for(int i=0; i<4; i++)
	{//row
		tmp_x=i*25;
		for(int j=0; j<4; j++)
		{//col
			tmp_y=j*25;
			tmpRect.x=j;
			tmpRect.y=i;
			tmpRect.w=25;
			tmpRect.h=25;
			creep_sprite_offsets[0][j+4*i] = tmpRect;//Store the offsets in the array
		}
	}
    if(background == NULL)
        return false;
    return true;
}

bool init()
{
    //Initialize all SDL subsystems
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return false;

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    if(screen == NULL)
        return false;

    SDL_WM_SetCaption(GAME_CAPTION.c_str(), NULL);
    return true;
}

void clean_up()
{//Delete all used surfaces
	SDL_FreeSurface(screen);
}

//Sets the clips for the creep
void creep_clips()
{
	//Local Variable
	int row = 0;
	//For int i to creep number
	for(int i = 0;i < CREEP_NUM; i++)
	{
		//Set the Creeps sprite int the SDL_RECT based on the creeps number
		for(int n = 0;n < 4;n++) //Loops throught the frames
		{
			set_creep_clip(i,n,row);
		}
		row++;
	}
}


void set_creep_clip(int creep,int sprite,int row)
{
	//TODO: Find a better way to set up these sprite clips
	//Set the first row of clips
	//(Facing North)
	creep_sprite_offsets[creep][0].x = 0;
	creep_sprite_offsets[creep][0].y = 0;
	creep_sprite_offsets[creep][0].w = CREEP_WIDTH;
	creep_sprite_offsets[creep][0].h = CREEP_HEIGHT;

	creep_sprite_offsets[creep][1].x = CREEP_WIDTH;
	creep_sprite_offsets[creep][1].y = 0;
	creep_sprite_offsets[creep][1].w = CREEP_WIDTH;
	creep_sprite_offsets[creep][1].h = CREEP_HEIGHT;

	creep_sprite_offsets[creep][2].x = CREEP_WIDTH*2;
	creep_sprite_offsets[creep][2].y = 0;
	creep_sprite_offsets[creep][2].w = CREEP_WIDTH;
	creep_sprite_offsets[creep][2].h = CREEP_HEIGHT;

	creep_sprite_offsets[creep][3].x = CREEP_WIDTH*3;
	creep_sprite_offsets[creep][3].y = 0;
	creep_sprite_offsets[creep][3].w = CREEP_WIDTH;
	creep_sprite_offsets[creep][3].h = CREEP_HEIGHT;

	creep_sprite_offsets[creep][4].x = 0;
	creep_sprite_offsets[creep][4].y = CREEP_HEIGHT;
	creep_sprite_offsets[creep][4].w = CREEP_WIDTH;
	creep_sprite_offsets[creep][4].h = CREEP_HEIGHT;

	creep_sprite_offsets[creep][5].x = CREEP_WIDTH;
	creep_sprite_offsets[creep][5].y = CREEP_HEIGHT;
	creep_sprite_offsets[creep][5].w = CREEP_WIDTH;
	creep_sprite_offsets[creep][5].h = CREEP_HEIGHT;

	creep_sprite_offsets[creep][6].x = CREEP_WIDTH*2;
	creep_sprite_offsets[creep][6].y = CREEP_HEIGHT;
	creep_sprite_offsets[creep][6].w = CREEP_WIDTH;
	creep_sprite_offsets[creep][6].h = CREEP_HEIGHT;

	creep_sprite_offsets[creep][7].x = CREEP_WIDTH*3;
	creep_sprite_offsets[creep][7].y = CREEP_HEIGHT;
	creep_sprite_offsets[creep][7].w = CREEP_WIDTH;
	creep_sprite_offsets[creep][7].h = CREEP_HEIGHT;

}
