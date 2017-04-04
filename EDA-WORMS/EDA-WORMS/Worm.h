#include <cstdint>
#include "Position.h"

typedef enum {STILL, WALKING_PENDING, WALKING, JUMPING, FINISHING_WALKING, FINISHING_JUMPING} wormState;

#define FPS			50.0

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
	bool lookingRight;	//Variable que define a donde mira el worm
	wormState IamDoing;	//Variable que me dice que esta haciendo el worm (saltando o caminando o quieto)
	uint32_t frameCount;
	bool aux;		// Variable que me indica cuando choca con los limites
	double randomPosition(double max);
};