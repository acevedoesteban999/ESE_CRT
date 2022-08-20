#pragma once
#include "_forms.h"
#include "_label.h"
class _baseButton:public _forms
{
public:
	
	_baseButton(char*name,CRD coord,int*TotalWigth,int*TotalHeight):_forms(name,coord,0,15,TotalWigth,TotalHeight)
	{
		type=_BASEBUTTON;
	}
	~_baseButton(){}
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
	virtual void New_CRD(CRD crd)
	{
		_forms::New_CRD(crd.AddX(5));
	}
	void _buttonSimpleDraw()
	{
		if(Draw)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef((GLfloat)(-*TotalWigth/2+coord.x),(GLfloat)(*TotalHeight/2-coord.y),(GLfloat)2* *TotalWigth-1); 
			
			if(!active)
			{
				glColor3f((GLfloat)0.3,(GLfloat)0.3,(GLfloat)0.3);
				glBegin(GL_LINES);
				glVertex3f(0,0,(GLfloat)-0.9);
				glVertex3f((GLfloat)Wigth/4,Height-3,(GLfloat)-0.9);
				glVertex3f((GLfloat)Wigth/4,(GLfloat)0,(GLfloat)-0.9);
				glVertex3f((GLfloat)2*Wigth/4,(GLfloat)Height-3,(GLfloat)-0.9);
				glVertex3f((GLfloat)Wigth/2,(GLfloat)0,(GLfloat)-0.9);
				glVertex3f((GLfloat)3*Wigth/4,(GLfloat)Height-3,(GLfloat)-0.9);
				glVertex3f((GLfloat)3*Wigth/4,(GLfloat)0,(GLfloat)-0.9);
				glVertex3f((GLfloat)Wigth,(GLfloat)Height-3,(GLfloat)-0.9);
				glEnd();	
			}
			
			glLineWidth(2);
			glColor3f(0,0,0);
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
		_buttonSimpleDraw();
		if(PulsadoPasivoBool&&active)
			glColor3f(0,(GLfloat)0.5,0);
		else
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
		this->type=_BUTTONCANCEL;
	}
	~_buttonCancel()
	{}
	void _draw()
	{
		_buttonSimpleDraw();
		if(PulsadoPasivoBool&&active)
			glColor3f((GLfloat)0.5,0,0);
		else
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

class _buttonAtras:public _button
{
public:
	_buttonAtras(char*name,CRD coord,int*TotalWigth,int*TotalHeight):_button(name,coord,TotalWigth,TotalHeight)
	{
		this->type=_BUTTONATRAS;
	}
	~_buttonAtras()
	{}
	void _draw()
	{
		_buttonSimpleDraw();
		if(PulsadoPasivoBool&&active)
			glColor3f((GLfloat)0.4,(GLfloat)0.4,0);
		else
			glColor3f((GLfloat)0.8,(GLfloat)0.8,0);
		glBegin(GL_POLYGON);
		glVertex3f(-2,-2,(GLfloat)-1);
		glVertex3f(-2,Height+2,(GLfloat)-1);
		glVertex3f(Wigth+2,Height+2,(GLfloat)-1);
		glVertex3f(Wigth+2,-2,(GLfloat)-1);
		glEnd();
		
		glColor3f(0,0,0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(Wigth,Height/2,(GLfloat)-0.9);
		glVertex3f(Wigth/2,Height/2,(GLfloat)-0.9);
		glVertex3f(Wigth/2,Height,(GLfloat)-0.9);
		glVertex3f(0,Height/2,(GLfloat)-0.9);
		glVertex3f(Wigth/2,0,(GLfloat)-0.9);
		glVertex3f(Wigth/2,Height/2,(GLfloat)-0.9);
		glEnd();
		glPopMatrix();
	}
};

class _buttonLabel:public _baseButton
{
protected:
	_label label;
public:
	_buttonLabel(char*name,char*Escritura,CRD coord,int*TotalWigth,int*TotalHeight):_baseButton(name,coord,TotalWigth,TotalHeight),label("LabelBase",Escritura,coord,1,0,0,0,TotalWigth,TotalHeight)
	{
		this->Wigth=label.Get_All_Wigth();
		this->type=_BUTTONLABEL;
	}
	~_buttonLabel(){}
	void New_CRD(CRD crd)
	{
		crd=crd.AddX(5);
		_forms::New_CRD(crd);
		label.New_CRD(crd);
	}
	//SET//
	void Set_Active(bool Active)
	{
		_forms::Set_Active(Active);
		label.Set_Active(Active);
	}
	//GET//
	float Get_All_Wigth()
	{
		return label.Get_All_Wigth()+5;
	}
	bool PulsadoPasivo(int x,int y)
	{
		if(_forms::Pulsado(x,y))
		{
			PulsadoPasivoBool=true;
			return true;
		}
		else if(PulsadoPasivoBool)
		{
			PulsadoPasivoBool=false;
			return true;
		}
		return false;
		
		
	}
	//PURAS//
	void _draw()
	{
		if(Draw)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef((GLfloat)(-*TotalWigth/2+coord.x),(GLfloat)(*TotalHeight/2-coord.y),(GLfloat)2* *TotalWigth-1); 
			glColor3f(0,0,0);
			glLineWidth(2);

			glBegin(GL_LINE_LOOP);
			glVertex3f((GLfloat)-2.5,(GLfloat)-2.5,(GLfloat)-1);
			glVertex3f((GLfloat)-2.5,(GLfloat)(Height+2.5),(GLfloat)-1);
			glVertex3f((GLfloat)Wigth,(GLfloat)(Height+2.5),(GLfloat)-1);
			glVertex3f((GLfloat)Wigth,(GLfloat)-2.5,(GLfloat)-1);
			glEnd();
			if(PulsadoPasivoBool&&active)
				glColor3f((GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4);
			else
				glColor3f((GLfloat)0.8,(GLfloat)0.8,(GLfloat)0.8);
			glBegin(GL_POLYGON);
			glVertex3f((GLfloat)-2.5,(GLfloat)-2.5,(GLfloat)-1);
			glVertex3f((GLfloat)-2.5,(GLfloat)(Height+2.5),(GLfloat)-1);
			glVertex3f((GLfloat)Wigth,(GLfloat)(Height+2.5),(GLfloat)-1);
			glVertex3f((GLfloat)Wigth,(GLfloat)-2.5,(GLfloat)-1);
			glEnd();
			glPopMatrix();
			label._draw();
		}
	}
};

class _buttonLabelCenter:public _buttonLabel,public _center
{
private:
	//CRD coordReferenciaInicial;
	//float*ParentWigth;
public:
	_buttonLabelCenter(char*name,char*Escritura,CRD coord,float*ParentWigth,int*TotalWigth,int*TotalHeight):_buttonLabel(name,Escritura,coord,TotalWigth,TotalHeight),_center(ParentWigth,this)
	{
		this->Wigth=label.Get_All_Wigth();
		this->type=_BUTTONLABELCENTER;
	}
	~_buttonLabelCenter(){}
	void New_CRD(CRD crd)
	{
		crd=crd.AddX(5);
		_center::New_CRD(crd);
		label.New_CRD(coord);
	}
	void Actualizar_ParentWigth()
	{
		_center::Actualizar_ParentWigth();
		label.New_CRD(coord);
	}
	/*void New_CRD(CRD crd)
	{
		coordReferenciaInicial=crd;
		_buttonLabel::New_CRD(crd);
	}
	void Actualizar_ParentWigth()
	{
		coord=coordReferenciaInicial.AddX((*ParentWigth)/2 - Get_All_Wigth()/2);
		_buttonLabel::New_CRD(coord);
	}*/
	//PURAS//
	void _draw()
	{
		_buttonLabel::_draw();
	}
};

class _buttonsDouble:public _forms
{
protected:
	float*ParentWigth;
	_button*btn1;
	_button*btn2;
	_type BtnPulsado;//true btn1 false btn2
public:
	_buttonsDouble(char*name,CRD coord,int*TotalWigth,int*TotalHeight,float*ParentWigth):_forms(name,coord,0,15,TotalWigth,TotalHeight)
	{
		this->ParentWigth=ParentWigth;
	}
	virtual ~_buttonsDouble()
	{
		delete btn1;
		delete btn2;
	}
	void New_CRD(CRD crd)
	{
		_forms::New_CRD(crd);
		btn1->New_CRD(crd.AddX((double)(*ParentWigth*0.25-btn1->Get_All_Wigth())));
		btn2->New_CRD(crd.AddX((double)(*ParentWigth*0.75-btn2->Get_All_Wigth())));
	}
	bool Pulsado(int x,int y)
	{
		
		if(btn1->Pulsado(x,y))
		{
			BtnPulsado=btn1->type;
			return true;
		}
		if(btn2->Pulsado(x,y))
		{
			BtnPulsado=btn2->type;
			return true;
		}
		BtnPulsado=_NULL;
		return false;
		
	}
	bool PulsadoPasivo(int x,int y)
	{
		bool ToReturnA,ToReturnC;
		ToReturnA=btn1->PulsadoPasivo(x,y);
		ToReturnC=btn2->PulsadoPasivo(x,y);
		return (ToReturnA||ToReturnC);
	}
	float Get_All_Wigth()
	{
		return (float)btn1->Get_All_Wigth()+btn2->Get_All_Wigth();
	}
	void _draw()
	{
		btn1->_draw();
		btn2->_draw();
	}
	_type Get_Type_Last_Pulsado()
	{
		return BtnPulsado;
	}
	virtual void PURE()=0;
};

class _buttonsAcceptCancel:public _buttonsDouble
{
public:
	_buttonsAcceptCancel(char*name,CRD coord,int*TotalWigth,int*TotalHeight,float*ParentWigth):_buttonsDouble(name,coord,TotalWigth,TotalHeight,ParentWigth)
	{
		btn1=new _buttonCancel("btnCancel",CRD(),TotalWigth,TotalHeight);
		btn2=new _buttonAccept("btnAcept",CRD(),TotalWigth,TotalHeight);
		this->type=_BUTTONSACCEPTCANCEL;
		this->New_CRD(coord);
	
	}
	~_buttonsAcceptCancel(){}
	void PURE(){}
};

class _buttonsAcceptAtras:public _buttonsDouble
{
public:
	_buttonsAcceptAtras(char*name,CRD coord,int*TotalWigth,int*TotalHeight,float*ParentWigth):_buttonsDouble(name,coord,TotalWigth,TotalHeight,ParentWigth)
	{
		btn1=new _buttonAtras("btnAtras",CRD(),TotalWigth,TotalHeight);
		btn2=new _buttonAccept("btnAccept",CRD(),TotalWigth,TotalHeight);
		this->type=_BUTTONSACCEPTATRAS;
		this->New_CRD(coord);
	
	}
	~_buttonsAcceptAtras(){}
	void PURE(){}
};


