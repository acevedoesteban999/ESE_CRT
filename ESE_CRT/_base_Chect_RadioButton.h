#pragma once
#include "_forms.h"
#include "_label.h"

class _base_Chect_RadioButton:public _forms
{
protected:
	_label label;
	GLfloat R,G,B;
	bool Chect;
public:	
	_base_Chect_RadioButton(char*name,char*Escritura,CRD coord,int*TotalWigth,int*TotalHeight,bool Chect=false):_forms(name,coord,15,15,TotalWigth,TotalHeight),label("LabelBase",Escritura,coord.AddX(20),1,0,0,0,TotalWigth,TotalHeight)
	{
		this->Chect=Chect;
		this->G=1;
	}
	~_base_Chect_RadioButton(){}
	void New_CRD(CRD crd)
	{
		_forms::New_CRD(crd);
		label.New_CRD(CRD(crd.x+20,crd.y,crd.z));
	}
	bool Pulsado(int x,int y)
	{
		if(_forms::Pulsado(x,y,this))
		{
			if(Chect)
				Chect=false;
			else
				Chect=true;
			return true;
		}
		return false;
	}
	//SET//
	void Set_Active(bool Active)
	{
		_forms::Set_Active(Active);
		label.Set_Active(Active);
	}
	//GET//
	bool Get_Chect(){return Chect;}
	float Get_All_Wigth()
	{
		return label.Get_All_Wigth()+15;
	}
	//PURAS//
	virtual void _draw()=0;
};

class _chectBox:public _base_Chect_RadioButton
{
public:
	_chectBox(char*name,char*Escritura,CRD crd,int*TotalWigth,int*TotalHeight,bool Chect=false):_base_Chect_RadioButton(name,Escritura,crd,TotalWigth,TotalHeight,Chect)
	{
		this->type=_CHECTBOX;
	}
	~_chectBox(){}
	void _draw()
	{
		if(Draw)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef((GLfloat)(-*TotalWigth/2+coord.x),(GLfloat)(*TotalHeight/2-coord.y),(GLfloat)2* *TotalWigth-1); 
       		glColor3f((GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7);
			if(this->Chect)
				glColor3f((GLfloat)0,(GLfloat)0,(GLfloat)0);
			else
				glColor3f((GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7);
			glBegin(GL_LINE_LOOP);
			glVertex3f(1,0,-1);
			glVertex3f(15,0,-1);
			glVertex3f(15,15,-1);
			glVertex3f(1,15,-1);
			glEnd();
			if(this->Chect||PulsadoPasivoBool||!active)
			{
				if(PulsadoPasivoBool&&active)
					glColor3f(0,(GLfloat)0.4,0);
				else 
					glColor3f(this->active?this->R:(GLfloat)0.2,this->active?this->G:(GLfloat)0.2,this->active?this->B:(GLfloat)0.2);
				glBegin(GL_POLYGON);
				glVertex3f(1,0,-1);
				glVertex3f(15,0,-1);
				glVertex3f(15,15,-1);
				glVertex3f(1,15,-1);
				glEnd();
			}
			glPopMatrix();
			label._draw();
		}
	}
};
class _radioButton:public _base_Chect_RadioButton
{
public:
	_radioButton(char*name,char*Escritura,CRD crd,int*TotalWigth,int*TotalHeight,bool Chect=false):_base_Chect_RadioButton(name,Escritura,crd,TotalWigth,TotalHeight,Chect)
	{
		type=_RADIOBUTTON;
	}
	~_radioButton(){}
	void _draw()
	{
		if(Draw)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef((GLfloat)(-*TotalWigth/2+coord.x),(GLfloat)(*TotalHeight/2-coord.y),(GLfloat)2* *TotalWigth-1); 
       		glColor3f((GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7);
			
			if(this->Chect)
				glColor3f((GLfloat)0,(GLfloat)0,(GLfloat)0);
			else
				glColor3f((GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7);
			glBegin(GL_POINTS);
			
			glVertex3f(7.5,0,-1);
			glVertex3f(15,7.5,-1);
			glVertex3f(7.5,15,-1);
			glVertex3f(0,7.5,-1);
			glEnd();
			if(this->Chect||PulsadoPasivoBool||!active)
			{
				if(PulsadoPasivoBool&&active)
					glColor3f(0,(GLfloat)0.4,0);
				else
					glColor3f(this->active?this->R:(GLfloat)0.2,this->active?this->G:(GLfloat)0.2,this->active?this->B:(GLfloat)0.2);
				glBegin(GL_POLYGON);
				glVertex3f(7.5,0,-1);
				glVertex3f(15,7.5,-1);
				glVertex3f(7.5,15,-1);
				glVertex3f(0,7.5,-1);
				glEnd();
			}
			glPopMatrix();
			label._draw();
		}
	}
	void Set_Check(bool Chect){this->Chect=Chect;} 
};
