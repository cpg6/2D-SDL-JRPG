/* Characters */
#include "character.h"
#include "collision.h"
#include "level.h"
#include <stdlib.h>



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
	if (currentLevel == 0)
		DrawSprite(c1->csprite,screen,c1->x,c1->y,c1->frame);
	else if (currentLevel == 1)
		DrawSprite(c1->csprite,screen,(c1->x-272),(c1->y+25),c1->frame);
	else if (currentLevel == 2)
		DrawSprite(c1->csprite,screen,(c1->x+304),(c1->y+25),c1->frame);
	
}

void CharacterMove(character *sprite, Uint8* keys)
{
	if(keys[SDLK_a])
	{
		//if (checkCollision(sprite,wall->wall))
			//return;
		sprite->x = sprite->x - 6;
	}
	else if(keys[SDLK_s])
	{
		sprite->y = sprite->y + 6;
	}
	else if(keys[SDLK_d])
	{
		sprite->x = sprite->x + 6;
	}
	else if(keys[SDLK_w])
	{
		sprite->y = sprite->y - 6;
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