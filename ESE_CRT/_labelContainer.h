#pragma once
#include "_baseContainer.h"
class _labelContainer:public _baseContainer
{
public:
	////IMPORTANT NO TEXTBOX////////
	_labelContainer(char*name,CRD coord,int*TotalWigth,int*TotalHeight):_baseContainer(name,coord,TotalWigth,TotalHeight)
	{
		type=_LABELCONTAINER;
	}
	~_labelContainer(){}
	void New_CRD(CRD crd)
	{
		_forms::New_CRD(crd);
		for(unsigned i=0;i<cont;i++)
		{
			forms[i]->New_CRD(CRD(crd.AddY(i*17)));
		}
	}
	//ADD//
	virtual void Add_Element(_forms*form)
	{		
		form->New_CRD(CRD(coord.AddY(cont*17)));
	
		_baseArrayForms::Add_Element(form);
	
	}
	////PURAS////
	bool Pulsado(int x,int y)
	{
		return false;
	};
	void _draw()
	{
		for(unsigned i=0;i<cont;i++)
			forms[i]->_draw();
	};
};

class _labelContainerFree:public _baseContainer
{
public:
	////IMPORTANT NO TEXTBOX////////
	_labelContainerFree(char*name,int*TotalWigth,int*TotalHeight):_baseContainer(name,CRD(),TotalWigth,TotalHeight)
	{
		type=_LABELCONTAINERFREE;
	}
	~_labelContainerFree()
	{}
	virtual void Add_Element(_forms*form)
	{
		if(form->type!=_LABEL)
			return;
		_baseArrayForms::Add_Element(form);
	}
	////PURAS////
	bool Pulsado(int x,int y)
	{
		return false;
	};
	void _draw()
	{
		for(unsigned i=0;i<cont;i++)
			forms[i]->_draw();
	};
};

class _labelContainerPrincipal:public _labelContainerFree
{
public:
	_labelContainerPrincipal(char*name,char*Frases100,int*TotalWigth,int*TotalHeight):_labelContainerFree(name,TotalWigth,TotalHeight)
	{
		Add_Label_Free("labelESE_CRT","ESE_CRT",CRD(0,17),true,1,(GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7);
		Add_Label_Free("labelChar","COM#",CRD(85,10),false,0,0,1,0);
		Add_Label_Free("labelUnsigned","00000",CRD(85,20),false,0,0,1,0);
		Add_Label_Free("labelReferenciar","No_Referenciado",CRD(0,40),false,1,1,1,0);
		Add_Label_Free("labelVersion",Frases100,CRD(),true,1,(GLfloat)0.6,(GLfloat)0.6,(GLfloat)0.6);
	}
	~_labelContainerPrincipal()
	{
	}
	//Add//
	void LabelsInicarConeccion(char*Char,char*Unsigned,char*Referenciar)
	{
		Set_Color("labelESE_CRT",0,(GLfloat)1,0);
		Set_Text("labelChar",Char);
		Set_Text("labelUnsigned",Unsigned);
		Set_Text("labelReferenciar",Referenciar);
		Set_Draw("labelChar",true);
		Set_Draw("labelUnsigned",true);
		Set_Draw("labelReferenciar",true);
	}
	void LabelsDetenerConeccion()
	{
		Set_Color("labelESE_CRT",(GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7);
		Set_Draw("labelChar",false);
		Set_Draw("labelUnsigned",false);
		Set_Draw("labelReferenciar",false);
	}
	////PURAS////
	bool Pulsado(int x,int y)
	{
		return _labelContainerFree::Pulsado(x,y);
	}
	void _draw()
	{
		_labelContainerFree::_draw();
	}
};

class _labelContainerCoordenadas:public _labelContainer
{
private:
	_label*lX;
	_label*lY;
	_label*lZ;
	CRD*dataESE;
public:
	_labelContainerCoordenadas(char*name,CRD coord,CRD*dataESE,int*TotalWigth,int*TotalHeight):_labelContainer(name,coord,TotalWigth,TotalHeight)
	{
		this->dataESE=dataESE;
		lX=new _label(name,"",CRD(),1,(GLfloat)0.1,(GLfloat)0.1,(GLfloat)0.1,this->TotalWigth,this->TotalHeight);
		Add_Element(lX);
		lY=new _label(name,"",CRD(),1,(GLfloat)0.1,(GLfloat)0.1,(GLfloat)0.1,this->TotalWigth,this->TotalHeight);
		Add_Element(lY);
		lZ=new _label(name,"",CRD(),1,(GLfloat)0.1,(GLfloat)0.1,(GLfloat)0.1,this->TotalWigth,this->TotalHeight);
		Add_Element(lZ);
		Actualizar_Coord();
	}
	~_labelContainerCoordenadas()
	{
	}
	//SET//
	void Actualizar_Coord()
	{
		lX->Set_Text((char*)(string("X: ")+ to_string(dataESE->x)).c_str());
		lY->Set_Text((char*)(string("Y: ") + to_string(dataESE->y)).c_str());
		lZ->Set_Text((char*)(string("Z: ") + to_string(dataESE->z)).c_str());
	}
	////PURAS////
	bool Pulsado(int x,int y)
	{
		return _labelContainer::Pulsado(x,y);
	}
	void _draw()
	{
		_labelContainer::_draw();
	}
};