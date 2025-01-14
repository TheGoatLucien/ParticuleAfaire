#pragma once
#include "ressourcesManager.h"


typedef struct Particle Particle;
struct Particle {
    Particle* pNext;          // * vers la prochaine particule comme les listes
    char name[30];            // Nom unique de la particule
    ressourceType type;       // type de ressource (SINGLE, SPRITESHEET, etc.)
    State state;
    sfVertexArray* vertices;  //   sommets pour les particules
    sfTexture* texture;       // texture associ�e aux particules
    float lifetime;           // dur�e de vie des particules
};

Particle* particleBegin;       // debut liste des particules

// fonctionnalit�s principales
void Particle_Onload(State _state);
Particle* GetParticle(char* _name);
void AddParticle(Particle* _particle);
Particle* RemoveParticle(Particle* _particle);
void RemoveAllParticle();
void RemoveAllParticleButALL();
