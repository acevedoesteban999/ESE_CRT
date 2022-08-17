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
				if(forms[i]->type==_TEXTBOX)
					TextBoxEscribiendo=i;
				else if(forms[i]->type==_BOX)
					if(forms[i]->TextBox_Get_Escribiendo())
						TextBoxEscribiendo=i;
			}
		}
		return false;
	}
};