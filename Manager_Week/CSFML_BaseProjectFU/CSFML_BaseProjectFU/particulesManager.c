#include "particulesManager.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Charge des particules pour un �tat dejeu
void Particle_Onload(State _state) {
    particleBegin = NULL; // initialiser la liste des particules a 0

    ressources* tempRessources = ResBegin; // parcourir les ressources charg�es
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

                tempParticle->textureUsageCount = (int*)malloc(sizeof(int));
                *(tempParticle->textureUsageCount) = 1; // La texture est utilis�e par une particule

                //cree le sprute
                tempParticle->sprite = sfSprite_create();
                sfSprite_setTexture(tempParticle->sprite, tempParticle->texture, sfTrue);

                // Initialiser les propri�t�s par d�faut
                tempParticle->position = (sfVector2f){ 0.0f, 0.0f };
                tempParticle->velocity = (sfVector2f){ 0.0f, 0.0f };
                tempParticle->lifetime = 0.0f;
                tempParticle->maxLifetime = 6.0f;

				// ajouter la particule � la liste
				AddParticle(tempParticle);
				
			}

           
        }
        tempRessources = tempRessources->pNext;
    }
}

// R�cup�rer une particule par son nom
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

// Ajouter une particule � la liste
void AddParticle(Particle* _particle) {
    if (_particle == NULL) {
        printf("Erreur : Impossible d'ajouter une particule NULL.\n");
        return;
    }
    if (_particle->sprite == NULL) {
        printf("Erreur : Particule avec sprite NULL ajout�e : %s\n", _particle->name);
        return;
    }
    // Incr�menter le compteur d'utilisation si la texture est d�j� partag�e
    if (_particle->textureUsageCount) {
        (*(_particle->textureUsageCount))++;
    }
    _particle->pNext = particleBegin;
    particleBegin = _particle;
    printf("Particule ajout�e : %s\n", _particle->name);
}


// Supprimer une particule sp�cifique
Particle* RemoveParticle(Particle* _particle) {
    if (_particle == NULL) return NULL;

    if (_particle == particleBegin) {
        Particle* next = _particle->pNext;

        // Lib�rer le sprite
        if (_particle->sprite) sfSprite_destroy(_particle->sprite);

        // D�cr�menter le compteur d'utilisation et lib�rer la texture si n�cessaire
        if (_particle->textureUsageCount) {
            (*(_particle->textureUsageCount))--;
            if (*(_particle->textureUsageCount) == 0) {
                printf("Lib�ration de la texture de la particule : %s\n", _particle->name);
                sfTexture_destroy(_particle->texture);
                free(_particle->textureUsageCount);
            }
        }

        free(_particle);
        particleBegin = next;
        return next;
    }
    else {
        Particle* current = particleBegin;
        while (current && current->pNext != _particle) {
            current = current->pNext;
        }
        if (current && current->pNext == _particle) {
            current->pNext = _particle->pNext;

            // Lib�rer le sprite
            if (_particle->sprite) sfSprite_destroy(_particle->sprite);

            // D�cr�menter le compteur d'utilisation et lib�rer la texture si n�cessaire
            if (_particle->textureUsageCount) {
                (*(_particle->textureUsageCount))--;
                if (*(_particle->textureUsageCount) == 0) {
                    printf("Lib�ration de la texture de la particule : %s\n", _particle->name);
                    sfTexture_destroy(_particle->texture);
                    free(_particle->textureUsageCount);
                }
            }

            free(_particle);
        }
        return current ? current->pNext : NULL;
    }
}



// Supprimer toutes les particules
void RemoveAllParticle() {
    while (particleBegin != NULL) {
        RemoveParticle(particleBegin);
    }
}

// Supprimer toutes les particules sauf celles associ�es � ALL
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
