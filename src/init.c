#include "headers/init.h"

static int initFlag = SDL_INIT_EVERYTHING;
static int rendererFlag = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ;
static int windowFlag = SDL_WINDOW_OPENGL;
static int rendererIndex = -1;      /* The index of the rendering driver to initizalize the first oen supporting the requested flags */
static int imgFlag = IMG_INIT_PNG;

void initSDL(void)
{
    if( SDL_Init(initFlag) < 0 )
    {
        fprintf(stderr,"SDL could not be initialized ! SDL Error : %s",SDL_GetError());
        exit(-1); // escape statement to exit
    }

    gameTools.window = SDL_CreateWindow("Boulder Dash",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        SCREEN_WIDTH,
                        SCREEN_HEIGHT,
                        windowFlag);
    if(!gameTools.window)
    {
        fprintf(stderr,"Window could not be initialized ! SDL Error : %s",SDL_GetError());
        exit(-1); // escape statement to exit
    }
    gameTools.renderer = SDL_CreateRenderer(gameTools.window,
                                            rendererIndex,
                                            rendererFlag);
    if(!gameTools.renderer)
    {
        fprintf(stderr,"Renderer could not be initialized ! SDL Error : %s",SDL_GetError());
        exit(-1);
    }
                        
    if( !(IMG_Init(imgFlag) & imgFlag) )
    {
        fprintf(stderr,"IMG_Init could not be initialized ! IMG Error : %s",IMG_GetError());
        exit(-1);
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        fprintf(stderr,"SDL_mixer could not be initialized! SDL_mixer Error: %s\n", Mix_GetError() );
        exit(-1);
    }
    if(TTF_Init())
    {
        fprintf(stderr,"SDL_ttf could not be initialized! SDL_ttf Error : %s\n",TTF_GetError());
        exit(-1);
    }
}
void initGame(void)
{
    int i = 0;

    for(i = 0 ; i < TEXT_NUMBER ; ++i)
        memset(boards+i,0,sizeof(boards[i]));

    for(i = 0 ; i < LEVEL_NUMBER ; ++i)
        memset(levels+i,0,sizeof(levels[i]));

    memset(&current,0,sizeof(current));
    memset(&state,0,sizeof(state));
    
    state.startScreen = TRUE;
    
    state.cursorPos.x = 450;
    state.cursorPos.y = 445;
    state.startGamePos.x = 450;
    state.startGamePos.y = 445;
    state.howToPlayPos.x = 450;
    state.howToPlayPos.y = 505;
    state.exitGamePos.x = 450;
    state.exitGamePos.y = 565;

}
void releaseTools(void)
{
    int i , j;

    SDL_DestroyWindow(gameTools.window);
    gameTools.window = NULL;
    
    SDL_DestroyRenderer(gameTools.renderer);
    gameTools.renderer = NULL;
    
    Mix_FreeMusic(sounds.backgroundMusic);
    sounds.backgroundMusic = NULL;

    Mix_FreeMusic(sounds.startScreenMusic);
    sounds.startScreenMusic = NULL;

    Mix_FreeChunk( sounds.collectDiamond );
    sounds.collectDiamond = NULL;

    Mix_FreeChunk( sounds.gameover );
    sounds.gameover = NULL;

    Mix_FreeChunk( sounds.levelUp );
    sounds.levelUp = NULL;

    Mix_FreeChunk( sounds.dropRock );
    sounds.dropRock = NULL;

    Mix_FreeChunk( sounds.moveEarth );
    sounds.moveEarth = NULL;

    for(i = 0 ; i < TEXT_NUMBER ; ++i)
    {
        SDL_DestroyTexture(boards[i].texture);
        boards[i].texture = NULL;
        
        if(i<4)
        free(boards[i].message);

        TTF_CloseFont(boards[i].font);
        boards[i].font = NULL;
    }

    for(i = 0 ; i < LEVEL_NUMBER ; ++i)
    {
        for(j = 0  ; j < EMPTY_TILE__TYPE_AMOUNT ; ++j)
        {
            SDL_DestroyTexture(levels[i].gameTexture.emptyTexture[j]);
                levels[i].gameTexture.emptyTexture[j] = NULL;
        }
        for(j = 0  ; j < BORDER_TILE__TYPE_AMOUNT ; ++j)
        {
            SDL_DestroyTexture(levels[i].gameTexture.borderTexture[j]);
                levels[i].gameTexture.borderTexture[j] = NULL;
        }
        for(j = 0  ; j < EARTH_TILE__TYPE_AMOUNT ; ++j)
        {
            SDL_DestroyTexture(levels[i].gameTexture.earthTexture[j]);
                levels[i].gameTexture.earthTexture[j] = NULL;
        } 
        for(j = 0  ; j < DIAMOND_TILE__TYPE_AMOUNT ; ++j)
        {
            SDL_DestroyTexture(levels[i].gameTexture.diamondTexture[j]);
                levels[i].gameTexture.diamondTexture[j] = NULL;
        }
        for(j = 0  ; j < LEVELPORT_TILE__TYPE_AMOUNT ; ++j)
        {
            SDL_DestroyTexture(levels[i].gameTexture.levelPortTexture[j]);
                levels[i].gameTexture.levelPortTexture[j] = NULL;
        }
        for(j = 0  ; j < ROCK_TILE__TYPE_AMOUNT ; ++j)
        {
            SDL_DestroyTexture(levels[i].gameTexture.rockTexture[j]);
                levels[i].gameTexture.rockTexture[j] = NULL;
        }
        for(j = 0  ; j < SPIDER_TILE__TYPE_AMOUNT ; ++j)
        {
            SDL_DestroyTexture(levels[i].gameTexture.spiderTexture[j]);
                levels[i].gameTexture.spiderTexture[j] = NULL;
        }

        for(j = 0  ; j < STANDING ; ++j)
        {
            SDL_DestroyTexture(levels[i].gameTexture.miner.standingAnimation[j]);
                levels[i].gameTexture.miner.standingAnimation[j] = NULL;
        }

        for(j = 0  ; j < RIGHT_WALKING ; ++j)
        {
            SDL_DestroyTexture(levels[i].gameTexture.miner.walkingRightAnimation[j]);
                levels[i].gameTexture.miner.walkingRightAnimation[j] = NULL;
        }

        for(j = 0  ; j < LEFT_WALKING ; ++j)
        {
            SDL_DestroyTexture(levels[i].gameTexture.miner.walkingLeftAnimation[j]);
                levels[i].gameTexture.miner.walkingLeftAnimation[j] = NULL;
        }

        for(j = 0  ; j < UP_WALKING ; ++j)
        {
            SDL_DestroyTexture(levels[i].gameTexture.miner.walkingUpAnimation[j]);
                levels[i].gameTexture.miner.walkingUpAnimation[j] = NULL;
        }

        for(j = 0  ; j < DOWN_WALKING ; ++j)
        {
            SDL_DestroyTexture(levels[i].gameTexture.miner.walkingDownAnimation[j]);
                levels[i].gameTexture.miner.walkingDownAnimation[j] = NULL;
        }
    }
    
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}