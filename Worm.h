#include <cstdint>
#include "Position.h"

typedef enum {STILL, WALKING_PENDING, WALKING, JUMPING, FINISHING_WALKING, FINISHING_JUMPING} wormState;

#define FPS			60.0

class Worm
{
public:
	Worm();

	void startJumping();
	void startMoving();
	void continueAction();
	double getX();
	double getY();
	wormState whatAmIDoing();
	uint32_t getCurrentFrame();
	bool _lookingRight();
	void lookRight(bool temp);

private:
	Position p;	//px
	bool lookingRight;
	wormState IamDoing;
	uint32_t frameCount;
	bool aux;
	double randomPosition(double max);
};