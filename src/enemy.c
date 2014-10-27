#include "enemy.h"
#include "collision.h"
#include "level.h"
#include <stdlib.h>
extern Map maps[MAX_MAPS];
extern int g_currentLevel;
extern int g_enemySpawned;
extern ScreenData  S_Data;

void InitEttin(ettin *sprite)												/** Init the Ettin */
{
	sprite->x = 256;
	sprite->y = 269;
	sprite->cx = 300;
	sprite->cy = 300;
	sprite->esprite = LoadSprite("images/ettin.png",36, 48);
	sprite->esprite_c = LoadSprite("images/ettin2.png",256,192);
	sprite->exp = 30;
	sprite->health = 80;
	sprite->attack = 15;
	sprite->defense = 3;
	sprite->flag = 0;
	sprite->frame = 0;
	sprite->collision.h = 48;
	sprite->collision.w = 36;
	sprite->collision.x = 256;
	sprite->collision.y = 269;
}

void InitBishop(bishop *sprite)												/** Init the Bishop */
{
	sprite->x = 768;
	sprite->y = 538;
	sprite->cx = 300;
	sprite->cy = 300;
	sprite->bsprite = LoadSprite("images/bishop.png",36, 48);
	sprite->bsprite_c = LoadSprite("images/bishop2.png",256,192);
	sprite->exp = 75;
	sprite->health = 45;
	sprite->attack = 25;
	sprite->defense = 0;
	sprite->flag = 0;
	sprite->frame = 0;
	sprite->collision.h = 48;
	sprite->collision.w = 36;
	sprite->collision.x = 768;
	sprite->collision.y = 538;
}

void DrawEnemy(bishop *b1, ettin *e1, SDL_Surface* screen, int currentLevel, int enemySpawned) /**Draw the Enemies to the overworld screen */
{
	if (b1->bsprite != NULL)
	{
		DrawSprite(b1->bsprite,screen,b1->x,b1->y,b1->frame);
		b1->collision.x = b1->x;
		b1->collision.y = b1->y;
	}
	if (e1->esprite != NULL)
	{
		DrawSprite(e1->esprite,screen,e1->x,e1->y,e1->frame);
		e1->collision.x = e1->x;
		e1->collision.y = e1->y;
	}
}

void DrawEnemy_C(bishop* b1, ettin* e1, int combatLevel, SDL_Surface* screen)					/** Draw the enemies to the combat screen */
{
	if (e1->esprite != NULL && combatLevel == 2)
	{
		DrawSprite(e1->esprite_c,screen,e1->cx,e1->cy,e1->frame);
	}
	if (b1->bsprite != NULL && combatLevel == 1)
	{
		DrawSprite(b1->bsprite_c,screen,b1->cx,b1->cy,b1->frame);
	}

}

void EnemyThink(bishop *bsprite, ettin *esprite, SDL_Surface* screen)							/** Enemy update function for the overworld too randomly move around */
{																								/** Need to incorporate time delay between movements -- FIXTHIS -- */
	int bishop, ettin;
	int tilex, tiley;
	int etilex, etiley;
	int max = 4;
	int min = 0;
	bishop = (rand() % (max+1-min))+min;
	ettin = (rand() % (max+1-min))+min;

																								/** Movement for Bishop with collision */
	if(bishop == 0) 
	{
																								/** Move left (bishop) */
		bsprite->x = bsprite->x - 6;
		if(bsprite->x < 0)
			bsprite->x += 6;
		tilex = bsprite->x/64;
		tiley = bsprite->y/48;
		if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
		{
			bsprite->x=bsprite->x + 6;
		}
	}
	else if (bishop == 1)																		/** Move Down (bishop) */
	{
		bsprite->y = bsprite->y + 6;
		tilex = bsprite->x/64;
		tiley = (bsprite->y+48)/48;

		if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
		{
			bsprite->y -= 6;
		}
	}
	else if (bishop == 2)																		/** Move Right (bishop) */
	{
		bsprite->x = bsprite->x + 6;
		if(bsprite->x+32 > S_Data.xres)
			bsprite->x -= 6;
		tilex = (bsprite->x+32)/64;
		tiley = bsprite->y/48;
		if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
		{
			bsprite->x=bsprite->x - 6;
		}
	}
	else if (bishop == 3)																		/** Move Up (bishop) */
	{
		bsprite->y = bsprite->y - 6;
		tilex = bsprite->x/64;
		tiley = bsprite->y/48;
		if(bsprite->y < 0)
			bsprite->y += 6;
		if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
		{
			bsprite->y += 6;
		}
	}

																								/** movement for ettin with collision */
	if (ettin == 0)																				/** Move left (ettin) */
	{
		esprite->x = esprite->x - 6;
		if(esprite->x < 0)
			esprite->x += 6;
		etilex = esprite->x/64;
		etiley = esprite->y/48;
		if (maps[g_currentLevel].tiles[etilex][etiley].pass != '1')
		{
			esprite->x=esprite->x + 6;
		}
	}
	else if (ettin == 1)																		/** Move Down (ettin) */
	{
		esprite->y = esprite->y + 6;
		etilex = esprite->x/64;
		etiley = (esprite->y+48)/48;

		if (maps[g_currentLevel].tiles[etilex][etiley].pass != '1')
		{
			esprite->y -= 6;
		}
	}
	else if (ettin == 2)																		/** Move Right (ettin) */
	{
		esprite->x = esprite->x + 6;
		if(esprite->x+32 > S_Data.xres)
			esprite->x -= 6;
		etilex = (esprite->x+32)/64;
		etiley = esprite->y/48;
		if (maps[g_currentLevel].tiles[etilex][etiley].pass != '1')
		{
			esprite->x=esprite->x - 6;
		}
	}
	else if (ettin == 3)																		/** Move Up (ettin) */
	{
		esprite->y = esprite->y - 6;
		etilex = esprite->x/64;
		etiley = esprite->y/48;
		if(esprite->y < 0)
			esprite->y += 6;
		if (maps[g_currentLevel].tiles[etilex][etiley].pass != '1')
		{
			esprite->y += 6;
		}
	}


}

void FreeBishop(bishop *b1)																		/** Free the bishop from memory */
{
	FreeSprite(b1->bsprite);
	memset(b1,0,sizeof(bishop));
}

void FreeEttin(ettin *e1)																		/** Free the ettin from memory */
{
	FreeSprite(e1->esprite);
	memset(e1,0,sizeof(ettin));

}