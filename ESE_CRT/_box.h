#pragma once
#include "_forms.h"
#include "_baseContainer.h"
class _box:public _baseContainer 
{
protected:
	unsigned _interfaz;
public:
	_box(char*name,CRD crd,int*TotalWigth,int*TotalHeight):_baseContainer(name,crd,TotalWigth,TotalHeight)
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
	
		float ff=form->Get_All_Wigth();
		if(ff>this->Wigth)
			Actualizar_ParentWigth(ff);
		
		form->New_CRD(CRD(coord.x,coordY,coord.z));

		if(form->type==_TEXTBOXCENTER||form->type==_LABELCENTER||form->type==_BUTTONLABELCENTER)
			form->Actualizar_ParentWigth();
		
		Height+=form->Get_All_Height()+10;
		
		_baseArrayForms::Add_Element(form);
	
	}
	////
	virtual bool PulsadoPasivo(int x,int y)
	{
		for(unsigned i=0;i<cont;i++)
			if(forms[i]->PulsadoPasivo(x,y))
				return true;
		return false;
	}
	/////PURAS////
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
					int ii;
					switch (forms[i]->type)//TYPE
					{
					case _TEXTBOX:
					case _TEXTBOXCENTER:
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
					case _BUTTONLABEL:
					case _BUTTONLABELCENTER:
						ii=Get_Element_By_Name(forms[i]->name);
						if(ii==-1)
							break;
						 Pulsar_Btn(ii);
						break;
					case _BUTTONATRAS:
						Interfaz_Atras();
						break;
					}
				}
			}
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
			glVertex3f(-3.5,7,(GLfloat)-1.2);
			glVertex3f((GLfloat)(Wigth+3.5),7,(GLfloat)-1.2);
			glVertex3f((GLfloat)(Wigth+3.5),(GLfloat)(-Height),(GLfloat)-1.2);
			glVertex3f(-3.5,-Height,(GLfloat)-1.2);
			glEnd();

			glLineWidth(3);
			glColor3f(0,0,0);
			glBegin(GL_LINE_LOOP);
			glVertex3f(-3.5,7,(GLfloat)-1.1);
			glVertex3f((GLfloat)(Wigth+3.5),7,(GLfloat)-1.1);
			glVertex3f((GLfloat)(Wigth+3.5),(GLfloat)-Height,(GLfloat)-1.1);
			glVertex3f(-3.5,(GLfloat)(-Height),(GLfloat)-1.1);
			glEnd();
			glLineWidth(1);	
			
			float ContHeigth=0;
			glColor3f(0,0,0);
			glBegin(GL_LINES);
			for(unsigned i=0;(int)i<int(cont-1);i++)
			{
				glVertex3f(2,(GLfloat)(-forms[i]->Height-5-ContHeigth),(GLfloat)-1.1);
				glVertex3f((GLfloat)(Wigth-2),(GLfloat)(-forms[i]->Height-5-ContHeigth),(GLfloat)-1.1);
				ContHeigth+=forms[i]->Height+10;		
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
public:
	_boxInterfazPrincipal(char*name,CRD crd,int*TotalWigth,int*TotalHeight):_box(name,crd,TotalWigth,TotalHeight)
	{
		Interfaz0();
	}
	~_boxInterfazPrincipal()
	{
	}
	//INTERFAZ//
	/*
	Interfaces:
	0 -> Bocetos & Exportar
	1 -> AddBoceto & BocetosActivos
	2 -> Interfaz de dibujo 
	*/
	void Interfaz_Atras()
	{
		Set_Interfaz(--_interfaz);
	};
	void Set_Interfaz(unsigned interfaZ)
	{
		switch (interfaZ)
		{
		case 0:
			Interfaz0();
			break;
		case 1:
			Interfaz1();
			break;
		case 2:
			Interfaz2();
			break;
		}
	}
	void Interfaz0()
	{
		this->Clear();	
		_interfaz=0;
		Add_Label("0L","Menu Principal",2,0.3,0.3,0.3);
		Add_ButtonLabelCenter("0btn1","Bocetos");
		Add_ButtonLabelCenter("0btn2","Exportar");
	}
	void Interfaz1()
	{
		this->Clear();	
		_interfaz=1;
		Add_Label("1label","Menu de Bocetos",2,0.3,0.3,0.3);
		Add_ButtonLabel("1btnLabelAddBoceto2D","Agregar un Boceto");
		Add_Label("1LabelBocetos","Bocetos Activos:");
		Add_ButtonAtras("1btnAtr");
	}
	void Interfaz2()
	{
		this->Clear();	
		_interfaz=2;
		Add_Label("2L1","Menu de Dubujo ",2,0.3,0.3,0.3);
		Add_Label("2L2","Boceto: ",2,0.3,0.3,0.3);
		Add_RadioButtonGroup("2RBG");
		Add_RadioButton_To_RadioButtonGroup("2RBG","2RB1","Puntos");
		Add_RadioButton_To_RadioButtonGroup("2RBG","2RB2","Lineas");
		Add_RadioButton_To_RadioButtonGroup("2RBG","2RB2","BSpline");
		Add_ChectBox("2CH","Mostrar Plano",true);
		Add_ButtonAtras("1btnAtr");
	}

	void Pulsarinterfaz0(unsigned ElementPulsadoPositionInArray)
	{
		switch (ElementPulsadoPositionInArray)
		{
		case 0://Label Menu Princial
			break;
		case 1://Bocetos
			Interfaz1();
			break;
		case 2://Exportar
			break;
		}
	}
	void Pulsarinterfaz1(unsigned ElementPulsadoPositionInArray)
	{
		switch (ElementPulsadoPositionInArray)
		{
		case 0://Label Menu de Bocetos
			break;
		case 1://Agrgar Boceto
			Interfaz2();//MOMENTNEO
			break;
		case 2://Label Bocetos Activos
			break;
		default:
			break;
		}
	}
	//TRABAJO_INTERNO//
	void Pulsar_Btn(unsigned ElementPulsadoPositionInArray)
	{
		switch (_interfaz)
		{
		case 0:
			Pulsarinterfaz0(ElementPulsadoPositionInArray);
			break;
		case 1:
			Pulsarinterfaz1(ElementPulsadoPositionInArray);
			break;
		default:
			break;
		}
	}
	void Pulsar_Accept()
	{
		
	}	
	void Pulsar_Cancel()
	{
		
	}
	//PURAS//
	bool Pulsado(int x,int y)
	{
		return _box::Pulsado(x,y);
	}
	void _draw()
	{
		_box::_draw();
	}
};

class _boxConnection:public _box
{
private:
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
		Add_LabelCenter("0label","Conectar a:");
		Add_TextBoxCenter("0textBoxChar",Char,_DEFAULT);
		Add_TextBoxCenter("0textBoxUnsigned",(char*)to_string(*Unsigned).c_str(),_INTCONTENT);
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
	//TRABAJO_INTERNO//
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
	
	//PURAS//
	bool Pulsado(int x,int y)
	{
		return _box::Pulsado(x,y);
	}
	void _draw()
	{
		_box::_draw();
	}
};
