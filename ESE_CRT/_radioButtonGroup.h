#pragma once
#include "_forms.h"
#include "_base_Chect_RadioButton.h"

class _radioButtonGroup:public _forms
{
protected:
	_radioButton**radioButtons;
	unsigned cant,cont;
	int ElementChect;
public:
	_radioButtonGroup(char*name,CRD coord,int*TotalWigth,int*TotalHeight):_forms(name,coord,0,0, TotalWigth, TotalHeight)
	{
		cont=0;
		cant=5;
		ElementChect=-1;
		radioButtons=new _radioButton*[cant];
		type=_RADIOBUTTONGROUP;
	}
	~_radioButtonGroup()
	{
		for(unsigned i=0;i<cont;i++)
			delete radioButtons[i];
		delete[]radioButtons;
	}
	virtual bool Pulsado(int x,int y)
	{
		if(_forms::Pulsado(x,y,this,true))
		{
			for(unsigned i=0;i<cont;i++)
			{
				if(radioButtons[i]->Pulsado(x,y))
				{
					if(i==ElementChect)
						radioButtons[i]->Set_Check(true);
					else
						radioButtons[ElementChect]->Set_Check(false);
					ElementChect=i;
				}
				else if(i!=ElementChect)
					radioButtons[i]->Set_Check(false);
			}
			return true;	
		}
		return false;
	}
	bool PulsadoPasivo(int x,int y)
	{
		for(unsigned i=0;i<cont;i++)
			if(radioButtons[i]->PulsadoPasivo(x,y))
				return true;
		return false;
	}
	void New_CRD(CRD crd)
	{
		_forms::New_CRD(crd);
		float SumHeight=0;
		for(unsigned i=0;i<cont;i++)
		{
			SumHeight+=radioButtons[i]->Get_All_Height();
			radioButtons[i]->New_CRD(CRD(crd.x,crd.y+(SumHeight)+(i?10:0),crd.z));
			SumHeight+=10;
		}
	}
	/*void New_Total_Prop(float TotalWigth,float TotalHeight)
	{
		_forms::New_Total_Prop(TotalWigth,TotalHeight);
		for(unsigned i=0;i<cont;i++)
			radioButtons[i]->New_Total_Prop(TotalWigth,TotalHeight);
	}
	void New_All_Prop(CRD  crd,float wigth,float height,float TotalWigth,float TotalHeight)
	{
		New_CRD(crd);
		New_Prop(wigth,height);
		New_Total_Prop(TotalWigth,TotalHeight);
	}*/
	//ADD//
	virtual void RadioButtonGroup_Add_RadioButton(char*RadioButtonName,char*escritura,bool Chect=false,bool active=true)
	{
		if(cont&&Chect&&this->active)
		{
			radioButtons[ElementChect]->Set_Check(false);
			ElementChect=cont;
		}
		else if(!cont&this->active)
		{
			Chect=true;
			ElementChect=0;
		}
		else if(!this->active)
		{
			ElementChect=-1;
			Chect=false;
		}
		
		if(this->Wigth<(float)(strlen(escritura)*10+15))
			this->Wigth=(float)(strlen(escritura)*10+15);
		
		_radioButton*rb=new _radioButton(RadioButtonName,escritura,CRD(),this->TotalWigth,this->TotalHeight,Chect);
		
		if(!this->active)
			rb->Set_Active(false);
		else
			rb->Set_Active(active);
		
		float coordY=0;
		if(cont)
			coordY+=(float)radioButtons[cont-1]->coord.y+10+rb->Get_All_Height();
		else
			coordY+=(float)coord.y+rb->Get_All_Height();

		rb->New_CRD(CRD(coord.x,coordY,coord.z));
		Height+=rb->Get_All_Height()+10;
		
		if(cont>=cant)
		{
			cant+=5;
			_radioButton**newRB=new _radioButton*[cant];
			
			for(unsigned i=0;i<this->cont;i++)
				newRB[i]=radioButtons[i];
			delete[]this->radioButtons;
			radioButtons=newRB;
		}
		radioButtons[cont++]=rb;
	}
	//SUB//
	virtual void RadioButtonGroup_Sub_RadioButton(char*nameRB)
	{	
		int i=Get_Element_by_Name(nameRB);
		if(i==-1)
			return;
		Height-=radioButtons[(unsigned)i]->Get_All_Height();
		delete radioButtons[(unsigned)i];
		for(unsigned ii=(unsigned)i;ii<this->cont-1;i++)
			this->radioButtons[ii]=this->radioButtons[ii+1];
		cont--;
		
		if(cont&&ElementChect==i)
		{
			radioButtons[0]->Set_Check(true);
			ElementChect=0;
		}
		if(!cont)
			ElementChect=-1;
	}
	//SET//
	virtual void Set_Active(bool Active)
	{
		_forms::Set_Active(Active);
		for(unsigned i=0;i<cont;i++)
			radioButtons[i]->Set_Active(Active);
		if(!Active)
		{
			if(ElementChect!=-1)
				radioButtons[(unsigned)ElementChect]->Set_Check(false);
			ElementChect=-1;
		}
		else
		{
			if(cont)
			{
				ElementChect=0;
				radioButtons[0]->Set_Check(true);
			}
		}
	}
	void Set_Element_Chect(unsigned ElementToChect)
	{
		if(ElementToChect==ElementChect)
			return;
		if(ElementToChect<cont)
		{
			ElementChect=ElementToChect;
			for(unsigned i=0;i<cont;i++)
			{
				if(i==ElementChect)
					radioButtons[i]->Set_Check(true);
				else
					radioButtons[i]->Set_Check(false);
			}	
		}
	}
	//GET//
	int Get_Element_by_Name(char*name)
	{
		for(unsigned i=0;i<cont;i++)
			if(!strcmp(name,radioButtons[i]->name))
				return (int)i;
		return -1;
	}
	float Get_All_Wigth()
	{
		float toReturn=0;
		for(unsigned i=0;i<cont;i++)
			if(radioButtons[i]->Get_All_Wigth()>toReturn)
				toReturn=radioButtons[i]->Get_All_Wigth();
		return toReturn;
	}
	int Get_Element_Chect()
	{
		return ElementChect;
	}
	//PURAS//
	void _draw()
	{
		if(Draw)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef((GLfloat)(-*TotalWigth/2+coord.x),(GLfloat)(*TotalHeight/2-coord.y),(GLfloat)2* *TotalWigth-1); 	
			/*if(!active)
			{
				
				glColor3f((GLfloat)0.3,(GLfloat)0.3,(GLfloat)0.3);
				glBegin(GL_LINES);
				
				glVertex3f(0,-Height+3,(GLfloat)-0.9);
				glVertex3f((GLfloat)Wigth/4,0,(GLfloat)-0.9);

				glVertex3f(0,(GLfloat)-Height+3,(GLfloat)-0.9);
				glVertex3f((GLfloat)Wigth/4,0,(GLfloat)-0.9);

				glVertex3f((GLfloat)Wigth/4,(GLfloat)-Height+3,(GLfloat)-0.9);
				glVertex3f((GLfloat)2*Wigth/4,0,(GLfloat)-0.9);

				glVertex3f((GLfloat)2*Wigth/4,(GLfloat)-Height+3,(GLfloat)-0.9);
				glVertex3f((GLfloat)3*Wigth/4,0,(GLfloat)-0.9);

				glVertex3f((GLfloat)3*Wigth/4,(GLfloat)-Height+3,(GLfloat)-0.9);
				glVertex3f((GLfloat)4*Wigth/4,0,(GLfloat)-0.9);
				glEnd();
		
			}*/
			glPopMatrix();
			for(unsigned i=0;i<cont;i++)
				radioButtons[i]->_draw();
		}
	}
};

