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
	sprite->cx = 100;
	sprite->cy = 300;
	sprite->esprite = LoadSprite("images/ettin.png",36, 48);
	sprite->esprite_c = LoadSprite("images/ettin2.png",256,192);
	sprite->exp = 30;
	sprite->health = 80;
	sprite->attack = 6;
	sprite->defense = 3;
	sprite->used = 1;
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
	sprite->cx = 100;
	sprite->cy = 300;
	sprite->bsprite = LoadSprite("images/bishop.png",36, 48);
	sprite->bsprite_c = LoadSprite("images/bishop2.png",256,192);
	sprite->exp = 75;
	sprite->health = 45;
	sprite->attack = 15;
	sprite->defense = 0;
	sprite->used = 1;
	sprite->flag = 0;
	sprite->frame = 0;
	sprite->collision.h = 48;
	sprite->collision.w = 36;
	sprite->collision.x = 768;
	sprite->collision.y = 538;
}

void InitCentaur(centaur *sprite)												/** Init the Centaur */
{
	sprite->x = 0;
	sprite->y = 0;
	sprite->cx = 100;
	sprite->cy = 300;
	sprite->csprite = LoadSprite("images/centaur.png",36, 48);
	sprite->csprite_c = LoadSprite("images/centaur2.png",256,192);
	sprite->exp = 100;
	sprite->health = 150;
	sprite->attack = 12;
	sprite->defense = 30;
	sprite->used = 1;
	sprite->flag = 0;
	sprite->frame = 0;
	sprite->collision.h = 48;
	sprite->collision.w = 36;
	sprite->collision.x = 768;
	sprite->collision.y = 538;
}

void InitSerpent(serpent *sprite)												/** Init the Serpent */
{
	sprite->x = 0;
	sprite->y = 0;
	sprite->cx = 100;
	sprite->cy = 300;
	sprite->ssprite = LoadSprite("images/serpent.png",36, 48);
	sprite->ssprite_c = LoadSprite("images/serpent2.png",256,192);
	sprite->exp = 80;
	sprite->health = 105;
	sprite->attack = 8;
	sprite->defense = 0;
	sprite->used = 1;
	sprite->flag = 0;
	sprite->frame = 0;
	sprite->collision.h = 48;
	sprite->collision.w = 36;
	sprite->collision.x = 256;
	sprite->collision.y = 269;
}

void InitKorax(korax *sprite)												/** Init the Boss Korax */
{
	sprite->x = 0;
	sprite->y = 0;
	sprite->cx = 100;
	sprite->cy = 300;
	sprite->ksprite = LoadSprite("images/korax.png",36, 48);
	sprite->ksprite_c = LoadSprite("images/korax2.png",256,192);
	sprite->exp = 75;
	sprite->health = 500;
	sprite->attack = 20;
	sprite->special = 50;
	sprite->defense = 5;
	sprite->used = 1;
	sprite->flag = 0;
	sprite->frame = 0;
	sprite->collision.h = 48;
	sprite->collision.w = 36;
	sprite->collision.x = 512;
	sprite->collision.y = 384;
}

void DrawEnemy(bishop* b1, ettin* e1, centaur* cen1, serpent* s1, korax* k1, SDL_Surface* screen,int currentLevel, int enemySpawned) /**Draw the Enemies to the overworld screen */
{
	if(currentLevel == 0)
	{
		if ((b1->bsprite != NULL))
		{
			DrawSprite(b1->bsprite,screen,b1->x,b1->y,b1->frame);
			b1->collision.x = b1->x;
			b1->collision.y = b1->y;
		}
		if ((e1->esprite != NULL))
		{
			DrawSprite(e1->esprite,screen,e1->x,e1->y,e1->frame);
			e1->collision.x = e1->x;
			e1->collision.y = e1->y;
		}
	}
	if(currentLevel == 1)
	{
		cen1->x = 368;
		cen1->y = 438;
		if ((cen1->csprite != NULL))
		{
			DrawSprite(cen1->csprite,screen,cen1->x,cen1->y,cen1->frame);
			cen1->collision.x = cen1->x;
			cen1->collision.y = cen1->y;
		}

		s1->x = 268;
		s1->y = 338;
		if ((s1->ssprite != NULL))
		{
			DrawSprite(s1->ssprite,screen,s1->x,s1->y,s1->frame);
			s1->collision.x = s1->x;
			s1->collision.y = s1->y;
		}
	}
	if(currentLevel == 2)
	{
		k1->x = 512;
		k1->y = 384;
		if ((k1->ksprite != NULL))
		{
			DrawSprite(k1->ksprite,screen,k1->x,k1->y,k1->frame);
			k1->collision.x = k1->x;
			k1->collision.y = k1->y;
		}
	}
}

