#pragma once
#include "Forms.h"
class Label:public Forms
{
private:
	char*escritura;
	GLfloat R,G,B;
	unsigned LetterSize;
public:
	Label()
	{
		escritura=new char[1];
	};
	Label(char*name,char*escritura,CRD coord,unsigned LetterSize,GLfloat R,GLfloat G,GLfloat B,float TotalWigth,float TotalHeight):Forms(name,coord, 0, 20, TotalWigth, TotalHeight)
	{
		this->t=Type::LABEL;
		this->R=R;
		this->G=G;
		this->B=B;
		this->LetterSize=LetterSize;
		this->escritura=new char[1];
		this->AddNewText(escritura);
	}
	~Label()
	{
		delete[]escritura;
	};
	void AddNewText(char*newTexts)
	{
		
		delete[]escritura;
		escritura=new char[strlen(newTexts)+1];
		escritura[strlen(newTexts)]=0;
		for(unsigned i=0;i<strlen(newTexts);i++)
			escritura[i]=newTexts[i];
		this->Wigth=(float)(strlen(escritura)*10);
		
	}
	void NewCRD(CRD crd)
	{
		
		coord=CRD(crd);
		
	}
	void Draw()
	{
		
			if(!this->NoDraw)
				Forms::teXt(escritura,(GLfloat)coord.x,(GLfloat)coord.y,(GLfloat)R,(GLfloat)G,(GLfloat)B,LetterSize,this);
			
		
	}
	void SetColor(GLfloat R,GLfloat G,GLfloat B){
		
		this->R=R;
		this->B=B;
		this->G=G;
		
	};
	unsigned Click(){return 0;};


};