#include "Worm.h"
#include <cmath>
#define START_POSITION	230
#define MAX_POSITION	480				//Es la diferencia entre el inicio y el final en px para que no se pase
#define MAX_Y_POSITION	616
#define V_JUMP		4.5
#define CORRECTION_FACTOR	0.03
#define V_WALK		27.0
#define GRAVITY		0.24
#define M_PI		(acos(-1.0))

Worm::Worm()
{
	p.setX(START_POSITION+randomPosition(MAX_POSITION));
	p.setY(MAX_Y_POSITION);
	lookingRight = (bool)(rand() & 1);
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

void Worm::startJumping()//Funcion que mueve 1 frame el salto
{
	IamDoing=JUMPING;
	aux=false;
	frameCount = 0;
}

void Worm::continueAction()	//Funcion que detecta si esta saltando o caminando y continua con ese movimiento
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

	if(IamDoing == JUMPING && aux == false)		//Si esta saltando y no choco con el final
	{
	
		p.setY(MAX_Y_POSITION - V_JUMP*sin((double)M_PI / 3)*(frameCount)+(GRAVITY/2)*pow(frameCount, 2));
		//Ecuacion de MRU para tiro oblicuo

		switch(lookingRight)
		{
			case true:
				if((p.getX() + ((frameCount)*V_JUMP*cos((double)M_PI / 3))*CORRECTION_FACTOR) < (START_POSITION+MAX_POSITION))
					p.setX(p.getX() + ((frameCount)*V_JUMP*cos((double)M_PI/3))*CORRECTION_FACTOR);
				break;
			case false:
				if ((p.getX() - ((frameCount)*V_JUMP*cos((double)M_PI / 3))*CORRECTION_FACTOR) > (START_POSITION))
					p.setX(p.getX() - ((frameCount)*V_JUMP*cos((double)M_PI / 3))*CORRECTION_FACTOR);
				break;
		}
		if(p.getY() >MAX_Y_POSITION)
		{
			p.setY(MAX_Y_POSITION);
			aux = true;
		}
		frameCount++;
	}
	else if(IamDoing == WALKING && aux == false) //Si esta caminando pero no choco con el final
	{
		switch(lookingRight)
		{
		case true: {
					if ((p.getX() + (V_WALK / FPS)) <= (START_POSITION + MAX_POSITION))
						p.setX(p.getX() + (V_WALK / FPS));
					break;
					}
		case false: {
			if ((p.getX() - (V_WALK / FPS)) >= (START_POSITION))
				p.setX(p.getX() - (V_WALK / FPS));
			break;
		}
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
	else if (IamDoing== FINISHING_WALKING)
	{
		IamDoing = STILL;
		frameCount++;
	}
	else if (IamDoing == FINISHING_JUMPING)
	{
		IamDoing = STILL;
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

uint32_t Worm::getCurrentFrame()
{
	return frameCount;
}


bool Worm::_lookingRight()
{
	return lookingRight;
}

void Worm::lookRight(bool temp)
{
	lookingRight=temp;
	return;
}