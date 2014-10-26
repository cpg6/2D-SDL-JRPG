#ifndef _ENEMY_
#define _ENEMY_
#include "graphics.h"
#include "level.h"


typedef struct Ettin_T 
{
	int x;
	int y;
	int cx;
	int cy;
	Sprite *esprite;
	Sprite *esprite_c;
	int health;
	int attack;
	int defense;
	float exp;
	long flag;
	Uint32 frame;
	SDL_Rect collision;

}ettin;

typedef struct Bishop_T 
{
	int x;
	int y;
	int cx;
	int cy;
	Sprite *bsprite;
	Sprite *bsprite_c;
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
void DrawEnemy(bishop* b1, ettin* e1, SDL_Surface* screen, int currentLevel, int enemySpawned);
void DrawEnemy_C(bishop* b1, ettin* e1, int combatLevel, SDL_Surface* screen);
void EnemyThink(bishop* b1, ettin* e1, SDL_Surface* screen);
void FreeBishop(bishop *b1);
void FreeEttin(ettin *e1);


#endif