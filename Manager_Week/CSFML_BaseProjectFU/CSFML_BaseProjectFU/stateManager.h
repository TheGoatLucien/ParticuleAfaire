#pragma once
#include "tools.h"
#include "windowManager.h"


typedef enum 
{
	RTNULL = -1, 
	ALL,
	INTRO,
	MENU,
	GAME,
	EDITOR,
	END
}State;


typedef struct 
{
	sfBool state;
	sfMutex* mutex;
}watcher;

watcher w;

static State state = MENU;

static sfBool onePass = sfFalse;
static sfBool isPaused = sfFalse;
static sfBool isOption = sfFalse;

sfThread* loadingThread;
sfSprite* spLoading;

void stateInit(Window* _window);
void stateEventUpdate(Window* _window, sfEvent* _event);
void stateUpdate(Window* _window);
void stateDisplay(Window* _window);
void stateDeinit(Window* _window);
void changeState(Window* _window, State _state);
void togglePause();
void toggleOptions();