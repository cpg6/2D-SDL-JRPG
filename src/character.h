#ifndef _CHARACTER_
#define _CHARACTER_
#include "graphics.h"
#include "level.h"
#define CHARFLAG_BATTLE			0


typedef struct Char_T 
{
	int x;
	int y;
	Sprite *csprite;
	int health;
	int attack;
	float exp;
	long flag;
	Uint32 frame;
	SDL_Rect collision;

}character;

void TeleportCharacter(character *ch, int new_level);
void InitCharacter(character *sprite);
void DrawCharacter(character* c1, SDL_Surface* screen, int currentLevel);
void CharacterMove(character *sprite, Uint8* keys);
void FreeCharacter(character* c1);

#endif