#pragma once
#include "_forms.h"

class _label:public _forms
{
protected:
	char*text;
	GLfloat R,G,B;
	unsigned LetterSize;
	//////////////FRIEND/////////////
	friend class _textBox;
	friend class _baseChRbBtn;
	friend class _textBoxCenter;
public:
	_label(char*name,char*escritura,CRD crd,unsigned LetterSize,double R,double G,double B,int*TotalWigth,int*TotalHeight):_forms(name,crd, 0, 20, TotalWigth, TotalHeight)
	{
		type=_LABEL;
		this->R=(GLfloat)R;
		this->G=(GLfloat)G;
		this->B=(GLfloat)B;
		this->LetterSize=LetterSize;
		this->text=new char[1];
		this->Set_Text(escritura);
	}
	~_label()
	{
		delete[]text;
	}
	bool PulsadoPasivo(int x,int y)
	{
		return false;
	}
	//SET//
	void Set_Letter_Size(unsigned letterSize){LetterSize=letterSize;}
	void Set_Color(double R,double G,double B)
	{
		this->R=(GLfloat)R;
		this->G=(GLfloat)G;
		this->B=(GLfloat)B;
	}
	virtual void Set_Text(char*text)
	{
		delete[]this->text;
		this->text=new char[strlen(text)+1];
		this->text[strlen(text)]=0;
		for(unsigned i=0;i<strlen(text);i++)
			this->text[i]=text[i];
		this->Wigth=Get_All_Wigth();
	}
	//GET//
	float Get_All_Wigth()
	{
		return (float)strlen(text)*(LetterSize==2?13:LetterSize==1?10:6);
	}
	char*Get_Text()
	{
		return text;
	}
	//PURAS//
	void _draw()
	{
		if(this->Draw)
		{
			glPushMatrix();
			glLoadIdentity();
			glColor3f(R,G,B);
			glRasterPos3f((GLfloat)(-*TotalWigth/2+coord.x),(GLfloat)(*TotalHeight/2-coord.y),(GLfloat)(2* *TotalWigth-1));
			
			
			if(!active)
			{
				glTranslatef((GLfloat)(-*TotalWigth/2+coord.x),(GLfloat)(*TotalHeight/2-coord.y),(GLfloat)2* *TotalWigth-1); 
				
				glColor3f((GLfloat)0.3,(GLfloat)0.3,(GLfloat)0.3);
				glBegin(GL_LINES);
				glVertex3f(0,0,(GLfloat)-0.9);
				glVertex3f((GLfloat)Wigth/4,Height-3,(GLfloat)-0.9);

				glVertex3f((GLfloat)Wigth/4,(GLfloat)0,(GLfloat)-0.9);
				glVertex3f((GLfloat)2*Wigth/4,(GLfloat)Height-3,(GLfloat)-0.9);

				glVertex3f((GLfloat)Wigth/2,(GLfloat)0,(GLfloat)-0.9);
				glVertex3f((GLfloat)3*Wigth/4,(GLfloat)Height-3,(GLfloat)-0.9);

				glVertex3f((GLfloat)3*Wigth/4,(GLfloat)0,(GLfloat)-0.9);
				glVertex3f((GLfloat)Wigth,(GLfloat)Height-3,(GLfloat)-0.9);
				glEnd();
				
			}
			for(unsigned int i=0;i<strlen(text);i++)
			{
				if(LetterSize==2)
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
				else if(LetterSize==1)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
				else if(LetterSize==0)
	 				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]);
		
			}
			glPopMatrix();
		}
	}
};

class _labelCenter:public _label,public _center
{
public:
	_labelCenter(char*name,char*escritura,CRD crd,unsigned LetterSize,double R,double G,double B,int*TotalWigth,int*TotalHeight,float*ParentWigth):_label(name,escritura,CRD(),LetterSize,R,G,B,TotalWigth,TotalHeight),_center(ParentWigth,this)
	{
		this->type=_LABELCENTER;
		this->New_CRD(crd);
	}
	~_labelCenter(){}
	void New_CRD(CRD crd)
	{
		_center::New_CRD(crd);
	}
	//SET//
	void Set_Text(char*text)
	{
		_label::Set_Text(text);
		New_CRD(this->coord);
	}
	////
	void Actualizar_ParentWigth()
	{
		_center::Actualizar_ParentWigth();
	}
	//PURAS//
	void _draw()
	{
		_label::_draw();	
	}
};