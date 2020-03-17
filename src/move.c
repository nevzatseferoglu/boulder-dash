#include "headers/move.h"

void getMinerLocation(int* x , int* y);
void getSpiderLocation(int* x, int* y);
void dropTilltheEmptyRock(int x , int y);
void dropTilltheEmptyDiamond(int x , int y);
void moveSpider(int x,int y,int* preDirection);
void dropRightLeft(int x , int y);
void searchAndDropRock(void);
void searchAndDropDiamond(void);
char* intToString(int number,int boardNumber);
void boardIssue(void);
void checkStatus(void);
void goNextLevel(void);
void deathCheck(void);
void fillTrue(void);
void prepLevel(void);
void getTotalDiamondNumber(void);
void goBackToLevel(void);
void frameSpeedIssues(void);
void timeCalculating(void);


Uint32 timeSum = 0;
int preDirection = 1;

int up = 1;
int right = 2;
int down = 3;
int left = 4;


int x,y;
int i,j;
int spiderX = -1;
int spiderY = -1;

void doPlayer(void)
{
	frameSpeedIssues();

	if(!levels[current.current_level_id].entryCheck)
	{
		prepLevel();
		levels[current.current_level_id].entryCheck = TRUE;
	}

	getMinerLocation(&x , &y);
	getSpiderLocation(&spiderX , &spiderY);
	searchAndDropRock();
	searchAndDropDiamond();

	fillTrue();

	if(spiderX != -1 && spiderY != -1)
	moveSpider(spiderX,spiderY,&preDirection);

	if (gameTools.keyboard[SDL_SCANCODE_LEFT] && !state.pause)
	{
		current.minerFlag = LEFT_WALKING_FLAG;

		if(!(state.startScreen || state.endGame))
		{
			if(!checkBorder(x-1,y))
			{
				if(checkEmpty(x-1,y))
				{
					levels[current.current_level_id].map[x-1][y] = miner;
					levels[current.current_level_id].map[x][y] = empty;
				}
				else if(checkEarth(x-1,y))
				{
					if(levels[current.current_level_id].deathFlag[x-1][y] == TRUE)
						levels[current.current_level_id].deathFlag[x-1][y] = -1;

					levels[current.current_level_id].map[x-1][y] = miner;
					levels[current.current_level_id].map[x][y] = empty;
					Mix_PlayChannel(-1,sounds.moveEarth,0);
				}
				else if(checkDiamond(x-1,y))
				{
					if(levels[current.current_level_id].deathFlag[x-1][y] == TRUE)
						levels[current.current_level_id].deathFlag[x-1][y] = -1;

					levels[current.current_level_id].map[x-1][y] = miner;
					levels[current.current_level_id].map[x][y] = empty;
					--(levels[current.current_level_id].totalDiamondNumber);

					++(current.collectedDiamond);
					current.reachedScore += 10;

					Mix_PlayChannel(-1,sounds.collectDiamond,0);
				}
				else if(levels[current.current_level_id].map[x-1][y] == rock && checkRock(x-1,y,SDL_SCANCODE_LEFT))
				{
					levels[current.current_level_id].map[x-1][y] = miner;
					levels[current.current_level_id].map[x-2][y] = rock;
					levels[current.current_level_id].map[x][y] = empty;
				}
				else if(checkLevel(x-1,y))
				{
					goNextLevel();
				}
			}
		}
	}
	else if (gameTools.keyboard[SDL_SCANCODE_RIGHT] && !state.pause)
	{
		current.minerFlag = RIGHT_WALKING_FLAG;
		if(!(state.startScreen || state.endGame))
		{
			if(!checkBorder(x+1,y))
			{
				if(checkEmpty(x+1,y))
				{
					levels[current.current_level_id].map[x+1][y] = miner;
					levels[current.current_level_id].map[x][y] = empty;
				}
				else if(checkEarth(x+1,y))
				{
					if(levels[current.current_level_id].deathFlag[x+1][y] == TRUE)
						levels[current.current_level_id].deathFlag[x+1][y] = -1;

					levels[current.current_level_id].map[x+1][y] = miner;
					levels[current.current_level_id].map[x][y] = empty;
					Mix_PlayChannel(-1,sounds.moveEarth,0);
				}
				else if(checkDiamond(x+1,y))
				{
					if(levels[current.current_level_id].deathFlag[x+1][y] == TRUE)
						levels[current.current_level_id].deathFlag[x+1][y] = -1;

					levels[current.current_level_id].map[x+1][y] = miner;
					levels[current.current_level_id].map[x][y] = empty;
					--(levels[current.current_level_id].totalDiamondNumber);
					++(current.collectedDiamond);
					current.reachedScore += 10;

					Mix_PlayChannel(-1,sounds.collectDiamond,0);
				}
				else if(levels[current.current_level_id].map[x+1][y] == rock && checkRock(x+1,y,SDL_SCANCODE_RIGHT))
				{
					levels[current.current_level_id].map[x+1][y] = miner;
					levels[current.current_level_id].map[x+2][y] = rock;
					levels[current.current_level_id].map[x][y] = empty;
				}
				else if(checkLevel(x+1,y))
				{
					goNextLevel();
				}
			}
		}
		
	}
	else if (gameTools.keyboard[SDL_SCANCODE_UP] && !state.pause)
	{
		current.minerFlag = UP_WALKING_FLAG;
		if(!(state.startScreen || state.endGame))
		{
			if(!checkBorder(x,y-1))
			{
				if(checkEmpty(x,y-1))
				{
					levels[current.current_level_id].map[x][y-1] = miner;
					levels[current.current_level_id].map[x][y] = empty;
				}
				else if(checkEarth(x,y-1))
				{
					if(levels[current.current_level_id].deathFlag[x][y-1] == TRUE)
						levels[current.current_level_id].deathFlag[x][y-1] = -1;

					levels[current.current_level_id].map[x][y-1] = miner;
					levels[current.current_level_id].map[x][y] = empty;
					Mix_PlayChannel(-1,sounds.moveEarth,0);
				}
				else if(checkDiamond(x,y-1))
				{
					if(levels[current.current_level_id].deathFlag[x][y-1] == TRUE)
						levels[current.current_level_id].deathFlag[x][y-1] = -1;

					levels[current.current_level_id].map[x][y-1] = miner;
					levels[current.current_level_id].map[x][y] = empty;
					--(levels[current.current_level_id].totalDiamondNumber);
					++(current.collectedDiamond);
					current.reachedScore += 10;
					Mix_PlayChannel(-1,sounds.collectDiamond,0);
				}
				else if(checkLevel(x,y-1))
				{
					goNextLevel();
				}
			}
		}
		else
		{
			if(state.cursorPos.y > 445 )	state.cursorPos.y -= 2*TILE_SIZE;
		}
	}
	else if (gameTools.keyboard[SDL_SCANCODE_DOWN] && !state.pause)
	{
		current.minerFlag = DOWN_WALKING_FLAG;
		if(!(state.startScreen || state.endGame))
		{
			if(!checkBorder(x,y+1))
			{
				if(checkEmpty(x,y+1))
				{
					levels[current.current_level_id].map[x][y+1] = miner;
					levels[current.current_level_id].map[x][y] = empty;
				}
				else if(checkEarth(x,y+1))
				{
					levels[current.current_level_id].map[x][y+1] = miner;
					levels[current.current_level_id].map[x][y] = empty;
					Mix_PlayChannel(-1,sounds.moveEarth,0);
				}
				else if(checkDiamond(x,y+1))
				{
					levels[current.current_level_id].map[x][y+1] = miner;
					levels[current.current_level_id].map[x][y] = empty;
					--(levels[current.current_level_id].totalDiamondNumber);
					++(current.collectedDiamond);
					current.reachedScore += 10;

					Mix_PlayChannel(-1,sounds.collectDiamond,0);
				}
				else if(checkLevel(x,y+1))
				{
					goNextLevel();
				}
			}
		}
		else
		{
			if(state.cursorPos.y <= 505)	state.cursorPos.y += 2*TILE_SIZE;
		}
	}
	else if(gameTools.keyboard[SDL_SCANCODE_M]) /* Mute level music which exist */
	{
		if( Mix_PlayingMusic() == 0 )
		{
			Mix_PlayMusic( sounds.backgroundMusic, -1 );
		}
		else
		{
			if( Mix_PausedMusic() == 1 )	Mix_ResumeMusic();
			else							Mix_PauseMusic();
		}
	}
	else if(gameTools.keyboard[SDL_SCANCODE_R] && !state.pause) /* Restarting Level */
	{
		goBackToLevel();
	}
	else if(gameTools.keyboard[SDL_SCANCODE_P]) /* Pausing Game */
	{
		if( Mix_PlayingMusic() == 0 )
		{
			Mix_PlayMusic( sounds.backgroundMusic, -1 );
		}
		else
		{
			if( Mix_PausedMusic() == 1 )	Mix_ResumeMusic();
			else							Mix_PauseMusic();
		}

		if(state.pause)
			state.pause = FALSE;
		else
			state.pause = TRUE;
	}
	else if(gameTools.keyboard[SDL_SCANCODE_RETURN])
	{
		if(state.endGame == TRUE)
		{
			quit = SDL_FALSE;
		}
		if(state.cursorPos.y == state.startGamePos.y)
		{
			state.startScreen = FALSE;
			Mix_HaltMusic();

			if( Mix_PlayingMusic() == 0 )
			{
				Mix_PlayMusic( sounds.backgroundMusic, -1 );
			}
			else
			{
				if( Mix_PausedMusic() == 1 )	Mix_ResumeMusic();
				else							Mix_PauseMusic();
			}
		}
		else if(state.cursorPos.y == state.howToPlayPos.y)
		{
			state.HowToPlay = TRUE;
		}
		else if(state.cursorPos.y == state.exitGamePos.y)
		{
			state.ExitGame = TRUE;
			quit = SDL_FALSE;
		}
	}
	else if(gameTools.keyboard[SDL_SCANCODE_ESCAPE])
	{
		state.HowToPlay = FALSE;
		state.ExitGame = FALSE;
	}
	else
	{
		current.minerFlag = STANDING_FLAG;
	}
	
	if(state.pause)
	{
		levels[current.current_level_id].pausePassedTime = (SDL_GetTicks()+oldTime) * 0.001 - levels[current.current_level_id].elapsedTime - timeSum;
	}
	else
	{
		timeCalculating();
		boardIssue();
		checkStatus();
	}
}
void getMinerLocation(int* x , int* y)
{
	for(j = 0 ; j < levels[current.current_level_id].height ; j++)
    {
        for(i = 0 ; i < levels[current.current_level_id].width ; i++)
        {
            if(levels[current.current_level_id].map[i][j] == miner)
			{
				*x = i , current.minerPos.x = i;
				*y = j , current.minerPos.y = j;
			}
        }
    }
}
void getSpiderLocation(int* x , int* y)
{
	for(j = 0 ; j < levels[current.current_level_id].height ; j++)
    {
        for(i = 0 ; i < levels[current.current_level_id].width ; i++)
        {
            if(levels[current.current_level_id].map[i][j] == spider)
			{
				*x = i;
				*y = j;
			}
        }
    }
}
void dropTilltheEmptyRock(int x , int y)
{
	if(levels[current.current_level_id].map[x][y+1] == empty)
	{
		levels[current.current_level_id].map[x][y+1] = rock;
		levels[current.current_level_id].flagMap[x][y+1] = TRUE;
		
		levels[current.current_level_id].map[x][y] = empty;
		levels[current.current_level_id].flagMap[x][y] = FALSE;

		if(levels[current.current_level_id].map[x][y+2] != empty && levels[current.current_level_id].map[x][y+2] != miner)
			Mix_PlayChannel(-1,sounds.dropRock,0);
	}
	else if(levels[current.current_level_id].map[x-1][y+1] == empty && levels[current.current_level_id].map[x-1][y] == empty && ((levels[current.current_level_id].map[x][y+1] == rock) || (levels[current.current_level_id].map[x][y+1] == diamond)))
	{
		levels[current.current_level_id].map[x-1][y+1] = rock;
		levels[current.current_level_id].flagMap[x-1][y+1] = TRUE;
		
		levels[current.current_level_id].map[x][y] = empty;
		levels[current.current_level_id].flagMap[x][y] = FALSE;
		
		if(levels[current.current_level_id].map[x-1][y+2] != empty && levels[current.current_level_id].map[x-1][y+2] != miner)
			Mix_PlayChannel(-1,sounds.dropRock,0);
	}
	else if(levels[current.current_level_id].map[x+1][y+1] == empty && levels[current.current_level_id].map[x+1][y] == empty && ((levels[current.current_level_id].map[x][y+1] == rock) || (levels[current.current_level_id].map[x][y+1] == diamond)))
	{
		levels[current.current_level_id].map[x+1][y+1] = rock;
		levels[current.current_level_id].flagMap[x+1][y+1] = TRUE;
		
		levels[current.current_level_id].map[x][y] = empty;
		levels[current.current_level_id].flagMap[x][y] = FALSE;

		if(levels[current.current_level_id].map[x+1][y+2] != empty && levels[current.current_level_id].map[x+1][y+2] != miner)
			Mix_PlayChannel(-1,sounds.dropRock,0);
	}
}
void dropTilltheEmptyDiamond(int x , int y)
{
	if(levels[current.current_level_id].map[x][y+1] == empty)
	{
		levels[current.current_level_id].map[x][y+1] = diamond;
		levels[current.current_level_id].flagMap[x][y+1] = TRUE;
		
		levels[current.current_level_id].map[x][y] = empty;
		levels[current.current_level_id].flagMap[x][y] = FALSE;
	}
	else if(levels[current.current_level_id].map[x-1][y+1] == empty && levels[current.current_level_id].map[x-1][y] == empty && ((levels[current.current_level_id].map[x][y+1] == rock) || (levels[current.current_level_id].map[x][y+1] == diamond)))
	{
		levels[current.current_level_id].map[x-1][y+1] = diamond;
		levels[current.current_level_id].flagMap[x-1][y+1] = TRUE;
		
		levels[current.current_level_id].map[x][y] = empty;
		levels[current.current_level_id].flagMap[x][y] = FALSE;
	}
	else if(levels[current.current_level_id].map[x+1][y+1] == empty && levels[current.current_level_id].map[x+1][y] == empty && ((levels[current.current_level_id].map[x][y+1] == rock) || (levels[current.current_level_id].map[x][y+1] == diamond)))
	{
		levels[current.current_level_id].map[x+1][y+1] = diamond;
		levels[current.current_level_id].flagMap[x+1][y+1] = TRUE;
		
		levels[current.current_level_id].map[x][y] = empty;
		levels[current.current_level_id].flagMap[x][y] = FALSE;
	}
}
void moveSpider(int x,int y,int* preDirection)
{
	if(*preDirection == 1 && levels[current.current_level_id].map[x][y-1] == empty)
	{
		levels[current.current_level_id].map[x][y-1] = spider;
		levels[current.current_level_id].map[x][y] = empty;
	}
	else
	{
		if(*preDirection == 1)
		*preDirection = 2;

		if(*preDirection == 2 && levels[current.current_level_id].map[x+1][y] == empty)
		{
			levels[current.current_level_id].map[x+1][y] = spider;
			levels[current.current_level_id].map[x][y] = empty;
		}
		else
		{
			if(*preDirection == 2)
			*preDirection = 3;

			if(*preDirection == 3 && levels[current.current_level_id].map[x][y+1] == empty)
			{
				levels[current.current_level_id].map[x][y+1] = spider;
				levels[current.current_level_id].map[x][y] = empty;
			}
			else
			{
				if(*preDirection == 3)
				*preDirection = 4;

				if(*preDirection == 4 && levels[current.current_level_id].map[x-1][y] == empty)
				{
					levels[current.current_level_id].map[x-1][y] = spider;
					levels[current.current_level_id].map[x][y] = empty;
				}
				else
				{
					if(*preDirection == 4)
					*preDirection = 1;
				}
			}
		}
	}
}
void searchAndDropRock(void)
{
	for(j = 0 ; j < levels[current.current_level_id].height ; j++)
    {
        for(i = 0 ; i < levels[current.current_level_id].width ; i++)
        {
            if(levels[current.current_level_id].map[i][j] == rock && levels[current.current_level_id].flagMap[i][j] == 0)
			{
				dropTilltheEmptyRock(i,j);
			}
        }
    }
	for(j = 0 ; j < levels[current.current_level_id].height ; ++j)
	{
		for(i = 0 ; i < levels[current.current_level_id].width ; ++i)
			levels[current.current_level_id].flagMap[i][j] = 0;
	}
}
void searchAndDropDiamond(void)
{
	for(j = 0 ; j < levels[current.current_level_id].height ; j++)
    {
        for(i = 0 ; i < levels[current.current_level_id].width ; i++)
        {
            if(levels[current.current_level_id].map[i][j] == diamond && levels[current.current_level_id].flagMap[i][j] == 0)
			{
				dropTilltheEmptyDiamond(i,j);
			}
        }
    }
	for(j = 0 ; j < levels[current.current_level_id].height ; ++j)
	{
		for(i = 0 ; i < levels[current.current_level_id].width ; ++i)
			levels[current.current_level_id].flagMap[i][j] = 0;
	}
}
void boardIssue(void)
{
	SDL_Surface* surf[TEXT_NUMBER] = {'\0'};

	boards[0].message = intToString(current.reachedScore,0); 									/* scoreBoard   */ 
	boards[1].message = intToString(levels[current.current_level_id].totalDiamondNumber,1); 	/* diamondBoard */
	boards[2].message = intToString(current.current_level_id+1,2); 								/* levelBoard 	*/
	boards[3].message = intToString(current.printTime,3); 										/* timeBoard	*/

	boards[4].message = "Start Game";
	boards[5].message = "How To Play";
	boards[6].message = "Exit Game";
	boards[7].message = "ESC";

	if(state.endGame)
	{
		boards[4].message = "Score";
		boards[5].message = "Please Enter to Quit !";
	}
	


	for(i = 0 ; i < TEXT_NUMBER ; ++i)
    {
        surf[i] = TTF_RenderText_Blended(boards[i].font , boards[i].message ,boards[i].color);
        if (surf[i] == NULL)
        {
            TTF_CloseFont(boards[i].font);
            fprintf(stderr,"surf[%d] could not be loaded ! TTF_Error() : %s\n",i,TTF_GetError());
            exit(-1);
        }
    }

    for(i = 0 ; i < TEXT_NUMBER ; ++i)
    {
        boards[i].texture = SDL_CreateTextureFromSurface(gameTools.renderer ,surf[i]);
        if (boards[i].texture == NULL)
        {
            fprintf(stderr,"boards[%d].texture  could not be loaded ! TTF_Error() : %s\n",i,TTF_GetError());
            exit(-1);
        }
    }

    for(i = 0 ; i < TEXT_NUMBER ; ++i)
        SDL_FreeSurface(surf[i]);
}
char* intToString(int number,int boardNumber)
{
    int i = 0 , digitNumber = 0;
    int tempNumber = number;
    char* message;
	char head = '0';

	if(state.endGame)
		head = ' ';

	if(boardNumber == 0)
	{
		message = calloc(sizeof(char),10);
		for(i = 0 ; i < 9 ; ++i)
		{
			message[i] = head;
		}
		message[i] = '\0';

		if(tempNumber == 0)
			return message;
		else
		{
			while(tempNumber > 0)
			{
				tempNumber /= 10;
				++digitNumber;
			}
			i = 8;
			while(digitNumber > 0)
			{
				*(message+i) = 48 + number % 10;
				number /= 10;
				--digitNumber, --i;
			}
			return message;
		}
	}
	else if(boardNumber == 1 || boardNumber == 3)
	{
		message = calloc(sizeof(char),4);
		for(i = 0 ; i < 3 ; ++i)
		{
			message[i] = '0';
		}
		message[i] = '\0';

		if(tempNumber == 0)
			return message;
		else
		{
			while(tempNumber > 0)
			{
				tempNumber /= 10;
				++digitNumber;
			}
			i = 2;
			while(digitNumber > 0)
			{
				*(message+i) = 48 + number % 10;
				number /= 10;
				--digitNumber, --i;
			}
			return message;
		}
	}
	else if(boardNumber == 2)
	{
		message = calloc(sizeof(char),3);
		for(i = 0 ; i < 2 ; ++i)
		{
			message[i] = '0';
		}
		message[i] = '\0';

		if(tempNumber == 0)
			return message;
		else
		{
			while(tempNumber > 0)
			{
				tempNumber /= 10;
				++digitNumber;
			}
			i = 1;
			while(digitNumber > 0)
			{
				*(message+i) = 48 + number % 10;
				number /= 10;
				--digitNumber, --i;
			}
			return message;
		}
	}
	else
	{
		message = calloc(sizeof(char),3);
		for(i = 0 ; i < 2 ; ++i)
		{
			message[i] = '0';
		}
		message[i] = '\0';
		return message;
	}
}
void checkStatus(void)
{
	deathCheck();
	if((levels[current.current_level_id].diamond_number <= current.collectedDiamond)&&(current.levelUpFlag))
	{
		levels[current.current_level_id].map[levels[current.current_level_id].levelUpX][levels[current.current_level_id].levelUpY] = levelPort;
		Mix_PlayChannel(-1,sounds.levelUp,0);
		current.levelUpFlag = FALSE;
	}
}
void goNextLevel(void)
{
	current.levelUpFlag = TRUE;
	levels[current.current_level_id].levelScore = current.reachedScore;
	
	++current.current_level_id;
	if(current.current_level_id == LEVEL_NUMBER)
	{
		Mix_HaltMusic();
		if( Mix_PlayingMusic() == 0 )
		{
			Mix_PlayMusic( sounds.endGame, -1 );
		}
		else
		{
			if( Mix_PausedMusic() == 1 )	Mix_ResumeMusic();
			else							Mix_PauseMusic();
		}
		state.endGame = TRUE;
		--current.current_level_id;
	}
	current.collectedDiamond = 0;
}
void deathCheck(void)
{	
	for(j = 0 ; j < levels[current.current_level_id].height ; ++j)
	{
		for(i = 0 ; i < levels[current.current_level_id].width ; ++i)
		{
			if(levels[current.current_level_id].map[i][j] == rock && levels[current.current_level_id].map[i][j+1] == miner && !(levels[current.current_level_id].deathFlag[i][j+1] == -1))
			{
				levels[current.current_level_id].map[i][j] = empty;
				levels[current.current_level_id].map[i][j+1] = rock;
				Mix_PlayChannel(-1,sounds.gameover,0);
				goBackToLevel();
			}
		}
	}
}
void fillTrue(void)
{
	for(j = 0 ; j < levels[current.current_level_id].height ; ++j)
	{
		for(i = 0 ; i < levels[current.current_level_id].width ; ++i)
		{
			if(levels[current.current_level_id].map[i][j] == rock && (levels[current.current_level_id].map[i][j+1] == earth || levels[current.current_level_id].map[i][j+1] == diamond))
			{
				levels[current.current_level_id].deathFlag[i][j+1] = TRUE;
			}
		}
	}
}
void getTotalDiamondNumber(void)
{
	for(j = 0 ; j < levels[current.current_level_id].height ; ++j)
	{
		for(i = 0 ; i < levels[current.current_level_id].width ; ++i)
		{
			if(levels[current.current_level_id].map[i][j] == diamond)
			{
				++levels[current.current_level_id].totalDiamondNumber;
			}
		}
	}
}
void prepLevel(void)
{
	getTotalDiamondNumber();
}
void goBackToLevel(void)
{
	for(j = 0 ; j < levels[current.current_level_id].height ; j++)
    {
        for(i = 0 ; i < levels[current.current_level_id].width ; i++)
        {
            levels[current.current_level_id].map[i][j] = levels[current.current_level_id].saveMap[i][j];
        }
    }
	levels[current.current_level_id].totalDiamondNumber += current.collectedDiamond;
	current.collectedDiamond = 0;

	if(current.current_level_id != 0)	current.reachedScore = levels[current.current_level_id - 1].levelScore;
	else								current.reachedScore = 0;
	current.levelUpFlag = TRUE;
}
void frameSpeedIssues(void)
{
	if(current.frameSpeed > MAX_FRAME_SPEED)
		current.frameSpeed = 0;	
	else
		current.frameSpeed += 1;
}
void timeCalculating(void)
{
	timeSum = 0;

	for(i = 0 ; i < current.current_level_id ; ++i)
		timeSum += (levels[i].elapsedTime + levels[i].pausePassedTime);

	levels[current.current_level_id].elapsedTime  = (SDL_GetTicks()+oldTime) * 0.001  - timeSum;
	levels[current.current_level_id].elapsedTime -= levels[current.current_level_id].pausePassedTime;

	current.printTime = levels[current.current_level_id].time - levels[current.current_level_id].elapsedTime;

}