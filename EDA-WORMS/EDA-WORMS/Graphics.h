#pragma once
#ifndef _GRAPHICS_H
#define _GGRAPHICS_H


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "Worm.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include<allegro5\allegro_video.h>
#include<allegro5\allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include<allegro5\allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include<allegro5\mouse.h>
#include<allegro5\mouse_cursor.h>



#define CUADRADITO_SIZE		60
#define SCREEN_W		1000
#define SCREEN_H		696

typedef uint32_t uint;

class Graphics
{
public:
	Graphics();
	int GraphicsMain();
	int allegro_setup();
	void allegro_desinstalar();
	void printWorm(Worm _worm);
	void intro();

private:
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *Scenario = NULL;
	ALLEGRO_BITMAP *sega = NULL;
	ALLEGRO_BITMAP* mouse = NULL;
	ALLEGRO_MOUSE_CURSOR *cursor = NULL;
	ALLEGRO_SAMPLE *sample2 = NULL;


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

	uint walkArray[50];
	uint jumpArray[50]; 
	ALLEGRO_BITMAP * bitmapArrWalk[15];
	ALLEGRO_BITMAP * bitmapArrJump[10];


	Worm worm1;
	Worm worm2;

	uint miliseconds;
	bool key_pressed[6]; //Estado de teclas, true cuando esta apretada
	bool redraw;
	bool do_exit;

	int loadImages();
	void dispatcher(ALLEGRO_EVENT ev);

};



#endif // !_GRAPHICS_H
