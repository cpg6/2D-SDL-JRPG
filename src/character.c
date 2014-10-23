/* Characters */
#include "character.h"
#include "collision.h"
#include "level.h"
#include <stdlib.h>
extern Map maps[MAX_MAPS];
extern int g_currentLevel;
extern ScreenData  S_Data;


void InitCharacter(character *sprite)
{
	sprite->x = 496;
	sprite->y = 588;
	sprite->csprite = LoadSprite("images/cyan.png",36, 48);
	sprite->exp = 0;
	sprite->health = 100;
	sprite->flag = 0;
	sprite->frame = 0;
	sprite->collision.h = 48;
	sprite->collision.w = 36;
	sprite->collision.x = 0;
	sprite->collision.y = 0;
}

void DrawCharacter(character *c1, SDL_Surface* screen, int currentLevel)
{
	//c1->frame = (c1->frame + 1)%4;
	if (g_currentLevel == 0)
		DrawSprite(c1->csprite,screen,c1->x,c1->y,c1->frame);
	else if (g_currentLevel == 1)
		DrawSprite(c1->csprite,screen,(c1->x),(c1->y),c1->frame);
	else if (g_currentLevel == 2)
		DrawSprite(c1->csprite,screen,(c1->x+304),(c1->y+25),c1->frame);
	
}

void TeleportCharacter(character *ch, int new_level)
{
	g_currentLevel = new_level;
	ch->x = maps[new_level].start[0] * 64;
	ch->y = maps[new_level].start[1] * 48;
}

void CharacterMove(character *sprite, Uint8* keys)
{
	int tilex, tiley;
	if(keys[SDLK_a]|| keys[SDLK_LEFT])
	{
		sprite->x = sprite->x - 6;
		if(sprite->x < 0)
			sprite->x += 6;
		tilex = sprite->x/64;
		tiley = sprite->y/48;
		if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
		{
			sprite->x=sprite->x + 6;
		}
	}
	else if(keys[SDLK_s]|| keys[SDLK_DOWN])
	{
		sprite->y = sprite->y + 6;
		tilex = sprite->x/64;
		tiley = (sprite->y+48)/48;
		if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
		{
			sprite->y -= 6;
		}else if(maps[g_currentLevel].tiles[tilex][tiley].teleportnum != -1)
			TeleportCharacter(sprite, maps[g_currentLevel].tiles[tilex][tiley].teleportnum);
		if(sprite->y+48 > S_Data.yres)
			sprite->y -= 6;
	}
	else if(keys[SDLK_d] || keys[SDLK_RIGHT])
	{
		sprite->x = sprite->x + 6;
		if(sprite->x+32 > S_Data.xres)
			sprite->x -= 6;
		tilex = (sprite->x+32)/64;
		tiley = sprite->y/48;
		if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
		{
			sprite->x=sprite->x - 6;
		}
	}
	else if(keys[SDLK_w]|| keys[SDLK_UP])
	{
		sprite->y = sprite->y - 6;
				tilex = sprite->x/64;
		tiley = sprite->y/48;
		if (maps[g_currentLevel].tiles[tilex][tiley].pass != '1')
		{
			sprite->y += 6;
		}
		if(sprite->y < 0)
			sprite->y += 6;
	}
	else if (keys[SDLK_l])
	{
		printf("location: %d, %d \n",
			sprite->x/64,sprite->y/48);

	}
}

void FreeCharacter(character* c1)
{
	FreeSprite(c1->csprite);
	memset(c1,0,sizeof(character));
	/*
	c1->x = NULL;
	c1->y = NULL;
	c1->exp = NULL;
	c1->health = NULL;
	c1->flag = NULL;
	c1->csprite = NULL;
	*/
}