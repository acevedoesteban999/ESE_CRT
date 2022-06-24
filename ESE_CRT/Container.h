#include "Forms.h"

class Container:public Forms
{
private:
	NullForms nullforms;
	unsigned cont,cant;
	Forms**forms;
	unsigned PulsadO,PasivePulsado;
public:
	Container(char*name="DefaultNameContainer",unsigned cant=10):Forms(name,CRD(0,0,0),0,0,0,0)
	{
		cont=0;
		this->cant=cant;
		forms=new Forms*[cant];
		this->t=Type::CONTAINER;
	}
	~Container()
	{
		for(unsigned i=0;i<cont;i++)
			delete forms[i];
		delete[]forms;
	}
	void ChecketCont(){
		if(cont>=cant-1)
		{
			Forms**newForms=new Forms*[cant+10];
			cant+=10;
			for(unsigned i=0;i<cont;i++)
				newForms[i]=forms[i];
			delete[]forms;
			forms=newForms;
		}
	}
	
	void Draw()
	{
		if(!this->NoDraw)
		{
			for(unsigned i=0;i<cont;i++)
				forms[i]->Draw();
		}
	}
	unsigned Click(){
		return (unsigned)t;
	}
	void NewTotalProp(float wigth,float height)
	{
		for(unsigned i=0;i<cont;i++)
			forms[i]->NewTotalProp(wigth,height);
	};
	void AddForms(Forms*forms)
	{
		ChecketCont();
		this->forms[cont++]=forms;
	}
	Forms* ContainerGetForms(char*FormsName)
	{
		for(unsigned i=0;i<cont;i++)
		{
			if(!strcmp(FormsName,forms[i]->name))
			{
				return forms[i];
			}
		}
		return &nullforms;
	}


};