#include "ESE_CRT.h"
#include <iostream>
#include <cmath>
void main(int argv,char*argc[])
{
	glutInit(&argv,argc);//inicio el GLUT
	ESE_CRT _ESE_CRT;
	glutMainLoop();//le digo q se quede esperando eventos 
	
}

