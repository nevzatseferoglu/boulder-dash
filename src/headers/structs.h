enum textureAll{
    miner,empty,border,earth,diamond,levelPort,rock, spider
};

struct gameState{
    int pause;
    int gameover;
    int startScreen;
    int boulderDash;
    SDL_Point cursorPos;
    SDL_Point startGamePos;
    SDL_Point howToPlayPos;
    SDL_Point exitGamePos;
    int startGame;
    int HowToPlay;
    int ExitGame;
    int Esc;
    int endGame;
    int passedLevel;
};

struct Delegate{
	void (*logic)(void);
	void (*draw)(void);
};

struct mainTools{
    SDL_Window* window;
    SDL_Renderer* renderer;
    struct Delegate gameParts;
    int keyboard[MAX_KEYBOARD_KEYS];
    SDL_Point camera;
};

struct minerTools{
    SDL_Texture* standingAnimation[STANDING];
    int minerStandingAnimation;

    SDL_Texture* walkingRightAnimation[RIGHT_WALKING];
    int minerWalkingRightAnimation;

    SDL_Texture* walkingLeftAnimation[LEFT_WALKING];
    int minerWalkingLeftAnimation;

    SDL_Texture* walkingUpAnimation[UP_WALKING];
    int minerWalkingUpAnimation;

    SDL_Texture* walkingDownAnimation[DOWN_WALKING];
    int minerWalkingDownAnimation;
};
struct totalTexture{
    struct minerTools miner;

    SDL_Texture* emptyTexture[EMPTY_TILE__TYPE_AMOUNT];
    int emptyAnimation;

    SDL_Texture* borderTexture[BORDER_TILE__TYPE_AMOUNT];
    int borderAnimation;

    SDL_Texture* earthTexture[EARTH_TILE__TYPE_AMOUNT];
    int earthAnimation;

    SDL_Texture* diamondTexture[DIAMOND_TILE__TYPE_AMOUNT];
    int diamondAnimation;

    SDL_Texture* levelPortTexture[LEVELPORT_TILE__TYPE_AMOUNT];
    int levelPortAnimation;

    SDL_Texture* rockTexture[ROCK_TILE__TYPE_AMOUNT];
    int rockAnimation;

    SDL_Texture* spiderTexture[SPIDER_TILE__TYPE_AMOUNT];
    int spiderAnimation;
};

struct Stage{
    SDL_Point camera;
};

struct soundTools{
    Mix_Music* backgroundMusic;
    Mix_Music* startScreenMusic;
    Mix_Music* endGame;
    Mix_Chunk* moveEarth;
    Mix_Chunk* dropRock;
    Mix_Chunk* collectDiamond;
    Mix_Chunk* levelUp;
    Mix_Chunk* gameover;
};
struct boardTools{
    SDL_Texture* texture;
    TTF_Font* font;
    char* message;
    int fontSize;
    SDL_Color color;
};

struct levelTools{
    struct totalTexture gameTexture;
    char* level;
    int id;
    int width;
    int height;
    int **map;
    int **saveMap;
    int **flagMap;
    int **deathFlag;
    int diamond_number;
    int totalDiamondNumber;
    int levelScore;
    Uint32 pausePassedTime; 
    Uint32 time;
    Uint32 elapsedTime;
    int levelUpX;
    int levelUpY;
    int entryCheck;
};

struct currentOwnershipTools{
    int reachedScore;
    int collectedDiamond;
    int current_level_id;
    Uint32 printTime;
    int levelUpFlag;
    SDL_Point minerPos;
    SDL_Point centerPos;
    int minerFlag;
    int frameSpeed;
};
