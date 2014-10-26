#include "graphics.h"
#include "character.h"
#include "enemy.h"


int checkCollision(SDL_Rect rec1, SDL_Rect rec2)
{
	if((rec1.x + rec1.w) >= rec2.x && (rec2.x + rec2.w) >= rec1.x && (rec1.y + rec1.h) >= rec2.y && (rec2.y + rec2.h) >= rec1.y)
	{
		return 1;
	}
	return 0;
}