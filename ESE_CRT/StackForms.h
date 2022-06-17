#pragma once
#include "TextBox.h"
#include "Button.h"
#include "Label.h"
#include "RadioButtonGroup.h"
class StackForms
{
private:
	Forms**forms;
	unsigned cant;
	unsigned cont;
	mutex m;
public:
	StackForms(){cont=0;cant=10;forms=new Forms*[cant];};
	~StackForms()
	{
		for(unsigned i=0;i<cont;i++)
			delete forms[i];
		delete[]forms;
	};
	static void Add(Forms*form,StackForms*sf){
		if(form->Cancel)
		{
			delete form;
			return;
		}
		for(int i=(int)sf->cont-1;i>=0;i--)
		{
			if(sf->ExistForm(form->name,sf->forms[i]))
			{
		       sf->Sub(form->name,sf);
			   break;
			}
		}
		if(form->destruir)
			return;
	
	if(sf->cont>=sf->cant)
	{
		Forms**NewForms=new Forms*[sf->cant+10];
		sf->cant+=10;
		for(unsigned i=0;i<sf->cont;i++)
			NewForms[i]=sf->forms[i];
		delete[]sf->forms;
		sf->forms=NewForms;
	}
	sf->forms[sf->cont++]=form;
}
	static void Sub(char*name,StackForms*sf)
	{
		sf->m.lock();
		for(int i=(int)sf->cont-1;i>=0;i--)
		{
			if(sf->ExistForm(name,sf->forms[i]))
			{
				delete sf->forms[i];
				for(unsigned ii=i;ii<sf->cont-1;ii++)
					sf->forms[ii]=sf->forms[ii+1];
				sf->cont--;
				break;
			}
		}
		sf->m.unlock();
		
	}
	static void DrawForms(StackForms*sf)
	{
		sf->m.lock();
		for(unsigned i=0;i<sf->cont;i++)
			    sf->forms[i]->Draw();
		sf->m.unlock();
	}
	static void ActivateForm(char*name,StackForms*sf){
		for(unsigned i=0;i<sf->cont;i++)
			if(sf->ExistForm(name,sf->forms[i]))
				sf->forms[i]->ActivateDesactivate(true);
	}
	static void ActivateRB(char*RBGname,char*RBname,StackForms*sf){
		for(unsigned i=0;i<sf->cont;i++)
			if(sf->forms[i]->t==Type::RADIOBUTTONGROUP&&ExistForm(RBGname,sf->forms[i]))
			{
				sf->forms[i]->RBGActivDesactRB(RBname,true);
				return;
				
				   
			}
	}
	static void ActvDesactOnlyForm(char*ElementsName,bool ActviDesact,StackForms*sf)
	{
		for(unsigned i=0;i<sf->cont;i++)
		{
			if(sf->ExistForm(ElementsName,sf->forms[i]))
			{
				//sf->forms[i]->ActivateDesactivate(ActviDesact);
				sf->forms[i]->active=ActviDesact;
				return;
			}
		}
	}
	static void DesactivateForm(char*name,StackForms*sf){
		for(unsigned i=0;i<sf->cont;i++)
			if(sf->ExistForm(name,sf->forms[i]))
				sf->forms[i]->ActivateDesactivate(false);
	}
	static void DesactivateRB(char*RBGname,char*RBname,StackForms*sf){
		for(unsigned i=0;i<sf->cont;i++)
			if(sf->forms[i]->t==Type::RADIOBUTTONGROUP&&ExistForm(RBGname,sf->forms[i]))
			{
				sf->forms[i]->RBGActivDesactRB(RBname,false);
				return;
				   
			}
	}
    static void AddText(char c,StackForms*sf){
		for(unsigned i=0;i<sf->cont;i++)
			if(sf->forms[i]->active&&(sf->forms[i]->t==Type::TEXTBOX||sf->forms[i]->t==Type::BOX)&&sf->forms[i]->Escribiendo())
				sf->forms[i]->AddText(c);
	}
	static void AddNewText(char*FormsName,char*newText,StackForms*sf)
	{
		for(unsigned i=0;i<sf->cont;i++)
		{
			if(sf->ExistForm(FormsName,sf->forms[i]))
			{
				sf->forms[i]->AddNewText(newText);
				break;
			}
		}
	}
	static void AddNewCRD(char*name,CRD crd,StackForms*sf){
	for(unsigned i=0;i<sf->cont;i++)
	   {
		if(sf->ExistForm(name,sf->forms[i]))
		   {
			sf->forms[i]->NewCRD(crd);
			break;
		   }
       }
	
	}
    static void SubText(StackForms*sf){
		for(unsigned i=0;i<sf->cont;i++)
			if(sf->forms[i]->active&&(sf->forms[i]->t==Type::TEXTBOX||sf->forms[i]->t==Type::BOX)&&sf->forms[i]->Escribiendo())
				sf->forms[i]->SubText();

}
	static void SetColor(char*name,GLfloat R,GLfloat G,GLfloat B,StackForms*sf){
		sf->GetForm(name,sf)->SetColor(R,G,B);
	
	}
	static void SetlabelColor(char*name,GLfloat R,GLfloat G,GLfloat B,StackForms*sf){
		sf->GetForm(name,sf)->SetLabelColor(R,G,B);
	
	}
	static Type FormsPasiveMouse(int x,int y,StackForms*sf)
	{
		for(int i=(int)sf->cont-1;i>=0;i--)
			if(sf->forms[i]->active&&sf->forms[i]->PulsadoPasivo(x,y))
				return sf->forms[i]->GetPasivePulsado();
		return Type::FORMS;
	}
	static void SetDraw(bool noDraw,char*name,StackForms*sf){
		sf->GetForm(name,sf)->SetDraw(noDraw,sf->GetForm(name,sf));
	}
	static unsigned PresionarForm(float x,float y,StackForms*sf){
		unsigned a=0;
		for(unsigned i=0;i<sf->cont;i++)
		{
			if(sf->forms[i]->active)
			{
			 if(sf->forms[i]->Pulsado(x,y))	 
				a=sf->forms[i]->Click();
			 else
				sf->forms[i]->NoClick();
			}
		}
		return a;
	}
	static void NewTotalsProp(float wigth,float height,StackForms*sf){
		for(unsigned i=0;i<sf->cont;i++)
			sf->forms[i]->NewTotalProp(wigth,height);
	
	}
	static Forms* GetForm(char*name,StackForms*sf)
	{
		for(int i=(int)sf->cont-1;i>=0;i--)
		{
			if(sf->ExistForm(name,sf->forms[i]))
				return sf->forms[i];
		}
		    Forms*f=new Button("ErrorGetForms",Type::FORMS,*new CRD(0,0,0),0,0,0,0,0,0,0);
			return f;
	
	}; 
	static Forms* GetForm(unsigned numero,StackForms*sf){if(numero<sf->cont)return sf->forms[numero];};
	static bool ExistForm(char*name,Forms*f)
	{
			if(!strcmp(f->name,name))
				return true;
	     return false;
	}
	static bool ExisteInStackForm(char*name,StackForms*sf)
	{
		for(unsigned i=0;i<sf->cont;i++)
			if(sf->ExistForm(name,sf->forms[i]))
				return true;
		return false;
	}
	bool GetEstoyEscribindo(){
		for(unsigned i=0;i<this->cont;i++)
			if(forms[i]->Escribiendo())
				return true;
			return false;
	}
	static void MoveOnReshape(char*formsName,bool rechape,StackForms*sf)
	{
		for(unsigned i=0;i<sf->cont;i++)
		{
			if(!strcmp(sf->forms[i]->name,formsName))
			{
				sf->forms[i]->MoveOnReshape(rechape);
				return;
			}
		}
	
	}
	static void NextFocus(char*formName,StackForms*sf)
	{
	    for(unsigned i=0;i<sf->cont;i++)
		{
			if(!strcmp(sf->forms[i]->name,formName))
			{
				sf->forms[i]->BoxNextFocus();
			    return;
			}
		}
	}
	static double* FocusClick(char*formName,StackForms*sf)
	{
	    for(unsigned i=0;i<sf->cont;i++)
			if(!strcmp(sf->forms[i]->name,formName))
				return sf->forms[i]->BoxFocusClick();
		double*toReturn=new double[2];
		toReturn[0]=0;
		toReturn[1]=0;
		return toReturn;
	}
};