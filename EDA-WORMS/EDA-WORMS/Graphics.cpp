#include "Graphics.h"
//void intro(ALLEGRO_DISPLAY*display,int largo,int alto);



enum MYKEYS {
	KEY_UP, KEY_LEFT, KEY_RIGHT,
	KEY_W, KEY_A, KEY_D		//keys
};

Graphics::Graphics()
{
	if(allegro_setup() == -1)
		fprintf(stderr, "ALLEGRO ERROR\n");
	if (loadImages() == -1)
		fprintf(stderr, "ALLEGRO ERROR\n");

	al_set_window_title(display, "SEGA GENESIS-WOMRS");
	al_set_mouse_cursor(display, cursor);
	al_set_display_icon(display, sega);


	intro();
	
	for (uint i = 0; i < 6; i++) { key_pressed[i] = false; } //Estado de teclas, true cuando esta apretada
	
	

	redraw = false;		//Variable que me indica cuando tengo que dibujar
	do_exit = false;	//Flag para indicar el final del programa
	miliseconds = false;	//Flag para evitar el movimiento antes de los 100ms

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source()); //REGISTRAMOS EL TECLADO

	al_clear_to_color(al_map_rgb(218, 227, 125));
	al_draw_bitmap(Scenario, 0.0, 0.0, 0);				//Dibujamos el fondo
	al_flip_display();
	al_start_timer(timer);		//Arraca el timer para 1 frame


	//ARREGLOS QUE CONTIENEN EL NUMERO DE IMAGENES PARA GRAFICAR LOS MOVIMIENTOS PERTINENTES
	//Al valor se le resta 1 para desreferenciar mas facil

	uint _walkArray []= {4,4,4,4,4,1,2,3,4,5,6,7,8,9,10,11,11,12,13,14,15,4,4,5,6,7,8,9,10,11,11,12,13,14,15,4,4,5,6,7,8,9,10,11,11,12,13,14,15,4};
	for (uint i = 0; i < 50; i++) { walkArray[i] = _walkArray[i] - 1; }
	
	uint _jumpArray []= {1,2,3,4,5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,6,7,8,9,10};
	for (uint i = 0; i < 50; i++) { jumpArray[i] = _jumpArray[i] - 1; }
	
	ALLEGRO_BITMAP *_bitmapArrWalk[] = {wWalkF1,wWalkF2,wWalkF3,wWalkF4,wWalkF5,wWalkF6,wWalkF7,wWalkF8,wWalkF9,wWalkF10,wWalkF11,wWalkF12,wWalkF13,wWalkF14,wWalkF15};
	for (uint i = 0; i < 15; i++) { bitmapArrWalk[i] = _bitmapArrWalk[i]; }
	ALLEGRO_BITMAP *_bitmapArrJump[] = {wJumpF1,wJumpF2,wJumpF3,wJumpF4,wJumpF5,wJumpF6,wJumpF7,wJumpF8,wJumpF9,wJumpF10};
	for (uint i = 0; i < 10; i++) { bitmapArrJump[i] = _bitmapArrJump[i]; }
}


