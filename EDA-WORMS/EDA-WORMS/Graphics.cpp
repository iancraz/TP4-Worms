#include "Graphics.h"



#define SCREEN_W		1000
#define SCREEN_H		696

enum MYKEYS {
	KEY_UP, KEY_LEFT, KEY_RIGHT,
	KEY_W, KEY_A, KEY_D		//keys
};

Graphics::Graphics()
{
	if(allegro_setup() == -1)
		fprintf(stderr, "ALLEGRO ERROR\n");
	for (uint i = 0; i < 6; i++) { key_pressed[i] = false; } //Estado de teclas, true cuando esta apretada
	redraw = false;
	do_exit = false;
}

int Graphics::GraphicsMain()
{
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source()); //REGISTRAMOS EL TECLADO

	al_clear_to_color(al_map_rgb(218, 227, 125));
	al_draw_bitmap(Scenario, 0.0, 0.0, 0);
	al_flip_display();
	al_start_timer(timer);
	

	while (!do_exit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		//al_get_next_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (key_pressed[KEY_UP])
				worm1.startJumping();

			if (key_pressed[KEY_LEFT])
			{
				worm1._lookingRight = false;
				if(worm1.whatAmIDoing() == STILL)
					worm1.startMoving
				else if (worm1.whatAmIDoing() == )
				
					//FALTA SETTER
			}
		
			if (key_pressed[KEY_RIGHT])
			{
				worm1_x += MOVE_RATE;
				worm_1._lookingRight = true;		//FALTA SETTER
			}

			if (key_pressed[KEY_W] && worm2_y >= MOVE_RATE)
				worm2_y -= MOVE_RATE;

			if (key_pressed[KEY_A] && worm2_x >= MOVE_RATE)
			{
				worm2_x -= MOVE_RATE;
				worm_2._lookingRight = false;		//FALTA SETTER
			}

			if (key_pressed[KEY_D] && worm2_x <= SCREEN_W - CUADRADITO_SIZE - MOVE_RATE)
			{
				worm2_x += MOVE_RATE;
				worm_2._lookingRight = true;		//FALTA SETTER
			}
				

			redraw = true;
		}

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			do_exit = true;

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key_pressed[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key_pressed[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key_pressed[KEY_RIGHT] = true;
				break;
			case ALLEGRO_KEY_W:
				key_pressed[KEY_W] = true;
				break;
			case ALLEGRO_KEY_A:
				key_pressed[KEY_A] = true;
				break;
			case ALLEGRO_KEY_D:
				key_pressed[KEY_D] = true;
				break;
			}
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key_pressed[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key_pressed[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key_pressed[KEY_RIGHT] = false;
				break;
			case ALLEGRO_KEY_W:
				key_pressed[KEY_W] = false;
				break;
			case ALLEGRO_KEY_A:
				key_pressed[KEY_A] = false;
				break;
			case ALLEGRO_KEY_D:
				key_pressed[KEY_D] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				do_exit = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {

			redraw = false;
			al_clear_to_color(al_map_rgb(218, 227, 125));
			al_draw_bitmap(Scenario, 0.0, 0.0, 0);
			al_draw_scaled_bitmap(worm1, 0.0,0.0, al_get_bitmap_width(worm1), al_get_bitmap_height(worm1), worm1.getX(), worm1.getY(), CUADRADITO_SIZE, CUADRADITO_SIZE, worm1._lookingRight);
			al_draw_scaled_bitmap(worm2, 0.0, 0.0, al_get_bitmap_width(worm2), al_get_bitmap_height(worm2), worm2.getX(), worm2.getY(), CUADRADITO_SIZE, CUADRADITO_SIZE, worm2._lookingRight);
			al_flip_display();
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}

void printWorm(uint32_t frameCount, Worm worm)
{

}

int Graphics::allegro_setup()
{
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}
	if (!al_init_image_addon())
	{
		fprintf(stderr, "Unable to start image addon \n"); 
		al_uninstall_system();
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}
	

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	return 0;
}


int Graphics::loadImages()
{
	Scenario = al_load_bitmap("resources/Scenario.png");
	if (!Scenario) {
		fprintf(stderr, "failed to create Scenario bitmap!\n");
		return -1;
	}

	wWalkF1 = al_load_bitmap("resources/wwalking/wwalk-F1.png");
	if (!wWalkF1)
	{
		fprintf(stderr, "failed to create wwalk-F1 bitmap!\n");
		return -1;
	}

	wWalkF2 = al_load_bitmap("resources/wwalking/wwalk-F2.png");
	if (!wWalkF2)
	{
		fprintf(stderr, "failed to create wwalk-F2 bitmap!\n");
		return -1;
	}

	wWalkF3 = al_load_bitmap("resources/wwalking/wwalk-F3.png");
	if (!wWalkF3)
	{
		fprintf(stderr, "failed to create wwalk-F3 bitmap!\n");
		return -1;
	}

	wWalkF4 = al_load_bitmap("resources/wwalking/wwalk-F4.png");
	if (!wWalkF4)
	{
		fprintf(stderr, "failed to create wwalk-F4 bitmap!\n");
		return -1;
	}

	wWalkF5 = al_load_bitmap("resources/wwalking/wwalk-F5.png");
	if (!wWalkF5)
	{
		fprintf(stderr, "failed to create wwalk-F5 bitmap!\n");
		return -1;
	}

	wWalkF6 = al_load_bitmap("resources/wwalking/wwalk-F6.png");
	if (!wWalkF6)
	{
		fprintf(stderr, "failed to create wwalk-F6 bitmap!\n");
		return -1;
	}

	wWalkF7 = al_load_bitmap("resources/wwalking/wwalk-F7.png");
	if (!wWalkF7)
	{
		fprintf(stderr, "failed to create wwalk-F7 bitmap!\n");
		return -1;
	}

	wWalkF8 = al_load_bitmap("resources/wwalking/wwalk-F8.png");
	if (!wWalkF8)
	{
		fprintf(stderr, "failed to create wwalk-F8 bitmap!\n");
		return -1;
	}

	wWalkF9 = al_load_bitmap("resources/wwalking/wwalk-F9.png");
	if (!wWalkF9)
	{
		fprintf(stderr, "failed to create wwalk-F9 bitmap!\n");
		return -1;
	}

	wWalkF10 = al_load_bitmap("resources/wwalking/wwalk-F10.png");
	if (!wWalkF10)
	{
		fprintf(stderr, "failed to create wwalk-F10 bitmap!\n");
		return -1;
	}

	wWalkF11 = al_load_bitmap("resources/wwalking/wwalk-F11.png");
	if (!wWalkF11)
	{
		fprintf(stderr, "failed to create wwalk-F11 bitmap!\n");
		return -1;
	}

	wWalkF12 = al_load_bitmap("resources/wwalking/wwalk-F12.png");
	if (!wWalkF12)
	{
		fprintf(stderr, "failed to create wwalk-F12 bitmap!\n");
		return -1;
	}

	wWalkF13 = al_load_bitmap("resources/wwalking/wwalk-F13.png");
	if (!wWalkF13)
	{
		fprintf(stderr, "failed to create wwalk-F13 bitmap!\n");
		return -1;
	}

	wWalkF14 = al_load_bitmap("resources/wwalking/wwalk-F14.png");
	if (!wWalkF14)
	{
		fprintf(stderr, "failed to create wwalk-F14 bitmap!\n");
		return -1;
	}
	
	wWalkF15 = al_load_bitmap("resources/wwalking/wwalk-F15.png");
	if (!wWalkF15)
	{
		fprintf(stderr, "failed to create wwalk-F15 bitmap!\n");
		return -1;
	}


	wJumpF1 = al_load_bitmap("resources/wjump/wjump-F1.png");
	if (!wJumpF1)
	{
		fprintf(stderr, "failed to create wjump-F1 bitmap!\n");
		return -1;
	}
	wJumpF2 = al_load_bitmap("resources/wjump/wjump-F2.png");
	if (!wJumpF2)
	{
		fprintf(stderr, "failed to create wjump-F2 bitmap!\n");
		return -1;
	}
	wJumpF3 = al_load_bitmap("resources/wjump/wjump-F3.png");
	if (!wJumpF3)
	{
		fprintf(stderr, "failed to create wjump-F3 bitmap!\n");
		return -1;
	}
	wJumpF4 = al_load_bitmap("resources/wjump/wjump-F4.png");
	if (!wJumpF4)
	{
		fprintf(stderr, "failed to create wjump-F4 bitmap!\n");
		return -1;
	}
	wJumpF5 = al_load_bitmap("resources/wjump/wjump-F5.png");
	if (!wJumpF5)
	{
		fprintf(stderr, "failed to create wjump-F5 bitmap!\n");
		return -1;
	}
	wJumpF6 = al_load_bitmap("resources/wjump/wjump-F6.png");
	if (!wJumpF6)
	{
		fprintf(stderr, "failed to create wjump-F6 bitmap!\n");
		return -1;
	}
	wJumpF7 = al_load_bitmap("resources/wjump/wjump-F7.png");
	if (!wJumpF7)
	{
		fprintf(stderr, "failed to create wjump-F7 bitmap!\n");
		return -1;
	}
	wJumpF8 = al_load_bitmap("resources/wjump/wjump-F8.png");
	if (!wJumpF8)
	{
		fprintf(stderr, "failed to create wjump-F8 bitmap!\n");
		return -1;
	}
	wJumpF9 = al_load_bitmap("resources/wjump/wjump-F9.png");
	if (!wJumpF9)
	{
		fprintf(stderr, "failed to create wjump-F9 bitmap!\n");
		return -1;
	}
	wJumpF10 = al_load_bitmap("resources/wjump/wjump-F10.png");
	if (!wJumpF10)
	{
		fprintf(stderr, "failed to create wjump-F10 bitmap!\n");
		return -1;
	}

	

	return 0;
}