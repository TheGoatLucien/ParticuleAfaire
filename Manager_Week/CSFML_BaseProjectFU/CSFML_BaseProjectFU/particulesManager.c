#include "particulesManager.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Charge des particules pour un état dejeu
void Particle_Onload(State _state) {
    particleBegin = NULL; // initialiser la liste des particules a 0

    ressources* tempRessources = ResBegin; // parcourir les ressources chargées
    while (tempRessources != NULL) {
        if (tempRessources->state == _state) {
            Particle* tempParticle = (Particle*)calloc(1, sizeof(Particle));
            strcpy(tempParticle->name, tempRessources->name);
            tempParticle->type = tempRessources->type;
            tempParticle->state = tempRessources->state;


			if (tempRessources->type == PARTICLE) {
				// Charger la texture des particules
				tempParticle->texture = sfTexture_createFromFile(tempRessources->path, NULL);
				if (!tempParticle->texture) {
					printf("Erreur : Impossible de charger la texture des particules %s\n", tempRessources->path);
					free(tempParticle);
					tempRessources = tempRessources->pNext;
					continue;
				}
                //cree le sprute
                tempParticle->sprite = sfSprite_create();
                sfSprite_setTexture(tempParticle->sprite, tempParticle->texture, sfTrue);

                // Initialiser les propriétés par défaut
                tempParticle->position = (sfVector2f){ 0.0f, 0.0f };
                tempParticle->velocity = (sfVector2f){ 0.0f, 0.0f };
                tempParticle->lifetime = 0.0f;
                tempParticle->maxLifetime = 5.0f;

				// ajouter la particule à la liste
				AddParticle(tempParticle);
				
			}

           
        }
        tempRessources = tempRessources->pNext;
    }
}

// Récupérer une particule par son nom
Particle* GetParticle(char* _name) {
    Particle* tempParticle = particleBegin;
    while (tempParticle != NULL) {
        if (strcmp(_name, tempParticle->name) == 0) {
            return tempParticle;
        }
        tempParticle = tempParticle->pNext;
    }
    return NULL;
}

// Ajouter une particule à la liste
void AddParticle(Particle* _particle) {
    _particle->pNext = particleBegin;
    particleBegin = _particle;
}

// Supprimer une particule spécifique
Particle* RemoveParticle(Particle* _particle) {
    if (_particle == particleBegin) {
        Particle* next = _particle->pNext;
        sfTexture_destroy(_particle->texture);
        sfSprite_destroy(_particle->sprite);
        free(_particle);
        particleBegin = next;
        return next;
    }
    else {
        Particle* current = particleBegin;
        while (current->pNext != _particle) {
            current = current->pNext;
        }
        current->pNext = _particle->pNext;
        sfTexture_destroy(_particle->texture);
        sfSprite_destroy(_particle->sprite);
        free(_particle);
        return current->pNext;
    }
}

// Supprimer toutes les particules
void RemoveAllParticle() {
    while (particleBegin != NULL) {
        RemoveParticle(particleBegin);
    }
}

// Supprimer toutes les particules sauf celles associées à ALL
void RemoveAllParticleButALL() {
    Particle* current = particleBegin;
    while (current != NULL) {
        if (current->state != ALL) {
            current = RemoveParticle(current);
        }
        else {
            current = current->pNext;
        }
    }
}
