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
	float exp;
	long flag;
	Uint32 frame;
	SDL_Rect collision;

}character;

typedef struct Fighter_T
{
	int x;
	int y;
	Sprite *fsprite;
	float exp;
	int attack;
	int defense;
}fighter;

typedef struct Mage_T
{
	int x;
	int y;
	Sprite *msprite;
	float exp;
	int attack;
	int defense;
}mage;

void TeleportCharacter(character *ch, int new_level);
void InitCharacter(character *sprite);
void InitFighter(fighter *sprite);
void InitMage(mage *sprite);
void DrawPCs(fighter* f1, mage* m1, SDL_Surface* screen2);
void DrawCharacter(character* c1, SDL_Surface* screen, int currentLevel);
void CharacterMove(character *sprite, Uint8* keys);
void FreeCharacter(character* c1);

#endif