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
#include "button.h"

/* Namespaces */
using namespace std;

//Function Prototypes
bool load_files();
bool init();
void clean_up();
void creep_clips();
void set_creep_clip(int,int,int);
bool creep_in_array(int);

/*Global Variables*/
//The Screens pointers
SDL_Surface *background 	= NULL;
SDL_Surface *screen 		= NULL;
SDL_Surface *sidebar 		= NULL;//sidebar for letting user buy towers
SDL_Surface *toolbar		= NULL;//toolbar for displaying info/upgrades
SDL_Surface *blank_surface 	= NULL;//used for creating 25x25 sprite blits (formats surface)
SDL_Surface *border  		= NULL;//border (27x27) to draw around turrets
vector<Creep> *CREEP_PTR 	= NULL;//global pointer to creeps array
vector<Turret> *TURRET_PTR 	= NULL;//global pointer to turrets array

//Creep Arrays
SDL_Rect creep_sprite_offsets[CREEP_NUM][16];
SDL_Surface *creep_sprites[CREEP_NUM];
vector<Creep> creeps;
vector<Creep> *creep_ptr;

//Turret Array
SDL_Surface *turret_sprites[TURRET_NUM][3];
SDL_Surface *turret_projectiles[TURRET_NUM];
vector<Turret> turrets;
vector<Projectile> projectiles;

//Button Array
vector<Button> buttons;

//FPS Regulator
Timer fps;

//Event structure
SDL_Event event;

