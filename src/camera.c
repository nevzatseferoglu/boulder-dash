#include "headers/camera.h"
void doCamera(void)
{
    current.centerPos.x = (SCREEN_WIDTH/2);
	current.centerPos.y = (SCREEN_HEIGHT/2);

    
    gameTools.camera.x = ((current.minerPos.x)*TILE_SIZE + TILE_SIZE/2 - current.centerPos.x);
    gameTools.camera.y = ((current.minerPos.y)*TILE_SIZE + TILE_SIZE/2 - current.centerPos.y);


    if(gameTools.camera.x < 0)
    {
        gameTools.camera.x = 0;
    }
    if(gameTools.camera.y < 0)
    {
        gameTools.camera.y = 0;
    }

    if( gameTools.camera.x > levels[current.current_level_id].width*TILE_SIZE - SCREEN_WIDTH)
    {
        gameTools.camera.x = levels[current.current_level_id].width*TILE_SIZE - SCREEN_WIDTH;
    }
    if( gameTools.camera.y > levels[current.current_level_id].height*TILE_SIZE - SCREEN_HEIGHT)
    {
        gameTools.camera.y = levels[current.current_level_id].height*TILE_SIZE - SCREEN_HEIGHT;
    }
}