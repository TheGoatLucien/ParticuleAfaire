#pragma once
#include "tools.h"


// Variables
typedef struct 
{
	sfRenderWindow* renderWindow;
	sfBool isDone;
	sfBool isFullscreen;
	char* windowTitle;
	sfVideoMode videoMode;
	sfVector2i defaultVideoMode;
	sfEvent event;
}Window;

// Prototypes
sfBool IsDone(Window* This);
sfBool IsFullscreen(Window* This);
void BeginDraw(Window* This); // Clear the window.
void EndDraw(Window* This); // Display the changes.
Window* windowSetup(const char* _Title, sfVector2i _defaultVideoMode);
void windowDestroy(Window* This);
void windowCreate(Window* This);
void ToggleFullscreen(Window* This);
void windowInit(Window* This);
void windowUpdate(Window* This);
void windowDraw(Window* This);