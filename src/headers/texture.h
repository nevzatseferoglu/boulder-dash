#include "common.h" 
extern enum textureAll textureType;
extern struct mainTools gameTools;
extern void blit(SDL_Texture *texture, int x, int y , int w , int h);
extern struct soundTools sounds;
extern struct boardTools boards[TEXT_NUMBER];
extern struct levelTools levels[LEVEL_NUMBER];
extern struct gameState state;

extern SDL_Texture* scoreBoard;
extern SDL_Texture* diamondBoard;
extern SDL_Texture* levelBoard;
extern SDL_Texture* timeBoard;
extern SDL_Texture* entireMap;
extern SDL_Texture* boulderDash;
extern SDL_Texture* howtoplay;
extern struct currentOwnershipTools current;
