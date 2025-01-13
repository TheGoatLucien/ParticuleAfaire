#pragma once
#include "ressourcesManager.h"

#include <SFML/Audio.h>

// Structure pour un son ou une musique
typedef struct Sound Sound;
struct Sound {
    Sound* pNext;
    char name[30];
    ressourceType type;
    State state;
    union {
        sfMusic* music;  // Musique
        sfSound* sound;  // Son
    };
    int compteur;
};

Sound* soundBegin;

float SFXVolume;
float musicVolume;

void Sound_Onload(State);
sfSound* GetSound(char* _name);
sfMusic* GetMusic(char* _name);
void AddSound(Sound* _sound);
Sound* RemoveSound(Sound* _sound);
void RemoveAllSound();
void RemoveAllSoundButALL();
