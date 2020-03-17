#include "src/headers/main.h"

int main()
{
    initSDL();
    initGame();
    initStage();
    loadMedia();
    
    oldTime = SDL_GetTicks();

    while(quit)
    {
        prepareWindow();
        doInput();
        
        gameTools.gameParts.logic();
        gameTools.gameParts.draw();

        presentWindow();
        SDL_Delay(98);
    }

    releaseTools();
    return 0;
}