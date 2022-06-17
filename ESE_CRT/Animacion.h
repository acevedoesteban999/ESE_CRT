#pragma once
#include "Forms.h"
#include <math.h>
class Animacion:public Forms
{
private:
	float x,y,speed;
	bool movY,subirBajar;
	GLfloat R,B,G;
public:
	Animacion(char*name,CRD coord,float wigth,float TotalWigth,float TotalHeight,float x=0,float R=1,float G=1,float B=1,float speed=1):Forms(name,coord,wigth,wigth,TotalWigth,TotalHeight)
	{

		if(wigth<30)
			this->Wigth=30;
		else
			this->Wigth=wigth;
		this->x=x;
		y=0;
		this->t=Type::ANIMACION;
		movY=subirBajar=false;
		this->R=(GLfloat)R;
		this->G=(GLfloat)G;
		this->B=(GLfloat)B;
		this->speed=speed;
	}
	~Animacion(){};
	void Draw()
	{
		if(active&&!NoDraw)
		{
			if(!movY&&(x<this->Wigth/2&&x>=-this->Wigth/2))
			{
				x+=(float)(0.7*speed);
				if(x>this->Wigth)
					x=this->Wigth;
			}
			else if(x>=this->Wigth/2&&!movY)
			{
				movY=true;
				subirBajar=!subirBajar;
			}
			else if(movY)
			{
				if(x>-this->Wigth/2)
				{
					x-=(float)(0.7*speed);
					if(subirBajar)
						y=PuntoCincunferencia(x);
					else
						y=-PuntoCincunferencia(x);
				}
				else
				{
					x=-Wigth/2;
					movY=false;
					y=0;
				}
			}
				glPushMatrix();
						glLoadIdentity();
						glTranslatef((GLfloat)(-TotalWigth/2+coord.x),(GLfloat)(TotalHeight/2-coord.y),(GLfloat)2*this->TotalWigth-1+TotalProfundidad); 
						glColor3f(this->R,this->G,this->B);
						glBegin(GL_POLYGON);
						glVertex3f(x,y,-1);
						glVertex3f((GLfloat)x+5,y,-1);
						glVertex3f((GLfloat)x+5,y-5,-1);
						glVertex3f(x,(GLfloat)y-5,-1);
						glEnd();
			glPopMatrix();
	}
}
	unsigned Click()
	{
	return 0;
	}
	float PuntoCincunferencia(float x)
	{
		return (float)(sqrt((this->Wigth/2)*(this->Wigth/2)-x*x));
	}
};

