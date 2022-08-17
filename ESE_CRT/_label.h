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
public:
	_label(char*name,char*escritura,CRD crd,unsigned LetterSize,GLfloat R,GLfloat G,GLfloat B,int*TotalWigth,int*TotalHeight):_forms(name,crd, 0, 20, TotalWigth, TotalHeight)
	{
		type=_LABEL;
		this->R=R;
		this->G=G;
		this->B=B;
		this->LetterSize=LetterSize;
		this->text=new char[1];
		this->Set_Text(escritura);
	}

	~_label()
	{
		delete[]text;
	}
	virtual void Set_Text(char*text)
	{
		delete[]this->text;
		this->text=new char[strlen(text)+1];
		this->text[strlen(text)]=0;
		for(unsigned i=0;i<strlen(text);i++)
			this->text[i]=text[i];
	}
	char*Get_Text()
	{
		return text;
	}
	void Set_Letter_Size(unsigned letterSize){LetterSize=letterSize;}
	void Set_Color(GLfloat R,GLfloat G,GLfloat B)
	{
		this->R=R;
		this->G=G;
		this->B=B;
	}
	float Get_All_Wigth()
	{
		return (float)strlen(text)*(LetterSize==2?13:LetterSize==1?10:6);
	}
	void _draw()
	{
		if(this->Draw)
		{
			glPushMatrix();
			glLoadIdentity();
			glColor3f(R,G,B);
			glRasterPos3f((GLfloat)(-*TotalWigth/2+coord.x),(GLfloat)(*TotalHeight/2-coord.y),(GLfloat)(2* *TotalWigth-1));
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

class _labelCenter:public _label
{
private:
	float*ParentWigth;
public:
	_labelCenter(char*name,char*escritura,CRD crd,unsigned LetterSize,GLfloat R,GLfloat G,GLfloat B,int*TotalWigth,int*TotalHeight,float*ParentWigth):_label(name,escritura,CRD(),LetterSize,R,G,B,TotalWigth,TotalHeight)
	{
		this->type=_LABELCENTER;
		this->ParentWigth=ParentWigth;
		this->New_CRD(crd);
	}
	~_labelCenter(){}
	void Set_Text(char*text)
	{
		_label::Set_Text(text);
		New_CRD(this->coord);
	}
	void New_CRD(CRD crd)
	{
		_forms::New_CRD(crd.AddX(*ParentWigth/2- Get_All_Wigth()/2));
	}
	void _draw()
	{
		_label::_draw();	
	}
};