void DrawEnemy_C(bishop* b1, ettin* e1, centaur* cen1, serpent* s1, korax* k1, int combatLevel, SDL_Surface* screen)					/** Draw the enemies to the combat screen */
{
	if (b1->bsprite != NULL && combatLevel == 1)
	{
		DrawSprite(b1->bsprite_c,screen,b1->cx,b1->cy,b1->frame);
	}
	
	if (e1->esprite != NULL && combatLevel == 2)
	{
		DrawSprite(e1->esprite_c,screen,e1->cx,e1->cy,e1->frame);
	}
	
	if (cen1->csprite != NULL && combatLevel == 3)
	{
		DrawSprite(cen1->csprite_c,screen,cen1->cx,cen1->cy,cen1->frame);
	}

	if (s1->ssprite != NULL && combatLevel == 4)
	{
		DrawSprite(s1->ssprite_c,screen,s1->cx,s1->cy,s1->frame);
	}

	if (k1->ksprite != NULL && combatLevel == 5)
	{
		DrawSprite(k1->ksprite_c,screen,k1->cx,k1->cy,k1->frame);
	}
}

void EnemyThink(bishop *bsprite, ettin *esprite, centaur *csprite, 
	serpent *ssprite, korax *ksprite, SDL_Surface* screen, int currentLevel)										/** Enemy update function for the overworld too randomly move around */
{																								/** Need to incorporate time delay between movements -- FIXTHIS -- */
	int bishop, ettin, centaur, serpent;
	int tilex, tiley;
	int etilex, etiley;
	int max = 4;
	int min = 0;

	bishop = (rand() % (max+1-min))+min;
	ettin = (rand() % (max+1-min))+min;
	centaur = (rand() % (max+1-min))+min;
	serpent = (rand() % (max+1-min))+min;
	if(currentLevel == 0)
	{
		if(bishop == 0)																				/** Movement for Bishop, ettin, centaur, and serpent with collision */
		{																							/** Move left (bishop) */
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
	if(currentLevel == 1)
	{
		if(centaur == 0) 
		{
																									/** Move left (centaur) */
			csprite->x = csprite->x - 6;
			if(csprite->x < 0)
				csprite->x += 6;
			tilex = csprite->x/64;
			tiley = csprite->y/48;
			if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
			{
				csprite->x = csprite->x + 6;
			}
		}
		else if (centaur == 1)																		/** Move Down (centaur) */
		{
			csprite->y = csprite->y + 6;
			tilex = csprite->x/64;
			tiley = (csprite->y+48)/48;

			if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
			{
				csprite->y -= 6;
			}
		}
		else if (centaur == 2)																		/** Move Right (centaur) */
		{
			csprite->x = csprite->x + 6;
			if(csprite->x+32 > S_Data.xres)
				csprite->x -= 6;
			tilex = (csprite->x+32)/64;
			tiley = csprite->y/48;
			if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
			{
				csprite->x = csprite->x - 6;
			}
		}
		else if (centaur == 3)																		/** Move Up (centaur) */
		{
			csprite->y = csprite->y - 6;
			tilex = csprite->x/64;
			tiley = csprite->y/48;
			if(csprite->y < 0)
				csprite->y += 6;
			if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
			{
				csprite->y += 6;
			}
		}

		if(serpent == 0) 
		{
																									/** Move left (serpent) */
			ssprite->x = ssprite->x - 6;
			if(ssprite->x < 0)
				ssprite->x += 6;
			tilex = ssprite->x/64;
			tiley = ssprite->y/48;
			if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
			{
				ssprite->x = ssprite->x + 6;
			}
		}
		else if (serpent == 1)																		/** Move Down (serpent) */
		{
			ssprite->y = ssprite->y + 6;
			tilex = ssprite->x/64;
			tiley = (ssprite->y+48)/48;

			if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
			{
				ssprite->y -= 6;
			}
		}
		else if (serpent == 2)																		/** Move Right (serpent) */
		{
			ssprite->x = ssprite->x + 6;
			if(ssprite->x+32 > S_Data.xres)
				ssprite->x -= 6;
			tilex = (ssprite->x+32)/64;
			tiley = ssprite->y/48;
			if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
			{
				ssprite->x = ssprite->x - 6;
			}
		}
		else if (centaur == 3)																		/** Move Up (serpent) */
		{
			ssprite->y = ssprite->y - 6;
			tilex = ssprite->x/64;
			tiley = ssprite->y/48;
			if(ssprite->y < 0)
				ssprite->y += 6;
			if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
			{
				ssprite->y += 6;
			}
		}
			
	}
		
}

void EnemyThink_C(bishop* b1, ettin* e1, centaur* cen1, serpent* s1, korax* k1,
	int combatState)																			/** Enemy think function for combat */
{


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

void FreeCentaur(centaur *cen1)																	/** Free the centaur from memory */	
{
	FreeSprite(cen1->csprite);
	memset(cen1,0,sizeof(centaur));
}

void FreeSerpent(serpent *s1)																	/** Free the serpent from memory */
{
	FreeSprite(s1->ssprite);
	memset(s1,0,sizeof(serpent));
}

void FreeKorax(korax *k1)																		/** Free Korax boss from memory */
{
	FreeSprite(k1->ksprite);
	memset(k1,0,sizeof(korax));
}