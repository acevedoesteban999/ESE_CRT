#pragma once
#include "CRD.h"
enum _type
{
	_FORMS,
	_NULL,
	_TEXTBOX,
	_TEXTBOXCENTER,
	_LABEL,
	_RADIOBUTTONGROUP,
	_RADIOBUTTONGROUPFREE,
	_CHECTBOX,
	_RADIOBUTTON,
	_BOX,
	_BUTTON,
	_BUTTONLABEL,
	_BUTTONLABELCENTER,
	_BUTTONATRAS,
	_CONTAINER,
	_BUTTONSACCEPTCANCEL,
	_BUTTONSACCEPTATRAS,
	_BASEBUTTON,
	_BUTTONACCEPT,
	_BUTTONCANCEL,
	_LABELCENTER,
	_LABELCONTAINERFREE,
	_LABELCONTAINER
};

class _forms
{
public:
	char*name;
	CRD coord;
	float Wigth,Height;//TotalProfundidad;
	int *TotalWigth,*TotalHeight;
	bool active,Draw;
	_type type;
	bool PulsadoPasivoBool;
	//////////////////////////
	_forms(char*name,CRD coord,float wigth,float height,int*TotalWigth,int*TotalHeight){
		this->name=new char[strlen(name)+1];
		this->name[strlen(name)]=0;
		for(unsigned i=0;i<strlen(name);i++)
			this->name[i]=name[i];
		this->TotalHeight=TotalHeight;
		this->TotalWigth=TotalWigth;
		//this->TotalProfundidad=0;
		this->Wigth=wigth;
		this->Height=height;
		this->coord=coord;
		this->active=true;
		this->Draw=true;
		PulsadoPasivoBool=false;
	};
	virtual ~_forms()
	{
		delete []name;
	};
	///////////////STATIC///////////////
	static bool Pulsado(int x,int y,_forms*f,bool PulsadoEspecial=false)
	{
		if(!f->Draw||!f->active)
			return false;
		if(PulsadoEspecial)
		{
			if(x>=f->coord.x&&x<=f->coord.x+f->Wigth&& y>=f->coord.y && y<=f->coord.y+f->Height)			
				return true;
		}
		else if(x>=f->coord.x&&x<=f->coord.x+f->Wigth&&y<=f->coord.y&&y>=f->coord.y-f->Height)			
			return true;
		return false;
	}
	///////////////VIRTUALES////////////
	virtual bool Pulsado(int x,int y)
	{
		return	_forms::Pulsado(x,y,this);
	}
	virtual bool PulsadoPasivo(int x,int y)
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
	virtual void New_CRD(CRD crd)
	{
		this->coord=crd;
	}
	virtual _type Get_BtnPulsado()
	{
		return _NULL;
	}
	virtual void Actualizar_ParentWigth(){};
	virtual int Get_Element_Chect(){return  -1;}
	//GET//
	virtual float Get_All_Wigth()
	{
		return Wigth;
	}
	virtual float Get_All_Height()
	{
		return Height;
	}
	virtual char* Get_Text(){return 0;}
	virtual bool Get_Chect(){return false;}
	virtual _type Get_Type_Last_Pulsado(){return type;}
	_type Get_Type(){return type;}
	//SET//
	virtual void Set_Draw(bool Draw)
	{
		this->Draw=Draw;
	}
	virtual void Set_Color(float R,float G,float B){}
	virtual void Set_Active(bool Active){this->active=Active;}
	virtual void Set_Element_Chect(unsigned DrawType){}
	//////LABEL//////
	virtual void Set_Text(char*text){};
	
	////////TEXTBOX////
	virtual bool TextBox_Get_Escribiendo(){return false;}
	//virtual char* TextBox_Get_Text(){	return nullptr;}
	virtual void TextBox_Add_Caracter(char caracter){}
	virtual void TextBox_Sub_Caracter(){}
	
	///////CHECTBOX/////
	
	//virtual bool Get_Chect(){	return false;}
	
	//////RADIOBUTTON////
	
	/////RADIOBUTTONGROUP///
	virtual void RadioButtonGroup_Add_RadioButton(char*RadioButtonName,char*escritura,bool Chect=false,bool active=true){}
	///////////////PURAS//////////////////
	virtual void _draw()=0; 
};

class _center
{
protected:
	CRD coordReferenciaInicial;
	float*ParentWigth;
	_forms*form;
public:
	_center(float*ParentWigth,_forms*form)
	{
		this->ParentWigth=ParentWigth;
		this->form=form;
	}
	~_center(){}
	void New_CRD(CRD crd)
	{
		coordReferenciaInicial=crd;
		form->_forms::New_CRD(crd);
	}
	static void Actualizar_ParentWigth(_forms*form,_center*center)
	{
		form->coord=center->coordReferenciaInicial.AddX((*center->ParentWigth)/2 - form->Get_All_Wigth()/2);
		//form->_forms::New_CRD(form->coord);
	} 
	void Actualizar_ParentWigth()
	{
		form->coord=coordReferenciaInicial.AddX((*ParentWigth)/2 - form->Get_All_Wigth()/2);
		//form->_forms::New_CRD(form->coord);
	}
};