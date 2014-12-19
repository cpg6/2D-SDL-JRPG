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
	int lvl;
	float nextlvl;
	int attack;
	int defense;
}fighter;

typedef struct Mage_T
{
	int x;
	int y;
	Sprite *msprite;
	float exp;
	int lvl;
	float nextlvl;
	int attack;
	int defense;
}mage;

void TeleportCharacter(character *ch, int new_level);									/** Returns the character start position for each map */
void InitCharacter(character *sprite);													/** Inits the character */
void InitFighter(fighter *sprite);														/** Inits the fighter class */
void InitMage(mage *sprite);															/** Inits the mage class */
void DrawPCs(fighter* f1, mage* m1, SDL_Surface* screen2);								/** Draws playable characters to combat screen */
void DrawCharacter(character* c1, SDL_Surface* screen, int currentLevel);				/** Draw function for character in overworld */
void CharacterMove(character *sprite, Uint8* keys);										/** Character move function for overworld */
void FreeCharacter(character* c1);														/** Free the character from memory */

#endif