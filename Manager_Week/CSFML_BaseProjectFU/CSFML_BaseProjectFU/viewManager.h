#pragma once
#include "tools.h"

 typedef struct 
{
	sfVector2i defaultVideoMode;
	sfVideoMode defaultDesktopMode;
	sfVector2f ratioResolution;
	sfFloatRect rectViewPort;
	sfView* view;
	sfVector2f PosView;
	sfFloatRect rectView;
}View;

View* mainView;

View* setupView(sfVector2i _defaultVideoMode, sfFloatRect _rectViewPort, sfVideoMode _defaultDesktopMode);
View* setupViewCustom(sfVector2i _defaultVideoMode, sfFloatRect _rectViewPort, sfVideoMode _defaultDesktopMode, sfFloatRect _rectView);
void setRectView(View* _view, sfFloatRect _rectview);
sfVector2f GetViewPosition(View* _view);
void SetViewPosition(View* _view, sfVector2f _position);