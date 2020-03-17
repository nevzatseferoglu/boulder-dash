#include "headers/check.h"

int checkArrayFrontier(int x , int y);
int checkBorder(int x, int y);
int checkEarth(int x, int y);
int checkDiamond(int x , int y);
int checkRock(int x, int y , int direction);
int checkEmpty(int x , int y);


int checkBorder(int x, int y)
{
    if(levels[current.current_level_id].map[x][y] == border)
        return TRUE;
    else
        return FALSE;
}
int checkEmpty(int x , int y)
{
    if(levels[current.current_level_id].map[x][y] == empty)
        return TRUE;
    else
        return FALSE;
}
int checkEarth(int x, int y)
{
    if(levels[current.current_level_id].map[x][y] == earth)
        return TRUE;
    else
        return FALSE;
}
int checkDiamond(int x , int y)
{
    if(levels[current.current_level_id].map[x][y] == diamond)
        return TRUE;
    else
        return FALSE;
}
int checkLevel(int x , int y)
{
    if(levels[current.current_level_id].map[x][y] == levelPort)
        return TRUE;
    else
        return FALSE;
}
int checkRock(int x, int y , int direction)
{
    if(direction == SDL_SCANCODE_LEFT)
    {
        if(levels[current.current_level_id].map[x-1][y] == empty)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
        
    }
    else if(direction == SDL_SCANCODE_RIGHT )
    {
        if(levels[current.current_level_id].map[x+1][y] == empty)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
        
    }
    else
        return FALSE;

}
int checkArrayFrontier(int x , int y)
{
    int i , j;
    
    for(i = 0 ; i < levels[current.current_level_id].width ; ++i)
    {
        if(levels[current.current_level_id].map[i][0] == levels[current.current_level_id].map[x][y])
            return FALSE;    
    }
    
    for(i = 0 ; i < levels[current.current_level_id].width ; ++i)
    {
        if(levels[current.current_level_id].map[i][levels[current.current_level_id].height-1] == levels[current.current_level_id].map[x][y])
            return FALSE;    
    }

    for(j = 0 ; j < levels[current.current_level_id].height ; ++j)
    {
        if(levels[current.current_level_id].map[0][j] == levels[current.current_level_id].map[x][y])
            return FALSE;    
    }

    for(j = 0 ; j < levels[current.current_level_id].height ; ++j)
    {
        if(levels[current.current_level_id].map[levels[current.current_level_id].width-1][j] == levels[current.current_level_id].map[x][y])
            return FALSE;    
    }
    return TRUE;
}