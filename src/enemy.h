#ifndef _ENEMY_
#define _ENEMY_
#include "graphics.h"
#include "level.h"


typedef struct Ettin_T											/** Defining the Ettin monster Structure */
{	
	int x;														/** Overworld x position */
	int y;														/** Overworld y position */
	int cx;														/** Combat x position */	
	int cy;														/** Combat y position */
	Sprite *esprite;											/** Overworld Sprite image */
	Sprite *esprite_c;											/** Combat Sprite Image */
	int health;													
	int attack;													
	int defense;												
	float exp;													
	long flag;													
	Uint32 frame;
	SDL_Rect collision;

}ettin;

typedef struct Bishop_T											/** Defining the Bishop monster Structure */
{
	int x;														/** Overworld x position */
	int y;														/** Overworld y position */
	int cx;														/** Combat x position */
	int cy;														/** Combat y position */
	Sprite *bsprite;											/** Overworld Sprite image */
	Sprite *bsprite_c;											/** Combat Sprite Image */
	int health;
	int attack;
	int defense;
	float exp;
	long flag;
	Uint32 frame;
	SDL_Rect collision;

}bishop;

void InitEttin(ettin *sprite);									
void InitBishop(bishop *sprite);								
void DrawEnemy(bishop* b1, ettin* e1, SDL_Surface* screen, int currentLevel, int enemySpawned); /** Draw enemies to the overworld */
void DrawEnemy_C(bishop* b1, ettin* e1, int combatLevel, SDL_Surface* screen);					/** Draw enemies to the combat screen */
void EnemyThink(bishop* b1, ettin* e1, SDL_Surface* screen);									/** Enemy update function for roaming enemies */
void FreeBishop(bishop *b1);																	/** Free the ettin from memory */
void FreeEttin(ettin *e1);																		/** Free the Bisop from memory */


#endif