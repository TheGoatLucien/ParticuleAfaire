#pragma once
#include "tools.h"
#include "stateManager.h"
#include "windowManager.h"

sfFont* fontScore;

void initMenu(Window* _window);
void updateMenu(Window* _window);
void displayMenu(Window* _window);
void deinitMenu();

