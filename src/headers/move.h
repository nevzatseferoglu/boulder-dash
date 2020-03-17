#include "common.h"
extern enum textureAll textureType;
extern int checkArrayFrontier(int x , int y);
extern int checkBorder(int x, int y);
extern int checkEarth(int x, int y);
extern int checkDiamond(int x , int y);
extern int checkRock(int x, int y , int direction);
extern int checkEmpty(int x , int y);
extern int checkLevel(int x , int y);
extern void blit(SDL_Texture *texture, int x, int y , int w , int h);
extern SDL_Texture* entireMap;

extern Uint32 oldTime;

extern struct gameState state;
extern struct mainTools gameTools;
extern struct Stage gameStage;
extern struct soundTools sounds;
extern struct levelTools levels[LEVEL_NUMBER];
extern struct boardTools boards[TEXT_NUMBER];
extern struct currentOwnershipTools current;
extern SDL_bool quit;