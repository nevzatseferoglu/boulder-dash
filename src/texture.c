#include "headers/texture.h"

void loadaudios(void);
void load_FontFormat(void);
void LoadExtraImage(void);

SDL_Texture* loadTexture(char* fileName)
{
    SDL_Texture* tempTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(fileName);

    if(!loadedSurface)
    {
        fprintf(stderr,"Surface IMG could not be loaded ! IMG Error %s ",SDL_GetError());
        exit(-1);
    }
    tempTexture = SDL_CreateTextureFromSurface(gameTools.renderer , loadedSurface);

    if(!tempTexture)
    {
        fprintf(stderr,"Texture IMG could not be loaded ! SDL Error %s ",SDL_GetError());
        exit(-1);
    }

    SDL_FreeSurface(loadedSurface);
    return tempTexture ;
}
void loadMedia(void)
{
    for(int i = 0 ; i < LEVEL_NUMBER ; ++i)
    {
        levels[i].gameTexture.miner.standingAnimation[0] = loadTexture("./images/Miner/Standing/s1.png");
        levels[i].gameTexture.miner.standingAnimation[1] = loadTexture("./images/Miner/Standing/s2.png");

        levels[i].gameTexture.miner.walkingRightAnimation[0] = loadTexture("./images/Miner/WalkingRight/r1.png");
        levels[i].gameTexture.miner.walkingRightAnimation[1] = loadTexture("./images/Miner/WalkingRight/r2.png");
        levels[i].gameTexture.miner.walkingRightAnimation[2] = loadTexture("./images/Miner/WalkingRight/r3.png");
        levels[i].gameTexture.miner.walkingLeftAnimation[0] = loadTexture("./images/Miner/WalkingLeft/l1.png");
        levels[i].gameTexture.miner.walkingLeftAnimation[1] = loadTexture("./images/Miner/WalkingLeft/l2.png");
        levels[i].gameTexture.miner.walkingLeftAnimation[2] = loadTexture("./images/Miner/WalkingLeft/l3.png");

        levels[i].gameTexture.miner.walkingUpAnimation[0] = loadTexture("./images/Miner/WalkingUp/u1.png");
        levels[i].gameTexture.miner.walkingUpAnimation[1] = loadTexture("./images/Miner/WalkingUp/u2.png");
        levels[i].gameTexture.miner.walkingUpAnimation[2] = loadTexture("./images/Miner/WalkingUp/u3.png");
        levels[i].gameTexture.miner.walkingUpAnimation[3] = loadTexture("./images/Miner/WalkingUp/u4.png");


        levels[i].gameTexture.miner.walkingDownAnimation[0] = loadTexture("./images/Miner/WalkingDown/d1.png");
        levels[i].gameTexture.miner.walkingDownAnimation[1] = loadTexture("./images/Miner/WalkingDown/d2.png");
        levels[i].gameTexture.miner.walkingDownAnimation[2] = loadTexture("./images/Miner/WalkingDown/d3.png");
        levels[i].gameTexture.miner.walkingDownAnimation[3] = loadTexture("./images/Miner/WalkingDown/d4.png");

        levels[i].gameTexture.emptyTexture[0] = loadTexture("./images/SolidBackground/Empty.png");
        levels[i].gameTexture.borderTexture[0] = loadTexture("./images/SolidBackground/Border.png");
        levels[i].gameTexture.earthTexture[0] = loadTexture("./images/SolidBackground/Earth.png");

        levels[i].gameTexture.diamondTexture[0] = loadTexture("./images/Diamond/Diamond1.png");
        levels[i].gameTexture.diamondTexture[1] = loadTexture("./images/Diamond/Diamond2.png");
        levels[i].gameTexture.diamondTexture[2]  = loadTexture("./images/Diamond/Diamond3.png");
        levels[i].gameTexture.diamondTexture[3]  = loadTexture("./images/Diamond/Diamond4.png");

        levels[i].gameTexture.levelPortTexture[0] = loadTexture("./images/LevelPort/Port1.png");
        levels[i].gameTexture.levelPortTexture[1] = loadTexture("./images/LevelPort/Port2.png");
        levels[i].gameTexture.levelPortTexture[2] = loadTexture("./images/LevelPort/Port3.png");
        levels[i].gameTexture.levelPortTexture[3] = loadTexture("./images/LevelPort/Port4.png");

        levels[i].gameTexture.rockTexture[0] = loadTexture("./images/Rock/Rock1.png");
        levels[i].gameTexture.rockTexture[1] = loadTexture("./images/Rock/Rock2.png");
        levels[i].gameTexture.rockTexture[2] = loadTexture("./images/Rock/Rock3.png");

        levels[i].gameTexture.spiderTexture[0] = loadTexture("./images/Spider/Spider1.png");
        levels[i].gameTexture.spiderTexture[1] = loadTexture("./images/Spider/Spider2.png");
        levels[i].gameTexture.spiderTexture[2] = loadTexture("./images/Spider/Spider3.png");
        levels[i].gameTexture.spiderTexture[3] = loadTexture("./images/Spider/Spider4.png");
    }
    
    LoadExtraImage();
    loadaudios();
}
void loadBackground(void)
{
    int x = 0 , y = 0;
    for(y = 2*(-1)*levels[current.current_level_id].height ; y < 2*levels[current.current_level_id].height ; ++y)
    {
        for(x = 2*(-1)*levels[current.current_level_id].width ; x < 2*levels[current.current_level_id].width ; ++x)
        {
            blit(levels[current.current_level_id].gameTexture.emptyTexture[0] , x*TILE_SIZE , y*TILE_SIZE , TILE_SIZE,TILE_SIZE);
        }
    }
}
void loadaudios(void)
{
    memset(&sounds,0,sizeof(sounds));

    sounds.startScreenMusic = Mix_LoadMUS( "./audios/Title_Screen.wav" );

    if( sounds.startScreenMusic == NULL )
    {
        fprintf( stderr,"Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        exit(-1);
    }

    sounds.backgroundMusic = Mix_LoadMUS( "./audios/Boulder_World.wav" );
    if( sounds.backgroundMusic == NULL )
    {
        fprintf( stderr,"Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        exit(-1);
    }

    sounds.endGame = Mix_LoadMUS( "./audios/rockford.wav" );
    if( sounds.endGame == NULL )
    {
        fprintf( stderr,"Failed to load beat music! Mix Error: %s\n", Mix_GetError() );
        exit(-1);
    }

    sounds.collectDiamond = Mix_LoadWAV("./audios/collectDiamond.wav");
    if(sounds.collectDiamond == NULL)
    {
        fprintf(stderr,"Failed to load chunk diamondCollect ! SDL_mixer Error : %s\n",Mix_GetError());
        exit(-1);
    }

    sounds.dropRock = Mix_LoadWAV("./audios/dropRock.wav");
    if(sounds.dropRock == NULL)
    {
        fprintf(stderr,"Failed to load chunk dropRock ! SDL_mixer Error : %s\n",Mix_GetError());
        exit(-1);
    }

    sounds.moveEarth = Mix_LoadWAV("./audios/moveEarth.wav");
    if(sounds.moveEarth == NULL)
    {
        fprintf(stderr,"Failed to load chunk moveEarth ! SDL_mixer Error : %s\n",Mix_GetError());
        exit(-1);
    }

    sounds.gameover = Mix_LoadWAV("./audios/gameover.wav");
    if(sounds.gameover == NULL)
    {
        fprintf(stderr,"Failed to load chunk gameover ! SDL_mixer Error : %s\n",Mix_GetError());
        exit(-1);
    }

    sounds.levelUp = Mix_LoadWAV("./audios/levelUp.wav");
    if(sounds.levelUp == NULL)
    {
        fprintf(stderr,"Failed to load chunk levelUp ! SDL_mixer Error : %s\n",Mix_GetError());
        exit(-1);
    }
    current.levelUpFlag = TRUE;

    Mix_VolumeChunk(sounds.gameover,CHUNK_VOLUME+100);
    Mix_VolumeChunk(sounds.levelUp,CHUNK_VOLUME+100);
    Mix_VolumeChunk(sounds.moveEarth,CHUNK_VOLUME);
    Mix_VolumeChunk(sounds.dropRock,CHUNK_VOLUME);
    Mix_VolumeChunk(sounds.collectDiamond,CHUNK_VOLUME-15);
    Mix_VolumeMusic(MUSIC_VOLUME);

    Mix_PlayMusic( sounds.startScreenMusic, -1 );
    
}
void LoadExtraImage(void)
{
    scoreBoard = NULL;
    diamondBoard = NULL;
    levelBoard = NULL;
    timeBoard = NULL;
    boulderDash = NULL;
    howtoplay = NULL;
    
    scoreBoard = loadTexture("./images/Board/scoreBoard.png");
    if(!scoreBoard)
    {
        fprintf(stderr,"scoreBoard could not be initialized !");
        exit(-1);
    }

    diamondBoard = loadTexture("./images/Board/diamondBoard.png");
    if(!diamondBoard)
    {
        fprintf(stderr,"diamondBoard could not be initialized !");
        exit(-1);
    }

    timeBoard = loadTexture("./images/Board/timeBoard.png");
    if(!timeBoard)
    {
        fprintf(stderr,"timeBoard could not be initialized !");
        exit(-1);
    }

    levelBoard = loadTexture("./images/Board/levelBoard.png");
    if(!levelBoard)
    {
        fprintf(stderr,"levelBoard could not be initialized !");
        exit(-1);
    }

    boulderDash = loadTexture("./images/Intro/boulderDash.png");
    if(!boulderDash)
    {
        fprintf(stderr,"boulderDash could not be initialized !");
        exit(-1);
    }

    howtoplay = loadTexture("./images/Intro/howtoplay.png");
    if(!howtoplay)
    {
        fprintf(stderr,"how to play could not be initialized !");
        exit(-1);
    }
}
void renderText(void)
{
    int i;
    
    SDL_Color color = {255,255,255,255};
    SDL_Color colorMenu = {255,255,0,255};

    for(i = 0 ; i < TEXT_NUMBER ; ++i)
        memset(boards+i,0,sizeof(boards[i]));

    boards[0].color = color;
    boards[1].color = color;
    boards[2].color = color;
    boards[3].color = color;

    boards[4].color = colorMenu;    /* Start Game    */
    boards[5].color = colorMenu;    /* How to Play   */
    boards[6].color = colorMenu;    /* Exit Game     */
    boards[7].color = colorMenu;    /* Esc           */

    for(i = 0 ; i < TEXT_NUMBER ; ++i)
        boards[i].fontSize = 50;


    for(i = 0 ; i < TEXT_NUMBER ; ++i)
    {
        if(i > 3)
        {
            boards[i].font = TTF_OpenFont("./TrueTypes/gameMenu.ttf",boards[i].fontSize);
            if(boards[i].font == NULL)
            {
                fprintf(stderr,"boards[%d] could not be opened from file ! TTF_Error() : %s",i,TTF_GetError());
                exit(-1);
            }
            TTF_SetFontStyle(boards[i].font ,TTF_STYLE_UNDERLINE);
        }
        else
        {    
            boards[i].font = TTF_OpenFont("./TrueTypes/game.ttf",boards[i].fontSize);
            if(boards[i].font == NULL)
            {
                fprintf(stderr,"boards[%d] could not be opened from file ! TTF_Error() : %s",i,TTF_GetError());
                exit(-1);
            }
            TTF_SetFontStyle(boards[i].font , TTF_STYLE_ITALIC);
        }
    }
    
}