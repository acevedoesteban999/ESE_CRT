#pragma once
#include <ctime>
#include "TimeDuration.h"
#include <iostream>
enum position{
	CENTER_TOP,CENTER_BUTTOM
	};
class MeSSenger
{
	
private:
	char*text;
	unsigned BigLV;
	GLfloat R,G,B,x,y,z;
	TimeDuration t;
	//mutex m;
public:
	 bool Finish;
	 MeSSenger(char*text,position Position,GLfloat wigth,GLfloat height,float Time=3,GLfloat R=1,GLfloat G=1,GLfloat B=1,unsigned BigLV=0,GLfloat x=0,GLfloat y=0,GLfloat z=0)
	 {
	 	this->text=new char[strlen(text)+1];
	 	this->text[strlen(text)]=0;
	 	for(unsigned i=0;i<strlen(text);i++)
	 		this->text[i]=text[i];
	 	if(Position==position::CENTER_TOP)
	 	{
	 		this->x=(GLfloat)-int(strlen(text)*4.5);
	 		this->y=(GLfloat)height/2-20;
	 		this->z=(GLfloat)2*wigth-1;
	 	}
		this->t.InitDecrementa(&t,Time);
		this->R=R;
		this->G=G;
		this->B=B;
		this->x+=x;
		this->y+=y;
		this->z+=z;
		Finish=false;

	 }
	~MeSSenger(void)
	{
		delete[]text;
	};
	static void Drawing_and_Decremt(MeSSenger*m,unsigned pos)
	{
		
		if(!TimeDuration::Decrementa(&m->t))
		{
			MeSSenger::textMSS(m->text,m->x,m->y,m->z,m->R,m->G,m->B,m->BigLV==1?1:0,m->BigLV>1?1:0,pos);
		}
		else
			m->Finish=true;		
	}
	static void textMSS(char*c,GLfloat x,GLfloat y,GLfloat z,GLfloat R,GLfloat G,GLfloat B,bool big,bool moreBig,unsigned pos)
	{
	//dibujo el char c en la posicion x,y,z con color RGB
	
		glColor3f(R,G,B);
		glRasterPos3f(x,y-(moreBig?24*pos:big?18*pos:10*pos),z);					  
		for(unsigned int i=0;i<strlen(c);i++)
		{
			if(moreBig)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
			else if(big)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c[i]);
			else 
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c[i]);	
		}
	}
	 /*static void NewMeSSenger(MeSSenger*m,char*text,position Position,GLfloat wigth,GLfloat height,float Time=3,GLfloat R=1,GLfloat G=1,GLfloat B=1,unsigned BigLV=0,GLfloat x=0,GLfloat y=0,GLfloat z=0)
	 {
	 	m->text=new char[strlen(text)+1];
	 	m->text[strlen(text)]=0;
	 	for(unsigned i=0;i<strlen(text);i++)
	 		m->text[i]=text[i];
	 	if(Position==position::CENTER_TOP)
	 	{
	 		m->x=(GLfloat)-int(strlen(text)*4.5);
	 		m->y=(GLfloat)height/2-20;
	 		m->z=(GLfloat)2*wigth-1;
	 	}*/

	// 	else if(Position==position::CENTER_BUTTOM)
	// 		{
	// 			m->x=(GLfloat)-int(strlen(meSSenger)*4.5);
	// 			m->y=-(GLfloat)height/2-20;
	// 			m->z=(GLfloat)2*wigth-1;
	// 		}
	// 	else
	// 		{
	// 		m->x=x;
	// 		m->y=y;
	// 		m->z=z;
	// 		}
	// 	m->t=new TimeDuration(Time);
	// 	m->R=R;
	// 	m->G=G;
	// 	m->B=B;
	// 	m->BigLV=BigLV;
	// 	m->Drawing=true;
	// 	m->m.unlock();
	// };
};

/*MeSSenger(char*meSSenger,position Position,GLfloat wigth,GLfloat height,float Time=3,GLfloat R=1,GLfloat G=1,GLfloat B=1,unsigned BigLV=0,GLfloat x=0,GLfloat y=0,GLfloat z=0)
	{
	this->meSSenger=new char[strlen(meSSenger)+1];
	this->meSSenger[strlen(meSSenger)]=0;
		for(unsigned i=0;i<strlen(meSSenger);i++)
			this->meSSenger[i]=meSSenger[i];
		if(Position==position::CENTER_TOP)
	{
		this->x=(GLfloat)-int(strlen(meSSenger)*4.5);
		this->y=(GLfloat)height/2-20;
		this->z=(GLfloat)2*wigth-1;
	}
	
		else if(Position==position::CENTER_BUTTOM)
	{
		this->x=(GLfloat)-int(strlen(meSSenger)*4.5);
		this->y=-(GLfloat)height/2-20;
		this->z=(GLfloat)2*wigth-1;
	}
	else
	{
	this->x=x;
	this->y=y;
	this->z=z;
	}
	this->t=new TimeDuration(Time);
		this->R=R;
		this->G=G;
		this->B=B;
		this->BigLV=BigLV;
		Drawing=true;
	};*/