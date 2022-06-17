#pragma once
#include "Forms.h"
class Button:public Forms
{
private:
	GLfloat R,G,B;
public:
	Button(){};
	Button(char*name,Type bt,CRD crd,GLfloat R,GLfloat G,GLfloat B,float wigth,float height,float TotalWigth,float TotalHeight):Forms(name,crd,wigth,height,TotalWigth,TotalHeight){
    this->R=R;
	this->G=G;
	this->B=B;
	this->t=bt;
	this->t=bt;
	}
	~Button(){};
	void Draw(){
		
			if(!this->NoDraw)
			{
			glPushMatrix();
					  glLoadIdentity();
					  glTranslatef((GLfloat)(-TotalWigth/2+coord.x),(GLfloat)(TotalHeight/2-coord.y),(GLfloat)2*this->TotalWigth-1+TotalProfundidad); 
					  glColor3f(this->active?this->R:(GLfloat)this->R/2,this->active?this->G:(GLfloat)this->G/2,this->active?this->B:(GLfloat)this->B/2);
					  glBegin(GL_POLYGON);
					  glVertex3f(0,0,-1);
					  glVertex3f((GLfloat)Wigth,0,-1);
					  glVertex3f((GLfloat)Wigth,(GLfloat)-Height,-1);
					  glVertex3f(0,(GLfloat)-Height,-1);
					  glEnd();
					  glColor3f(0,0,0);
					  glBegin(GL_LINE_LOOP);
					  glVertex3f(0,0,(GLfloat)-0.9);
					  glVertex3f((GLfloat)Wigth,0,(GLfloat)-0.9);
					  glVertex3f((GLfloat)Wigth,(GLfloat)-Height,(GLfloat)-0.9);
					  glVertex3f(0,(GLfloat)-Height,(GLfloat)-0.9);
					  glEnd();
					  if(this->t==Type::BUTTONEXIT)
					  {
						  glTranslatef((GLfloat)Wigth/2,(GLfloat)-Height/2,(GLfloat)-0.9);
						  glColor3f(1,1,1);
						  glBegin(GL_LINES);
						  glVertex3f(0,6,0);
						  glVertex3f(0,0,0);
						  glEnd();
						  glBegin(GL_LINE_STRIP);
						  glVertex3f(2,3,0);
						  glVertex3f(3,2,0);
						  glVertex3f(4,1,0);

						  glVertex3f(5,0,0);

						  glVertex3f(4,-1,0);
						  glVertex3f(3,-2,0);
						  glVertex3f(2,-3,0);
						  glVertex3f(1,-4,0);

						  glVertex3f(0,-5,0);

						  glVertex3f(-1,-4,0);
						  glVertex3f(-2,-3,0);
						  glVertex3f(-3,-2,0);
						  glVertex3f(-4,-1,0);

						  glVertex3f(-5,0,0);

						  glVertex3f(-4,1,0);
						  glVertex3f(-3,2,0);
						  glVertex3f(-2,3,0);
						  glVertex3f(-1,4,0);
						  glEnd();	  
					  }
					  glPopMatrix();
			}
		
	};
	void SetColor(GLfloat R,GLfloat G,GLfloat B)
	{
		
		this->R=R;
		this->B=B;
		this->G=G;
		
	};
		unsigned Click(){return t;};


};