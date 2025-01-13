#pragma once
#include "ressourcesManager.h"


typedef struct particles
{
	sfSprite* particles_sprite;
	sfVector2f particles_pos;
	sfVector2f particles_speed;
	particles* pNext;
	State state;
	float Lifetime;
};

particles* particlesBegin;

sfSprite* getSprite(char* _name);

void Onload_Particles(State);

void Add_Particles(particles* _particles);

void Remove_Particles();