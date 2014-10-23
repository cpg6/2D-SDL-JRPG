/*

#ifndef __myentities__
#define __myentities__

typedef struct entity_s
{
	int inuse;
	Sprite *sprite;
	int frame;
	vec2_t position;
	vec2_t velocity;
	SDL_Rect bbox;
	float radius;
} Entity;

void initEntityList();
void closeEntityList();
void drawEntityList();
void updateEntityList();
void thinkEntityList();
Entity *newEntity();
void freeEntity(Entity *ent);

#endif //include guards

*/