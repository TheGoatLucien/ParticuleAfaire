#pragma once
#include "ressourcesManager.h"

typedef struct Texture Texture;
struct Texture
{
	Texture* pNext;
	char name[30];
	ressourceType type;
	State state;
	sfTexture* sftexture;
	int compteur;
	sfIntRect spSheetRec;
	float frameTime;
	int NbFrame;
	int row;
};

 typedef enum 
{
	TEXNULL = -1, PATH, CONFIG
}StateTexture;

Texture* textureBegin;

void Texture_Onload(State);
sfTexture* GetTexture(char* _name);
int GetNbFrame(char* _name);
float GetFrameTime(char* _name);
sfIntRect GetRect(char* _name);
void AddTexture(Texture* _texture);
Texture* RemoveTexture(Texture* _texture);
void RemoveAllTexture();
void RemoveAllTextureButALL();