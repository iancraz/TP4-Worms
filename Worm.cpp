#include "Worm.h"
#include <cmath>
#define START_POSITION	240
#define MAX_POSITION	470				//Es la diferencia entre el inicio y el final en px para que no se pase
#define MAX_Y_POSITION	616
#define V_JUMP_Y	17.0
#define V_JUMP_X 60
#define V_WALK	27.0
#define GRAVITY	0.24
#define M_PI (acos(-1.0))

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

void Worm::startJumping()
{
	IamDoing=JUMPING;
	aux=false;
	frameCount = 0;
}

void Worm::continueAction()
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
	
		//float velocidad_en_el_punto = abs((0.866 *V_JUMP) - (GRAVITY * 3.25*(frameCount+1)));


	
		p.setY(MAX_Y_POSITION - (0.866 *V_JUMP_Y*1.63333*(frameCount + 1)) + (GRAVITY* pow((double) (1.633333*(frameCount + 1)),2)));
		switch(lookingRight)
		{
			case true:
				p.setX(p.getX()+(cos((double)60*M_PI/180)*V_JUMP_X*((double)1/(FPS - frameCount+1))));
				break;
			case false:
				p.setX(p.getX()-(cos((double)60*M_PI/180)*V_JUMP_X*((double)1/(FPS - frameCount+1))));
				break;
		}
		if(p.getY() >MAX_Y_POSITION)
		{
			p.setY(MAX_Y_POSITION);
			aux = true;
		}
		frameCount++;
	}
	else if(IamDoing == WALKING && aux == false)
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