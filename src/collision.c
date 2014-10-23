#include "graphics.h"
#include "character.h"


int checkCollision(SDL_Rect *r1, SDL_Rect *r2)
{
	if(!(r2->x > (r1->x + r1->w) || 
        (r2->x + r2->w) < r1->x  || 
		 r2->y > (r1->y + r1->h) ||
        (r2->y + r2->h) < r1->y))
		return 0;
	return 1;
}