#pragma once
#include "_forms.h"
#include "_label.h"
enum _textBoxType
{
  _DEFAULT,_UNSIGNEDCONTENT,_INTCONTENT,_FLOATCONTENT,_CHARCONTENT
};
class _textBox:public _forms
{
private:
	_label label;
	bool escribiendo;
	bool punto;
	//TimeDuration tim;
	_textBoxType TextBoxType;
	unsigned cont,max;
	//bool dosClicks;
public:
	_textBox(char*name,char*Escritura,CRD crd,float wigth,int*TotalWigth,int*TotalHeight,_textBoxType TextBoxType=_DEFAULT):_forms(name,crd,0,20,TotalWigth,TotalHeight),label("LabelBase","",coord.AddX(20),1,0,0,0,TotalWigth,TotalHeight)
	{
		this->TextBoxType=TextBoxType;
		punto=false;
		if(wigth<40)
			this->Wigth=40;
		else if(wigth<strlen(Escritura)*10)
			this->Wigth=(float)(strlen(Escritura)*10);
		else
			this->Wigth=wigth;
		max=(unsigned)Wigth/9;
		delete[]label.text;
		label.text=new char[max+1];
		
		cont=strlen(Escritura);
		if(cont>max)
			cont=max;
			
		label.text[cont]=0;
		for(unsigned i=0;i<cont;i++)
			label.text[i]=Escritura[i];
		type=_TEXTBOX;
	}
	~_textBox(){}
	void _draw()
	{
			if(this->Draw)
			{
				glPushMatrix();
				glLoadIdentity();
				glTranslatef((GLfloat)(-*TotalWigth/2+coord.x),(GLfloat)(*TotalHeight/2-coord.y),(GLfloat)2* *TotalWigth-1); 
				glColor3f((GLfloat)0.97,(GLfloat)0.97,(GLfloat)0.97);
				glBegin(GL_POLYGON);
				glVertex3f(0,-1.5,-1);
				glVertex3f((GLfloat)Wigth,-1.5,-1);
				glVertex3f((GLfloat)Wigth,(GLfloat)(Height-1.5),-1);
				glVertex3f(0,(GLfloat)(Height-1.5),-1);
				glEnd();
				if(!active)
				{
					glColor3f((GLfloat)0.3,(GLfloat)0.3,(GLfloat)0.3);
					glBegin(GL_LINES);
					glVertex3f(0,0,(GLfloat)-0.9);
					glVertex3f((GLfloat)Wigth/4,-Height,(GLfloat)-0.9);

					glVertex3f((GLfloat)Wigth/4,(GLfloat)0,(GLfloat)-0.9);
					glVertex3f((GLfloat)2*Wigth/4,(GLfloat)-Height,(GLfloat)-0.9);

					glVertex3f((GLfloat)Wigth/2,(GLfloat)0,(GLfloat)-0.9);
					glVertex3f((GLfloat)3*Wigth/4,(GLfloat)-Height,(GLfloat)-0.9);

					glVertex3f((GLfloat)3*Wigth/4,(GLfloat)0,(GLfloat)-0.9);
					glVertex3f((GLfloat)Wigth,(GLfloat)-Height,(GLfloat)-0.9);
					glEnd();
				  
				}
				glLoadIdentity();
				//TextAlignCenter(escritura,(GLfloat)coord.x,(GLfloat)coord.y,active?(GLfloat)0:(GLfloat)0.2,active?(GLfloat)0:(GLfloat)0.2,active?(GLfloat)0:(GLfloat)0.2,1,this);
				label._draw();
			}
			glPopMatrix();	


	}
	bool Pulsado(int x,int y)
	{
		if(escribiendo)
			escribiendo=false;
		if(_forms::Pulsado(x,y,this))
		{
			escribiendo=true;
			return true;
		}
		return false;
	}
	void New_CRD(CRD crd)
	{
		_forms::New_CRD(crd);
		label.New_CRD(crd);
	}
	/*void New_Total_Prop(float TotalWigth,float TotalHeight)
	{
		_forms::New_Total_Prop(TotalWigth,TotalHeight);
		label.New_Total_Prop(TotalWigth,TotalHeight);
	}
	void New_All_Prop(CRD  crd,float wigth,float height,float TotalWigth,float TotalHeight)
	{
		New_CRD(crd);
		New_Prop(wigth,height);
		New_Total_Prop(TotalWigth,TotalHeight);
		label.New_CRD(crd);
		label.New_Prop(wigth,height);
		label.New_Total_Prop(TotalWigth,TotalHeight);
	}*/
	void TextBox_Add_Caracter(char caracter)
	{
		if(cont>=max)
			return;
		switch(TextBoxType)
		{
		case _textBoxType::_UNSIGNEDCONTENT:
			if(!isdigit(caracter))
			{
				return;
			}
			break;
		case _textBoxType::_INTCONTENT:
			if(!isdigit(caracter))
			{
				if(caracter!='-'||cont!=0)
					return;
			}
			break;
		case _textBoxType::_FLOATCONTENT:
			if(!isdigit(caracter))
			{
				if(caracter=='.'&&!punto)
					punto=true;
				else if(caracter=='.'&&punto)
					return;
                else if(caracter!='-'||cont!=0)
					return;
			}
			break;
		case _textBoxType::_CHARCONTENT:
			if(!isalpha(caracter))
				return;
			break;	
		}
		label.text[cont++]=caracter;
		label.text[cont]=0;
	}
	void TextBox_Sub_Caracter()
	{
		if(cont)
		{	
			if(TextBoxType==_textBoxType::_FLOATCONTENT&&label.text[cont-1]=='.')
				punto=false;
               label.text[--cont]=0;
		}
	}
	bool TextBox_Get_Escribiendo()
	{
		return escribiendo;
	}
	char* Get_Text()
	{
		return label.Get_Text();
	}
	float Get_All_Wigth()
	{
		return label.Get_All_Wigth()+20;
	}
	void New_Wigth(float Wigth)
	{
		this->Wigth=(float)(Wigth-Wigth*0.05);
		char*newText=new char[cont+1];
		for(unsigned i=0;i<cont;i++)
			newText[i]=label.text[i];

		max=(unsigned)this->Wigth/9;
		delete[]label.text;
		label.text=new char[max+1];
		unsigned contMax=(cont>max?max:cont);
		for(unsigned i=0;i<contMax;i++)
			label.text[i]=newText[i];
		label.text[contMax]=0;
		delete[]newText;
		cont=contMax;
	}

};