class _radioButtonGroupFree:public _radioButtonGroup
{
public:
	_radioButtonGroupFree(char*name,CRD coord,int*TotalWigth,int*TotalHeight):_radioButtonGroup(name,coord,TotalWigth,TotalHeight)
	{
		this->type=_RADIOBUTTONGROUPFREE;
	}
	~_radioButtonGroupFree(){}
	//ADD//
	void RadioButtonGroup_Add_RadioButton(char*RadioButtonName,char*escritura,bool Chect=false,bool active=true)
	{
		if(this->Wigth<(float)(strlen(escritura)*10+15))
			this->Wigth=(float)(strlen(escritura)*10+15);
		
		_radioButton*rb=new _radioButton(RadioButtonName,escritura,CRD(),this->TotalWigth,this->TotalHeight,Chect);
		
		if(!this->active)
			rb->Set_Active(false);
		else
			rb->Set_Active(active);
		
		float coordY=0;
		if(cont)
			coordY+=(float)radioButtons[cont-1]->coord.y+10+rb->Get_All_Height();
		else
			coordY+=(float)coord.y+rb->Get_All_Height();

		rb->New_CRD(CRD(coord.x,coordY,coord.z));
		
		Height+=rb->Get_All_Height()+10;
		
		if(cont>=cant)
		{
			cant+=5;
			_radioButton**newRB=new _radioButton*[cant];
			
			for(unsigned i=0;i<this->cont;i++)
				newRB[i]=radioButtons[i];
			delete[]this->radioButtons;
			radioButtons=newRB;
		}
		radioButtons[cont++]=rb;
	}
	//SUB//
	void RadioButtonGroup_Sub_RadioButton(char*nameRB)
	{	
		int i=Get_Element_by_Name(nameRB);
		if(i==-1)
			return;
		Height-=radioButtons[(unsigned)i]->Get_All_Height();
		delete radioButtons[(unsigned)i];
		for(unsigned ii=(unsigned)i;ii<this->cont-1;i++)
			this->radioButtons[ii]=this->radioButtons[ii+1];
		cont--;
		if(ElementChect!=-1)
		{
			radioButtons[(unsigned)ElementChect]->Set_Check(false);
			ElementChect=-1;
		}

	}
	//SET//
	void Set_Active(bool Active)
	{
		_forms::Set_Active(Active);
		for(unsigned i=0;i<cont;i++)
			radioButtons[i]->Set_Active(Active);
		if(!Active&&ElementChect!=-1)
		{
			radioButtons[(unsigned)ElementChect]->Set_Check(false);
			ElementChect=-1;
		}
			
		
	}
	////
	bool Pulsado(int x,int y)
	{
		if(_forms::Pulsado(x,y,this,true))
		{
			for(unsigned i=0;i<cont;i++)
			{
				if(radioButtons[i]->Pulsado(x,y))
				{
					if(ElementChect!=-1&&i!=ElementChect)
						radioButtons[(unsigned)ElementChect]->Set_Check(false);
					if(radioButtons[i]->Get_Chect())
					{		
						ElementChect=i;
					}
					else 
						ElementChect=-1;
					return true;
				}
			}
		}
		return false;
	}
	
};