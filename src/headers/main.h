#include "common.h"

enum textureAll textureType;

extern void initSDL(void);  
extern void initGame(void);
extern void initStage(void);
extern void releaseTools(void);
extern void doInput(void);
extern void prepareWindow(void);
extern void presentWindow(void);
extern void loadMedia(void);

SDL_Texture* scoreBoard;
SDL_Texture* diamondBoard;
SDL_Texture* levelBoard;
SDL_Texture* timeBoard;
SDL_Texture* entireMap;
SDL_Texture* boulderDash;
SDL_Texture* howtoplay;

Uint32 oldTime;

SDL_bool quit = SDL_TRUE;

struct gameState state;
struct currentOwnershipTools current;
struct mainTools gameTools;
struct Stage gameStage;
struct soundTools sounds;
struct boardTools boards[TEXT_NUMBER];
struct levelTools levels[LEVEL_NUMBER];