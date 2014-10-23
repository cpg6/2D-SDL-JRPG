/*
#include entity.h

Entity * __entityList = Null;
int __MaxEntities = 0;

void initEntityList()
{
	//load entity config from file
	__entityList = (Entity *)malloc(sizeof(Entity)*__MaxEntities);
	if (__entityList == NULL)
	{
		fprintf(stderr, "initEntityList: FATAL: cannot allocate entity list \n");
		exit(-1);
		return;
	}
	memset(__entityList,0,sizeof(Entity)*__MaxEntities);

}

void closeEntityList();
void drawEntityList();
void updateEntityList();
void thinkEntityList();

Entity *ntEntity()
{
	for (i = 0; i < __MaxEntities; i++)
	{
		if (__entityList[i].used == 0)
		{
			__entityList[i].used = 1;
			return & __entityList[i];
		}
	}
	return NULL;
}

void freeEntity(Entity **ent)
{
	//handle free resources like Sprite data
	memset(*ent,0,sizeof(Entity));
	*ent = NULL;
}

*/