void Graphics::intro()
{
	
	ALLEGRO_BITMAP* logo = NULL;
	ALLEGRO_BITMAP* image = NULL;
	ALLEGRO_BITMAP *imagen2 = NULL;
	ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue1 = NULL;
	ALLEGRO_EVENT evIntro;
	ALLEGRO_TIMER *timer1 = NULL;
	ALLEGRO_FONT * font = NULL;

	int alto = SCREEN_W;
	int largo = SCREEN_H;


	logo = al_load_bitmap("resources/worms.png");
	if (!logo)
	{
		fprintf(stderr, "failed to create logo bitmap!\n");
	}

	imagen2 = al_load_bitmap("resources/logo_gusano.png");
	if (!imagen2)
	{
		fprintf(stderr, "failed to create imagen2 bitmap!\n");
	}

	

	sample = al_load_sample("resources/Sega1991.wav");
	if (!sample)
	{
		fprintf(stderr, "failed to create sample!\n");
	}

	

	font = al_load_font("resources/ARCADE.TTF", 72, 0);
	if (!font)
	{
		fprintf(stderr, "failed to create sega bitmap!\n");
	}

	timer1 = al_create_timer(0.5);
	if (!timer1)
	{
		fprintf(stderr, "failed to create timer1!\n");
	}
	event_queue1 = al_create_event_queue();
	if (!event_queue1)
	{
		fprintf(stderr, "failed to create eventqueue1!\n");
	}

	
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	al_rest(2.5);

	al_draw_scaled_bitmap(sega,
		0, 0,                                // source origin
		al_get_bitmap_width(sega),     // source width
		al_get_bitmap_height(sega),    // source height
		largo / 6, alto / 4,                                // target origin
		al_get_bitmap_width(sega) * 2 / 3, al_get_bitmap_height(sega)*0.5,                                // target dimensions
		0                                    // flags
	);

	al_flip_display();

	al_rest(2.5);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_stop_samples();
	al_destroy_sample(sample);
	//=========================================================================================================================	
	al_play_sample(sample2, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

	for (int i = alto; i >= -500; i -= 10) {

		al_draw_bitmap(logo, largo / 3, i, 0);
		al_draw_bitmap(imagen2, largo *0.5, i + (alto / 6) + 500, 0);

		al_flip_display();
		al_rest(0.1);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_flip_display();

	}


	al_draw_bitmap(imagen2, largo *  0.5, alto / 6, 0);
	al_flip_display();
	al_rest(2);
	for (float timer = 1; timer != 30; timer++) {

		al_draw_tinted_bitmap(imagen2,
			al_map_rgba_f(1 / timer, 1 / timer, 1 / timer, 1 / timer),
			largo *0.5, alto / 6, 0);
		al_flip_display();


		al_rest(0.08);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_flip_display();
	}

	switch (rand() % 5)
	{
	case 4: {
		image = al_load_bitmap("resources/fondo0.jpg");
		al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), 0, 0, alto, largo, 0);
		al_flip_display();
		break;
	}
	case 3: {
		image = al_load_bitmap("resources/fondo1.png");
		al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), 0, 0, alto, largo, 0);
		al_flip_display();
		break;
	}
	case 2: {
		image = al_load_bitmap("resources/fondo2.png");
		al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), 0, 0, alto, largo, 0);
		al_flip_display();
		break;
	}
	case 1: {
		image = al_load_bitmap("resources/fondo3.png");
		al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), 0, 0, alto, largo, 0);
		al_flip_display();
		break;
	}
	case 0: {
		image = al_load_bitmap("resources/fondo4.png");
		al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), 0, 0, alto, largo, 0);
		al_flip_display();
		break;
	}

	}
	al_destroy_bitmap(imagen2);
	al_flip_display();


	al_register_event_source(event_queue1, al_get_display_event_source(display));
	al_register_event_source(event_queue1, al_get_timer_event_source(timer1));
	al_register_event_source(event_queue1, al_get_keyboard_event_source());

	al_start_timer(timer1);

	while (1)
	{
		al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), 0, 0, alto, largo, 0);
		al_flip_display();


		al_wait_for_event(event_queue1, &evIntro);

		if (evIntro.type == ALLEGRO_EVENT_TIMER) {
			al_draw_text(font, al_map_rgb(255, 255, 255), alto / 2, (largo * 5 / 6), ALLEGRO_ALIGN_CENTRE, "Press any key to continue");
			al_flip_display();
			al_rest(0.2);

		}
		else if (evIntro.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit(3);
		}
		else if (evIntro.type == ALLEGRO_EVENT_KEY_DOWN) {
			break;
		}

		al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), 0, 0, alto, largo, 0);
		al_flip_display();

	}

	al_destroy_bitmap(image);
	al_destroy_bitmap(logo);
	al_destroy_font(font);
	al_destroy_timer(timer1);
	al_destroy_event_queue(event_queue1);
}

int Graphics::GraphicsMain()
{
	while (!do_exit)
	{
		ALLEGRO_EVENT ev;

		al_wait_for_event(event_queue, &ev);
		dispatcher(ev);

		if (redraw)
		{
			worm1.continueAction();
			worm2.continueAction();
			redraw = false;
			al_clear_to_color(al_map_rgb(218, 227, 125));
			al_draw_bitmap(Scenario, 0.0, 0.0, 0);
			printWorm(worm1);
			printWorm(worm2);
			al_flip_display();
		}



	}
	

	return 0;
}


