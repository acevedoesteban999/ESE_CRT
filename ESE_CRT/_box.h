#pragma once
#include "_forms.h"
#include "_baseLayouts.h"
class _box:public _baseLayouts 
{
public:
	_box(char*name,CRD crd,int*TotalWigth,int*TotalHeight):_baseLayouts(name,crd,TotalWigth,TotalHeight)
	{
		type=_BOX;
		this->TextBox_Get_Escribiendo();
	}
	~_box()
	{
	}
	void New_CRD(CRD crd)
	{
		_forms::New_CRD(crd);
		float SumHeight=0;
		for(unsigned i=0;i<cont;i++)
		{
			SumHeight+=forms[i]->Get_All_Height();
			forms[i]->New_CRD(CRD(crd.x,crd.y+(SumHeight)+(i?10:0),crd.z));
			SumHeight+=10;
		}
	}
	///////////ADD///////////
	void Add_Element(_forms*form)
	{
		double coordY=0; 
		if(cont)
		{
			coordY+=forms[cont-1]->coord.y+10;
			if(form->type!=_RADIOBUTTONGROUP)
				coordY+=form->Get_All_Height();
			if(forms[cont-1]->type==_RADIOBUTTONGROUP)
				coordY+=forms[cont-1]->Get_All_Height();
		}
		else
			coordY+=coord.y+form->Get_All_Height();
	
		if(form->Get_All_Wigth()>this->Wigth)
			New_Wigth(form->Get_All_Wigth());

		form->New_CRD(CRD(coord.x,coordY,coord.z));
		Height+=form->Get_All_Height()+10;
		
		_baseArrayForms::Add_Element(form);
	
	}
	/////PURAS////
	bool Pulsado(int x,int y)
	{
		if(TextBoxEscribiendo!=-1)
			TextBoxEscribiendo=-1;
		if(_forms::Pulsado(x,y,this,true))
		{
			for(unsigned i=0;i<cont;i++)
				if(forms[i]->Pulsado(x,y))
					if(forms[i]->type==_TEXTBOX)
						TextBoxEscribiendo=i;
			return true;
		}
		return false;
	}
	void _draw()
	{
		if(Draw)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef((GLfloat)(-*TotalWigth/2+coord.x),(GLfloat)(*TotalHeight/2-coord.y),(GLfloat)2* *TotalWigth-1); 
			glColor3f(1,1,1);
			glBegin(GL_POLYGON);
			glVertex3f(-2.5,7,(GLfloat)-1.2);
			glVertex3f((GLfloat)(Wigth+2.5),7,(GLfloat)-1.2);
			glVertex3f((GLfloat)(Wigth+2.5),(GLfloat)(-Height),(GLfloat)-1.2);
			glVertex3f(-2.5,-Height,(GLfloat)-1.2);
			glEnd();

			glLineWidth(3);
			glColor3f(0,0,0);
			glBegin(GL_LINE_LOOP);
			glVertex3f(-2.5,7,(GLfloat)-1.1);
			glVertex3f((GLfloat)(Wigth+2.5),7,(GLfloat)-1.1);
			glVertex3f((GLfloat)(Wigth+2.5),(GLfloat)-Height,(GLfloat)-1.1);
			glVertex3f(-2.5,(GLfloat)(-Height),(GLfloat)-1.1);
			glEnd();
			glLineWidth(1);	
			
			float ContHeigth=0;
			glColor3f(0,0,0);
			glBegin(GL_LINES);
			for(unsigned i=0;(int)i<int(cont-1);i++)
			{
				if(forms[i]->type==_RADIOBUTTONGROUP)
					ContHeigth-=20;
				glVertex3f(2,(GLfloat)(-forms[i]->Height-5-ContHeigth),(GLfloat)-1.1);
				glVertex3f((GLfloat)(Wigth-2),(GLfloat)(-forms[i]->Height-5-ContHeigth),(GLfloat)-1.1);
				ContHeigth+=forms[i]->Height+10;
				
				/*glVertex3f(0,(GLfloat)(-ContHeigth+2.5),(GLfloat)-1.1);
				glVertex3f(Wigth,(GLfloat)(-ContHeigth+2.5),(GLfloat)-1.1);
				ContHeigth+=forms[i]->Get_All_Height()+10;
				glVertex3f(Wigth,(GLfloat)(-ContHeigth+2.5),(GLfloat)-1.1);
				glVertex3f(-2,(GLfloat)(-ContHeigth+2.5),(GLfloat)-1.1);*/
				
			}
			glEnd();
			
			glPopMatrix();
			for(unsigned i=0;i<cont;i++)
				forms[i]->_draw();
		}
	}
};

