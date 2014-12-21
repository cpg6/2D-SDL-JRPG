#include <stdlib.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
#include "level.h"
#include "character.h"
#include "collision.h"
#include "enemy.h"
#include "button.h"



extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect Camera;
Map maps[MAX_MAPS];
int g_currentLevel;
int g_enemySpawned;
int g_combatState;

void Init_All();


/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{

	SDL_Surface *temp, *temp2;
	SDL_Surface *bg;
	SDL_Surface *fontSurface1, *fontSurface2, *fontSurface3, *fontSurface4, *fontSurface5, *fontSurface6, *fontSurface7, *fontSurface8, *fontdamage,
		*fontSurface9, *fontSurface10, *fontSurface11, *fontSurface12, *fontSurface13, *fontSurface14;
	SDL_Surface *menuScreen;
	

	Sprite *bordertile, *grasstile, *castletile, *walltile, *bloodtile, *doortile, *enemy_ettin, *enemy_bishop, *combat_bg; 
	Sprite *fightericon, *mageicon, *selector;
	character* c1;
	ettin* e1;
	bishop* b1;
	fighter* f1;
	mage* m1;
	attackButton* ab1;
	blockButton* bb1;

	char *map_files[MAX_MAPS] = 
	{	
	"levels/map1.txt",
	"levels/map2.txt",
	"levels/map3.txt"
	};
	

	int collision1, collision2, mx, my, damage;
	int done, keyn,x , tempExp, tempExp2, fighterFlag, mageFlag, fighterTurn, mageTurn;
	Uint8 *keys;
	Init_All();
	TTF_Init();
																		

	g_currentLevel = 0;														/** Set current level to first as default */
	g_enemySpawned = 0;														/** Wound up not needing this -- FIXTHIS -- */
	g_combatState = 0;														/** Set initial combat state to false or 0*/
	
	temp = IMG_Load("images/battle.png");									/** load the battle stage background into memory*/
	temp2 = IMG_Load("images/menubg.png");									/** load menu background into memory */

	bordertile = LoadSprite("images/border.png",64,48);						/** load all tile sprites into memory */
	grasstile = LoadSprite("images/deadgrass.png",64,48);					/** load all tile sprites into memory */
	castletile = LoadSprite("images/castletile.png",64,48);					/** load all tile sprites into memory */
	walltile = LoadSprite("images/wall.png",64,48);
	bloodtile = LoadSprite("images/blood.png",64,48);
	doortile = LoadSprite("images/door.png",64,48);
	enemy_ettin = LoadSprite("images/ettin.png",36, 48);
	enemy_bishop = LoadSprite("images/bishop.png",36, 48);
	combat_bg = LoadSprite("images/battle.png",1024,768);
	fightericon = LoadSprite("images/fighter_icon.png",192,272);
	mageicon = LoadSprite("images/mage_icon.png",192,272);
	selector = LoadSprite("images/selector.png",60,72);

    c1 = (character*) malloc(sizeof(character));							/**allocate memory for all objects/entities and init them! */
	e1 = (ettin*) malloc(sizeof(ettin));
	b1 = (bishop*) malloc(sizeof(bishop));
	f1 = (fighter*) malloc(sizeof(fighter));
	m1 = (mage*) malloc(sizeof(mage));
	ab1 = (attackButton*) malloc(sizeof(attackButton));
	bb1 = (blockButton*) malloc(sizeof(blockButton));

	
    InitCharacter(c1);
	InitEttin(e1);
	InitBishop(b1);
	InitFighter(f1);
	InitMage(m1);



	
	TTF_Font* font = TTF_OpenFont("fonts/font1.ttf",24);
	TTF_Font* dmgfont = TTF_OpenFont("fonts/font.ttf",48);
	SDL_Color textColor = {176,6,6};
	SDL_Color dmgColor = {255,255,255};



	SDL_Rect textLoc1 = {100, 100, 0, 0};									/** SDL 1.2 Sucks, cant handle text very well, makes for very ineffecient stuff*/
	SDL_Rect textLoc9 = {100, 125, 0, 0};
	SDL_Rect textLoc11= {100, 150, 0, 0};
	SDL_Rect textLoc13= {100, 175, 0, 0};
	SDL_Rect textLoc2 = {100, 200, 0, 0};
	SDL_Rect textLoc3 = {100, 225, 0, 0};
	SDL_Rect textLoc4 = {100, 250, 0, 0};
	SDL_Rect textLoc5 = {100, 400, 0, 0};
	SDL_Rect textLoc10= {100, 425, 0, 0};
	SDL_Rect textLoc12= {100, 450, 0, 0};
	SDL_Rect textLoc14= {100, 475, 0, 0};
	SDL_Rect textLoc6 = {100, 500, 0, 0};
	SDL_Rect textLoc7 = {100, 525, 0, 0};
	SDL_Rect textLoc8 = {100, 550, 0, 0};
	
	
	
	
	SDL_Rect dmgLoc1  = {208, 497, 0, 0};

	for(x=0;x<MAX_MAPS; x++)												/** Load the maps from text files into memory */
		loadMap(&maps[x],map_files[x]);
	TeleportCharacter(c1,g_currentLevel);									/**Conduct the first teleport of the character at start */
    done = 0;
    do
    {
		keys = SDL_GetKeyState(&keyn);
		//==================================================================================
		// Menu Screen Begin
		//==================================================================================

		char fighterAttack[12];
		sprintf(fighterAttack,"Attack: %i", f1->attack);
		char fighterDefense[12];
		sprintf(fighterDefense,"Defense: %i", f1->defense);
		char fighterExp[18];
		sprintf(fighterExp, "Experience: %4.2f", f1->exp);
		char mageAttack[12];
		sprintf(mageAttack, "Attack: %i", m1->attack);
		char mageDefense[12];
		sprintf(mageDefense, "Defense: %i", m1->defense);
		char mageExp[18];
		sprintf(mageExp, "Experience: %4.2f", m1->exp);
		char fighterLvl[20];
		sprintf(fighterLvl, "Current Level: %i", f1->lvl);
		char mageLvl[20];
		sprintf(mageLvl, "Current Level: %i", m1->lvl);
		char fighterhp[20];
		sprintf(fighterhp,"HP: %i",f1->hp);
		char magehp[20];
		sprintf(magehp,"HP: %i",m1->hp);
		char magemaxhp[20];
		sprintf(magemaxhp,"MaxHP: %i", m1->maxhp);
		char fightermaxhp[20];
		sprintf(fightermaxhp,"MaxHP: %i", f1->maxhp);


		fontSurface1 = TTF_RenderText_Solid(font,"Fighter",textColor);
		fontSurface9 = TTF_RenderText_Solid(font,fighterLvl, textColor);
		fontSurface11= TTF_RenderText_Solid(font,fighterhp,textColor);
		fontSurface13= TTF_RenderText_Solid(font,fightermaxhp,textColor);
		fontSurface2 = TTF_RenderText_Solid(font,fighterAttack,textColor);
		fontSurface3 = TTF_RenderText_Solid(font,fighterDefense,textColor);
		fontSurface4 = TTF_RenderText_Solid(font,fighterExp,textColor);
		fontSurface5 = TTF_RenderText_Solid(font,"Mage",textColor);
		fontSurface10= TTF_RenderText_Solid(font,mageLvl,textColor);
		fontSurface12= TTF_RenderText_Solid(font,magehp,textColor);
		fontSurface14= TTF_RenderText_Solid(font,magemaxhp,textColor);
		fontSurface6 = TTF_RenderText_Solid(font,mageAttack,textColor);
		fontSurface7 = TTF_RenderText_Solid(font,mageDefense,textColor);
		fontSurface8 = TTF_RenderText_Solid(font,mageExp,textColor);
		
		if(keys[SDLK_k])													/** text test */
		{

			if(temp2 != NULL)						
				menuScreen = SDL_DisplayFormat(temp2);

			if(menuScreen != NULL)
				SDL_BlitSurface(menuScreen,NULL,buffer,NULL);

			SDL_BlitSurface(fontSurface1, NULL, buffer, &textLoc1);
			SDL_BlitSurface(fontSurface9, NULL, buffer, &textLoc9);
			SDL_BlitSurface(fontSurface11, NULL, buffer, &textLoc11);
			SDL_BlitSurface(fontSurface13, NULL, buffer, &textLoc13);
			SDL_BlitSurface(fontSurface2, NULL, buffer, &textLoc2);
			SDL_BlitSurface(fontSurface3, NULL, buffer, &textLoc3);
			SDL_BlitSurface(fontSurface4, NULL, buffer, &textLoc4);
			SDL_BlitSurface(fontSurface5, NULL, buffer, &textLoc5);
			SDL_BlitSurface(fontSurface10, NULL, buffer, &textLoc10);
			SDL_BlitSurface(fontSurface12, NULL, buffer, &textLoc12);
			SDL_BlitSurface(fontSurface14, NULL, buffer, &textLoc14);
			SDL_BlitSurface(fontSurface6, NULL, buffer, &textLoc6);
			SDL_BlitSurface(fontSurface7, NULL, buffer, &textLoc7);
			SDL_BlitSurface(fontSurface8, NULL, buffer, &textLoc8);

			DrawSprite(fightericon,buffer,512,100,0);
			DrawSprite(mageicon,buffer,512,384,0);
			SDL_Flip(screen);

		}

		//==================================================================================
		// Menu Screen End
		//==================================================================================

		collision1 = checkCollision(c1->collision,b1->collision);			/** Continuously check if there is a collision detected */
		collision2 = checkCollision(c1->collision,e1->collision);			/** Continuously check if there is a collision detected */
		if (collision1 == 1)
		{
			printf("COLLISION DETECTED!!!!!!! BISHOP \n");					/** if collided w/ bishop set combat state and Init */
			g_combatState = 1;
			InitAttackButton(ab1);
			InitBlockButton(bb1);
		}
		if (collision2 == 1)
		{
			printf("COLLISION DETECTED!!!!!!! ETTIN \n");					/** if collided w/ ettin set combat state and Init */
			g_combatState = 2;
			InitAttackButton(ab1);
			InitBlockButton(bb1);
		}
		
		ResetBuffer ();



		//==================================================================================
		// Combat Loop Begin, STATES WITH TYPES OF ENEMIES
		//==================================================================================

		while (g_combatState > 0)											/** Loop for combat screen */
		{
			keys = SDL_GetKeyState(&keyn);
			ResetBuffer ();
			bg = SDL_DisplayFormat(temp);
			fighterFlag = 1;
			mageFlag = 1;
			fighterTurn = 0;
			mageTurn = 0;

			if (g_combatState == 1)											/** if collided with a bishop, enter combat with a bishop */
			{
				if(temp != NULL)						
					bg = SDL_DisplayFormat(temp);

				if(bg != NULL)
					SDL_BlitSurface(bg,NULL,buffer,NULL);					/** Draw the combat background */
				SDL_Flip(buffer);
				DrawPCs(f1, m1, screen);									/** Draw the playable characters to the screen */
				DrawEnemy_C(b1, e1, g_combatState, screen);					/** Draw Enemy Combatants */
				DrawButton_C(ab1,bb1,screen);								/** Draw GUI buttons to screen */
				
				DrawMouse();
					
				//if(fighterFlag)
				//{
					f1->time = f1->time + SDL_GetTicks();						/** Start Fighter Timer */
					if (f1->time > 700000)
					{
						mageFlag = 0;												/** set flag to false to stop its counter */
						DrawSprite(selector,screen,f1->x-6,f1->y-6,0);				/** Selector Test */
						if(SDL_GetMouseState(&mx,&my) && (( mx > ab1->collision.x ) && ( mx < ab1->collision.x + ab1->collision.w ) &&	
							( my > ab1->collision.y ) && ( my < ab1->collision.y + ab1->collision.h )))										/** check collision on attack button and mouse press*/
						{
							b1->health = (b1->health + b1->defense) - f1->attack;
							damage = f1->attack - b1->defense;
							char numDamage[10];
							sprintf(numDamage,"%i",damage);
							fontdamage = TTF_RenderText_Solid(dmgfont,numDamage,dmgColor);
							SDL_BlitSurface(fontdamage, NULL, screen, &dmgLoc1);
							SDL_Flip(screen);
							printf("COLLISION DETECTED!!!!!!! \n");
							f1->time = 0;
							mageFlag = 1;
							SDL_Flip(screen);
						}
						/* ===Not done yet===
						else if(SDL_BUTTON_LEFT && (( mx > bb1->collision.x ) && ( mx < bb1->collision.x + bb1->collision.w ) && 
							( my > bb1->collision.y ) && ( my < bb1->collision.y + bb1->collision.h )))
						{
							b1->health = b1->health - f1->attack + b1->defense;
							printf("COLLISION DETECTED!!!!!!! \n");
						}
						*/
					}
				//}

				//if(mageFlag)
				//{
					m1->time = m1->time + SDL_GetTicks();						/** Start Mage Timer */
					if (m1->time > 900000)
					{
						fighterFlag = 0;											/** set flag to false to stop its counter */
						DrawSprite(selector,screen,m1->x-6,m1->y-6,0);				/** Selector Test */
						if(SDL_GetMouseState(&mx,&my) && (( mx > ab1->collision.x ) && ( mx < ab1->collision.x + ab1->collision.w ) &&	
							( my > ab1->collision.y ) && ( my < ab1->collision.y + ab1->collision.h )))										/** check collision on attack button and mouse press*/
						{
							b1->health = (b1->health + b1->defense) - m1->attack;
							damage = m1->attack - b1->defense;
							char numDamage[10];
							sprintf(numDamage,"%i",damage);
							fontdamage = TTF_RenderText_Solid(dmgfont,numDamage,dmgColor);
							SDL_BlitSurface(fontdamage, NULL, screen, &dmgLoc1);
							SDL_Flip(screen);
							printf("COLLISION DETECTED!!!!!!! \n");
							m1->time = 0;
							fighterFlag = 1;										/**set flag back to true to resume counter */
							SDL_Flip(screen);
						}
						/* ===Not done yet===
						else if(SDL_BUTTON_LEFT && (( mx > bb1->collision.x ) && ( mx < bb1->collision.x + bb1->collision.w ) && 
							( my > bb1->collision.y ) && ( my < bb1->collision.y + bb1->collision.h )))
						{
							b1->health = b1->health - f1->attack + b1->defense;
							printf("COLLISION DETECTED!!!!!!! \n");
						}
						*/
					}
					
				//}


			}

			if (g_combatState == 2)											/** if collided with a ettin, enter combat with a ettin */
			{
				if(temp != NULL)						
					bg = SDL_DisplayFormat(temp);

				if(bg != NULL)
					SDL_BlitSurface(bg,NULL,buffer,NULL);					/** Draw the combat background */
				SDL_Flip(buffer);
				DrawPCs(f1, m1, screen);									/** Draw the playable characters to the screen */
				DrawEnemy_C(b1, e1, g_combatState, screen);					/** Draw Enemy Combatants */
				DrawButton_C(ab1,bb1,screen);								/** Draw GUI buttons to screen */
				DrawMouse();

				//if(fighterFlag)
				//{
					f1->time = f1->time + SDL_GetTicks();						/** Start Fighter Timer */
					if (f1->time > 700000)
					{
						mageFlag = 0;												/** set flag to false to stop its counter */
						DrawSprite(selector,screen,f1->x-6,f1->y-6,0);				/** Selector Test */
						if(SDL_GetMouseState(&mx,&my) && (( mx > ab1->collision.x ) && ( mx < ab1->collision.x + ab1->collision.w ) &&	
							( my > ab1->collision.y ) && ( my < ab1->collision.y + ab1->collision.h )))										/** check collision on attack button and mouse press*/
						{
							e1->health = (e1->health + e1->defense) - f1->attack;
							damage = f1->attack - b1->defense;
							char numDamage[10];
							sprintf(numDamage,"%i",damage);
							fontdamage = TTF_RenderText_Solid(dmgfont,numDamage,dmgColor);
							SDL_BlitSurface(fontdamage, NULL, screen, &dmgLoc1);
							SDL_Flip(screen);
							printf("COLLISION DETECTED!!!!!!! \n");
							f1->time = 0;
							mageFlag = 1;
							SDL_Flip(screen);
						}
						/* ===Not done yet===
						else if(SDL_BUTTON_LEFT && (( mx > bb1->collision.x ) && ( mx < bb1->collision.x + bb1->collision.w ) && 
							( my > bb1->collision.y ) && ( my < bb1->collision.y + bb1->collision.h )))
						{
							b1->health = b1->health - f1->attack + b1->defense;
							printf("COLLISION DETECTED!!!!!!! \n");
						}
						*/
					}
				//}

				//if(mageFlag)
				//{
					m1->time = m1->time + SDL_GetTicks();						/** Start Fighter Timer */
					if (m1->time > 900000)
					{
						fighterFlag = 0;											/** set flag to false to stop its counter */
						DrawSprite(selector,screen,m1->x-6,m1->y-6,0);				/** Selector Test */
						if(SDL_GetMouseState(&mx,&my) && (( mx > ab1->collision.x ) && ( mx < ab1->collision.x + ab1->collision.w ) &&	
							( my > ab1->collision.y ) && ( my < ab1->collision.y + ab1->collision.h )))										/** check collision on attack button and mouse press*/
						{
							e1->health = (e1->health + e1->defense) - m1->attack;
							damage = m1->attack - b1->defense;
							char numDamage[10];
							sprintf(numDamage,"%i",damage);
							fontdamage = TTF_RenderText_Solid(dmgfont,numDamage,dmgColor);
							SDL_BlitSurface(fontdamage, NULL, screen, &dmgLoc1);
							SDL_Flip(screen);
							printf("COLLISION DETECTED!!!!!!! \n");
							m1->time = 0;
							fighterFlag = 1;
							SDL_Flip(screen);
						}
						/* ===Not done yet===
						else if(SDL_BUTTON_LEFT && (( mx > bb1->collision.x ) && ( mx < bb1->collision.x + bb1->collision.w ) && 
							( my > bb1->collision.y ) && ( my < bb1->collision.y + bb1->collision.h )))
						{
							b1->health = b1->health - f1->attack + b1->defense;
							printf("COLLISION DETECTED!!!!!!! \n");
						}
						*/	
					}
				//}
			}
			NextFrame();
			SDL_PumpEvents();
			SDL_Flip(screen);

		//==================================================================================
		// Combat Loop: END STATES AND EXPERIENCE/STAT HANDLING
		//==================================================================================

			if(b1->health <= 0 && g_combatState == 1)						/** If fighting a bishop and his HP goes below 0 End */
			{
				g_combatState = 0;
				f1->exp = f1->exp + b1->exp;								/**Add exp to both the fighter and the mage */
				m1->exp = m1->exp + b1->exp;
				if (f1->exp > f1->nextlvl)									/** Condition to check for a level up*/
				{
					f1->nextlvl = f1->nextlvl + (f1->nextlvl * .25);		/** if leveled up, increase stats */
					f1->exp = 0;
					f1->attack = f1->attack + 3;						
					f1->defense = f1->defense +3;
					f1->lvl = f1->lvl + 1;
					f1->maxhp = f1->maxhp + (f1->maxhp *.1);
					f1->hp = f1->maxhp;
					SDL_Delay(1500);										/** Delay for printing text to the screen for level up */

				}

				if (m1->exp > m1->nextlvl)									/** Condition to check for a level up*/
				{
					m1->nextlvl = m1->nextlvl + (m1->nextlvl * .25);		/** if leveled up, increase stats */
					m1->exp = 0;
					m1->attack = m1->attack + 1;
					m1->defense = m1->defense +1;
					m1->lvl = m1->lvl + 1;
					m1->maxhp = m1->maxhp + (m1->maxhp *.1);
					m1->hp = m1->maxhp;
					SDL_Delay(1500);										/** Delay for printing text to the screen for level up */

				}
				SDL_FreeSurface(bg);										/** Free the surface before ending the loop at the end */
				FreeBishop(b1);												/** FIXTHIS -- removes from the map in other levels as well */
			}

			if(e1->health <= 0 && g_combatState == 2)						/** If fighting an ettin and his HP goes below 0 End */
			{
				g_combatState = 0;
				f1->exp = f1->exp + e1->exp;								/**Add exp to both the fighter and the mage */
				m1->exp = m1->exp + e1->exp;
				if (f1->exp > f1->nextlvl)									/** Condition to check for a level up*/
				{
					f1->nextlvl = f1->nextlvl + (f1->nextlvl * .25);        /** if leveled up, increase stats */
					f1->exp = 0; 
					f1->attack = f1->attack + 3;
					f1->defense = f1->defense +3;
					f1->lvl = f1->lvl + 1;
					f1->maxhp = f1->maxhp + (f1->maxhp *.1);
					f1->hp = f1->maxhp;
					SDL_Delay(1500);										/** Delay for printing text to the screen for level up */
				}

				if (m1->exp > m1->nextlvl)									/** Condition to check for a level up*/
				{
					m1->nextlvl = m1->nextlvl + (m1->nextlvl * .25);		/** if leveled up, increase stats */
					m1->exp = 0;
					m1->attack = m1->attack + 1;
					m1->defense = m1->defense +1;
					m1->lvl = m1->lvl + 1;
					m1->maxhp = m1->maxhp + (m1->maxhp *.1);
					m1->hp = m1->maxhp;
					SDL_Delay(1500);										/** Delay for printing text to the screen for level up */
				}
				SDL_FreeSurface(bg);										/** Free the surface before ending the loop at the end */
				FreeEttin(e1);												/** FIXTHIS -- removes from the map in other levels as well */
				SDL_Flip(screen);
			}
		}

		//==================================================================================
		// END Combat Loop
		//==================================================================================

		
		CharacterMove(c1,keys);
		EnemyThink(b1, e1, screen);
		
		if(keys[SDLK_k])													/** Stop Drawing the level if on the menu screen */
			done = 0;
		else
			drawLevel(g_currentLevel,bordertile, grasstile, castletile, walltile, bloodtile, doortile, &maps[g_currentLevel], enemy_ettin, enemy_bishop, g_enemySpawned); /*draw level*/
		
		if(keys[SDLK_k])													/** Stop Drawing the character if on the menu screen */
			done = 0;
		else
			DrawCharacter(c1,screen,g_currentLevel);
		
		if(keys[SDLK_k])													/** Stop Drawing the Enemies if on the menu screen */
			done = 0;
		else
			DrawEnemy(b1,e1,screen,g_currentLevel,g_enemySpawned);
		SDL_Flip(screen);
		NextFrame();
		SDL_PumpEvents();
		if(keys[SDLK_ESCAPE])done = 1;
  }while(!done);															/** End of the main game loop */

  FreeCharacter(c1);
  CloseSprites();
  SDL_FreeSurface(fontSurface1);
  SDL_FreeSurface(fontSurface2);
  SDL_FreeSurface(fontSurface3);
  SDL_FreeSurface(fontSurface4);
  SDL_FreeSurface(fontSurface5);
  SDL_FreeSurface(fontSurface6);
  SDL_FreeSurface(fontSurface7);
  SDL_FreeSurface(fontSurface8);
  SDL_FreeSurface(fontSurface9);
  SDL_FreeSurface(fontSurface10);
  SDL_FreeSurface(fontSurface11);
  SDL_FreeSurface(fontSurface12);
  SDL_FreeSurface(fontSurface13);
  SDL_FreeSurface(fontSurface14);
  TTF_Quit();
  exit(0);		/*technically this will end the program, but the compiler likes all functions that can return a value TO return a value*/
  return 0;
}

void CleanUpAll(void)
{
  CloseSprites();
  /*any other cleanup functions can be added here*/ 
}

void Init_All()
{
  Init_Graphics();
  InitMouse();
  atexit(CleanUpAll);
}
