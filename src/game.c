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
Map maps[MAX_MAPS];
int g_currentLevel;
int g_enemySpawned;

void Init_All();


/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{

	SDL_Surface *temp;
	SDL_Surface *bg;
	Sprite *bordertile, *grasstile, *castletile, *walltile, *bloodtile, *doortile, *enemy_ettin, *enemy_bishop; 
	character* c1;
	ettin* e1;
	bishop* b1;
	char *map_files[MAX_MAPS] = 
	{	
	"levels/map1.txt",
	"levels/map2.txt",
	"levels/map3.txt"
	};

	int done, keyn,x ;
	Uint8 *keys;
	Init_All();
	g_currentLevel = 0; /* Set current level to first as default */
	g_enemySpawned = 0; /**Set inital enemy spawn to true */
	temp = IMG_Load("images/AncientCastle.png");/*notice that the path is part of the filename*/
	if(temp != NULL)						/*ALWAYS check your pointers before you use them*/
		bg = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	//  if(bg != NULL)
	//   SDL_BlitSurface(bg,NULL,buffer,NULL);


	bordertile = LoadSprite("images/border.png",64,48);
	grasstile = LoadSprite("images/deadgrass.png",64,48);
	castletile = LoadSprite("images/castletile.png",64,48);
	walltile = LoadSprite("images/wall.png",64,48);
	bloodtile = LoadSprite("images/blood.png",64,48);
	doortile = LoadSprite("images/door.png",64,48);
	enemy_ettin = LoadSprite("images/ettin.png",36, 48);
	enemy_bishop = LoadSprite("images/bishop.png",36, 48);

    c1 = (character*) malloc(sizeof(character));
	e1 = (ettin*) malloc(sizeof(ettin));
	b1 = (bishop*) malloc(sizeof(bishop));
    InitCharacter(c1);
	InitEttin(e1);
	InitBishop(b1);

	for(x=0;x<MAX_MAPS; x++)
		loadMap(&maps[x],map_files[x]);
	TeleportCharacter(c1,g_currentLevel);
    done = 0;
    do
    {
		keys = SDL_GetKeyState(&keyn);
		ResetBuffer ();
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
		if(keys[SDLK_ESCAPE])done = 1;
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

