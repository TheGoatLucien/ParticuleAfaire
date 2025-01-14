#include "game.h"
#include "textureManager.h"
#include "viewManager.h"
#include "stateManager.h"
#include "soundManager.h"
#include "Gamepad.h"
#include "pause.h"
#include "particulesManager.h"

#include <Windows.h>

//sfSprite* sprite;
sfSprite* spBG1;
sfSprite* spBG2;

sfBool gamepadChangePos;
sfVector2f BG1Pos;
sfVector2f BG2Pos;

float timer;
int nbreJoueur;
int waveCount;

float waveTimer;
float soloTimer;
float defaultwaveTimer;
float defaultsoloTimer;
float bossTimer;

sfBool phaseWave;
sfBool phaseBoss;
sfBool phaseBossCompleted;
sfBool gameover;



void initGame(Window* _window)
{
    Texture_Onload(GAME);
    Sound_Onload(GAME); // Charger les sons pour le jeu
    Particle_Onload(GAME); // Charger les particules pour le jeu
    // Jouer la musique de fond
    sfMusic* gameMusic = GetMusic("game_theme");
    if (gameMusic) {
        sfMusic_setLoop(gameMusic, sfTrue);
        sfMusic_play(gameMusic);
    }

    spBG1 = sfSprite_create();
    spBG2 = sfSprite_create();

    sfSprite_setTexture(spBG1, GetTexture("BG1"), sfTrue);
    sfSprite_setTexture(spBG2, GetTexture("BG2"), sfTrue);

    sfSprite_setPosition(spBG2, vector2f(0.0f, -1080.0f));

    sfVector3f ambientLight = { 0.1f, 0.1f, 0.3f };

    BG1Pos = vector2f(0.0f, 0.0f);
    BG2Pos = vector2f(0.0f, -1080.0f);

    SetViewPosition(mainView, vector2f(960.f, 540.f));

    GamepadDetection();

    Sleep(2000); // A enlever juste pour le test Thread

    w.state = sfTrue;

}

void updateGame(Window* _window)
{
    //joue la music

    timer += getDeltaTime();
    Particle* current = particleBegin;
    while (current != NULL) {
        // Mettre � jour la position en fonction de la v�locit�
        current->position.x += current->velocity.x * getDeltaTime();
        current->position.y += current->velocity.y * getDeltaTime();
        sfSprite_setPosition(current->sprite, current->position);

        // R�duire la dur�e de vie
        current->lifetime += getDeltaTime();
        if (current->lifetime >= current->maxLifetime) {
            current = RemoveParticle(current); // Supprimer la particule expir�e
        }
        else {
            current = current->pNext;
        }
    }

    // oncr�er des particules d'explosion
    if (sfKeyboard_isKeyPressed(sfKeySpace)) {
        Particle* explosionParticles = GetParticle("explosion_particles");
        if (explosionParticles) {
            explosionParticles->position = (sfVector2f){ 500.0f, 500.0f };
            explosionParticles->velocity = (sfVector2f){ 0.0f, -100.0f }; // Mouvement vers le haut
            explosionParticles->lifetime = 0.0f; // R�initialiser la dur�e de vie
        }
    }
    for (int i = 0; i < 8; i++)
    {
        if (Gamepad_isButtonPressed(i, OPTION) && timer > 0.2f)
        {
            sfSound* clickSound = GetSound("menu_select");
            if (clickSound)
                sfSound_play(clickSound);
            togglePause();
            timer = 0.0f;
        }
    }

    if (sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue && timer > 0.2f)
    {
        sfSound* clickSound = GetSound("menu_select");
        if (clickSound)
            sfSound_play(clickSound);
        togglePause();
        timer = 0.0f;
    }

    gamepadChangePos = sfFalse;

    BG1Pos.y = BG1Pos.y + 100.f * getDeltaTime();
    BG2Pos.y = BG2Pos.y + 100.f * getDeltaTime();
    if (BG1Pos.y >= 1080.0f)
        BG1Pos.y = BG2Pos.y - 1080.0f;
    if (BG2Pos.y >= 1080.0f)
        BG2Pos.y = BG1Pos.y - 1080.0f;

    sfSprite_setPosition(spBG1, BG1Pos);
    sfSprite_setPosition(spBG2, BG2Pos);
}

void displayGame(Window* _window)
{
    sfRenderWindow_drawSprite(_window->renderWindow, spBG1, NULL);
    sfRenderWindow_drawSprite(_window->renderWindow, spBG2, NULL);
	//afficher les parti

     // affichage des particules
    Particle* current = particleBegin;
    while (current != NULL) {
        sfRenderWindow_drawSprite(_window->renderWindow, current->sprite, NULL);
        current = current->pNext;
    }
}

void deinitGame()
{
    deinitPause();
    sfSprite_destroy(spBG1);
    sfSprite_destroy(spBG2);
    RemoveAllTextureButALL();
    RemoveAllSoundButALL(); // Lib�rer les sons du jeu
    RemoveAllParticleButALL();  // Lib�rer les particules du jeu
}

