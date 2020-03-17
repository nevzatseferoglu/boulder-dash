#include "common.h"
extern struct mainTools gameTools;
extern enum textureAll textureType;
extern struct Stage gameStage;
extern void blit(SDL_Texture *texture, int x, int y , int w , int h);
extern char* readFile(char*);
extern struct boardTools boards[TEXT_NUMBER];

extern SDL_Texture* scoreBoard;
extern SDL_Texture* diamondBoard;
extern SDL_Texture* levelBoard;
extern SDL_Texture* timeBoard;
extern SDL_Texture* entireMap;
extern SDL_Texture* boulderDash;
extern SDL_Texture* howtoplay;

extern struct gameState state;
extern void renderText(void);
extern struct levelTools levels[LEVEL_NUMBER];
extern struct currentOwnershipTools current;