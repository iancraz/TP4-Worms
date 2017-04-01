#pragma once
#ifndef _GRAPHICS_H
#define _GGRAPHICS_H

#include <cstdio>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "Worm.h"

typedef uint32_t uint;

class Graphics
{
public:
	Graphics();
	int GraphicsMain();
	int allegro_setup();

private:
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *Scenario = NULL;


	ALLEGRO_BITMAP *wWalkF1 = NULL;
	ALLEGRO_BITMAP *wWalkF2 = NULL;
	ALLEGRO_BITMAP *wWalkF3 = NULL;
	ALLEGRO_BITMAP *wWalkF4 = NULL;
	ALLEGRO_BITMAP *wWalkF5 = NULL;
	ALLEGRO_BITMAP *wWalkF6 = NULL;
	ALLEGRO_BITMAP *wWalkF7 = NULL;
	ALLEGRO_BITMAP *wWalkF8 = NULL;
	ALLEGRO_BITMAP *wWalkF9 = NULL;
	ALLEGRO_BITMAP *wWalkF10 = NULL;
	ALLEGRO_BITMAP *wWalkF11 = NULL;
	ALLEGRO_BITMAP *wWalkF12 = NULL;
	ALLEGRO_BITMAP *wWalkF13 = NULL;
	ALLEGRO_BITMAP *wWalkF14 = NULL;
	ALLEGRO_BITMAP *wWalkF15 = NULL;

	ALLEGRO_BITMAP *wJumpF1 = NULL;
	ALLEGRO_BITMAP *wJumpF2 = NULL;
	ALLEGRO_BITMAP *wJumpF3 = NULL;
	ALLEGRO_BITMAP *wJumpF4 = NULL;
	ALLEGRO_BITMAP *wJumpF5 = NULL;
	ALLEGRO_BITMAP *wJumpF6 = NULL;
	ALLEGRO_BITMAP *wJumpF7 = NULL;
	ALLEGRO_BITMAP *wJumpF8 = NULL;
	ALLEGRO_BITMAP *wJumpF9 = NULL;
	ALLEGRO_BITMAP *wJumpF10 = NULL;


	Worm worm1;
	Worm worm2;

	bool key_pressed[6]; //Estado de teclas, true cuando esta apretada
	bool redraw;
	bool do_exit;

	int loadImages();

};



#endif // !_GRAPHICS_H
