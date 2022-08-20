#pragma once
#include "_forms.h"
#include "_label.h"
enum _textBoxType
{
  _DEFAULT,_UNSIGNEDCONTENT,_INTCONTENT,_FLOATCONTENT,_CHARCONTENT
};
class _textBox:public _forms
{
protected:
	_label label;
	bool escribiendo;
	bool punto;
	_textBoxType TextBoxType;
	unsigned cont,max;
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
		Set_Text(Escritura);
		type=_TEXTBOX;
	}
	~_textBox(){}
	virtual void New_CRD(CRD crd)
	{
		_forms::New_CRD(crd);
		label.New_CRD(crd);
	}
	bool Pulsado(int x,int y)
	{
		if(escribiendo)
		{
			escribiendo=false;
			Set_Color(0,0,0);
		}
		if(_forms::Pulsado(x,y,this))
		{
			Set_Color(0,0,1);
			escribiendo=true;
			return true;
		}
		return false;
	}
	//ADD//
	virtual void TextBox_Add_Caracter(char caracter)
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
	//SUB//
	virtual void TextBox_Sub_Caracter()
	{
		if(cont)
		{	
			if(TextBoxType==_textBoxType::_FLOATCONTENT&&label.text[cont-1]=='.')
				punto=false;
               label.text[--cont]=0;
		}
	}
	//SET//
	void Set_Text(char*text=nullptr)
	{
		char*newText;
		if(text==nullptr)
		{
			newText=new char[cont+1];
			for(unsigned i=0;i<cont;i++)
				newText[i]=label.text[i];
		}
		else
		{
			cont=strlen(text);
			newText=text;
		}
		max=(unsigned)this->Wigth/9;
		delete[]label.text;
		label.text=new char[max+1];
		unsigned contMax=(cont>max?max:cont);
		for(unsigned i=0;i<contMax;i++)
			label.text[i]=newText[i];
		label.text[contMax]=0;
		if(text==nullptr)
			delete[]newText;
		cont=contMax;
	}
	void Set_Color(float R,float G,float B)
	{
		label.Set_Color(R,G,B);
	}
	void Set_Active(bool Active)
	{
		_forms::Set_Active(Active);
		label.Set_Active(Active);
	}
	//GET//
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
	////
	virtual void Actualizar_ParentWigth()
	{
		Set_Text();	
	}
	//PURAS//
	void _draw()
	{
			if(this->Draw)
			{
				glPushMatrix();
				glLoadIdentity();
				glTranslatef((GLfloat)(-*TotalWigth/2+coord.x),(GLfloat)(*TotalHeight/2-coord.y),(GLfloat)2* *TotalWigth-1); 
				if(PulsadoPasivoBool&&active)
					glColor3f((GLfloat)0.57,(GLfloat)0.57,(GLfloat)0.57);
				else
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
};
class _textBoxCenter:public _textBox,public _center
{
public:
	_textBoxCenter(char*name,char*Escritura,CRD crd,float wigth,int*TotalWigth,int*TotalHeight,float*ParentWigth,_textBoxType TextBoxType=_DEFAULT):_textBox(name,Escritura,crd,wigth,TotalWigth,TotalHeight),_center(ParentWigth,this)
	{
		this->type=_TEXTBOXCENTER;
	}
	~_textBoxCenter(){}
	void New_CRD(CRD crd)
	{
		_center::New_CRD(crd);
		label.New_CRD(crd);
	}
	
	//ADD//
	void TextBox_Add_Caracter(char caracter)
	{
		_textBox::TextBox_Add_Caracter(caracter);
		Actualizar_ParentWigth();
	}
	//SUB//
	void TextBox_Sub_Caracter()
	{
		_textBox::TextBox_Sub_Caracter();
		Actualizar_ParentWigth();
	}
	////
	void Actualizar_ParentWigth()
	{
		_textBox::Actualizar_ParentWigth();
		_center::Actualizar_ParentWigth(&label,this);
		
	}
};