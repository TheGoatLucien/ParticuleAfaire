#include "soundManager.h"

// TODO : comme pour le texture manager mais avec les sons


void Sound_Onload(State _state) {
    soundBegin = NULL;

    ressources* tempRessources = ResBegin;
    while (tempRessources != NULL) {
        if (tempRessources->state == _state) {
            Sound* tempSound = (Sound*)calloc(1, sizeof(Sound));
            strcpy(tempSound->name, tempRessources->name);
            tempSound->type = tempRessources->type;
            tempSound->state = tempRessources->state;

            if (tempRessources->type == MUSIC) {
                tempSound->music = sfMusic_createFromFile(tempRessources->path);
                if (!tempSound->music) {
                    printf("Unable to load music: %s\n", tempRessources->path);
                    exit(1);
                }
            }
            else if (tempRessources->type == SOUNDFX) {
                tempSound->sound = sfSound_create();
                sfSoundBuffer* buffer = sfSoundBuffer_createFromFile(tempRessources->path);
                if (!buffer) {
                    printf("Unable to load sound: %s\n", tempRessources->path);
                    exit(1);
                }
                sfSound_setBuffer(tempSound->sound, buffer);
            }

            tempSound->compteur = 0;
            AddSound(tempSound);
        }
        tempRessources = tempRessources->pNext;
    }
}

sfSound* GetSound(char* _name) {
    Sound* tempSound = soundBegin;
    while (tempSound != NULL) {
        if (strcmp(_name, tempSound->name) == 0 && tempSound->type == SOUNDFX) {
            return tempSound->sound;
        }
        tempSound = tempSound->pNext;
    }
    return NULL;
}

sfMusic* GetMusic(char* _name) {
    Sound* tempSound = soundBegin;
    while (tempSound != NULL) {
        if (strcmp(_name, tempSound->name) == 0 && tempSound->type == MUSIC) {
            return tempSound->music;
        }
        tempSound = tempSound->pNext;
    }
    return NULL;
}

void AddSound(Sound* _sound) {
    _sound->pNext = soundBegin;
    soundBegin = _sound;
}

Sound* RemoveSound(Sound* _sound) {
    if (_sound == soundBegin) {
        Sound* tempSound = _sound->pNext;
        soundBegin = tempSound;
        free(_sound);
        return tempSound;
    }
    else {
        Sound* tempSound = soundBegin;
        while (tempSound->pNext != _sound) {
            tempSound = tempSound->pNext;
        }
        tempSound->pNext = _sound->pNext;
        free(_sound);
        return tempSound->pNext;
    }
}

void RemoveAllSound() {
    Sound* tempSound = soundBegin;
    while (tempSound != NULL) {
        Sound* toDelete = tempSound;
        tempSound = tempSound->pNext;

        if (toDelete->type == MUSIC) {
            sfMusic_destroy(toDelete->music);
        }
        else if (toDelete->type == SOUNDFX) {
            sfSoundBuffer* buffer = (sfSoundBuffer*)sfSound_getBuffer(toDelete->sound);
            sfSound_destroy(toDelete->sound);
            sfSoundBuffer_destroy(buffer);
        }
        free(toDelete);
    }
    soundBegin = NULL;
}

void RemoveAllSoundButALL() {
    Sound* tempSound = soundBegin;
    while (tempSound != NULL) {
        if (tempSound->state != ALL) {
            if (tempSound == soundBegin) {
                Sound* next = tempSound->pNext;
                if (tempSound->type == MUSIC) {
                    sfMusic_destroy(tempSound->music);
                }
                else if (tempSound->type == SOUNDFX) {
                    sfSoundBuffer* buffer = (sfSoundBuffer*)sfSound_getBuffer(tempSound->sound);
                    sfSound_destroy(tempSound->sound);
                    sfSoundBuffer_destroy(buffer);
                }
                free(tempSound);
                tempSound = next;
                soundBegin = next;
            }
            else {
                Sound* prev = soundBegin;
                while (prev->pNext != tempSound) {
                    prev = prev->pNext;
                }
                prev->pNext = tempSound->pNext;
                if (tempSound->type == MUSIC) {
                    sfMusic_destroy(tempSound->music);
                }
                else if (tempSound->type == SOUNDFX) {
                    sfSoundBuffer* buffer = (sfSoundBuffer*)sfSound_getBuffer(tempSound->sound);
                    sfSound_destroy(tempSound->sound);
                    sfSoundBuffer_destroy(buffer);
                }
                free(tempSound);
                tempSound = prev->pNext;
            }
        }
        else {
            tempSound = tempSound->pNext;
        }
    }
}


