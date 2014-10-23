#include "graphics.h"
#include "level.h"

extern SDL_Surface *screen; /*pointer to the draw buffer*/
extern SDL_Surface *buffer; /*pointer to the background image buffer*/
extern Map maps[MAX_MAPS];

void loadMap(Map *map, char *file)
{
	char c;
	int i;
	int j;
	FILE *in;
	in = fopen(file, "r");
	for (i = 0; i<16;i++)  /** for loop to read tilenumber to tiles*/
	{
		for(j=0;j<16;j++)
		{
			fread(&map->tiles[j][i].tnum,sizeof(char),1,in);
		}
	}
	for (i = 0; i<16;i++)  /** for loop to read passability to tiles*/
	{
		for(j=0;j<16;j++)
		{
			fread(&map->tiles[j][i].pass,sizeof(short),1,in);
		}
	}
	for (i = 0; i<16;i++) /** for loop to read teleport number to tiles*/
	{
		for(j=0;j<16;j++)
		{
			fread(&map->tiles[j][i].teleportnum,sizeof(int),1,in);
		}
	}
}

void drawLevel(int currentLevel, Sprite *bordertile, Sprite *grasstile, Sprite *castletile, Sprite *walltile, Sprite *bloodtile, Sprite *doortile,Map *map)
{
	int i, j;
	if (currentLevel == 0)  /*Draw level one */
	{
		for(i = 0; i < 16; i++)
		{
			for(j = 0; j < 16; j++)
			{
				switch(maps[0].tiles[i][j].tnum)
				{
				case '&':
					DrawSprite(grasstile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				case '#':
					DrawSprite(walltile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				case '*':
					DrawSprite(castletile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				case 'b':
					DrawSprite(bloodtile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				case 'd':
					DrawSprite(doortile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				default:
					DrawSprite(bordertile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				}
			}
		}
	}
	else if (currentLevel == 1)
	{
		for(i = 0; i < 16; i++)
		{
			for(j = 0; j < 16; j++)
			{
				switch(maps[1].tiles[i][j].tnum)
				{
				case '&':
					DrawSprite(grasstile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				case '#':
					DrawSprite(walltile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				case '*':
					DrawSprite(castletile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				case 'b':
					DrawSprite(bloodtile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				case 'd':
					DrawSprite(doortile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				default:
					DrawSprite(bordertile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				}
			}
		}
	}

	else if (currentLevel == 2)
	{
		for(i = 0; i < 16; i++)
		{
			for(j = 0; j < 16; j++)
			{
				switch(maps[2].tiles[i][j].tnum)
				{
				case '&':
					DrawSprite(grasstile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				case '#':
					DrawSprite(walltile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				case '*':
					DrawSprite(castletile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				case 'b':
					DrawSprite(bloodtile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				case 'd':
					DrawSprite(doortile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				default:
					DrawSprite(bordertile,buffer,((i*64)%1024), ((j*48)%768), 0);
					break;
				}
			}
		}
	}

}

/*
//struct Tile tiles[6]; Fail attempt 
 struct Tile tiles0[16][16] = {
 const struct Tile nulltile = { 0, 0, ""};
 for(x = 0; x < 16;x++)
	
		tiles0[x][y] = nulltile;
/*		Fail attempt
struct Tile tiles0 = {0,0,"images/border.png"};
struct Tile tiles1 = {1,1,"images/deadgrass.png"};
struct Tile tiles2 = {2,2,"images/castletile.png"};
struct Tile tiles3 = {3,3,"images/blood.png"};
struct Tile tiles4 = {4,4,"images/door.png"};
struct Tile tiles5 = {5,5,"images/wall.png"};

Fail
tiles[0].id = 0;
tiles[0].traversable = 0;
tiles[0].spr = LoadSprite("images/border.png");

tiles[1].id = 1;
tiles[1].traversable = 1;
tiles[1].spr = LoadSprite("images/deadgrass.png");

tiles[2].id = 2;
tiles[2].traversable = 1;
tiles[2].spr = LoadSprite("images/castletile.png");

tiles[3].id = 3;
tiles[3].traversable = 1;
tiles[3].spr = LoadSprite("images/blood.png");

tiles[4].id = 4;
tiles[4].traversable = 1;
tiles[4].spr = LoadSprite("images/door.png");

tiles[5].id = 5;
tiles[5].traversable = 0;
tiles[5].spr = LoadSprite("images/wall.png");
*/

/*
void InitWall(wall wall)
{
	wall-> = 48;
	wall->wall->w = 64;
	wall->wall->x = wall->xpos;
	wall->wall->y = wall->ypos;
}

void InitBorder(border *border)
{
	border->border->h = 48;
	border->border->w = 64;
	border->border->x = border->xpos;
	border->border->y = border->ypos;
}

void InitDoor(door *door)
{
	door->door->h = 48;
	door->door->w = 64;
	door->door->x = door->xpos;
	door->door->y = door->ypos;
}

void InitEnemy(enemy *enemy)
{
	enemy->enemy->h = 48;
	enemy->enemy->w = 64;
	enemy->enemy->x = enemy->xpos;
	enemy->enemy->y = enemy->ypos;
}

	/*
	tile reference
	w = border pass = 0
	& = grass  pass = 1
	* = castle tile
	# = wall
	b = blood
	d = door
	*/
/*
char map1[16][16] = 
	{
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','#','#','#','#','#','#','#','#','#','#','#','#','#','#','w'},
		{'w','#','#','#','d','#','#','#','#','#','#','d','#','#','#','w'},
		{'w','#','#','*','*','*','*','*','*','*','*','*','*','#','#','w'},
		{'w','#','#','*','*','*','*','*','*','*','*','*','*','#','#','w'},
		{'w','#','#','*','*','*','*','*','*','*','*','*','*','#','#','w'},
		{'w','*','*','*','*','*','#','#','#','#','*','*','*','*','*','w'},
		{'w','*','*','*','*','#','#','b','b','#','#','*','*','*','*','w'},
		{'w','*','*','*','*','#','b','b','b','b','#','*','*','*','*','w'},
		{'w','*','*','*','*','#','#','b','b','#','#','*','*','*','*','w'},
		{'w','*','*','*','*','*','#','#','#','#','*','*','*','*','*','w'},
		{'w','*','*','*','*','*','*','*','*','*','*','*','*','*','*','w'},
		{'w','&','&','&','&','&','&','&','&','&','&','&','&','&','&','w'},
		{'w','&','&','&','&','&','&','&','&','&','&','&','&','&','&','w'},
		{'w','&','&','&','&','&','&','&','&','&','&','&','&','&','&','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'}
	};
	
	char map2[16][16] = 
	{
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','#','#','#','#','#','#','#','#','#','#','#','#','#','#','w'},
		{'w','#','*','*','#','b','b','b','b','b','b','#','*','*','#','w'},
		{'w','#','*','*','#','b','b','b','b','b','b','#','*','*','#','w'},
		{'w','#','*','*','#','#','b','b','b','b','#','#','*','*','#','w'},
		{'w','#','*','*','*','#','#','#','#','#','#','*','*','*','#','w'},
		{'w','#','*','*','*','*','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','*','*','*','*','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','*','*','*','*','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','*','*','*','*','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','*','*','*','*','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','*','*','*','*','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','*','*','*','*','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','*','*','*','*','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','#','d','#','#','#','#','#','#','#','#','#','#','#','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'}
	};

	char map3[16][16] = 
	{
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','#','#','#','#','#','#','#','#','#','#','#','#','#','#','w'},
		{'w','#','b','#','*','*','*','*','*','*','*','*','#','b','#','w'},
		{'w','#','#','#','*','*','*','*','b','*','*','*','#','#','#','w'},
		{'w','#','*','*','*','*','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','*','b','*','*','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','*','*','*','*','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','*','*','*','*','*','*','*','b','*','*','*','*','#','w'},
		{'w','#','*','*','*','*','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','*','*','*','*','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','*','*','*','*','*','*','*','*','*','*','*','b','#','w'},
		{'w','#','*','*','*','b','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','#','#','*','*','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','b','#','*','*','*','*','*','*','*','*','*','*','#','w'},
		{'w','#','#','#','#','#','#','#','#','#','#','#','d','#','#','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'}
	};


	int i, j;
	if (currentLevel == 1)  /*Draw level one */
/*
	{
		for(i = 0; i < 16; i++)
		{
			
			for(j = 0; j < 16; j++)
			{
				if(map1[j][i] == 0)
					DrawSprite(bordertile,buffer,((i*64)%1024), ((j*48)%768), 0);
				else if(map1[j][i] == '&')
					DrawSprite(grasstile,buffer,((i*64)%1024), ((j*48)%768), 0);
				else if(map1[j][i] == '*')
					DrawSprite(castletile,buffer,((i*64)%1024), ((j*48)%768), 0);
				else if(map1[j][i] == '#')
					DrawSprite(walltile,buffer,((i*64)%1024), ((j*48)%768), 0);
				else if(map1[j][i] == 'b')
					DrawSprite(bloodtile,buffer,((i*64)%1024), ((j*48)%768), 0);
				else if(map1[j][i] == 'd')
					DrawSprite(doortile,buffer,((i*64)%1024), ((j*48)%768), 0);
				
			}
			
		}
	}

	if (currentLevel == 2)
	{
		for(i = 0; i < 16; i++)
		{
			for(j = 0;j < 16; j++)
			{
				if(map2[j][i] == 0)
					DrawSprite(bordertile,buffer,((i*64)%1024), ((j*48)%768), 0);
				else if(map2[j][i] == '&')
					DrawSprite(grasstile,buffer,((i*64)%1024), ((j*48)%768), 0);
				else if(map2[j][i] == '*')
					DrawSprite(castletile,buffer,((i*64)%1024), ((j*48)%768), 0);
				else if(map2[j][i] == '#')
					DrawSprite(walltile,buffer,((i*64)%1024), ((j*48)%768), 0);
				else if(map2[j][i] == 'b')
					DrawSprite(bloodtile,buffer,((i*64)%1024), ((j*48)%768), 0);
				else if(map2[j][i] == 'd')
					DrawSprite(doortile,buffer,((i*64)%1024), ((j*48)%768), 0);
			}
		}
	}

	if (currentLevel == 3)
	{
		for(i = 0; i < 16; i++)
		{
			for(j = 0;j < 16; j++)
			{
				if(map3[j][i] == 0)
					DrawSprite(bordertile,buffer,((i*64)%1024), ((j*48)%768), 0);
				else if(map3[j][i] == '&')
					DrawSprite(grasstile,buffer,((i*64)%1024), ((j*48)%768), 0);
				else if(map3[j][i] == '*')
					DrawSprite(castletile,buffer,((i*64)%1024), ((j*48)%768), 0);
				else if(map3[j][i] == '#')
					DrawSprite(walltile,buffer,((i*64)%1024), ((j*48)%768), 0);
				else if(map3[j][i] == 'b')
					DrawSprite(bloodtile,buffer,((i*64)%1024), ((j*48)%768), 0);
				else if(map3[j][i] == 'd')
					DrawSprite(doortile,buffer,((i*64)%1024), ((j*48)%768), 0);
			}
		}
	}
*/