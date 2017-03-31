#include <iostream>



typedef enum { STILL, WALKING_PENDING, WALKING, JUMPING, FINISHING_WALKING, FINISHING_JUMING } wormState;


class Worm
{
private:
	Position p;	//px
	bool lookingRight;
	wormState IamDoing;
	unsigned frameCount;	//


public:
	Worm();
	void startJumping();
	void startMoving();
	void continueAction();
	void stopMoving();
	void stopJumping();
	getPosition();
	getCurrentFrame();
	getWormState();
	bool _lookingRight();

};


do {
	ev = al_get_next_event(eventq);

	if (ev != AL_NO_EVENT)
	{
		dispach(event, wormarray);
	}
} while (ev != exit)

