#pragma once
#include "Forms.h"
class RadioButton:public Forms
{
private:
	
	unsigned forma;
	GLfloat R,G,B;
	float letterWigtH;
public:
	bool Checket,SoloLabel;
	Label*l;
	RadioButton()
	{
		l=new Label();
	};
	RadioButton(char*RadioButtonName,CRD coord,char*escritura,float TotalWigth,float TotalHeight,bool Checket=false):Forms(RadioButtonName,coord,15,15,TotalWigth,TotalHeight){
		SoloLabel=false;
		this->Checket=Checket;
		l=new Label(RadioButtonName,escritura,*new CRD(coord.x+20,coord.y-2,coord.z),1,(GLfloat)0,(GLfloat)0,(GLfloat)0,TotalWigth,TotalHeight);
		t=Type::RADIOBUTTON;
		forma=0;
		R=B=0;
		G=1;
		this->letterWigtH=(float)(strlen(escritura)*10+20);
		this->Wigth=20;
		this->Height=20;
	};
	~RadioButton()
	{
		delete l;
	};
	void Draw(){
			if(!this->NoDraw)
			{
				 glPushMatrix();
				 glLoadIdentity();
				 glTranslatef((GLfloat)(-TotalWigth/2+coord.x),(GLfloat)(TotalHeight/2-coord.y),(GLfloat)2*this->TotalWigth-1+TotalProfundidad); 
       			 glColor3f((GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7);
				 if(!SoloLabel)
				 {
						if(!this->active)
						{
						   glBegin(GL_LINE_LOOP);
							glVertex3f(0,0,-1);
							glVertex3f(15,0,-1);
							glVertex3f(15,-15,-1);
							glVertex3f(0,-15,-1);
						    glEnd();
						    glBegin(GL_LINES);
							glVertex3f(0,0,-1);
							glVertex3f(15,-15,-1);
							glVertex3f(0,-7.5,-1);
							glVertex3f(7.5,-15,-1);
							glVertex3f(7.5,0,-1);
							glVertex3f(15,-7.5,-1);
						    glEnd();
						}
				else
				{
					if(this->Checket)
						glColor3f((GLfloat)0,(GLfloat)0,(GLfloat)0);
					else
						glColor3f((GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7);
					glBegin(GL_LINE_LOOP);
					glVertex3f(0,0,-1);
					glVertex3f(15,0,-1);
					glVertex3f(15,-15,-1);
					glVertex3f(0,-15,-1);
					glEnd();
					if(this->Checket)
					{
						glColor3f(this->active?this->R:(GLfloat)0.2,this->active?this->G:(GLfloat)0.2,this->active?this->B:(GLfloat)0.2);
						glBegin(GL_POLYGON);
						glVertex3f(0,0,-1);
						glVertex3f(15,0,-1);
						glVertex3f(15,-15,-1);
						glVertex3f(0,-15,-1);
						glEnd();
					}
				}
			}
		glPopMatrix();
		l->Draw();
		}
	};
	void NotChecket(){Checket=false;}
	void NewTotalProp(float wigth,float height){
		Forms::NewTotalProp(wigth,height);
		l->NewTotalProp(wigth,height);
	}
	void AddNewText(char*newText){
		l->AddNewText(newText);
		this->Wigth=(float)(strlen(newText)*10+20);
	};
	void CambiarChecket(){
		
		Checket?Checket=false:Checket=true;
		
	};
	void NewCRD(CRD crd){
		coord=CRD(crd);
		l->NewCRD(CRD(crd.x+20,crd.y,crd.z));
	}
	float LetterWigth(){return letterWigtH;}
	static void SetStyle(GLfloat R,GLfloat G,GLfloat B,unsigned forma,RadioButton*rb){
		rb->forma=forma;
		rb->R=R;
		rb->G=G;
		rb->B=B;
	};
	bool RBGetCheket(){return this->Checket;};	
	unsigned Click(){
		if(!Checket)
		   Checket=true;
		else
		   Checket=false;
	return (unsigned)t;};
	void SetCoord(float x,float y,float z){
		this->coord.x=x;
		this->coord.y=y;
		this->coord.z=z;
		this->l->coord.x=x+20;
		this->l->coord.y=y;
		this->l->coord.z=z;
	}
	 void SetCoord(CRD coord)
	 {
		this->coord=CRD(coord);
		this->l->coord=CRD(coord);
	}
	void SetColor(GLfloat R,GLfloat G,GLfloat B)
	{
		
		this->R=R;
		this->B=B;
		this->G=G;
		
	};
	void SetLabelColor(GLfloat R,GLfloat G,GLfloat B){
		this->l->SetColor(R,G,B);
	}
	static void SetSoloLabel(bool SoloLabeL,RadioButton*rb){rb->SoloLabel=SoloLabeL;};
};