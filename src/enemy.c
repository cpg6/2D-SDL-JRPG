#include "enemy.h"
#include "collision.h"
#include "level.h"
#include <stdlib.h>
extern Map maps[MAX_MAPS];
extern int g_currentLevel;
extern ScreenData  S_Data;

void InitEttin(ettin *sprite)
{
	sprite->x = 496;
	sprite->y = 588;
	sprite->esprite = LoadSprite("images/ettin.png",36, 48);
	sprite->exp = 0;
	sprite->health = 100;
	sprite->flag = 0;
	sprite->frame = 0;
	sprite->collision.h = 48;
	sprite->collision.w = 36;
	sprite->collision.x = 0;
	sprite->collision.y = 0;
}

void InitBishop(bishop *sprite)
{
	sprite->x = 496;
	sprite->y = 588;
	sprite->bsprite = LoadSprite("images/bishop.png",36, 48);
	sprite->exp = 0;
	sprite->health = 100;
	sprite->flag = 0;
	sprite->frame = 0;
	sprite->collision.h = 48;
	sprite->collision.w = 36;
	sprite->collision.x = 0;
	sprite->collision.y = 0;
}

void DrawEnemy(bishop *b1, ettin *e1, SDL_Surface* screen, int currentLevel)
{
	int i, j;
	for(i = 0; i < 16; i++)
	{
		for(j = 0; j < 16; j++)
		{
		if (maps[g_currentLevel].tiles[i][j].enemySpawn == 'b')
			DrawSprite(b1->bsprite,screen,((i*64)%1024), ((j*48)%768),b1->frame);
		else if (maps[g_currentLevel].tiles[i][j].enemySpawn == 'e')
			DrawSprite(e1->esprite,screen,((i*64)%1024), ((j*48)%768),e1->frame);
		}
	}
}
