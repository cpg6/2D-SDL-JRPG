#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
#include "level.h"
#include "character.h"
#include "collision.h"
#include "enemy.h"
//#include "SDL_ttf.h"

extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect Camera;
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
	//SDL_Surface *fontSurface;
	//TTF_Font *font;
	//SDL_Color text_color;
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
	int done, keyn,x , tempExp, tempExp2;
	Uint8 *keys;
	Init_All();

																			/** Fonts Need Attention to be Fixed, currently a mess
    font = TTF_OpenFont("fonts/font2.ttf",16);
	text_color.r = 255;
	text_color.b = 255;
	text_color.g = 255;
	fontSurface = TTF_RenderText_Solid(font, , text_color);
    fontRect.x = x;
    fontRect.y = y;
    SDL_BlitSurface(fontSurface, NULL, screen, &fontRect);
	*/

	g_currentLevel = 0;														/** Set current level to first as default */
	g_enemySpawned = 0;														/** Wound up not needing this -- FIXTHIS -- */
	g_combatState = 0;														/** Set initial combat state to false or 0*/
	
	temp = IMG_Load("images/battle.png");									/** load the battle stage background into memory*/


	bordertile = LoadSprite("images/border.png",64,48);						/** load all tile sprites into memory */
	grasstile = LoadSprite("images/deadgrass.png",64,48);					/** load all tile sprites into memory */
	castletile = LoadSprite("images/castletile.png",64,48);					/** load all tile sprites into memory */
	walltile = LoadSprite("images/wall.png",64,48);
	bloodtile = LoadSprite("images/blood.png",64,48);
	doortile = LoadSprite("images/door.png",64,48);
	enemy_ettin = LoadSprite("images/ettin.png",36, 48);
	enemy_bishop = LoadSprite("images/bishop.png",36, 48);
	combat_bg = LoadSprite("images/battle.png",1024,768);

    c1 = (character*) malloc(sizeof(character));							/**allocate memory for all sprites/entities and init them! */
	e1 = (ettin*) malloc(sizeof(ettin));
	b1 = (bishop*) malloc(sizeof(bishop));
	f1 = (fighter*) malloc(sizeof(fighter));
	m1 = (mage*) malloc(sizeof(mage));
    InitCharacter(c1);
	InitEttin(e1);
	InitBishop(b1);
	
	
	for(x=0;x<MAX_MAPS; x++)												/** Load the maps from text files into memory */
		loadMap(&maps[x],map_files[x]);
	TeleportCharacter(c1,g_currentLevel);									/**Conduct the first teleport of the character at start */
    done = 0;
    do
    {
		collision1 = checkCollision(c1->collision,b1->collision);			/** Continuously check if there is a collision detected */
		collision2 = checkCollision(c1->collision,e1->collision);			/** Continuously check if there is a collision detected */
		if (collision1 == 1)
		{
			printf("COLLISION DETECTED!!!!!!! BISHOP \n");					/** if collided w/ bishop set combat state and Init */
			g_combatState = 1;
			InitFighter(f1);
			InitMage(m1);
		}
		if (collision2 == 1)
		{
			printf("COLLISION DETECTED!!!!!!! ETTIN \n");					/** if collided w/ ettin set combat state and Init */
			g_combatState = 2;
			InitFighter(f1);
			InitMage(m1);
		}
		keys = SDL_GetKeyState(&keyn);
		ResetBuffer ();

		//==================================================================================
		// Combat Loop
		//==================================================================================

		while (g_combatState > 0)											/** Loop for combat screen */
		{
			keys = SDL_GetKeyState(&keyn);
			ResetBuffer ();
			
			if (g_combatState == 1)											/** if collided with a bishop, enter combat with a bishop */
			{
				if(temp != NULL)						
					bg = SDL_DisplayFormat(temp);

				if(bg != NULL)
					SDL_BlitSurface(bg,NULL,buffer,NULL);					/** Draw the combat background */

				DrawPCs(f1, m1, screen);									/** Draw the playable characters to the screen */
				DrawEnemy_C(b1, e1, g_combatState, screen);					/** Draw Enemy Combatants */

				if(keys[SDLK_g])											/** conduct an attack */
				{
					b1->health = b1->health - f1->attack + b1->defense;
				}
				
			}

			if (g_combatState == 2)											/** if collided with a ettin, enter combat with a ettin */
			{
				if(temp != NULL)						
					bg = SDL_DisplayFormat(temp);

				if(bg != NULL)
					SDL_BlitSurface(bg,NULL,buffer,NULL);					/** Draw the combat background */

				DrawPCs(f1, m1, screen);									/** Draw the playable characters to the screen */
				DrawEnemy_C(b1, e1, g_combatState, screen);					/** Draw Enemy Combatants */

				if(keys[SDLK_g])											/** conduct an attack */
				{
					e1->health = e1->health - f1->attack + e1->defense;
				}
			}
			NextFrame();
			SDL_PumpEvents();

			if(b1->health <= 0 && g_combatState == 1)						/** If fighting a bishop and his HP goes below 0 End */
			{
				g_combatState = 0;
				f1->exp = f1->exp + b1->exp;								/**Add exp to both the fighter and the mage */
				m1->exp = m1->exp + b1->exp;
				if (f1->exp > f1->nextlvl)									/** Condition to check for a level up*/
				{
					f1->nextlvl = f1->nextlvl + (f1->nextlvl * .15);		/** if leveled up, increase stats */
					f1->exp = 0;
					f1->attack = f1->attack + 3;						
					f1->defense = f1->defense +3;
					SDL_Delay(1500);										/** Delay for printing text to the screen for level up */

				}

				if (m1->exp > m1->nextlvl)									/** Condition to check for a level up*/
				{
					m1->nextlvl = m1->nextlvl + (m1->nextlvl * .15);		/** if leveled up, increase stats */
					m1->exp = 0;
					m1->attack = m1->attack + 1;
					m1->defense = m1->defense +1;
					SDL_Delay(1500);										/** Delay for printing text to the screen for level up */

				}
				SDL_FreeSurface(bg);										/** Free the surface before ending the loop at the end */
				FreeBishop(b1);												/** FIXTHIS -- removes from the map in other levels as well */
			}

			if(e1->health <= 0 && g_combatState == 2)						/** If fighting an ettin and his HP goes below 0 End */
			{
				g_combatState = 0;
				f1->exp = f1->exp + e1->exp;								/**Add exp to both the fighter and the mage */
				m1->exp = m1->exp + e1->exp;
				if (f1->exp > f1->nextlvl)									/** Condition to check for a level up*/
				{
					f1->nextlvl = f1->nextlvl + (f1->nextlvl * .25);        /** if leveled up, increase stats */
					f1->exp = 0; 
					f1->attack = f1->attack + 3;
					f1->defense = f1->defense +3;
					SDL_Delay(1500);										/** Delay for printing text to the screen for level up */
				}

				if (m1->exp > m1->nextlvl)									/** Condition to check for a level up*/
				{
					m1->nextlvl = m1->nextlvl + (m1->nextlvl * .25);		/** if leveled up, increase stats */
					m1->exp = 0;
					m1->attack = m1->attack + 1;
					m1->defense = m1->defense +1;
					SDL_Delay(1500);										/** Delay for printing text to the screen for level up */
				}
				SDL_FreeSurface(bg);										/** Free the surface before ending the loop at the end */
				FreeEttin(e1);												/** FIXTHIS -- removes from the map in other levels as well */
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
		if(keys[SDLK_ESCAPE])done = 1;
  }while(!done);															/** End of the main game loop */

  FreeCharacter(c1);
  CloseSprites();
  //TTF_Quit();
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
