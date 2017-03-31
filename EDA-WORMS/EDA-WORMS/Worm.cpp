#include "Worm.h"
#include <cmath>
#define START_POSITION	701
#define MAX_POSITION	511
#define MAX_Y_POSITION	616
#define V_JUMP	27.0
#define V_WALK	27.0
#define GRAVITY	0.24

Worm::Worm()
{
	p.setx(START_POSITION+randomPosition(MAX_POSITION));
	p.setY(MAX_Y_POSITION);
	lookignRight = (rand()%2);
	IamDoing = STILL;
	frameCount = 0;
	aux=false;
}

double Worm::randomPosition(double max)
{
	double temp;
	temp = (double)(rand()/((double)RAND_MAX/max));
	return temp;
}

void Worm::startMoving(void)//Funcion que mueve la posicion del worm en un frame.
{
	IamDoing = WALKING;
	aux=false;
	frameCount=0;
}

void Worm::startJumping()
{
	IamDoing=JUMPING;
	aux=false;
	frameCount = 0;
}

void Worms::continueAction()
{
	if(frameCount > FPS || aux == true)
	{
		switch(IamDoing)
		{
			case JUMPING:
				if(aux==true)
					IamDoing=FINISHING_JUMPING;
				break;
			case WALKING:
				IamDoing=FINISHING_WALKING;
				break;
			default:
				IamDoing=STILL;
				break;
		}
		frameCount=0;
		aux=false;
	}

	if(IamDoing == JUMPING && aux == false)
	{
		p.setY(MIN_Y_POSITION + sin((double)60*2*M_PI/180)*V_JUMP* ((double)1/(FPS - frameCount + 1)) + (GRAVITY * pow(((double)1/(FPS - frameCount +1)),2)));
		switch(lookignRight)
		{
			case true:
				p.setX(p.getX()+cos((double)60*2*M_PI/180)*V_JUMP*((double)1/(FPS - frameCount+1)));
				break;
			case false:
				p.setX(p.getX()-cos((double)60*2*M_PI/180)*V_JUMP*((double)1/(FPS - frameCount+1)));
				break;
		}
		if(p.getY() > MAX_Y_POSITION)
		{
			p.setY(MAX_Y_POSITION);
			aux = true;
		}
		frameCount++;
	}
	else if(IamDoing == WALKING && aux == false)
	{
		switch(lookignRight)
		{
			case true:
				if((p.getX()+(V_WALK/FPS)) <= (START_POSITION + MAX_POSITION))
					setX(p.getX()+(V_WALK/FPS));
				break;
			case false:
			if((p.getX()-(V_WALK/FPS)) >= (START_POSITION + MAX_POSITION))
					setX(p.getX()-(V_WALK/FPS));
				break;
		}
		if(frameCount == (int32_t)(FPS+1))
			IamDoing=FINISHING_WALKING;
		if (p.getX()> (START_POSITION + MAX_POSITION))
		{
			p.setX(START_POSITION + MAX_POSITION);
		}
		else if (p.getX()<START_POSITION)
		{
			p.setX(START_POSITION);
		}
		frameCount++;
	}
	return;


}


wormState Worm::whatAmIDoing()
{
	return IamDoing;
}

double Worm::getX()
{
	return p.getX();
}

double Worm::getY()
{
	return p.getY();
}

uint32_t worm::getCurrentFrame()
{
	return frameCount;
}


bool Worm::_lookingRight()
{
	return lookignRight;
}
