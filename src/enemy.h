#ifndef _ENEMY_
#define _ENEMY_
#include "graphics.h"
#include "level.h"


typedef struct Ettin_T 
{
	int x;
	int y;
	Sprite *esprite;
	int health;
	int attack;
	float exp;
	long flag;
	Uint32 frame;
	SDL_Rect collision;

}ettin;

typedef struct Bishop_T 
{
	int x;
	int y;
	Sprite *bsprite;
	int health;
	int attack;
	float exp;
	long flag;
	Uint32 frame;
	SDL_Rect collision;

}bishop;

void InitEttin(ettin *sprite);
void InitBishop(bishop *sprite);
void DrawEnemy(bishop* b1, ettin* e1, SDL_Surface* screen, int currentLevel, int enemySpawned);
void EnemyThink(bishop* b1, ettin* e1, SDL_Surface* screen);
void FreeBishop(bishop *b1);
void FreeEttin(ettin *e1);


#endif