#include "headers/map.h"
void loadMap(void);
void drawExtraImage(void);
char* intToString(int number);
void levelUptoBorder(int i);
void frameIncrement(void);
void startScreen(void);
void menu(void);
void endSceen(void);
void scoreTable(void);

int x = 0 , y = 0 , i = 0;

void initMap(void)
{
    loadMap();
    renderText();
}   
void loadMap(void)
{
    char* temp = NULL;
    char fileName[50] = {'\0'};
    
    for(i = 0 ; i < LEVEL_NUMBER ; ++i)
    {
        sprintf (fileName,"levels/level_%d.txt",i+1);
        levels[i].level = readFile(fileName);

        temp = levels[i].level;

        if(levels[i].level == NULL)
        {
            fprintf(stderr,"levels[%d] Char* Variable could not be loaded !\n",i);
            exit(-1);
        }

        levels[i].map = malloc(sizeof(int*)*levels[i].width);

        if (!levels[i].map)
        {
            printf ("\nMemory Allocation Failure !\n\n");
            exit (-1);
        }

        for (int j = 0; j < levels[i].width; j++)
        {
            *(levels[i].map+j) = malloc(sizeof(int)*levels[i].height); 

            if (!*(levels[i].map+j))
            {
                printf ("\nMemory Allocation Failure !\n");
                exit (-1);
            }
        }

        levels[i].saveMap = malloc(sizeof(int*)*levels[i].width);

        if (!levels[i].saveMap)
        {
            printf ("\nMemory Allocation Failure !\n\n");
            exit (-1);
        }

        for (int j = 0; j < levels[i].width; j++)
        {
            *(levels[i].saveMap+j) = malloc(sizeof(int)*levels[i].height); 

            if (!*(levels[i].saveMap+j))
            {
                printf ("\nMemory Allocation Failure !\n");
                exit (-1);
            }
        }

        levels[i].flagMap = malloc(sizeof(int*)*levels[i].width);

        if (!levels[i].flagMap)
        {
            printf ("\nMemory Allocation Failure !\n\n");
            exit (-1);
        }

        for (int j = 0; j < levels[i].width; j++)
        {
            *(levels[i].flagMap+j) = calloc(levels[i].height,sizeof(int)); 

            if (!*(levels[i].flagMap+j))
            {
                printf ("\nMemory Allocation Failure !\n");
                exit (-1);
            }
        }

        levels[i].deathFlag = malloc(sizeof(int*)*levels[i].width);

        if (!levels[i].deathFlag)
        {
            printf ("\nMemory Allocation Failure !\n\n");
            exit (-1);
        }

        for (int j = 0; j < levels[i].width; j++)
        {
            *(levels[i].deathFlag+j) = calloc(levels[i].height,sizeof(int)); 

            if (!*(levels[i].deathFlag+j))
            {
                printf ("\nMemory Allocation Failure !\n");
                exit (-1);
            }
        }
        
        for(y = 0 ; y < levels[i].height ; ++y)
        {
            for(x = 0 ; x < levels[i].width ; ++x)
            {

                if(*temp == 'b')         levels[i].map[x][y] = border       , levels[i].saveMap[x][y] = border;
                else if(*temp == 'd')    levels[i].map[x][y] = diamond      , levels[i].saveMap[x][y] = diamond;
                else if(*temp == '.')    levels[i].map[x][y] = empty        , levels[i].saveMap[x][y] = empty;
                else if(*temp == 'l')    levels[i].map[x][y] = levelPort    , levels[i].saveMap[x][y] = levelPort;
                else if(*temp == 'm')    levels[i].map[x][y] = miner        , levels[i].saveMap[x][y] = miner;
                else if(*temp == 'r')    levels[i].map[x][y] = rock         , levels[i].saveMap[x][y] = rock;
                else if(*temp == 's')    levels[i].map[x][y] = spider       , levels[i].saveMap[x][y] = spider;
                else if(*temp == 'e')    levels[i].map[x][y] = earth        , levels[i].saveMap[x][y] = earth;
                
                if(*(temp+1)== '\n')
                    temp+=2;
                else
                    ++temp;
            }
        }
        levelUptoBorder(i);
        memset(fileName,0,50);
        free(levels[i].level);
        temp = NULL;
    }
}
void drawMap(void)
{
    for(y = 0 ; y < levels[current.current_level_id].height ; y++)
    {
        for(x = 0 ; x < levels[current.current_level_id].width ; x++)
        {
            switch(levels[current.current_level_id].map[x][y])
            {
                case miner:
                    if(current.minerFlag == STANDING_FLAG)
                    blit(levels[current.current_level_id].gameTexture.miner.standingAnimation[levels[current.current_level_id].gameTexture.miner.minerStandingAnimation],x*TILE_SIZE + -gameTools.camera.x,y*TILE_SIZE + -gameTools.camera.y,TILE_SIZE,TILE_SIZE);
                    else if(current.minerFlag == LEFT_WALKING_FLAG)
                    blit(levels[current.current_level_id].gameTexture.miner.walkingLeftAnimation[levels[current.current_level_id].gameTexture.miner.minerWalkingLeftAnimation],x*TILE_SIZE + -gameTools.camera.x,y*TILE_SIZE + -gameTools.camera.y,TILE_SIZE,TILE_SIZE);
                    else if(current.minerFlag == RIGHT_WALKING_FLAG)
                    blit(levels[current.current_level_id].gameTexture.miner.walkingRightAnimation[levels[current.current_level_id].gameTexture.miner.minerWalkingRightAnimation],x*TILE_SIZE + -gameTools.camera.x,y*TILE_SIZE + -gameTools.camera.y,TILE_SIZE,TILE_SIZE);
                    else if(current.minerFlag == UP_WALKING_FLAG)
                    blit(levels[current.current_level_id].gameTexture.miner.walkingUpAnimation[levels[current.current_level_id].gameTexture.miner.minerWalkingUpAnimation],x*TILE_SIZE + -gameTools.camera.x,y*TILE_SIZE + -gameTools.camera.y,TILE_SIZE,TILE_SIZE);
                    else if(current.minerFlag == DOWN_WALKING_FLAG)
                    blit(levels[current.current_level_id].gameTexture.miner.walkingDownAnimation[levels[current.current_level_id].gameTexture.miner.minerWalkingDownAnimation],x*TILE_SIZE + -gameTools.camera.x,y*TILE_SIZE + -gameTools.camera.y,TILE_SIZE,TILE_SIZE);
                break;

                case empty:
                    blit(levels[current.current_level_id].gameTexture.emptyTexture[levels[current.current_level_id].gameTexture.emptyAnimation],x*TILE_SIZE + -gameTools.camera.x,y*TILE_SIZE + -gameTools.camera.y,TILE_SIZE,TILE_SIZE);
                break;

                case border:
                    blit(levels[current.current_level_id].gameTexture.borderTexture[levels[current.current_level_id].gameTexture.borderAnimation],x*TILE_SIZE + -gameTools.camera.x,y*TILE_SIZE + -gameTools.camera.y,TILE_SIZE,TILE_SIZE);
                break;

                case earth:
                    blit(levels[current.current_level_id].gameTexture.earthTexture[levels[current.current_level_id].gameTexture.earthAnimation],x*TILE_SIZE + -gameTools.camera.x,y*TILE_SIZE + -gameTools.camera.y,TILE_SIZE,TILE_SIZE);
                break;

                case diamond:
                    blit(levels[current.current_level_id].gameTexture.diamondTexture[levels[current.current_level_id].gameTexture.diamondAnimation],x*TILE_SIZE + -gameTools.camera.x,y*TILE_SIZE + -gameTools.camera.y,TILE_SIZE,TILE_SIZE);
                break;

                case levelPort:
                    blit(levels[current.current_level_id].gameTexture.levelPortTexture[levels[current.current_level_id].gameTexture.levelPortAnimation],x*TILE_SIZE + -gameTools.camera.x,y*TILE_SIZE + -gameTools.camera.y,TILE_SIZE,TILE_SIZE);
                break;

                case rock:
                    blit(levels[current.current_level_id].gameTexture.rockTexture[levels[current.current_level_id].gameTexture.rockAnimation],x*TILE_SIZE + -gameTools.camera.x,y*TILE_SIZE + -gameTools.camera.y,TILE_SIZE,TILE_SIZE);
                break;

                case spider:
                    blit(levels[current.current_level_id].gameTexture.spiderTexture[levels[current.current_level_id].gameTexture.spiderAnimation],x*TILE_SIZE + -gameTools.camera.x,y*TILE_SIZE + -gameTools.camera.y,TILE_SIZE,TILE_SIZE);
                break;
            }
        }
    }

    frameIncrement();
    drawExtraImage();
}
void drawEntireMap(void)
{
    blit(entireMap , 0 , 0 , SCREEN_WIDTH ,SCREEN_HEIGHT);
}
void drawExtraImage(void)
{
    blit(levelBoard     , 200*1 , 10 , BOARD_WIDTH,BOARD_HEIGHT);
    blit(timeBoard      , 200*2 , 10 , BOARD_WIDTH,BOARD_HEIGHT);
    blit(diamondBoard   , 200*3 , 10 , BOARD_WIDTH,BOARD_HEIGHT);
    blit(scoreBoard     , 200*4 , 10 , 180,BOARD_HEIGHT);

    blit(boards[2].texture , 185*1+50 , 6 , 75,40);      /*     Level   Board   */
    blit(boards[3].texture , 188*2+56 , 6 , 80,40);      /*     Time    Board   */
    blit(boards[1].texture , 191*3+59 , 6 , 80,40);      /*     Diamond Board   */
    blit(boards[0].texture , 188*4+56 , 6, 170,40);      /*     Score   Board   */
}
void levelUptoBorder(int i)
{
    for(y = 0 ; y < levels[i].height ; ++y)
        {
            for(x = 0 ; x < levels[i].width ; ++x)
            {
                if(levels[i].map[x][y] == levelPort)
                {
                    levels[i].levelUpX = x;
                    levels[i].levelUpY = y;
                    levels[i].map[x][y] = border;
                }
                if(levels[i].saveMap[x][y] == levelPort)
                {
                    levels[i].levelUpX = x;
                    levels[i].levelUpY = y;
                    levels[i].saveMap[x][y] = border;
                }
            }
        }
}
void frameIncrement(void)
{
    if(!state.pause || state.startScreen)
    {
        if(current.frameSpeed % 2 == 0)
        {
            ++levels[current.current_level_id].gameTexture.miner.minerStandingAnimation;
            if(levels[current.current_level_id].gameTexture.miner.minerStandingAnimation == STANDING) levels[current.current_level_id].gameTexture.miner.minerStandingAnimation = 0;

            ++levels[current.current_level_id].gameTexture.miner.minerWalkingLeftAnimation;
            if(levels[current.current_level_id].gameTexture.miner.minerWalkingLeftAnimation == LEFT_WALKING) levels[current.current_level_id].gameTexture.miner.minerWalkingLeftAnimation = 0;

            ++levels[current.current_level_id].gameTexture.miner.minerWalkingRightAnimation;
            if(levels[current.current_level_id].gameTexture.miner.minerWalkingRightAnimation == RIGHT_WALKING) levels[current.current_level_id].gameTexture.miner.minerWalkingRightAnimation = 0;

            ++levels[current.current_level_id].gameTexture.miner.minerWalkingUpAnimation;
            if(levels[current.current_level_id].gameTexture.miner.minerWalkingUpAnimation == UP_WALKING) levels[current.current_level_id].gameTexture.miner.minerWalkingUpAnimation = 0;

            ++levels[current.current_level_id].gameTexture.miner.minerWalkingDownAnimation;
            if(levels[current.current_level_id].gameTexture.miner.minerWalkingDownAnimation == DOWN_WALKING) levels[current.current_level_id].gameTexture.miner.minerWalkingDownAnimation = 0;

        }
            ++levels[current.current_level_id].gameTexture.emptyAnimation;
            if(levels[current.current_level_id].gameTexture.emptyAnimation == 1) levels[current.current_level_id].gameTexture.emptyAnimation = 0;

            ++levels[current.current_level_id].gameTexture.borderAnimation;
            if(levels[current.current_level_id].gameTexture.borderAnimation == 1)    levels[current.current_level_id].gameTexture.borderAnimation = 0;

            ++levels[current.current_level_id].gameTexture.earthAnimation;
            if(levels[current.current_level_id].gameTexture.earthAnimation == 1) levels[current.current_level_id].gameTexture.earthAnimation = 0;

            ++levels[current.current_level_id].gameTexture.diamondAnimation;
            if(levels[current.current_level_id].gameTexture.diamondAnimation == 4)   levels[current.current_level_id].gameTexture.diamondAnimation = 0;

            ++levels[current.current_level_id].gameTexture.levelPortAnimation;
            if(levels[current.current_level_id].gameTexture.levelPortAnimation == 4) levels[current.current_level_id].gameTexture.levelPortAnimation = 0;

            ++levels[current.current_level_id].gameTexture.rockAnimation;
            if(levels[current.current_level_id].gameTexture.rockAnimation == 3)  levels[current.current_level_id].gameTexture.rockAnimation = 0;

            ++levels[current.current_level_id].gameTexture.spiderAnimation;
            if(levels[current.current_level_id].gameTexture.spiderAnimation == 4)    levels[current.current_level_id].gameTexture.spiderAnimation = 0;
    }
}
void startScreen(void)
{
    int x = 0 , y = 0;

    if(!(state.startScreen && state.HowToPlay))
    {
        for(y = 2*(-1)*levels[current.current_level_id].height ; y < 2*levels[current.current_level_id].height ; ++y)
        {
            for(x = 2*(-1)*levels[current.current_level_id].width ; x < 2*levels[current.current_level_id].width ; ++x)
            {
                if(x < 4)
                blit(levels[current.current_level_id].gameTexture.rockTexture[levels[current.current_level_id].gameTexture.rockAnimation] , x*TILE_SIZE , y*TILE_SIZE , TILE_SIZE,TILE_SIZE);
                else
                blit(levels[current.current_level_id].gameTexture.emptyTexture[levels[current.current_level_id].gameTexture.emptyAnimation] , x*TILE_SIZE , y*TILE_SIZE , TILE_SIZE,TILE_SIZE);


                if( y > 20 && (x > 3 || x < 20))
                blit(levels[current.current_level_id].gameTexture.earthTexture[levels[current.current_level_id].gameTexture.earthAnimation] , x*TILE_SIZE , y*TILE_SIZE , TILE_SIZE,TILE_SIZE);
                if( x > 38 && y <= 20)
                blit(levels[current.current_level_id].gameTexture.rockTexture[levels[current.current_level_id].gameTexture.rockAnimation] , x*TILE_SIZE , y*TILE_SIZE , TILE_SIZE,TILE_SIZE);
            }
        }

        if(state.boulderDash <= SCREEN_HEIGHT/2 - 300)  blit(boulderDash,SCREEN_WIDTH/2 - 325,state.boulderDash,640,320);
        else                                            blit(boulderDash,SCREEN_WIDTH/2 - 325,SCREEN_HEIGHT/2 - 300,640,320);

        menu();
        frameIncrement();
        state.boulderDash += 4;
    }
    else
    {
        blit(howtoplay,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    }
}
void endSceen(void)
{
        for(y = 2*(-1)*levels[current.current_level_id].height ; y < 2*levels[current.current_level_id].height ; ++y)
        {
            for(x = 2*(-1)*levels[current.current_level_id].width ; x < 2*levels[current.current_level_id].width ; ++x)
            {
                if(x < 4)
                blit(levels[current.current_level_id].gameTexture.rockTexture[levels[current.current_level_id].gameTexture.rockAnimation] , x*TILE_SIZE , y*TILE_SIZE , TILE_SIZE,TILE_SIZE);
                else
                blit(levels[current.current_level_id].gameTexture.emptyTexture[levels[current.current_level_id].gameTexture.emptyAnimation] , x*TILE_SIZE , y*TILE_SIZE , TILE_SIZE,TILE_SIZE);


                if( y > 20 && (x > 3 || x < 20))
                blit(levels[current.current_level_id].gameTexture.earthTexture[levels[current.current_level_id].gameTexture.earthAnimation] , x*TILE_SIZE , y*TILE_SIZE , TILE_SIZE,TILE_SIZE);
                if( x > 38 && y <= 20)
                blit(levels[current.current_level_id].gameTexture.rockTexture[levels[current.current_level_id].gameTexture.rockAnimation] , x*TILE_SIZE , y*TILE_SIZE , TILE_SIZE,TILE_SIZE);
            }
        }

        if(state.boulderDash <= SCREEN_HEIGHT/2 - 300)  blit(boulderDash,SCREEN_WIDTH/2 - 325,state.boulderDash,640,320);
        else                                            blit(boulderDash,SCREEN_WIDTH/2 - 325,SCREEN_HEIGHT/2 - 300,640,320);
        scoreTable();
        frameIncrement();
        state.boulderDash += 4;
}
void menu(void)
{
    if(state.boulderDash > SCREEN_HEIGHT/2 - 300)
    {
        blit(boards[4].texture , 485 , 440 , 260 , 50);
        blit(boards[5].texture , 485 , 440 + 2*TILE_SIZE , 260 , 50);
        blit(boards[6].texture , 485 , 440 + 4*TILE_SIZE , 260 , 50);
        blit(levels[current.current_level_id].gameTexture.miner.walkingRightAnimation[levels[current.current_level_id].gameTexture.miner.minerWalkingRightAnimation] , state.cursorPos.x , state.cursorPos.y , TILE_SIZE , TILE_SIZE);
    }
}
void scoreTable(void)
{
    blit(boards[4].texture,505,440,260,50);
    blit(boards[5].texture,485,580,310,40);
    blit(scoreBoard,485, 440+2*TILE_SIZE,290,BOARD_HEIGHT+30);
    blit(boards[0].texture,390,430+2*TILE_SIZE,280,70);
}