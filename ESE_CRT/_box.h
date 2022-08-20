#pragma once
#include "_forms.h"
#include "_baseContainer.h"
#include "_manejadorBocetos.h"
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
	~_box(){}
	char*GetCharDelete(char*Char1,char*Char2)
	{
		string s=(string(Char1)+string(Char2));
		char*toReturn=new char[s.length()+1];
		toReturn[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			toReturn[i]=s[i];
		return toReturn; 
	}
	char*GetCharDelete(char*Char,unsigned Unsigned)
	{
		string s=(string(Char)+to_string(Unsigned));
		char*toReturn=new char[s.length()+1];
		toReturn[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			toReturn[i]=s[i];
		return toReturn; 
	}
	char*GetCharDelete(char*Char1,unsigned Unsigned,char*Char2)
	{
		string s=string(Char1)+to_string(Unsigned)+string(Char2);
		char*toReturn=new char[s.length()+1];
		toReturn[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			toReturn[i]=s[i];
		return toReturn; 
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
			if(form->type!=_RADIOBUTTONGROUP||form->type!=_RADIOBUTTONGROUPFREE)
				coordY+=form->Get_All_Height();
			if(forms[cont-1]->type==_RADIOBUTTONGROUP||forms[cont-1]->type==_RADIOBUTTONGROUPFREE)
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
					switch (forms[i]->Get_Type_Last_Pulsado())//TYPE
					{
					case _TEXTBOX:
					case _TEXTBOXCENTER:
						TextBoxEscribiendo=i;
						break;
					case _BUTTONACCEPT:
						Pulsar_Accept();
						break;
					case _BUTTONCANCEL:
						Pulsar_Cancel();
						break;
					case _BUTTONATRAS :
						Pulsar_Atras();
						break;
					case _BUTTONLABEL:
					case _BUTTONLABELCENTER:
					case _RADIOBUTTONGROUP:
					case _RADIOBUTTONGROUPFREE:
					case _CHECTBOX:
						ii=Get_Element_By_Name(forms[i]->name);
						if(ii==-1)
							break;
							Pulsar_Btn(ii);
						break;
					}
				}
			}
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


//class _boxFree:public _box
//{
//private:
//	_type LastPulsadoType;
//public:
//	_boxFree(char*name,CRD coord,int*TotalWigth,int*TotalHeight):_box(name,coord,TotalWigth,TotalHeight)
//	{
//		this->type=_BOXFREE;
//	}
//	~_boxFree(){}
//	//GET//
//	_type Get_Type_Last_Pulsado()
//	{
//		return LastPulsadoType;
//	}
//	//PURAS//
//	void _draw()
//	{
//		for(unsigned i=0;i<cont;i++)
//			forms[i]->_draw();
//	}
//	bool Pulsado(int x,int y)
//	{
//		if(TextBoxEscribiendo!=-1)
//			TextBoxEscribiendo=-1;
//		if(_forms::Pulsado(x,y,this,true))
//		{
//			for(unsigned i=0;i<cont;i++)
//			{
//				if(forms[i]->Pulsado(x,y))
//				{
//					LastPulsadoType=forms[i]->type;
//					return true;
//				}
//			}
//		}
//		return false;
//	}
//};

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

class _boxInterfazPrincipal:public _box
{
private:
	_manejadorBocetos*_MB;
public:
	_boxInterfazPrincipal(char*name,CRD crd,_manejadorBocetos*MB,int*TotalWigth,int*TotalHeight):_box(name,crd,TotalWigth,TotalHeight)
	{
		this->_MB=MB;
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
		case 3:
			Interfaz3();
			break;
		}
	}
	//Menu Principal//
	void Interfaz0()
	{
		this->Clear();	
		_interfaz=0;
		Add_Label("0L","Menu Principal",2,0.3,0.3,0.3);
		Add_ButtonLabelCenter("0btn1","Bocetos");
		Add_ButtonLabelCenter("0btn2","Exportar");
	}
	//Menu de Bocetos//
	void Interfaz1()
	{
		this->Clear();	
		_interfaz=1;
		Add_Label("1L0","Menu de Bocetos",2,0.3,0.3,0.3);
		Add_ButtonLabel("1btn1","Agregar un Boceto");
		Add_ButtonLabel("1btn2","Remover un Boceto");
		if(!_MB->cont)
		{
			forms[cont-1]->Set_Active(false);
		}
		
		char*GetCharDeleteChar;
		GetCharDeleteChar=GetCharDelete("Bocetos Activos:",_MB->cont);
		Add_Label("1L3",GetCharDeleteChar);
		delete[]GetCharDeleteChar;
		
		if(!_MB->cont)
			Add_Label("1L4","Sin Bocetos",1,0.3,0.3,0.3);
		else
			for(unsigned i=0;i<_MB->cont;i++)
			{
				GetCharDeleteChar=GetCharDelete("1btnC",i+5);
				Add_ButtonLabelCenter(GetCharDeleteChar,_MB->bocetos[i]->Get_Name());
				delete[]GetCharDeleteChar;
			}
		GetCharDeleteChar=GetCharDelete("1BtnA",_MB->cont+5);
		Add_ButtonAtras(GetCharDeleteChar);
		delete[]GetCharDeleteChar;
	}
	//Menu de Dubujo//
	void Interfaz2()
	{
		this->Clear();	
		_interfaz=2;
		Add_Label("2L0","Menu de Dubujo",2,0.3,0.3,0.3);
		
		char*GetCharDeleteChar;
		GetCharDeleteChar=GetCharDelete("Boceto:",_MB->Get_BocetoAPintarName());
		Add_Label("2L1",GetCharDeleteChar,2,0.3,0.3,0.3);
		delete[]GetCharDeleteChar;
		
		Add_RadioButtonGroup("2RBG2");
		Add_RadioButton_To_RadioButtonGroup("2RBG2","RB0","Puntos");
		Add_RadioButton_To_RadioButtonGroup("2RBG2","RB1","Lineas");
		Add_RadioButton_To_RadioButtonGroup("2RBG2","RB2","Lineas Continuas");
		Add_RadioButton_To_RadioButtonGroup("2RBG2","RB3","BSpline");
		unsigned drawType=(unsigned)_MB->Get_DrawType();
		forms[cont-1]->Set_Element_Chect(drawType);
		Add_ChectBox("2CH3","Mostrar Plano",true);
		Add_ButtonAtras("2btnA4");
	}
	//Menu de Agregar//
	void Interfaz3()
	{
		this->Clear();	
		_interfaz=3;
		Add_Label("3L0","Menu de Agregar",2,0.3,0.3,0.3);
		Add_ButtonLabelCenter("3TB1","Boceto2D");
		Add_ButtonLabelCenter("3TB2","Boceto3D");
		Add_ButtonAtras("3BAA2");
	}
	//Menu de Remover//
	void Interfaz4()
	{
		this->Clear();	
		_interfaz=4;
		Add_Label("4L0","Menu de Remover",2,0.3,0.3,0.3);
		Add_RadioButtonGroup("4RBG1");
		char*GetCharDeleteChar;
		for(unsigned i=0;i<_MB->cont;i++)
		{
			
			GetCharDeleteChar=GetCharDelete("RB",i);
			Add_RadioButton_To_RadioButtonGroup("4RBG1",GetCharDeleteChar,_MB->bocetos[i]->Get_Name());
			delete[]GetCharDeleteChar;	
		}
		Add_ButtonsAcceptAtras("4BAA2");
	}
	//Agregar Boceto3D//
	void Interfaz5()
	{
		this->Clear();	
		_interfaz=5;
		Add_Label("5L0","Nombre del Boceto3D",2,0.3,0.3,0.3);
		Add_TextBoxCenter("5Tb1","Boceto0");
		Add_ButtonsAcceptAtras("5BAA2");
	}
	//Agregar Boceto2D//
	void Interfaz6()
	{
		this->Clear();	
		_interfaz=6;
		Add_Label("6L0","Nombre del Boceto2D",2,0.3,0.3,0.3);
		Add_TextBoxCenter("6TB1","Boceto0");
		Add_Label("6L2","Tipo de Plano",2,0.3,0.3,0.3);
		Add_RadioButtonGroup("6RBG3");
		Add_RadioButton_To_RadioButtonGroup("6RBG3","RB0","XY");
		Add_RadioButton_To_RadioButtonGroup("6RBG3","RB1","XZ");
		Add_RadioButton_To_RadioButtonGroup("6RBG3","RB2","YZ");
		Add_RadioButton_To_RadioButtonGroup("6RBG3","RB3","Manual");
		
		Add_ChectBox("6CH4","En Coord. Final");
		Add_RadioButtonGroupFree("6RBGF5");
		forms[cont-1]->Set_Active(false);
		Add_RadioButton_To_RadioButtonGroup("6RBGF5","RB0","X:101,Y:104,Z:1007");
		Add_RadioButton_To_RadioButtonGroup("6RBGF5","RB1","X:102,Y:105,Z:1008");
		Add_RadioButton_To_RadioButtonGroup("6RBGF5","RB2","X:103,Y:106,Z:1009");
		
		
		Add_ButtonsAcceptAtras("6BAA6");
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
			Interfaz3();
			break;
		case 2://Sub Boceto
			Interfaz4();
			break;
		case 3://Label Bocetos Activos
			break;
		default:
			_MB->Set_BocetoAPintar(ElementPulsadoPositionInArray-4);
			Interfaz2();
			break;
		}
	}
	void Pulsarinterfaz2(unsigned ElementPulsadoPositionInArray)
	{
		int i,ii;
		switch (ElementPulsadoPositionInArray)
		{
		case 0://Label dibujo
		case 1://Label nombre de boceto
			break;
		case 2://RBG DrawType
			i=Get_Element_By_Name("2RBG2");
			if(i==-1)
				break;
			ii=forms[i]->Get_Element_Chect();
			if(ii==-1)
				break;
			_MB->Set_DrawType((_drawType)(unsigned)ii);
			break;
		case 3://CH Draw Plano//
			i=Get_Element_By_Name("2CH3");
			if(i==-1)
				break;
			_MB->Set_DrawPlane(forms[i]->Get_Chect());
			cout<<"Puesto"<<endl;
			break;
		}
	}
	void Pulsarinterfaz3(unsigned ElementPulsadoPositionInArray)
	{
		switch (ElementPulsadoPositionInArray)
		{
		case 0://label menu agregar
			break;
		case 1://btn boceto2d
			Interfaz6();
			break;
		case 2://btn boceto3d
			Interfaz5();
			break;
		}
	}
	void Pulsarinterfaz6(unsigned ElementPulsadoPositionInArray)
	{
		int i,ii,iii;
		bool ib;
		switch (ElementPulsadoPositionInArray)
		{
		case 0://label nombre
			break;
		case 1://TX nombre
			break;
		case 2://Label tipo de plano
			break;
		case 3://RBG tipo de plano
			i=Get_Element_By_Name("6RBG3");
			if(i==-1)
				break;
			ii=forms[i]->Get_Element_Chect();
			if(ii==-1)
				break;
			if(ii==3)
				ib=true;
			else
				ib=false;

			iii=Get_Element_By_Name("6RBGF5");
			if(iii==-1)
				break;
			forms[iii]->Set_Active(ib);
			iii=Get_Element_By_Name("6CH4");
			if(iii==-1)
				break;
			forms[iii]->Set_Active(!ib);
			break;
		case 4://CH en coord. final
			break;
		case 5://RBG  MANUAL
			break;
		case 6://btn boceto3
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
		case 2:
			Pulsarinterfaz2(ElementPulsadoPositionInArray);
			break;
		case 3:
			Pulsarinterfaz3(ElementPulsadoPositionInArray);
			break;
		case 6:
			Pulsarinterfaz6(ElementPulsadoPositionInArray);
			break;
		default:
			break;
		}
	}
	void Pulsar_Accept()
	{
		int i,toRemove;
		switch(_interfaz)
		{
		case 4://Menu de Remover//
			i=Get_Element_By_Name("4RBG1");
			if(i==-1)
				break;
			toRemove=forms[i]->Get_Element_Chect();
			if(toRemove==-1)
				break;
			_MB->Sub_Boceto(toRemove);
			Interfaz1();
			break;
		case 5://Agregar Boceto3D//
			i=Get_Element_By_Name("5Tb1");
			if(i==-1)
				break;
			_MB->Add_Boceto3D(forms[(unsigned)i]->Get_Text());
			Interfaz1();
			break;
		}
	}	
	void Pulsar_Cancel()
	{
		
	}
	void Pulsar_Atras()
	{
		switch (_interfaz)
		{
		
		case 3://Menu de Agregar//
		case 4://Menu de Remover//
			_interfaz=1;
			break;
		case 5://Agregar Boceto3D//
		case 6://Agregar Boceto2D//
			_interfaz=3;
			break;
		case 2://Menu de Dubujo//
			_MB->Set_BocetoAPintar();//SET -1//
		default:
			_interfaz--;
			break;
		}
		Set_Interfaz(_interfaz);
	};
	
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


