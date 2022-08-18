#pragma once
#include "_forms.h"
#include "_baseArrayForms.h"
class _manejadorForms:public _baseArrayForms
{
public:
	_manejadorForms():_baseArrayForms()
	{
	}
	~_manejadorForms(){}
	void _draw()
	{
		for(unsigned i=0;i<cont;i++)
			forms[i]->_draw();
	}
	/////PURAS//////
	bool Pulsado(int x,int y)
	{
		if(TextBoxEscribiendo!=-1)
			TextBoxEscribiendo=-1;
		for(unsigned i=0;i<cont;i++)
		{
			if(forms[i]->Pulsado(x,y))
			{	
				if(forms[i]->TextBox_Get_Escribiendo())
						TextBoxEscribiendo=i;
				return true;
			}
		}
		return false;
	}
	bool PulsadoPasivo(int x,int y)
	{
		for(unsigned i=0;i<cont;i++)
			if(forms[i]->PulsadoPasivo(x,y))
				return true;
		return false;
	};
};