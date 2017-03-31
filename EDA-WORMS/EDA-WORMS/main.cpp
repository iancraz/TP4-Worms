#include <iostream>
#include <cstdint>
#include "Position.h"
#include "Graphics.h"


int main(int argc, char* argv[])
{
	Graphics g;
	g.GraphicsMain();
	return 0;
}

//
//class Worm
//{
//private:
//	Position p;	//px
//	bool lookingRight;
//	wormState IamDoing;
//	unsigned frameCount;	//
//
//
//public:
//	Worm();
//	void startJumping();
//	void startMoving();
//	void continueAction();
//	void stopMoving();
//	void stopJumping();
//	getPosition();
//	getCurrentFrame();
//	getWormState();
//	bool _lookingRight();
//
//};
//
//
//do {
//	ev = al_get_next_event(eventq);
//
//	if (ev != AL_NO_EVENT)
//	{
//		dispach(event, wormarray);
//	}
//} while (ev != exit)
//
