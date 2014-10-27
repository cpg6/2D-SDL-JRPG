
#ifndef _LEVELS_
#define _LEVELS_
#define MAX_MAPS		3
#include "character.h"

/** The method to draw each level Javadocs*/

typedef struct Tile_t
{
	char tnum;
	char pass;
	struct charTile *onTile;
	char teleportnum;
	char enemySpawn;				//handles spawn locations of enemies
}Tile;

typedef struct Map_t
{
	struct Tile_t tiles[16][16];
	int start[2];
	struct sprite *tilesheet;

}Map;



void drawLevel(int currentLevel, Sprite *bordertile, Sprite *grasstile, Sprite *castletile, Sprite *walltile, 
	Sprite *bloodtile, Sprite *doortile, Map *map, Sprite *ettin, Sprite *bishop, int enemySpawned); /*used to draw the level and update the levels */
void loadMap(Map *map, char *file);																	/** Loads maps into memory */

#endif

/*  Previous thought process, useless so far
typedef struct Tile_t
{
	int id;
	int traversable;
	char name[30];

}Tile;

typedef struct Wall_t
{
	int xpos;
	int ypos;
	int width;
	int height;
	SDL_Rect wall;

}wall;

typedef struct Door_t
{
	int xpos;
	int ypos;
	int width;
	int height;
	SDL_Rect* door;

}door;

typedef struct border_t
{
	int xpos;
	int ypos;
	int width;
	int height;
	SDL_Rect* border;

}border;

typedef struct enemy_t
{
	int xpos;
	int ypos;
	int width;
	int height;
	SDL_Rect* enemy;

}enemy;

void InitEnemy(enemy *enemy);
void InitBorder(border *border);
void InitDoor(door *door);
void InitWall(wall wall);
*/