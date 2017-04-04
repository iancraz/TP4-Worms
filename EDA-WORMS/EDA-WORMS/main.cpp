//======================================================================================================================
//			ALGORITMOS Y ESTRUCTURAS DE DATOS
//				ITBA 2017
//
//	TP4 - WORMS
//
//
//	Grupo 5:
//		SANTIAGO ANDRES BUALO
//		IAN CRUZ DIAZ
//		IÑAKI GONZALEZ BIGLIARDI
//		
//	Git:
//	https://github.com/igonzalezb/EDA-WORMS.git
//
//
//======================================================================================================================


#include <iostream>
#include <cstdint>
#include "Position.h"
#include "Graphics.h"


int main(int argc, char* argv[])
{
	srand(time(NULL));
	Graphics g;
	g.GraphicsMain();
	g.allegro_desinstalar();
	return 0;
}