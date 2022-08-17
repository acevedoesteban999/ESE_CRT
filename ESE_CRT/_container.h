#pragma once
#include "_baseLayouts.h"
class _container:public _baseLayouts
{
public:
	////IMPORTANT NO TEXTBOX////////
	_container(char*name,int*TotalWigth,int*TotalHeight):_baseLayouts(name,CRD(),TotalWigth,TotalHeight)
	{
		type=_CONTAINER;
	}
	~_container()
	{}
	void Add_Element(_forms*form)
	{
		if(form->type!=_LABEL)
			return;
		_baseArrayForms::Add_Element(form);
	}
	////PURAS////
	bool Pulsado(int x,int y)
	{
		for(unsigned i=0;i<cont;i++)
				if(forms[i]->Pulsado(x,y))
					return true;
		return false;
	};
	void _draw()
	{
		for(unsigned i=0;i<cont;i++)
			forms[i]->_draw();
	};
};

class _containerPrincipal:public _container
{
public:
	_containerPrincipal(char*name,char*Frases100,int*TotalWigth,int*TotalHeight):_container(name,TotalWigth,TotalHeight)
	{
		Add_Label_Free("labelESE_CRT","ESE_CRT",CRD(0,17),true,1,0.7,0.7,0.7);
		Add_Label_Free("labelChar","COM#",CRD(85,10),false,0,0,1,0);
		Add_Label_Free("labelUnsigned","00000",CRD(85,20),false,0,0,1,0);
		Add_Label_Free("labelReferenciar","No_Referenciado",CRD(0,40),false,1,1,1,0);
		Add_Label_Free("labelVersion",Frases100,CRD(),1,0.6,0.6,0.6);
	}
	~_containerPrincipal()
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
		return _container::Pulsado(x,y);
	}
	void _draw()
	{
		_container::_draw();
	}
};