void Graphics::printWorm(Worm worm)
{

	if(worm.whatAmIDoing() == WALKING ||worm.whatAmIDoing() == FINISHING_WALKING )
	{
			al_draw_scaled_bitmap(bitmapArrWalk[walkArray[worm.getCurrentFrame()]], 0.0, 0.0, al_get_bitmap_width(wWalkF4), al_get_bitmap_height(wWalkF4), worm.getX(), worm.getY(), CUADRADITO_SIZE, CUADRADITO_SIZE, worm._lookingRight());
	}
	else if(worm.whatAmIDoing() == JUMPING ||worm.whatAmIDoing() == FINISHING_JUMPING)
	{
			al_draw_scaled_bitmap(bitmapArrJump[jumpArray[worm.getCurrentFrame()]], 0.0, 0.0, al_get_bitmap_width(wWalkF4), al_get_bitmap_height(wWalkF4), worm.getX(), worm.getY(), CUADRADITO_SIZE, CUADRADITO_SIZE, worm._lookingRight());
	}
	else
		al_draw_scaled_bitmap(wWalkF4, 0.0, 0.0, al_get_bitmap_width(wWalkF4), al_get_bitmap_height(wWalkF4), worm.getX(), worm.getY(), CUADRADITO_SIZE, CUADRADITO_SIZE, worm._lookingRight());

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


	if (!al_install_audio())
	{
		fprintf(stderr, "Unable to start audio addon \n");
		al_uninstall_system();
		return -1;
	}
	if (!al_install_keyboard())
	{
		fprintf(stderr, "Unable to start keyboard addon \n");
		al_uninstall_system();
		return -1;
	}
	if (!al_install_mouse())
	{
		fprintf(stderr, "Unable to start mouse addon \n");
		al_uninstall_system();
		return -1;
	}
	if (!al_init_acodec_addon())
	{
		fprintf(stderr, "Unable to start audio codec addon \n");
		al_uninstall_system();
		return -1;
	}
	if (!al_reserve_samples(1))
	{
		fprintf(stderr, "Unable to reserve samples \n");
		al_uninstall_system();
		return -1;
	}
	

	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();	// initialize the ttf (True Type Font) addon


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


	sega = al_load_bitmap("resources/sega.png");
	if (!sega)
	{
		fprintf(stderr, "failed to create sega bitmap!\n");
	}

	mouse = al_load_bitmap("resources/mouse/mouse.png");
	if (!mouse)
	{
		fprintf(stderr, "failed to create mouse bitmap!\n");
	}

	cursor = al_create_mouse_cursor(mouse, 0, 0);
	if (!cursor)
	{
		fprintf(stderr, "failed to create cursor bitmap!\n");
	}

	sample2 = al_load_sample("resources/WormsReloadedOST.wav");
	if (!sample2)
	{
		fprintf(stderr, "failed to create sample2!\n");
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


void Graphics::dispatcher(ALLEGRO_EVENT ev)
{
	if (ev.type == ALLEGRO_EVENT_TIMER)
	{
		if (key_pressed[KEY_UP] && worm2.whatAmIDoing() == STILL)
		{
			worm2.startJumping();
			key_pressed[KEY_UP] = false;
		}
		else if (key_pressed[KEY_LEFT] && (worm2.whatAmIDoing() == STILL || worm2.whatAmIDoing() == FINISHING_WALKING))
		{
			if (miliseconds == 6)
			{
				worm2.lookRight(false);
				worm2.startMoving();
				//key_pressed[KEY_LEFT] = false;
			}
			else 
			{
				worm2.lookRight(false);
				miliseconds++;
			}
				
		}

		else if (key_pressed[KEY_RIGHT] && (worm2.whatAmIDoing() == STILL || worm2.whatAmIDoing() == FINISHING_WALKING))
		{
			if (miliseconds == 6)
			{
				worm2.lookRight(true);
				worm2.startMoving();
				//key_pressed[KEY_RIGHT] = false;
			}
			else
			{
				worm2.lookRight(true);
				miliseconds++;
			}
				
		}
		else if (key_pressed[KEY_W] && worm1.whatAmIDoing() == STILL)
		{
			worm1.startJumping();
			key_pressed[KEY_W] = false;
		}
		else if (key_pressed[KEY_A] && (worm1.whatAmIDoing() == STILL || worm1.whatAmIDoing() == FINISHING_WALKING))
		{
			if (miliseconds == 6)
			{
				worm1.lookRight(false);
				worm1.startMoving();
				//key_pressed[KEY_A] = false;
			}
			else
			{
				worm1.lookRight(false);
				miliseconds++;
			}
				
		}

		else if (key_pressed[KEY_D] && (worm1.whatAmIDoing() == STILL || worm1.whatAmIDoing() == FINISHING_WALKING))
		{
			if (miliseconds == 6)
			{
				worm1.lookRight(true);
				worm1.startMoving();
				//key_pressed[KEY_D] = false;
			}
			else
			{
				worm1.lookRight(true);
				miliseconds++;
			}
				
		}
		redraw = true;
	}
	else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		do_exit = true;
	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_UP:
			if (worm2.whatAmIDoing() == STILL)
				key_pressed[KEY_UP] = true;
			break;
		case ALLEGRO_KEY_LEFT:
			if (worm2.whatAmIDoing() == STILL || worm2.whatAmIDoing() == FINISHING_WALKING)
				key_pressed[KEY_LEFT] = true;
			break;
		case ALLEGRO_KEY_RIGHT:
			if (worm2.whatAmIDoing() == STILL || worm2.whatAmIDoing() == FINISHING_WALKING)
				key_pressed[KEY_RIGHT] = true;
			break;
		case ALLEGRO_KEY_W:
			if (worm1.whatAmIDoing() == STILL)
				key_pressed[KEY_W] = true;
			break;
		case ALLEGRO_KEY_A:
			if (worm1.whatAmIDoing() == STILL || worm1.whatAmIDoing() == FINISHING_WALKING)
				key_pressed[KEY_A] = true;
			break;
		case ALLEGRO_KEY_D:
			if (worm1.whatAmIDoing() == STILL || worm1.whatAmIDoing() == FINISHING_WALKING)
				key_pressed[KEY_D] = true;
			break;
		}
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		switch (ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_UP:
			key_pressed[KEY_UP] = false;
			break;
		case ALLEGRO_KEY_LEFT:
			key_pressed[KEY_LEFT] = false;
			miliseconds = 0;
			break;
		case ALLEGRO_KEY_RIGHT:
			key_pressed[KEY_RIGHT] = false;
			miliseconds = 0;
			break;
		case ALLEGRO_KEY_W:
			key_pressed[KEY_W] = false;
			break;
		case ALLEGRO_KEY_A:
			key_pressed[KEY_A] = false;
			miliseconds = 0;
			break;
		case ALLEGRO_KEY_D:
			key_pressed[KEY_D] = false;
			miliseconds = 0;
			break;
		case ALLEGRO_KEY_ESCAPE:
			do_exit = true;
			break;
		}
	}
}


