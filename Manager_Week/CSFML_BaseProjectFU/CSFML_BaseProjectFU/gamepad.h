#pragma once
#include "tools.h"
//#include "player.h"

typedef enum gamepadPS4 gamepadPS4;
enum gamepadPS4
{
	CROIX,
	ROND,
	CARRE,
	TRIANGLE,
	L1,
	R1,
	SHARE,
	OPTION,
	BSTICKL,
	BSTICKR,
	PS,
	BTOUCHPAD,
	L2,
	R2,
	NOTUSED,
	STICKLX,
	STICKLY,
	CROSSX,
	CROSSY,
	STICKRX,
	STICKRY,
	TRIGGER_R2,
	TRIGGER_L2
};

typedef struct gamepad gamepad;
struct gamepad
{
	sfVector2f stickL;
	sfVector2f stickR;
	sfVector2f cross;
	float TriggerL;
	float TriggerR;
	int Bouton[14];
};
gamepad Gamepad[8];

void GamepadDetection();
void GamepadManager(int _joystickId, sfEvent event);
int Gamepad_isButtonPressed(unsigned int _joystickId, gamepadPS4 _button);
float Gamepad_isJoystickMoved(unsigned int _joystickId, gamepadPS4 _Axis);