int main(int argc, char* args[]) {
	bool quit = false;
	bool draw_border = false;
	Point border_pt;

	//Initialize
	if(init() == false)
		return 1;

	//Load the files
	if(load_files() == false)
		return 1;

	//Set up Menu
	Button tmp_button(SCREEN_WIDTH-30, 5, 25, 25, turret_sprites[0][0], turret_sprites[0][1], turret_sprites[0][2]);
	Button tmp_button2(SCREEN_WIDTH-30, 30, 25, 25, turret_sprites[1][0], turret_sprites[1][1], turret_sprites[1][2]);
	buttons.push_back(tmp_button);
	buttons.push_back(tmp_button2);


	//Set the creeps clips
	creep_clips();
	CREEP_PTR = &creeps;
	TURRET_PTR = &turrets;

	//Initialize test objects
	//int x_pos,int y_pos,int tcost,int cost_up,int trange,int tdamage,double tcooldown
	Turret tmp(365, 157, 50, 0, 275, 1, 250.0);
	Turret tmp2(209, 157, 30, 0, 275, 1, 125.0);
	tmp.set_type(0);
	tmp2.set_type(1);
	//Creep ctmp(261,442, 30, 2,5, 0, false, 3);
	//creeps.push_back(ctmp);
	turrets.push_back(tmp);
	turrets.push_back(tmp2);

	//Set default direction
	int direction = CREEP_NORTH;

	//Gamestate
	//bool spawning = true;
	int time = 0;
	//int *time_ptr = &time;

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

					//Check to see if any towers are here, or if we are placing a tower.
					if(is_tower_here(action))
					{//There is already a tower here.
						//TODO: Select this tower & cancel the 'place tower' process if it was initiated
						cout << "A Tower already exists at " << action.x << "," << action.y << "." << endl;
						draw_border = true;
						border_pt.x = action.x-1;
						border_pt.y = action.y-1;

					} else {
						/*TODO: If placing a tower, check to see if we have enough money.
						 * 		If we do, then subtract the cost from our money, and then
						 * 		place the tower at 'action'.
						 */
						cout << "No Tower exists at " << action.x << "," << action.y << "." << endl;
						draw_border = false;
						if(buttons.size()>=1)
						{
							for(int l_b=0; l_b < (signed int)buttons.size(); l_b++)
							{
								if(buttons.at(l_b).is_button(event.button.x, event.button.y))
								{
									buttons.at(l_b).set_down();
									//TODO: Do w/e this button is supposed to do.
								}
							}
						}

					}

				}
			}
			if(event.type == SDL_MOUSEBUTTONUP)
			{
				if(buttons.size()>=1)
				{
					for(int l_bu=0; l_bu < (signed int)buttons.size(); l_bu++)
					{
						if(buttons.at(l_bu).is_button(event.button.x, event.button.y))
						{
							buttons.at(l_bu).set_highlight();
						}
					}
				}
			}
			if(event.type == SDL_MOUSEMOTION)
			{
				if(buttons.size()>=1)
				{
					for(int l_but=0; l_but < (signed int)buttons.size(); l_but++)
					{
						if(buttons.at(l_but).is_button(event.motion.x, event.motion.y))
						{
							buttons.at(l_but).set_highlight();
						} else {
							buttons.at(l_but).set_up();
						}
					}
				}
			}
		}
		/***************************************************************************
		 LOGIC
		***************************************************************************/

		if(time == 0)
		{
			//Spawn a creep
			Creep temp(261,442,300,2,5,0,false,3,0);
			creeps.push_back(temp);
			time = 120;
		}
		time--;


		if(creeps.size() >= 1)
		{
			for(int i=0; i < (signed int)creeps.size(); i++)
				creeps.at(i).move(direction);//calls the add_frame function in Creeps
		}

		//Move the projectiles
		if(creeps.size() >= 1)
		{
			for(int i=0; i < (signed int)creeps.size();i++)
			{
				if(creeps.at(i).is_dead())
					creeps.erase(creeps.begin()+i);
			}
		}

		if(projectiles.size()>=1)//Out-of-bounds error if we don't check the size
		{
			for(int proj=0; proj < (signed int) projectiles.size(); proj++)
			{
				if(!projectiles.at(proj).is_disabled())
					projectiles.at(proj).move();
			}
			for(int f=projectiles.size()-1; f>-1; f--)
			{
				//Delete this projectile
				if(projectiles.at(f).is_disabled())
					projectiles.erase(projectiles.begin() + f);
			}
		}


		//Creates projectiles
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
								tmp_proj.set_damage(10);
								tmp_proj.set_target_id(creeps.at(l_c).get_id());
								tmp_proj.set_type(turrets.at(l_t).get_type());
								projectiles.push_back(tmp_proj);
							}
						}
					}
					turrets.at(l_t).update_cooldown();
				}
			}
		}

		//Determine what creeps are still alive. if dead, remove from the vector
		if(creeps.size() >= 1)
		{
			for(int i=0; i < (signed int)creeps.size();i++)
			{
				if(creeps.at(i).is_dead())
				{
					if(projectiles.size()>=1)
					{//check to see if there are any projectiles pointing to this creep
						for(int a_p=0; a_p<(signed int)projectiles.size(); a_p++)
						{
							if(projectiles.at(a_p).get_target()==&creeps.at(i))
							{
								projectiles.at(a_p).disable();
							}
						}
					}
					creeps.erase(creeps.begin()+i);
				}
			}
		}

		/***************************************************************************
		RENDERING
		***************************************************************************/
		apply_surface(0, 0, background, screen);

		for(int i=0; i<(signed int)turrets.size(); i++)
		{
			apply_surface(turrets.at(i).get_x(), turrets.at(i).get_y(), turret_sprites[turrets.at(i).get_type()][0], screen);
		}

		//Draw the selection border
		if(draw_border)
		{
			apply_surface(border_pt.x, border_pt.y, border, screen);
		}

		//Loops through each creep in the creep vector and renders it
		if(creeps.size() >= 1)
		{
			for(int i = 0; i < (signed int)creeps.size();i++)
			{
				creeps.at(i).show(creeps.at(i).get_x(),creeps.at(i).get_y(),creep_sprites[0],screen,&creep_sprite_offsets[0][creeps.at(i).get_frame()]);

				//If the creep reaches the edge, send it back to the bottom
				if(creeps.at(i).get_y() < -24)
				{
					creeps.at(i).set_y(SCREEN_HEIGHT-90);
				}
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

		//Draw the sidebar/toolbar
		apply_surface(SCREEN_WIDTH-35, 0, sidebar, screen);
		apply_surface(0, SCREEN_HEIGHT-90, toolbar, screen);

		//Draw buttons last
		if(buttons.size() >= 1)
		{
			for(int i_b=0; i_b < (signed int)buttons.size(); i_b++)
			{
				if(buttons.at(i_b).is_down() == 0)
				{
					//Button is up
					apply_surface(buttons.at(i_b).get_x(), buttons.at(i_b).get_y(), buttons.at(i_b).image, screen);
				} else if(buttons.at(i_b).is_down() == 1)
				{
					//Button is highlighted
					apply_surface(buttons.at(i_b).get_x(), buttons.at(i_b).get_y(), buttons.at(i_b).image_highlight, screen);
				} else {
					//Button is down
					apply_surface(buttons.at(i_b).get_x(), buttons.at(i_b).get_y(), buttons.at(i_b).image_down, screen);
				}
			}
		}

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
	//TODO: Add Cleanup routine that doesn't crash or freeze the game.
	return 0;
}

bool load_files()
{//Load the files needed for the program

	background = load_image("background.bmp");
	sidebar = load_image("sidebar.bmp");
	toolbar = load_image("toolbar.bmp");


	//load the first turret
	blank_surface = load_image("blank.bmp");
	border = load_image("border.bmp");

	//This loop loads the turret sprite sheet, and then loads each sprite into the turret_sprites array
	SDL_Surface *turret_sprite_sheet = NULL;
	turret_sprite_sheet = load_image("turret_sprite.bmp");
	for(int a=0; a<TURRET_NUM; a++)
	{
		for(int b=0; b<3; b++)
		{
			SDL_Rect myRect;
			myRect.x=b*25;
			myRect.y=a*25;
			myRect.h=25;
			myRect.w=25;
			turret_sprites[a][b] = load_image("blank.bmp");
			//turret_sprites[a][b] = blank_surface;//make it 25x25, and formatted.r
			apply_surface(0, 0, turret_sprite_sheet, turret_sprites[a][b], &myRect);
		}
	}


	turret_projectiles[0] = load_image("turret1_projectile.bmp");
	turret_projectiles[1] = load_image("turret2_projectile.bmp");


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
	//SDL_FreeSurface(screen);
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

//Spawns a creep offscreen
void spawn(vector<Creep> *ptr,int *time)
{
	//Static local variable
	//Determines when to make a creep

	/*
	if(&time == 0)
	{
		//Spawn a creep
		Creep temp(261,442,2,2,5,0,false,3);
		ptr->push_back(temp);
		*time = 0;
	}
	*/

}
