#pragma once
#include "Forms.h"
#include "RadioButton.h"
class RadioButtonGroup:public Forms
{
protected:
	unsigned cantRB,contRB,Checket;
	RadioButton**RB;
	mutex m;
public:
	RadioButtonGroup()
	{
		RB=new RadioButton*[1];
	};
	RadioButtonGroup(char*name,CRD coord,float TotalWigth,float TotalHeight):Forms(name,coord,0,0, TotalWigth, TotalHeight){
		t=Type::RADIOBUTTONGROUP;
		cantRB=10;
		contRB=0;
		RB=new RadioButton*[cantRB];
		Checket=0;
};
	~RadioButtonGroup()
	{
		for(unsigned i=0;i<contRB;i++)
			delete RB[i];
		delete[]RB;
	};
	void NewTotalProp(float wigth,float height){
		Forms::NewTotalProp(wigth,height);
		for(unsigned i=0;i<contRB;i++)
			RB[i]->NewTotalProp(wigth,height);
	}	
	void Draw()
	{
			
			if(!this->NoDraw)
			{
				glPushMatrix();
				glLoadIdentity();
				glTranslatef((GLfloat)(-TotalWigth/2+coord.x),(GLfloat)(TotalHeight/2-coord.y),(GLfloat)2*this->TotalWigth-1+TotalProfundidad); 
				glColor3f(1,1,1);
				glBegin(GL_POLYGON);
				glVertex3f(-5,5,(GLfloat)-1.1);
				glVertex3f(Wigth,5,(GLfloat)-1.1);
				glVertex3f(Wigth,-Height-5,(GLfloat)-1.1);
				glVertex3f(-5,-Height-5,(GLfloat)-1.1);
				glEnd();
				glPopMatrix();
				m.lock();
				for(unsigned i=0;i<contRB;i++)
				   this->RB[i]->Draw();
				m.unlock();
	
			}
			
	}
    unsigned Click(){
	for(unsigned i=0;i<contRB;i++)
		RB[i]->NotChecket();
	this->RB[Checket]->Click();
	return(unsigned)t;
	}
	void NewCRD(CRD newcoord){
		this->coord=newcoord;
		for(unsigned i=0;i<contRB;i++)
			RB[i]->NewCRD(newcoord+CRD(0,i*15,0));
	}
	bool Pulsado(float x,float y)
	{
		
		if(Forms::Pulsado(x,y))
		   {
		   for(unsigned i=0;i<contRB;i++)
		      {
				  if(y>=RB[i]->coord.y&&y<=RB[i]->coord.y+15&&x>=RB[i]->coord.x&&x<=RB[i]->coord.x+15)
				   {
					   if(RB[i]->active)
					   {
							RB[i]->CambiarChecket();		   
							this->Checket=i;
							return true;
					   }
					   return false;
			       }
		      }
		  
		}
	   return false;
	}
	bool PulsadoPasivo(int x,int y)
	{
	  if(Forms::Pulsado((float)x,(float)y))
		   {
		   for(unsigned i=0;i<contRB;i++)
		      {
				   if(y>=RB[i]->coord.y&&y<=RB[i]->coord.y+15&&x>=RB[i]->coord.x&&x<=RB[i]->coord.x+15)
				   {
					   if(RB[i]->active)
					      return true;
					   return false;
			       }
		      }
		}
	   return false;
	};
	Type GetPasivePulsado()
	{
		return  Type::RADIOBUTTON; 
	}
	void RBGAddRB(char*RadioButtonName,char*escritura,bool Cheket=false,bool active=true){
		
		if(Cheket)
		{
			Checket=contRB;
			for(unsigned i=0;i<this->contRB;i++)
				RB[i]->NotChecket();
		    }
		if(this->Wigth<(float)(strlen(escritura)*10+20))
			this->Wigth=(float)(strlen(escritura)*10+20);
		RadioButton*rb=new RadioButton(RadioButtonName,CRD(this->coord.x,(double)(this->coord.y+this->Height),this->coord.z),escritura,this->TotalWigth,this->TotalHeight,Cheket);
		rb->active=active;
		if(this->contRB>=this->cantRB)
		{
			RadioButton**newRB=new RadioButton*[this->cantRB+10];
			this->cantRB+=10;
			for(unsigned i=0;i<this->contRB;i++)
				newRB[i]=this->RB[i];
			delete[]this->RB;
			this->RB=newRB;
		}

		this->RB[this->contRB++]=rb;
		this->Height+=rb->Height;
		
	}
    void RBGSubRB(char*nameRB)
	{
		m.lock();
		for(unsigned i=0;i<this->contRB;i++)
		{
			if(!strcmp(this->RB[i]->name,nameRB))
			{
	            delete RB[i];
				for(unsigned ii=i;ii<this->contRB-1;i++)
					this->RB[i]=this->RB[i+1];
				break;
			}
		}
		this->contRB--;
		this->Height-=18;
		m.unlock();
		
	}
	void Activate(){
		this->active=true;
		for(unsigned i=0;i<contRB;i++)
			RB[i]->ActivateDesactivate(true);
	};
	void Desactivate(){
		this->active=false;
		for(unsigned i=0;i<contRB;i++)
			RB[i]->ActivateDesactivate(false);
	};
	static RadioButton* GetRD(char*name,RadioButtonGroup*rbg){
		for(unsigned i=0;i<rbg->contRB;i++)
			if(!strcmp(rbg->RB[i]->name,name))
				return rbg->RB[i];
		return new RadioButton("GETRDError",*(new CRD(0,0,0)),"Error",0,0);
	
	}
	void SetCoord(float x,float y,float z){
		this->coord.x=x;
		this->coord.y=y;
		this->coord.z=z;
		for(unsigned i=0;i<contRB;i++)
		{
			RB[i]->SetCoord(x,y,z);
			y+=RB[0]->Height;
		}
	}
	void SetCoord(CRD coord){
		this->coord=CRD(coord);
		for(unsigned i=0;i<contRB;i++)
		{
			RB[i]->SetCoord(coord);
			coord.y+=RB[0]->Height;
		}
	}
	void SetNewProp(float wigth,float height){
		
		if(wigth)
			this->Wigth=wigth+25;
		if(height)
			this->Height=height;
		
	}
	void SetProfundidad(float profundidad)
	{
		this->TotalProfundidad=profundidad;
		for(unsigned i=0;i<contRB;i++)
			RB[i]->SetProfundidad(profundidad);
	}
	unsigned RBGGetChecket(){
		return Checket;};
	void CambiarChecket(){
		RB[Checket]->NoClick();
		Checket==contRB-1?Checket=0:Checket++;
		RB[Checket]->Click();
	}
	double* RBGGetChecketPositton(){
	   double*a=new double[2];
	   a[0]=RB[Checket]->coord.x;
	   a[1]=RB[Checket]->coord.y;
	   return a;
	}
	unsigned RBGGetMaxChecket(){return this->contRB;};
	unsigned GetCONTRB(){return contRB;};
	void RBGActivDesactRB(char*name,bool activate){
		for(unsigned i=0;i<contRB;i++)
		{
			if(!strcmp(RB[i]->name,name))
			{
				RB[i]->active=activate;
				return;
			}
		}
	}
	bool GetRBChecket(char*name){
		for(unsigned i=0;i<contRB;i++)
			if(RB[i]->active&&!strcmp(name,RB[i]->name))
				return RB[i]->RBGetCheket()?1:0;
		return 0;
	};
	void RBGSetRBChecket(char*RBname,bool checket){
		for(unsigned i=0;i<contRB;i++)
			if(!strcmp(RBname,RB[i]->name))
				RB[i]->Checket=checket;
	};
	void ActivateDesactivate(bool ActDesact){
	      for(unsigned i=0;i<contRB;i++)
			  RB[i]->ActivateDesactivate(ActDesact);
	}
	bool RBGGetRBActiveDesavt(char*nameRB)
	{
	  for(unsigned i=0;i<contRB;i++)
		  if(!strcmp(RB[i]->name,nameRB))
			  return RB[i]->GetActiveDesavt();
	  return false;
	}
	void RBGNextChecket(){
		if(this->Checket==this->contRB-1)
	 	   this->Checket=0;
		else
			this->Checket++;
		this->Click();
	};
	bool RBGGetRBChecket(char*nameRB)
	{
		 for(unsigned i=0;i<contRB;i++)
		  if(!strcmp(RB[i]->name,nameRB))
			  return RB[i]->RBGetCheket();
		 return false;
	}
	
};