class _boxInterfazPrincipal:public _box
{
private:
	unsigned _interfaz;
public:
	_boxInterfazPrincipal(char*name,CRD crd,int*TotalWigth,int*TotalHeight):_box(name,crd,TotalWigth,TotalHeight)
	{
		_interfaz=0;
		Add_ButtonLabel("0btnL","btn1");
	}
	~_boxInterfazPrincipal()
	{
	}
	bool Pulsado(int x,int y)
	{
		if(TextBoxEscribiendo!=-1)
			TextBoxEscribiendo=-1;
		if(_forms::Pulsado(x,y,this,true))
		{
			for(unsigned i=0;i<cont;i++)
				if(forms[i]->Pulsado(x,y))
				{
					if(forms[i]->type==_TEXTBOX)
						TextBoxEscribiendo=i;
				}
			return true;
		}
		return false;
	}
	void _draw()
	{
		_box::_draw();
	}
};


class _boxConnection:public _box
{
private:
	unsigned _interfaz;
	unsigned*Unsigned;
	char*Char;
	bool(*IniciarConnection)(char*,unsigned);
	bool(*DetenerConnection)(void);
public:
	_boxConnection(char*name,CRD crd,char*Char,unsigned*Unsigned,int*TotalWigth,int*TotalHeight,bool(*Function1)(char*,unsigned),bool(*Function2)(void)):_box(name,crd,TotalWigth,TotalHeight)
	{
		this->IniciarConnection=Function1;
		this->DetenerConnection=Function2;
		this->Char=Char;
		this->Unsigned=Unsigned;
		Interfaz0();
		this->Draw=false;

	}
	~_boxConnection()
	{
	}
	//INTERFAZ//
	void Interfaz0()
	{
		this->Clear();	
		_interfaz=0;
		Add_LabelCenter("0label","Conectar:");
		Add_TextBox("0textBoxChar",Char,_DEFAULT);
		Add_TextBox("0textBoxUnsigned",(char*)to_string(*Unsigned).c_str(),_INTCONTENT);
		Add_ButtonsAcceptCancel("0btnAC");
		Set_Draw(false);
	}
	void Interfaz1()
	{
		this->Clear();	
		_interfaz=1;
		Add_LabelCenter("1label","Desconectar?");
		Add_ButtonsAcceptCancel("1btnAC");
		Set_Draw(false);
	}

	//PURAS//
	bool Pulsado(int x,int y)
	{
		if(TextBoxEscribiendo!=-1)
			TextBoxEscribiendo=-1;
		if(_forms::Pulsado(x,y,this,true))
		{
			for(unsigned i=0;i<cont;i++)
			{
				if(forms[i]->Pulsado(x,y))
				{
					switch (forms[i]->type)//TYPE
					{
					case _TEXTBOX:
						TextBoxEscribiendo=i;
						break;
					case _BUTTONSACCEPTCANCEL:
						if(forms[i]->Get_BtnPulsado()==_BUTTONACCEPT)
						{
							Pulsar_Accept();			
						}
						else
						{
							Pulsar_Cancel();
						}
						break;
					}
				}
			}
			return true;
		}
		return false;
	}
	void Pulsar_Accept()
	{
		switch (_interfaz)
		{
		case 0://Conectar
			if(Conectar())
				Interfaz1();
			break;
		case 1://Desconectar
			if(Desconectar())
				Interfaz0();
			break;
		}
	}
	void Pulsar_Cancel()
	{
		switch (_interfaz)
		{
		case 0://Conectar
		case 1://Desconectar
			Draw=false;
			break;
		}
	}
	bool Conectar()
	{
		char*_Char=Get_Text("0textBoxChar");
		char*_Unsigned=Get_Text("0textBoxUnsigned");
		return IniciarConnection(_Char,(unsigned)atol(_Unsigned));
	}
	bool Desconectar()
	{
		return DetenerConnection();
	}
	void _draw()
	{
		_box::_draw();
	}
};
