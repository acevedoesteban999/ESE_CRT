#pragma once
#include "Forms.h"
class Box:public Forms{

private:
	Forms**forms;
	unsigned cant,cont;
	unsigned PulsadO,PasivePulsado;
	int Focus,FocusTimeDurat;
	TimeDuration td;
	bool TimeDurationBool;
	bool DrawLineForElement;
public:
	Box():Forms("DefaultNameBox",*new CRD(0,0,0),0,0,0,0)
	{ 
	   cont=0;
	   cant=10;
	   forms=new Forms*[cant];
	   this->t=Type::BOX;
	   PulsadO=PasivePulsado=FocusTimeDurat=0;
	   this->Focus=-1;
	   TimeDurationBool=false;
	   DrawLineForElement=true;
	}
	Box(char*name,CRD coord,float TotalWigth,float TotalHeight):Forms(name,coord,0,0,TotalWigth,TotalHeight)
	{
	   cont=0;
	   cant=10;
	   forms=new Forms*[cant];
	   this->t=Type::BOX;
	   PulsadO=PasivePulsado=FocusTimeDurat=0;
	   this->Focus=-1;
	   TimeDurationBool=false;
	   DrawLineForElement=true;
	}
	~Box()
	{
		for(unsigned i=0;i<cont;i++)
			delete forms[i];
		delete[]forms;
	};
	void ChecketCont(Box*b){
		if(b->cont>=b->cant)
		{
			Forms**newForms=new Forms*[b->cant+10];
			b->cant+=10;
			for(unsigned i=0;i<b->cont;i++)
				newForms[i]=b->forms[i];
			delete[]b->forms;
			b->forms=newForms;
		}
	}
	static void AddForm(Forms*f,Box*b,float x=0,float y=0,float z=0)
	{
		
		b->ChecketCont(b);

		f->SetCoord((float)(b->coord.x+x),(float)(b->coord.y+b->Height+y),(float)(b->coord.z+z));
		b->Height+=f->Height+y+5;
		if(f->LetterWigth()+x>b->Wigth-25)
			b->Wigth=f->LetterWigth()+x+25;

		b->forms[b->cont++]=f;
		
    }
	bool Pulsado(float x,float y)
	{
		
		if(Forms::Pulsado(x,y))
		   {
		   for(unsigned i=0;i<cont;i++)
		      {
				  if(forms[i]->Pulsado(x,y)&&forms[i]->active)
				  {
					  PulsadO=i;
				      return true;
				  }
		      }
		  
		}
	   return false;
	}
	bool PulsadoPasivo(int x,int y)
	{
		  if(Forms::Pulsado((float)x,(float)y))
		   {
		   for(unsigned i=0;i<cont;i++)
		      {
				  if(forms[i]->active&&forms[i]->PulsadoPasivo(x,y))
				  {
					  PasivePulsado=i;
				      return true;
				  }
		      }
		  
		}
		  return false;
	}
	Type GetPasivePulsado(){return forms[PasivePulsado]->GetPasivePulsado();};
	void Draw(){
		
			if(!this->NoDraw)
			{
				glPushMatrix();
				glLoadIdentity();
				glTranslatef((GLfloat)(-TotalWigth/2+coord.x),(GLfloat)(TotalHeight/2-coord.y),(GLfloat)2*this->TotalWigth-1+TotalProfundidad); 
				glColor3f(1,1,1);
				glBegin(GL_POLYGON);
				glVertex3f(-5,5,(GLfloat)-1.2);
				glVertex3f(Wigth,5,(GLfloat)-1.2);
				glVertex3f(Wigth,-Height-5,(GLfloat)-1.2);
				glVertex3f(-5,-Height-5,(GLfloat)-1.2);
				glEnd();

				glLineWidth(3);
				glColor3f(0,0,0);
				glBegin(GL_LINE_LOOP);
				glVertex3f(-5,5,(GLfloat)-1.1);
				glVertex3f(Wigth,5,(GLfloat)-1.1);
				glVertex3f(Wigth,-Height-5,(GLfloat)-1.1);
				glVertex3f(-5,-Height-5,(GLfloat)-1.1);
				glEnd();
				glLineWidth(1);	
			
				if(DrawLineForElement)
				{
					float ContHeigth=0;
					for(unsigned i=0;i<cont;i++)
					{
						if(this->Focus==(int)i)
						{
							glLineWidth(3);
							glColor3f(0,0,1);
						}
						else if(TimeDurationBool&&FocusTimeDurat==i)
						{
							if(td.Incrementa(&td)>3)
							{
								TimeDurationBool=false;
								td.ResettIncrementa(&td);
							}
							else
							{
							glLineWidth(3);
							glColor3f(1,0,0);
							}
						}

						else
						   glColor3f(0,0,0);
						glBegin(GL_LINE_LOOP);
						glVertex3f(-2,(GLfloat)(-ContHeigth+2.5),(GLfloat)-1.1);
						glVertex3f(Wigth-5,(GLfloat)(-ContHeigth+2.5),(GLfloat)-1.1);
						ContHeigth+=forms[i]->Height+5;
						glVertex3f(Wigth-5,(GLfloat)(-ContHeigth+2.5),(GLfloat)-1.1);
						glVertex3f(-2,(GLfloat)(-ContHeigth+2.5),(GLfloat)-1.1);
						glEnd();
						if(this->Focus==i||(this->FocusTimeDurat==i&&TimeDurationBool))
							glLineWidth(1);
					}
				}
				glPopMatrix();
				for(unsigned i=0;i<cont;i++)
					forms[i]->Draw();
			}
		
	}
	unsigned Click(){
		for(unsigned i=0;i<cont;i++)
			if(i!=PulsadO)
			   forms[i]->NoClick();
		forms[PulsadO]->Click();
		return (unsigned)t;
	}
	void NoClick(){};
	void NewCRD(CRD newcoord)
	{
		for(unsigned i=0;i<cont;i++)
		{
			forms[i]->NewCRD(forms[i]->coord-this->coord+newcoord);
		}
		this->coord=CRD(newcoord);

	}
	void NewCRD(char*Formsname,CRD crd)
	{
		for(unsigned i=0;i<cont;i++)
		{
			if(!strcmp(Formsname,forms[i]->name))
			{
				forms[i]->NewCRD(crd);
				return;
			}
		}
		return;
	};
	CRD BoxGetElementCoord(char*ElementName)
	{
		for(unsigned i=0;i<cont;i++)
		{
			if(!strcmp(ElementName,forms[i]->name))
			{
				return forms[i]->coord;
			}
		}
		return CRD(0,0,0);
	}
	unsigned GetCont(){return cont;};
	unsigned GetChecket(){return PulsadO;};
	unsigned BoxGetRBG_RBChecket(char*RBGname,char*RBname){
		for(unsigned i=0;i<cont;i++)
			if(!strcmp(forms[i]->name,RBGname))
				return forms[i]->RBGGetChecket();
		return 0;
	};
	bool BoxGetRBChecket(char*RBname)
	{
		for(unsigned i=0;i<cont;i++)
			if(!strcmp(forms[i]->name,RBname))
				return forms[i]->RBGetCheket();
		return false;
	}
	unsigned BoxGetRBGChecket(char*RBGname)
	 {
		 for(unsigned i=0;i<cont;i++)
			if(!strcmp(forms[i]->name,RBGname))
				return forms[i]->RBGGetChecket();
		 return 0;
	 
	 
	 }
    unsigned BoxGetElemChecket(){
		 return PulsadO;
	 }
	bool Escribiendo()
	{
		for(unsigned i=0;i<cont;i++)
			if(forms[i]->t==Type::TEXTBOX&&forms[i]->Escribiendo())
				return true;
		return false;
	}
	void AddText(char c){
		for(unsigned i=0;i<cont;i++)
			if(forms[i]->active&&forms[i]->Escribiendo())
				forms[i]->AddText(c);
	}
	void SubText(){
		for(unsigned i=0;i<cont;i++)
			if(forms[i]->active&&forms[i]->Escribiendo())
				forms[i]->SubText();

}
	void ActivateDesactivate(bool ActDesact){
		
		this->active=ActDesact;
		
		for(unsigned i=0;i<cont;i++)
			forms[i]->ActivateDesactivate(ActDesact);
	}
	bool BoxGetActiveDesact(char*ElementName){
	     for(unsigned i=0;i<cont;i++)
			 if(!strcmp(forms[i]->name,ElementName))
				 return forms[i]->GetActiveDesavt();
		 return false;
	};
	bool BoxGetRBGActiveDesact(char*RBGName,char*RBName){
	 for(unsigned i=0;i<cont;i++)
		 if(!strcmp(forms[i]->name,RBGName))
			 return forms[i]->RBGGetRBActiveDesavt(RBName);
	 return false;
	};
	void BoxCambiarChecketRB(char*RBname){
	   for(unsigned i=0;i<cont;i++)
		 if(!strcmp(forms[i]->name,RBname))
			 forms[i]->CambiarChecket();

	};
	void BoxSetActivateDesactivate(char*ElementName,bool actvDesact){
	for(unsigned i=0;i<cont;i++)
		if(!strcmp(forms[i]->name,ElementName))
			forms[i]->ActivateDesactivate(actvDesact);
	};
	void NewTotalProp(float wigth,float height)
	{
	   Forms::NewTotalProp(wigth,height);
	   for(unsigned i=0;i<cont;i++)
		   forms[i]->NewTotalProp(wigth,height);
	}
	void SetProfundidad(float profundidad)
	{
		this->TotalProfundidad=profundidad;
		for(unsigned i=0;i<cont;i++)
			forms[i]->SetProfundidad(profundidad);
	}
	char* BoxGetEscritura(char*TextBoxname){
		for(unsigned i=0;i<cont;i++)
			if(!strcmp(forms[i]->name,TextBoxname))
				return forms[i]->GetEscritura();
		return new char(0);
		
	};
	void BoxNextFocus(){
		
		if(this->Focus>=(int)(cont-1))
		   this->Focus=-1;
		else
		   this->Focus++;
		
	};
	double* BoxFocusClick() {
		double*toReturn=new double[2];
		toReturn[0]=0;
		toReturn[1]=0;
		if(this->Focus>=0)
		{
			if(this->forms[Focus]->t==Type::RADIOBUTTON)
			{
				toReturn[0]=this->forms[Focus]->coord.x;
				toReturn[1]=this->forms[Focus]->coord.y;
			}
			if(this->forms[Focus]->t==Type::RADIOBUTTONGROUP)
			{
				forms[Focus]->RBGNextChecket();
				toReturn=forms[Focus]->RBGGetChecketPositton();
			}
		
		}
		return  toReturn;
	};
	unsigned BoxGetCont(){return cont;};
	int BoxGetFocus(){return Focus;};
	void BoxSetFocus(int focus)
	{
		
		this->Focus=focus;
		
	}
	void BoxSetFocusColorTimer(char*ElemntName)
	{
		
		for(unsigned i=0;i<cont;i++)
		{
			if(!strcmp(ElemntName,this->forms[i]->name))
			{
				FocusTimeDurat=i;
				break;
			}
			else if(i==cont-1)
				return;
		}
		TimeDurationBool=true;
		td.ResettIncrementa(&td);
		td.Incrementa(&td);
		
	};
	void BoxSetDrawLineForElement(bool DrAw)
	{
		
		this->DrawLineForElement=DrAw;
		
	};
	void SetWigthElementProp(char*ElementName,float WiGth)
	{
		for(unsigned i=0;i<cont;i++)
		{
			if(!strcmp(ElementName,this->forms[i]->name))
			{
				forms[i]->SetNewProp(WiGth);
				return;
			}
		}
		return;
	}
	void SetHeightElementProp(char*ElementName,float HeiGht)
	{
		for(unsigned i=0;i<cont;i++)
		{
			if(!strcmp(ElementName,this->forms[i]->name))
			{
				forms[i]->SetNewProp(0,HeiGht);
				return;
			}
		}
		return;
	}
	void SetCoordElementProp(char*ElementName,CRD coord)
	{
		for(unsigned i=0;i<cont;i++)
		{
			if(!strcmp(ElementName,this->forms[i]->name))
			{
				//*forms[i]->coord=*coord;
				forms[i]->NewCRD(coord);
				return;
			}
		}
		return;
	}
	float GetWigthElement(char*ElementName)
	{
		for(unsigned i=0;i<cont;i++)
		{
			if(!strcmp(ElementName,this->forms[i]->name))
			{
				return forms[i]->Wigth;
			}
		}
		return 0;
	}
	float GetHeightElement(char*ElementName)
	{
		for(unsigned i=0;i<cont;i++)
		{
			if(!strcmp(ElementName,this->forms[i]->name))
			{
				return forms[i]->Height;
			}
		}
		return 0;
	}
};