#pragma once
#include "_baseArrayForms.h"
#include "_forms.h"

class _baseLayouts:public _baseArrayForms, public _forms
{
public:
	_baseLayouts(char*name,CRD crd,int*TotalWigth,int*TotalHeight):_forms(name,crd,0,0,TotalWigth,TotalHeight),_baseArrayForms()
	{
	}
	~_baseLayouts()
	{
	}
	//NEW//
	virtual void New_CRD(CRD crd)
	{
		_forms::New_CRD(crd);
		for(unsigned i=0;i<cont;i++)
			forms[i]->New_CRD(CRD(crd));
	}
	void New_CRD(char*name,CRD crd)
	{
		_baseArrayForms::New_CRD(name,crd);
	}
	void New_Wigth(float Wigth)
	{
		this->Wigth=Wigth;
		for(unsigned i=0;i<cont;i++)
			if(forms[i]->type==_TEXTBOX)
				forms[i]->New_Wigth(Wigth);
			else if(forms[i]->type==_LABELCENTER)
				forms[i]->New_CRD(forms[i]->coord);
	}
	void Clear()
	{
		_baseArrayForms::Clear();
		Wigth=0;
		Height=0;
	}
	//ADD//
	void  Add_Label_Free(char*name,char*escritura,CRD crd,bool Draw=true,unsigned LetterSize=1,GLfloat R=0,GLfloat G=0,GLfloat B=0)
	{
		_label*lF=new _label(name,escritura,crd,LetterSize,R,G,B,this->TotalWigth,this->TotalHeight);
		lF->Set_Draw(Draw);
		Add_Element(lF);
	}
	void Add_Label(char*name,char*escritura,unsigned LetterSize=1,GLfloat R=0,GLfloat G=0,GLfloat B=0)
	{
		_label*l=new _label(name,escritura,CRD(),LetterSize,R,G,B,this->TotalWigth,this->TotalHeight);
		Add_Element(l);
	}
	void Add_LabelCenter(char*name,char*escritura,unsigned LetterSize=1,GLfloat R=0,GLfloat G=0,GLfloat B=0)
	{
		_labelCenter*lC=new _labelCenter(name,escritura,CRD(),LetterSize,R,G,B,TotalWigth,TotalHeight,&this->Wigth);
		Add_Element(lC);

	}
	void Add_TextBox(char*name,char*escritura,_textBoxType TextBoxType=_DEFAULT)
	{
		_textBox*tb=new _textBox(name,escritura,CRD(),(float)(this->Wigth-this->Wigth*0.05),this->TotalWigth,this->TotalHeight,TextBoxType);
		Add_Element(tb);
	}
	void Add_ChectBox(char*name,char*Escritura,bool Chect=false)
	{
		_chectBox* cb=new _chectBox(name,Escritura,CRD(),this->TotalWigth,this->TotalHeight,Chect);
		Add_Element(cb);
	}
	void Add_RadioButtonGroup(char*name)
	{
		_radioButtonGroup* rbg=new _radioButtonGroup(name,CRD(),this->TotalWigth,this->TotalHeight);
		Add_Element(rbg);
	}
	void Add_RadioButton_To_RadioButtonGroup(char*RadioButtonGroupName,char*RadioButtonName,char*Escritura,bool Chect=false)
	{
		int i=Get_Element_By_Name(RadioButtonGroupName);
		if(i==-1)
			return;
		forms[i]->RadioButtonGroup_Add_RadioButton(RadioButtonName,Escritura,Chect);
		this->Height+=25;
	}
	void Add_ButtonLabel(char*name,char*Escritura)
	{
		_buttonLabel*btnL=new _buttonLabel(name,Escritura,CRD(),TotalWigth,TotalHeight);
		Add_Element(btnL);
	}
	void Add_ButtonAccept(char*name)
	{
		_buttonAccept*btnA=new _buttonAccept(name,CRD(),this->TotalWigth,this->TotalHeight);
		Add_Element(btnA);
	}
	void Add_ButtonCancel(char*name)
	{
		_buttonCancel*btnC=new _buttonCancel(name,CRD(),this->TotalWigth,this->TotalHeight);
		Add_Element(btnC);
	}
	void Add_ButtonsAcceptCancel(char*name)
	{
		_buttonsAcceptCancel*btnAC=new _buttonsAcceptCancel(name,CRD(),TotalWigth,TotalHeight,&this->Wigth);
		Add_Element(btnAC);
	}

	void Add_ButtonX2(char*name,char*Escritura1,char*Escritura2)
	{
		//_buttonsX2*btnX2=new _buttonsX2(name,Escritura1,Escritura2,,coord,TotalWigth,TotalHeight,&this->Wigth);
	}

	//TEXTBOX//
	bool TextBox_Get_Escribiendo()
	{
		return _baseArrayForms::TextBox_Get_Escribiendo();
	}
	void TextBox_Add_Caracter(char caracter)
	{
		_baseArrayForms::TextBox_Add_Caracter(caracter);
	}
	void TextBox_Sub_Caracter()
	{
		_baseArrayForms::TextBox_Sub_Caracter();
	}
	//SET//
	void Set_Draw(bool Draw)
	{
		_forms::Set_Draw(Draw);
	}
	void Set_Draw(char*name,bool Draw)
	{
		_baseArrayForms::Set_Draw(name,Draw);
	}
	void Set_Color(GLfloat R,GLfloat G,GLfloat B)
	{
		_forms::Set_Color(R,G,B);
	}
	void Set_Color(char*name,GLfloat R,GLfloat G,GLfloat B)
	{
		_baseArrayForms::Set_Color(name,R,G,B);
	}
	void Set_Text(char*name,char*text)
	{
		_baseArrayForms::Set_Text(name,text);
	}
	//GET//
	char* Get_Text(char*name)
	{
		return _baseArrayForms::Get_Text(name);
	}
	//PURAS//
	virtual bool Pulsado(int x,int y)=0;
	virtual void _draw()=0;
};