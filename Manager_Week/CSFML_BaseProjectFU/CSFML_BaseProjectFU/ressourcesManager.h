#pragma once
#include "tools.h"
#include "stateManager.h"


typedef enum 
{
	SINGLE, SPRITESHEET, ANIMATION, SOUNDFX, MUSIC, FONT, VIDEO
}ressourceType;

typedef struct ressources ressources;
struct ressources
{
	ressources* pNext;
	State state;
	ressourceType type;
	char name[30];
	char path[200];
};

ressources* ResBegin;

void OnLoad(char* _path);
void AddRessources(ressources* _ressources);
ressources* RemoveRessources(ressources* _ressources);