#include "Graphics.h"



#define SCREEN_W		1000
#define SCREEN_H		696
#define MOVE_RATE		0.45
#define CUADRADITO_SIZE		64

enum MYKEYS {
	KEY_UP, KEY_LEFT, KEY_RIGHT,
	KEY_W, KEY_A, KEY_D		//keys
};

Graphics::Graphics()
{
	allegro_setup();
	for (uint i = 0; i < 6; i++) { key_pressed[i] = false; } //Estado de teclas, true cuando esta apretada
	redraw = false;
	do_exit = false;
}

int Graphics::GraphicsMain()
{
	
	bool isLookingRight1 = false;
	bool isLookingRight2 = false;
	float worm1_x = SCREEN_W / 4.0 - CUADRADITO_SIZE / 2.0;			//CAMBIAR A LA CLASE
	float worm1_y = 616;

	float worm2_x = SCREEN_W / 2.0 - CUADRADITO_SIZE / 2.0;
	float worm2_y = 616;

	
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
			if (key_pressed[KEY_UP] && worm1_y >= MOVE_RATE)
				worm1_y -= MOVE_RATE;

			if (key_pressed[KEY_LEFT] && worm1_x >= MOVE_RATE)
			{
				worm1_x -= MOVE_RATE;
				isLookingRight1 = false;		//FALTA SETTER
			}
		
			if (key_pressed[KEY_RIGHT] && worm1_x <= SCREEN_W - CUADRADITO_SIZE - MOVE_RATE)
			{
				worm1_x += MOVE_RATE;
				isLookingRight1 = true;		//FALTA SETTER
			}

			if (key_pressed[KEY_W] && worm2_y >= MOVE_RATE)
				worm2_y -= MOVE_RATE;

			if (key_pressed[KEY_A] && worm2_x >= MOVE_RATE)
			{
				worm2_x -= MOVE_RATE;
				isLookingRight2 = false;		//FALTA SETTER
			}

			if (key_pressed[KEY_D] && worm2_x <= SCREEN_W - CUADRADITO_SIZE - MOVE_RATE)
			{
				worm2_x += MOVE_RATE;
				isLookingRight2 = true;		//FALTA SETTER
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
			al_draw_scaled_bitmap(worm1, 0.0,0.0, al_get_bitmap_width(worm1), al_get_bitmap_height(worm1), worm1_x, worm1_y, CUADRADITO_SIZE, CUADRADITO_SIZE, isLookingRight1);
			al_draw_scaled_bitmap(worm2, 0.0, 0.0, al_get_bitmap_width(worm2), al_get_bitmap_height(worm2), worm2_x, worm2_y, CUADRADITO_SIZE, CUADRADITO_SIZE, isLookingRight2);
			al_flip_display();
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}

//void printWorm(uint32_t frameCount, Worm worm)
//{
//
//}

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
}


int Graphics::loadImages()
{
	Scenario = al_load_bitmap("resources/Scenario.png");
	if (!Scenario) {
		fprintf(stderr, "failed to create Scenario bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	worm1 = al_load_bitmap("resources/test.png");
	if (!worm1) {
		fprintf(stderr, "failed to create worm1 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	worm2 = al_load_bitmap("resources/test.png");
	if (!worm2) {
		fprintf(stderr, "failed to create worm1 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
}