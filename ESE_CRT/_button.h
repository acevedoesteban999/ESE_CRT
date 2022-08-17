#pragma once
#include "_forms.h"
#include "_label.h"
class _baseButton:public _forms
{
	friend class _buttonsX2;
protected:
	//_label label;
	GLfloat R,G,B;
public:
	_baseButton(char*name,CRD coord,int*TotalWigth,int*TotalHeight):_forms(name,coord,0,15,TotalWigth,TotalHeight)
	{
		type=_BASEBUTTON;	
		R=G=B=0;
	}
	~_baseButton(){}
	void Set_Color(GLfloat R,GLfloat G,GLfloat B)
	{
		this->R=R;
		this->G=G;
		this->B=B;
	}
	void _draw()=0;
};


class _button:public _baseButton
{
public:
	_button(char*name,CRD coord,int*TotalWigth,int*TotalHeight):_baseButton(name,coord,TotalWigth,TotalHeight)
	{
		this->Wigth=this->Height;
		this->type=_BUTTON;
	}
	~_button()
	{
	}
	void _buttonDraw()
	{
			if(Draw)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef((GLfloat)(-*TotalWigth/2+coord.x),(GLfloat)(*TotalHeight/2-coord.y),(GLfloat)2* *TotalWigth-1); 
			glLineWidth(2);
			
			glBegin(GL_LINE_LOOP);
			glVertex3f(-2,-2,(GLfloat)-1);
			glVertex3f(-2,Height+2,(GLfloat)-1);
			glVertex3f(Wigth+2,Height+2,(GLfloat)-1);
			glVertex3f(Wigth+2,-2,(GLfloat)-1);
			glEnd();
		}
	}
	void _draw()=0;
};
class _buttonAccept:public _button
{
public:
	_buttonAccept(char*name,CRD coord,int*TotalWigth,int*TotalHeight):_button(name,coord,TotalWigth,TotalHeight)
	{
		this->type=_BUTTONACCEPT;
	}
	~_buttonAccept()
	{}
	void _draw()
	{
		_buttonDraw();
		glColor3f(0,1,0);
		glBegin(GL_POLYGON);
		glVertex3f(-2,-2,(GLfloat)-1);
		glVertex3f(-2,Height+2,(GLfloat)-1);
		glVertex3f(Wigth+2,Height+2,(GLfloat)-1);
		glVertex3f(Wigth+2,-2,(GLfloat)-1);
		glEnd();
		
		glColor3f(0,0,0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(0,Height/2,(GLfloat)-0.9);
		glVertex3f(Wigth/3,0,(GLfloat)-0.9);
		glVertex3f(Wigth*2/3,Height/2,(GLfloat)-0.9);
		glVertex3f(Wigth,Height,(GLfloat)-0.9);
		glEnd();
		glPopMatrix();
	}
};
class _buttonCancel:public _button
{
public:
	_buttonCancel(char*name,CRD coord,int*TotalWigth,int*TotalHeight):_button(name,coord,TotalWigth,TotalHeight)
	{
		this->type=_BUTTONACCEPT;
	}
	~_buttonCancel()
	{}
	void _draw()
	{
		_buttonDraw();
		glColor3f(1,0,0);
		glBegin(GL_POLYGON);
		glVertex3f(-2,-2,(GLfloat)-1);
		glVertex3f(-2,Height+2,(GLfloat)-1);
		glVertex3f(Wigth+2,Height+2,(GLfloat)-1);
		glVertex3f(Wigth+2,-2,(GLfloat)-1);
		glEnd();
	
		glColor3f(0,0,0);
		glBegin(GL_LINES);
		glVertex3f(0,Height,(GLfloat)-0.9);
		glVertex3f(Wigth-1,0,(GLfloat)-0.9);
		glVertex3f(0,0,(GLfloat)-0.9);
		glVertex3f(Wigth-1,Height,(GLfloat)-0.9);
		glEnd();
		glPopMatrix();
	}
};


class _buttonLabel:public _baseButton
{
private:
	_label label;
public:
	_buttonLabel(char*name,char*Escritura,CRD coord,int*TotalWigth,int*TotalHeight):_baseButton(name,coord,TotalWigth,TotalHeight),label("LabelBase",Escritura,coord,1,0,0,0,TotalWigth,TotalHeight)
	{
		//label.Set_Text(Escritura);
		this->Wigth=label.Get_All_Wigth();
		//label.New_CRD(CRD(coord.x,coord.y,coord.z));
		//label.TotalWigth=TotalWigth;
		//label.TotalHeight=TotalHeight;
	}
	~_buttonLabel(){}
	void New_CRD(CRD crd)
	{
		crd=crd.AddX(5);
		_forms::New_CRD(crd);
		label.New_CRD(crd);
	}
	float Get_All_Wigth()
	{
		return label.Get_All_Wigth()+10;
	}
	//PURAS//
	void _draw()
	{
		if(Draw)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef((GLfloat)(-*TotalWigth/2+coord.x),(GLfloat)(*TotalHeight/2-coord.y),(GLfloat)2* *TotalWigth-1); 
			glColor3f(R,G,B);
			glLineWidth(2);

			glBegin(GL_LINE_LOOP);
			glVertex3f(-2.5,-2.5,(GLfloat)-1);
			glVertex3f(-2.5,Height+2.5,(GLfloat)-1);
			glVertex3f(Wigth,Height+2.5,(GLfloat)-1);
			glVertex3f(Wigth,-2.5,(GLfloat)-1);
			glEnd();
			glColor3f(0.7,0.7,0.7);
			glBegin(GL_POLYGON);
			glVertex3f(-2.5,-2.5,(GLfloat)-1);
			glVertex3f(-2.5,Height+2.5,(GLfloat)-1);
			glVertex3f(Wigth,Height+2.5,(GLfloat)-1);
			glVertex3f(Wigth,-2.5,(GLfloat)-1);
			glEnd();
			glPopMatrix();
			label._draw();
		}
	}
};
class _buttonsAcceptCancel:public _forms
{
private:
	float*ParentWigth;
	_buttonAccept btnA;
	_buttonCancel btnC;
	_type BtnPulsado;//true btnA false btnC
public:
	_buttonsAcceptCancel(char*name,CRD coord,int*TotalWigth,int*TotalHeight,float*ParentWigth):_forms(name,coord,0,15,TotalWigth,TotalHeight),btnA("btnAcept",CRD(),TotalWigth,TotalHeight),btnC("btnCancel",CRD(),TotalWigth,TotalHeight)
	{
		this->type=_BUTTONSACCEPTCANCEL;
		this->ParentWigth=ParentWigth;
		this->New_CRD(coord);
	}
	~_buttonsAcceptCancel(){}
	void New_CRD(CRD crd)
	{
		_forms::New_CRD(crd);
		btnA.New_CRD(crd.AddX((double)(*ParentWigth*0.25)));
		btnC.New_CRD(crd.AddX((double)(*ParentWigth*0.75)));
	}
	bool Pulsado(int x,int y)
	{
		
		if(btnA.Pulsado(x,y))
		{
			BtnPulsado=_BUTTONACCEPT;
			return true;
		}
		if(btnC.Pulsado(x,y))
		{
			BtnPulsado=_BUTTONCANCEl;
			return true;
		}
		BtnPulsado=_NULL;
		return false;
		
	}
	float Get_All_Wigth()
	{
		return (float)btnA.Get_All_Wigth()+btnC.Get_All_Wigth();
	}
	void _draw()
	{
		btnA._draw();
		btnC._draw();
	}
	_type Get_BtnPulsado()
	{
		return BtnPulsado;
	}
};