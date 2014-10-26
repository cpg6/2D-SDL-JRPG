#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
#include "level.h"
#include "character.h"
#include "collision.h"
#include "enemy.h"

extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect Camera;
//extern SDL_Surface *combatscreen;
//extern SDL_Surface *combatbuffer;
Map maps[MAX_MAPS];
int g_currentLevel;
int g_enemySpawned;
int g_combatState;

void Init_All();


/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{

	SDL_Surface *temp;
	SDL_Surface *bg;
	Sprite *bordertile, *grasstile, *castletile, *walltile, *bloodtile, *doortile, *enemy_ettin, *enemy_bishop, *combat_bg; 
	character* c1;
	ettin* e1;
	bishop* b1;
	fighter* f1;
	mage* m1;
	char *map_files[MAX_MAPS] = 
	{	
	"levels/map1.txt",
	"levels/map2.txt",
	"levels/map3.txt"
	};
	int collision1, collision2;
	int done, keyn,x ;
	Uint8 *keys;
	Init_All();
	g_currentLevel = 0; /** Set current level to first as default */
	g_enemySpawned = 0; /**Set inital enemy spawn to true */
	g_combatState = 0; /** Set initial combat state to false or 0*/
	
	temp = IMG_Load("images/battle.png");/*notice that the path is part of the filename*/
	//if(bg != NULL)
		//SDL_BlitSurface(bg,NULL,buffer,NULL);
	//SDL_FreeSurface(temp);


	bordertile = LoadSprite("images/border.png",64,48);
	grasstile = LoadSprite("images/deadgrass.png",64,48);
	castletile = LoadSprite("images/castletile.png",64,48);
	walltile = LoadSprite("images/wall.png",64,48);
	bloodtile = LoadSprite("images/blood.png",64,48);
	doortile = LoadSprite("images/door.png",64,48);
	enemy_ettin = LoadSprite("images/ettin.png",36, 48);
	enemy_bishop = LoadSprite("images/bishop.png",36, 48);
	combat_bg = LoadSprite("images/battle.png",1024,768);

    c1 = (character*) malloc(sizeof(character));
	e1 = (ettin*) malloc(sizeof(ettin));
	b1 = (bishop*) malloc(sizeof(bishop));
	f1 = (fighter*) malloc(sizeof(fighter));
	m1 = (mage*) malloc(sizeof(mage));
    InitCharacter(c1);
	InitEttin(e1);
	InitBishop(b1);
	

	for(x=0;x<MAX_MAPS; x++)
		loadMap(&maps[x],map_files[x]);
	TeleportCharacter(c1,g_currentLevel);
    done = 0;
    do
    {
		collision1 = checkCollision(c1->collision,b1->collision);
		collision2 = checkCollision(c1->collision,e1->collision);
		if (collision1 == 1)
		{
			printf("COLLISION DETECTED!!!!!!! BISHOP \n");
			g_combatState = 1;
			InitFighter(f1);
			InitMage(m1);
		}
		if (collision2 == 1)
		{
			printf("COLLISION DETECTED!!!!!!! ETTIN \n");
			g_combatState = 2;
			InitFighter(f1);
			InitMage(m1);
		}
		keys = SDL_GetKeyState(&keyn);
		ResetBuffer ();

		//==================================================================================
		// Combat Loop
		//==================================================================================

		while (g_combatState > 0) /** Loop for combat screen */
		{
			keys = SDL_GetKeyState(&keyn);
			ResetBuffer ();
			
			if (g_combatState == 1) //Bishop combat window
			{
				if(temp != NULL)						
					bg = SDL_DisplayFormat(temp);

				if(bg != NULL)
					SDL_BlitSurface(bg,NULL,buffer,NULL);

				DrawPCs(f1, m1, screen);
				DrawEnemy_C(b1, e1, g_combatState, screen);
				//Exit condition will need to remove sprite if enemy dies otherwise collision loops to keep screen up.
				
			}

			if (g_combatState == 2) //Ettin combat window
			{
				if(temp != NULL)						
					bg = SDL_DisplayFormat(temp);

				if(bg != NULL)
					SDL_BlitSurface(bg,NULL,buffer,NULL);

				DrawPCs(f1, m1, screen);
				DrawEnemy_C(b1, e1, g_combatState, screen);
				//Exit condition will need to remove sprite if enemy dies otherwise collision loops to keep screen up.
			}
			NextFrame();
			SDL_PumpEvents();

			if(keys[SDLK_ESCAPE] && g_combatState == 1)
			{
				g_combatState = 0; //Temporary end condition for testing
				SDL_FreeSurface(bg);
				FreeBishop(b1);
			}

			if(keys[SDLK_ESCAPE] && g_combatState == 2)
			{
				g_combatState = 0; //Temporary end condition for testing
				SDL_FreeSurface(bg);
				FreeEttin(e1);
			}
		}

		//==================================================================================
		// END Combat Loop
		//==================================================================================

		DrawMouse();
		CharacterMove(c1,keys);
		EnemyThink(b1, e1, screen);
		drawLevel(g_currentLevel,bordertile, grasstile, castletile, walltile, bloodtile, doortile, &maps[g_currentLevel], enemy_ettin, enemy_bishop, g_enemySpawned); /*draw level*/
		DrawCharacter(c1,screen,g_currentLevel);
		DrawEnemy(b1,e1,screen,g_currentLevel,g_enemySpawned);
		NextFrame();
		SDL_PumpEvents();
		// if(SDL_GetMouseState(&mx,&my))
		// {
		//DrawSprite(tile,buffer,(mx /32) * 32,(my /32) * 32,0); 
		
		//}
		//if(keys[SDLK_ESCAPE])done = 1;
  }while(!done);
  FreeCharacter(c1);
  CloseSprites();
  exit(0);		/*technically this will end the program, but the compiler likes all functions that can return a value TO return a value*/
  return 0;
}

void CleanUpAll(void)
{
  CloseSprites();
  /*any other cleanup functions can be added here*/ 
}

void Init_All()
{
  Init_Graphics();
  InitMouse();
  atexit(CleanUpAll);
}

