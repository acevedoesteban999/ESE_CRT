#pragma once
#include "_forms.h"
#include "_base_Chect_RadioButton.h"

class _radioButtonGroup:public _forms
{
private:
	_radioButton**radioButtons;
	unsigned cant,cont,ElementChect;

public:
	_radioButtonGroup(char*name,CRD coord,int*TotalWigth,int*TotalHeight):_forms(name,coord,0,0, TotalWigth, TotalHeight)
	{
		cont=0;
		cant=5;
		ElementChect=0;
		radioButtons=new _radioButton*[cant];
		type=_RADIOBUTTONGROUP;
	}
	~_radioButtonGroup()
	{
		for(unsigned i=0;i<cont;i++)
			delete radioButtons[i];
		delete[]radioButtons;
	}
	void _draw()
	{
		if(Draw)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef((GLfloat)(-*TotalWigth/2+coord.x),(GLfloat)(*TotalHeight/2-coord.y),(GLfloat)2* *TotalWigth-1); 
			//glColor3f(1,1,1);
			/*glBegin(GL_POLYGON);
			glVertex3f(-5,5,(GLfloat)-1.1);
			glVertex3f(Wigth,5,(GLfloat)-1.1);
			glVertex3f(Wigth,-Height-5,(GLfloat)-1.1);
			glVertex3f(-5,-Height-5,(GLfloat)-1.1);
			glEnd();*/
			glPopMatrix();
			for(unsigned i=0;i<cont;i++)
				radioButtons[i]->_draw();
		}
	}
	bool Pulsado(int x,int y)
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
	void New_CRD(CRD crd)
	{
		_forms::New_CRD(crd);
		for(unsigned i=0;i<cont;i++)
			radioButtons[i]->New_CRD(CRD(crd.x,crd.y+(20*(i+1))+(i?5:0),crd.z));
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
	void RadioButtonGroup_Add_RadioButton(char*RadioButtonName,char*escritura,bool Chect=false,bool active=true){
		if(cont&&Chect)
		{
			radioButtons[ElementChect]->Set_Check(false);
			ElementChect=cont;
		}
		if(!cont)
		{
			Chect=true;
			ElementChect=0;
		}
		if(this->Wigth<(float)(strlen(escritura)*13+20))
			this->Wigth=(float)(strlen(escritura)*13+20);
		_radioButton*rb=new _radioButton(RadioButtonName,escritura,CRD(this->coord.x,(double)(this->coord.y+20*(cont+1)+(cont?5:0)),this->coord.z),this->TotalWigth,this->TotalHeight,Chect);
		rb->active=active;
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
		Height+=rb->Height+5;
	}
	void RadioButtonGroup_Sub_RadioButton(char*nameRB)
	{	
		int i=Get_Element_by_Name(nameRB);
		if(i==-1)
			return;
		delete radioButtons[(unsigned)i];
		for(unsigned ii=(unsigned)i;ii<this->cont-1;i++)
			this->radioButtons[ii]=this->radioButtons[ii+1];
		cont--;
		Height-=18;
		if(cont&&ElementChect==i)
		{
			radioButtons[0]->Set_Check(true);
			ElementChect=0;
		}
		
	}
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
	float Get_All_Height()
	{
		return (float)(cont*20);
	}
};