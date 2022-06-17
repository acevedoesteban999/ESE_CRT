#pragma once
#include "Forms.h"
#include "CRD.h"
class StackAnimation:public Forms
{
public:
	Animacion**animations;
	unsigned cant,cont;
	mutex m;
	StackAnimation(char*name):Forms(name,CRD(0,0,0),0,0,0,0){
		Wigth=Height=0;
		cont=0;
		cant=10;
		animations=new Animacion*[cant];
	};
	~StackAnimation()
	{
		for(unsigned i=0;i<cont;i++)
			delete animations[i];
		delete[]animations;
	};
	void Draw()
	{
		m.lock();
		if(active&&!NoDraw)
			for(unsigned i=0;i<cont;i++)
				animations[i]->Draw();
		m.unlock();
	}
	void Sub(char*AnimationName)
	{
		m.lock();
		for(unsigned i=0;i<cont;i++)
		{
			if(!strcmp(AnimationName,animations[i]->name))
			{
				delete animations[i];
				for(unsigned ii=i;ii<cont-1;ii++)
					animations[ii]=animations[ii+1];
				cont--;
				break;
			}
		}
		m.unlock();

	}
	unsigned Click(){return 0;};
	void STANSetAnimation(char*name,CRD coord,float wigth,float TotalWigth,float TotalHeight,float x,float R,float G,float B,float speed){
		
		if(cont>=cant)
		 {
			 Animacion**NewAnimations=new Animacion*[cant+10];
			 cant=+10;
			 for(unsigned i=0;i<cont;i++)
				 NewAnimations[i]=animations[i];
			 delete[]animations;
			 animations=NewAnimations;
		 }
		if(wigth>this->Wigth)
		{
			this->Wigth=wigth;
			this->Height=this->Wigth;
		}
		animations[cont++]=new Animacion(name,coord,wigth,TotalWigth,TotalHeight,x,R,G,B,speed);
		
	};
	void NewTotalProp(float wigth,float height)
	{
		for(unsigned i=0;i<cont;i++)
			animations[i]->NewTotalProp(wigth,height);
	}
	void MoveOnReshape(bool reshape){
		for(unsigned i=0;i<cont;i++)
			animations[i]->reshapeBool=reshape;
	}
	void SetCoord(CRD coord)
	{
		Forms::SetCoord(coord);
		for(unsigned i=0;i<cont;i++)
			animations[i]->SetCoord(coord);
	}
	void NewCRD(CRD crd)
	{
		Forms::NewCRD(crd);
		for(unsigned i=0;i<cont;i++)
			animations[i]->NewCRD(crd);
	}
	void SetProfundidad(float profundidad)
	{
		Forms::SetProfundidad(profundidad);
		for(unsigned i=0;i<cont;i++)
			animations[i]->SetProfundidad(profundidad);
	}
	void ActivateDesactivate(bool ActDesact)
	{
		Forms::ActivateDesactivate(ActDesact);
		for(unsigned i=0;i<cont;i++)
			animations[i]->ActivateDesactivate(ActDesact);
	}
	

};