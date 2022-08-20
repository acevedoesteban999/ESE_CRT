#pragma once
#pragma once
#include "_forms.h"

class _baseArrayForms
{
protected:
	_forms**forms;
	unsigned cont,cant;
	int TextBoxEscribiendo;
public:
	_baseArrayForms()
	{
		cont=0;
		cant=10;
		TextBoxEscribiendo=-1;
		forms=new _forms*[cant];
	}
	virtual ~_baseArrayForms()
	{
		for(unsigned i=0;i<cont;i++)
			delete forms[i];
		delete[]forms;
	}
	virtual void New_CRD(char*name,CRD crd)
	{
		int i=Get_Element_By_Name(name);
		if(i==-1)
			return;
		forms[i]->New_CRD(crd);
	}
	void Reset()
	{
		Clear();
		delete[]forms;
		cant=10;
		forms=new _forms*[cant];
	} 
	virtual void Clear()
	{
		for(unsigned i=0;i<cont;i++)
			delete forms[i];
		cont=0;
	}
	virtual void Actualizar_ParentWigth()
	{
		for(unsigned i=0;i<cont;i++)
			forms[i]->Actualizar_ParentWigth();
	}
	///ADD//
	virtual void Add_Element(_forms*form)
	{
		if(cont>=cant)
		{
			cant+=10;
			_forms**newForms=new _forms*[cant];
			for(unsigned i=0;i<cont;i++)
				newForms[i]=forms[i];
			delete[]forms;
			forms=newForms;
		}
		forms[cont++]=form;
	}
	//SUB//
	void Sub_Element(char*name)
	{
		int i=Get_Element_By_Name(name);
		if(i==-1)
			return;
		delete forms[(unsigned)i];
		for(unsigned ii=(unsigned)i;ii<this->cont-1;ii++)
			forms[ii]=forms[ii+1];
		cont--;
	}
	//GET//
	int Get_Element_By_Name(char*name)
	{
		for(unsigned i=0;i<cont;i++)
			if(!strcmp(name,forms[i]->name))
				return i;
		return -1;
	}
	float Get_All_Wigth()
	{
		float toReturn=0;
		for(unsigned i=0;i<cont;i++)
			if(forms[i]->Get_All_Wigth()>toReturn)
				toReturn=forms[i]->Get_All_Wigth();
		return toReturn;
	}
	virtual char* Get_Text(char*name)
	{
		int i=Get_Element_By_Name(name);
		if(i==-1)
			return 0;
		return forms[i]->Get_Text();
	}
	//SET//
	virtual void Set_Draw(char*name,bool Draw)
	{
		int i=Get_Element_By_Name(name);
		if(i==-1)
			return;
		forms[i]->Set_Draw(Draw);
	}
	virtual void Set_Color(char*name,GLfloat R,GLfloat G,GLfloat B)
	{
		int i=Get_Element_By_Name(name);
		if(i==-1)
			return;
		forms[i]->Set_Color(R,G,B);
	};
	virtual void Set_Text(char*name,char*text)
	{
		int i=Get_Element_By_Name(name);
		if(i==-1)
			return;
		forms[i]->Set_Text(text);
	}
	virtual void Set_Active(bool Active)
	{
		for(unsigned i=0;i<cont;i++)
			forms[i]->Set_Active(Active);
	}
	virtual void Set_Active(char*name,bool Active)
	{
		int i=Get_Element_By_Name(name);
		if(i==-1)
			return;
		forms[i]->Set_Active(Active);
	}
	//TEXTBOX//
	void TextBox_Add_Caracter(char caracter)
	{
		if(TextBoxEscribiendo==-1)
			return;
		forms[(unsigned)TextBoxEscribiendo]->TextBox_Add_Caracter(caracter);
	}
	void TextBox_Sub_Caracter()
	{
		if(TextBoxEscribiendo==-1)
			return;
		forms[(unsigned)TextBoxEscribiendo]->TextBox_Sub_Caracter();
	}
	bool TextBox_Get_Escribiendo()
	{
		if(TextBoxEscribiendo==-1)
			return false;
		return true;
	}
	//PURAS//
	virtual bool Pulsado(int x, int y)=0;
};