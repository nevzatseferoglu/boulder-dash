#include "headers/drawIssue.h"

void prepareWindow()
{
	SDL_RenderClear(gameTools.renderer);
	if(!state.endGame)
	loadBackground();
	
}

void presentWindow()
{                   
    SDL_RenderPresent(gameTools.renderer);
}

void blit(SDL_Texture *texture, int xPos, int yPos , int w , int h)
{
	SDL_Rect dest;
	
	dest.x = xPos;
	dest.y = yPos;
	dest.w = w;
	dest.h = h;
	
	SDL_RenderCopy(gameTools.renderer, texture, NULL, &dest);
}