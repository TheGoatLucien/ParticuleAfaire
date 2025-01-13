#pragma once
#include "tools.h"
#include "stateManager.h"

typedef enum dialBox dialBox;
enum dialBox
{
	INFO,
	ALERT
};

typedef struct stDialogBox stDialogBox;
struct stDialogBox
{
	sfVector2f position;
	sfVector2f size;
	dialBox type;
	sfRectangleShape* dialogshape;
	sfRectangleShape* dialogshapeNo;
	sfRectangleShape* dialogshapeYes;
	char* message;
	sfText* txt;
	sfText* txtYes;
	sfText* txtNo;
};

stDialogBox* currentDialogBox;
sfBool isDialogBox;
sfBool DialogBoxChoice;
int DialogBoxCode;

void dialogBoxCreate(dialBox _type, char* _message, int _DialogBoxCode);
void dialogBoxUpdate(Window* _window);
void dialogBoxDisplay(Window* _window);
void dialogBoxDestroy();
void DialogBoxManager(Window* _window, int _code);