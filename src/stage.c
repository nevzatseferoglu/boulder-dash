#include "headers/stage.h"

static void logic(void);
static void draw(void);

void initStage(void)
{
	gameTools.gameParts.logic = logic;
	gameTools.gameParts.draw = draw;
	
	initMap();
}
static void logic(void)
{
	doPlayer();
	doCamera();
}
static void draw(void)
{
	if(state.startScreen)
		startScreen();
	else if(state.endGame)
		endSceen();
	else
		drawMap();
}	