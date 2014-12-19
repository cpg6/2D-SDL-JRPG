#ifndef _BUTTON_
#define _BUTTON_
#include "graphics.h"
#include "level.h"

typedef struct attackButton_T									/** Defining the Attack Button for combat Structure */
{
	int cx;														/** Combat x position */
	int cy;														/** Combat y position */
	Sprite *sprite_c;											/** Combat Sprite Image */
	Uint32 frame;
	SDL_Rect collision;

}attackButton;

typedef struct blockButton_T									/** Defining the Block Button for combat Structure */
{
	int cx;														/** Combat x position */
	int cy;														/** Combat y position */
	Sprite *sprite_c;											/** Combat Sprite Image */
	Uint32 frame;
	SDL_Rect collision;

}blockButton;

void InitAttackButton(attackButton *sprite);
void InitBlockButton(blockButton *sprite);
void DrawButton_C(attackButton* ab1, blockButton* bb1, SDL_Surface* screen);
void FreeButton(attackButton *ab1, blockButton *bb1);

#endif