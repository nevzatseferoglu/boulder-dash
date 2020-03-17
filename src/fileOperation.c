#include "headers/fileOperation.h"

void increase(char** level);

char* readFile(char* map_file_name)
{
    int i;
    size_t result;

    int fileSize;
    int currentPosition;
    int tempNumber;
    int quit = TRUE;
    
    char junk1[MAX_LINE] = {'\0'};
    char junk2[MAX_LINE] = {'\0'};

    char analyseLine[MAX_LINE] = {'\0'};

    
    FILE* fptr = NULL;

    fptr = fopen(map_file_name,"rb");
    
    if(fptr == NULL)
    {
        fprintf(stderr,"Error ! , file could not be opened");
        exit(-1);
    }

    sscanf(fgets(analyseLine,MAX_LINE,fptr),"%s%s%d",junk1,junk2,&tempNumber);
    
    for(i = 0 ; i < LEVEL_NUMBER && quit ; ++i)
    {
        if(tempNumber == i+1)
        {
            levels[i].id = tempNumber;
            sscanf(fgets(analyseLine,MAX_LINE,fptr),"%s%s%d",junk1,junk2,&tempNumber);
            levels[i].width = tempNumber;
            sscanf(fgets(analyseLine,MAX_LINE,fptr),"%s%s%d",junk1,junk2,&tempNumber);
            levels[i].height = tempNumber;
            sscanf(fgets(analyseLine,MAX_LINE,fptr),"%s%s%d",junk1,junk2,&tempNumber);
            levels[i].diamond_number = tempNumber;
            sscanf(fgets(analyseLine,MAX_LINE,fptr),"%s%s%d",junk1,junk2,&tempNumber);
            levels[i].time = tempNumber;
            quit = FALSE;
        }
    }

    fseek(fptr,1,SEEK_CUR);         /* Incrementing File Position  at ones to reach the map data in specific file */
    currentPosition = ftell(fptr);
    
    fseek (fptr, 0 , SEEK_END);
    fileSize = ftell(fptr);
    rewind(fptr);

    fileSize -= currentPosition;

    fseek(fptr, currentPosition , SEEK_SET);

    levels[i-1].level = (char*) malloc(sizeof(char)*(fileSize+1));
    if (levels[i-1].level == NULL)
    {
        fprintf (stderr,"Memory error\n");
        exit (-1);
    }

    memset(levels[i-1].level,0,fileSize+1);
    result = fread (levels[i-1].level,1,fileSize,fptr);

    if (result != fileSize)
    {
        fprintf (stderr,"Reading error\n");
        exit (-1);
    }
    levels[i-1].level[fileSize] = '\0';

    fclose(fptr);

    return levels[i-1].level;
}