void Graphics::allegro_desinstalar()
{
	al_destroy_bitmap(wWalkF1);
	al_destroy_bitmap(wWalkF2);
	al_destroy_bitmap(wWalkF3);
	al_destroy_bitmap(wWalkF4);
	al_destroy_bitmap(wWalkF5);
	al_destroy_bitmap(wWalkF6);
	al_destroy_bitmap(wWalkF7);
	al_destroy_bitmap(wWalkF8);
	al_destroy_bitmap(wWalkF9);
	al_destroy_bitmap(wWalkF10);
	al_destroy_bitmap(wWalkF11);
	al_destroy_bitmap(wWalkF12);
	al_destroy_bitmap(wWalkF13);
	al_destroy_bitmap(wWalkF14);
	al_destroy_bitmap(wWalkF15);

	al_destroy_bitmap(wJumpF1);
	al_destroy_bitmap(wJumpF2);
	al_destroy_bitmap(wJumpF3);
	al_destroy_bitmap(wJumpF4);
	al_destroy_bitmap(wJumpF5);
	al_destroy_bitmap(wJumpF6);
	al_destroy_bitmap(wJumpF7);
	al_destroy_bitmap(wJumpF8);
	al_destroy_bitmap(wJumpF9);
	al_destroy_bitmap(wJumpF10);

	al_destroy_bitmap(Scenario);
	al_destroy_bitmap(sega);
	al_destroy_bitmap(mouse);
	al_destroy_sample(sample2);

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);


	al_uninstall_system();
	al_shutdown_image_addon();
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_shutdown_primitives_addon();
	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
	


}