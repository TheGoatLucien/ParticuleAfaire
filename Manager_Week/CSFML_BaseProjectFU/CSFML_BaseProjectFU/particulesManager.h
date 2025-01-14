#pragma once
#include "ressourcesManager.h"


typedef struct Particle Particle;
struct Particle {
    Particle* pNext;          // * vers la prochaine particule comme les listes
    char name[30];            // Nom unique de la particule
    ressourceType type;       // type de ressource (SINGLE, SPRITESHEET, etc.)
    State state;
    sfSprite* sprite;          // Sprite de la particule
    sfTexture* texture;        // Texture associée
	sfVector2f position;       // Position de la particule
	sfVector2f velocity;       // Vitesse de la particule
	float lifetime;            // Durée de vie de la particule
	float maxLifetime;         // Durée de vie maximale de la particule
    int* textureUsageCount;
};

Particle* particleBegin;       // debut liste des particules

// fonctionnalités principales
void Particle_Onload(State _state);
Particle* GetParticle(char* _name);
void AddParticle(Particle* _particle);
Particle* RemoveParticle(Particle* _particle);
void RemoveAllParticle();
void RemoveAllParticleButALL();
