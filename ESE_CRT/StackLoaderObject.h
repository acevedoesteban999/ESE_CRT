#pragma once
#include "LoaderObject.h"
class StackLoaderObject
{
public:
	//////////////////////////////////////////////////VARIABLES////////////////////////
	int contLoaderObject;
    int cantLoaderObject;
	GLfloat*DataESE;
	//double*CoordReales;
	bool Salir,errorCarga;
	/////////DINAMICOS///////////////
    LoaderObject**Stack;
	///////////////////////////////////////////////////METODOS///////////////////////////

	///////////////CONSTRUCTORES Y DESTUCTOR//////
	StackLoaderObject(GLfloat*DataESE=nullptr)
	{
		this->DataESE=DataESE;
		contLoaderObject=0;
		cantLoaderObject=10;
		Stack=new LoaderObject*[cantLoaderObject];//inicializo el arreglo
		//CoordReales=new double[3];
		Salir=errorCarga=false;
	};
	~StackLoaderObject()
	{
		//delete DataESE; no delete porq se va a eliminar en otra zona
		//delete[]CoordReales;
		for(unsigned i=0;i<(unsigned)contLoaderObject;i++)
			delete Stack[i];
		delete[]Stack;
	}
	////////////////PUSH/////////////////////////
	static void push(char*c,StackLoaderObject*slo,double R,double G,double B)
	{
		//agrego un nuevo LoaderObject(.obj con direccion *c) en el Stack 
		if(R>1)//evito errores en el color ya q tiene q ser 0<(GLfloat)Color<1
			R=1;
		if(R<0)
			R=0;
		if(G>1)
			G=1;
		if(G<0)
			G=0;
		if(B>1)
			B=1;
		if(B<0)
			B=0;
		LoaderObject*newLoaderObject=new LoaderObject(c,R,G,B);
	
		if(newLoaderObject->empty==false)
		{
		   if(slo->contLoaderObject>=slo->cantLoaderObject)//aumento el tamaño del arreglo en caso de ser necesario
			  {
			   LoaderObject**newdata=new LoaderObject*[slo->cantLoaderObject+10];
			   slo->cantLoaderObject+=10;
			   for(int i=0;i<slo->cantLoaderObject;i++)
				   newdata[i]=slo->Stack[i];
			   delete[]slo->Stack;
			   slo->Stack=newdata;
 			   }
		   slo->Stack[slo->contLoaderObject++]=newLoaderObject;
	   
		} 
		else
		{
			slo->errorCarga=true;
		}
};
	static void pushByTxt(char*name,StackLoaderObject*slo){
   //agrego todos los .obj del txt "Entrada_de_Modelos" 
	fstream f;
    f.open(name,ios::in);
    char c[100];
     if(f.is_open())
        {
			bool noCargarObj=false;
			while(!f.eof()&&!slo->Salir)
		    {
	           f.getline(c,100);
			   if(c[0]=='#')
			   {
				   noCargarObj=true;
			   }
			   else if(c[0]=='&'&&!noCargarObj)
			   {
				   string name_obj(c);
				   name_obj=name_obj.substr(1,name_obj.find_first_of(" "));
				   string s(c);
				   s=s.substr(name_obj.length()+1,s.length()-name_obj.length());
				   string r=s.substr(0,s.find_first_of(" "));
				   s=s.substr(s.find_first_of(" ")+1,s.length()-s.find_first_of(" "));
				   string g=s.substr(0,s.find_first_of(" "));
				   s=s.substr(s.find_first_of(" ")+1,s.length()-s.find_first_of(" "));
				   string b=s.substr(0,s.find_first_of(" "));
				   slo->push((char*)name_obj.c_str(),slo,(double)atof(r.c_str()),(double)atof(g.c_str()),(double)atof(b.c_str()));
				}
			}
		}
		else
		{
			 cout<<"Error:----X---->'"<<name<<endl;//si no existe el archivo en esa direccion
			slo->errorCarga=true;
		}
		f.close();		   
};
	///////////////DRAWS//////////////////////////
	static void smallEjeCoordSLO(GLfloat size){
	//pinto un eje de coordenada x,y,z

	
		glColor3f(1.0,0.0,0.0);

	glBegin(GL_LINES);
	glVertex3f(size,0.0,0.0);
	glVertex3f(0.0,0.0,0.0);
	glEnd();

	
		glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0,size,0.0);
	glVertex3f(0.0,0.0,0.0);
	glEnd();

	
		glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0,0.0,size);
	glVertex3f(0.0,0.0,0.0);
	glEnd();
	

}
	static void draw(StackLoaderObject*slo,int i){
	//posiciono,pinto y trasaldo(para q el proximo se pueda posicionar)ademas pinto los ejes de coordenadas de guia
	
		glPushMatrix();
		if(i==-1)
		{
			for(int ii=0;ii<slo->contLoaderObject;ii++)
			   slo->RotateAndMoveArticAndDraw(ii,slo);	
		}	
		else if(i<=slo->contLoaderObject&&i>=0) 
		{
			slo->Stack[i]->pintarse(slo->Stack[i]);
			StackLoaderObject::smallEjeCoordSLO(25);
		}
		else if(i==-2)
		{
	
		}
		glPopMatrix();
	
		//glPushMatrix();
		/////////////////////////////////////////////////////////////////////
		//glLoadIdentity();
		////Explicacion:la coordenada q me devuelve la matrx de modelview tiene q ser sacada ahora
		////porq la matriz ya viene de antes;del dispaly con una rotacion y un whell distintas de la del 00
		////por eso se carga la identidad,no se puede cargar antes,debido a q los objetos se pintarian esaticos en la palntalla
		////por lo tanto se sacan las coordenadas ahora;
		//for(int ii=0;ii<=slo->contLoaderObject;ii++)
		//		   {   
		//			    slo->RotateAndMoveArticAndDraw(ii,slo);
		//           }
		//GLdouble mModel[16];
		//glGetDoublev(GL_MODELVIEW_MATRIX,mModel);
		//slo->CoordReales[0]=(double)mModel[12];
		//slo->CoordReales[1]=(double)mModel[13];
		//slo->CoordReales[2]=(double)mModel[14];
		//glPopMatrix();
		//37.481040954589844 361.38070678710937 472.38644409179687
};
	static void RotateAndMoveArticAndDraw(int caso,StackLoaderObject*slo){
	//procedimientos(moviminto segun Data) q se hacen con aterioridad para q quede pintado en la posicion q se desee
	
	//cada caso corresponde con la posicion del LoaderObject en el Stack
	switch (caso+1)
	{
	case 1:
	case 3:
	case 5:
	case 7:
		break;
	case 2:
		glTranslatef(slo->DataESE[0],0,0);
		break;
	case 4:
		glTranslatef(0,slo->DataESE[1],0);
		break;
	case 6:
		glTranslatef(0,0,slo->DataESE[2]);
		break;
/*
	//case 2:
	//	glTranslatef(0.0,0.0,(GLfloat)51.000);		
	//	break;

	//case 3:
	//	//////////////////////////////////////
	//	glRotatef(slo->DataESE[0],0.0,0.0,1.0);	
	//	break;
	//case 5:
	//	glTranslatef(0.0,0.0,(GLfloat)37.300);
	//	glRotatef(-90,1,0,0);
	//	//////////////////////////////////////
	//	glRotatef(slo->DataESE[1],0.0,0.0,1.0);	
	//	break;			

	//case 7:
	//	glTranslatef((GLfloat)150.00,0.0,0.0);
	//	//////////////////////////////////////
	//	glRotatef(slo->DataESE[2],0.0,0.0,1.0);	
	//	break;

	//case 9:
	//	glTranslatef((GLfloat)228.959,0.0,(GLfloat)-25.802);	
	//	break;

	//case 10:
	//	//////////////////////////////////////
	//	glRotatef(slo->DataESE[3],0.0,0.0,1.0);
	//	break;

	//case 12:
	//	glRotatef(90,1,0,0);
	//	//////////////////////////////////////
	//	glRotatef(slo->DataESE[4],0.0,0.0,1.0);
	//	break;

	//case 14:
	//	glRotatef(-90,0,0,1);
	//	glRotatef(-90,1,0,0);
	//	//////////////////////////////////////
	//	glRotatef(slo->DataESE[5],0.0,0.0,1.0);
	//	
	//	
	//	break;

	//case 16:
	//	glTranslatef(0.0,0.0,(GLfloat)61.15);
	//	glRotatef(90,1,0,0);
	//	glRotatef(90,0,0,1);
	//	glTranslatef(0.0,0.0,(GLfloat)-177.00);
	//	break;
	//default:
	//	// glTranslatef(0.0,(GLfloat)100,0);
	//	break;
	//*case 0:
	//	break;

	//case 1:
	//	   glTranslatef(0.0,0.0,(GLfloat)-0.25);
	//	break;

 //    case 2:
	//	 glRotatef(slo->DataESE[0],0.0,0.0,1.0);
	//	 glTranslatef(0.0,0.0,(GLfloat)7.45);	
	//	break;

	//case 3:
	//	glTranslatef(0.0,(GLfloat)-18.2,(GLfloat)36.5);
	//    glRotatef(-slo->DataESE[1],0,1,0);
	//	break;

	//case 4:
	//	glTranslatef(0.0,(GLfloat)0.5,0.0);
	//	break;

	//case 5:
	//	glTranslatef((GLfloat)-150,0,0);
	//	glRotatef(-slo->DataESE[2],0,1,0);
	//	break;
	//	
	//	case 6:
	//	   glTranslatef(0.0,(GLfloat)12.3,0.0);	
	//	break;

	//	case 7:
	//		glTranslatef(0.0,0.0,(GLfloat)200);
	//	break;

	//	case 8:
	//		glTranslatef(0,(GLfloat)7.716,(GLfloat)25.5);
	//		glRotatef(slo->DataESE[3],1,0,0);
	//	break;

	//	case 9:
	//		glTranslatef(0,0.0,(GLfloat)53);
	//		glRotatef(slo->DataESE[4],0,1,0);
	//	break;

	//	case 10:	
	//		glTranslatef(0.0,(GLfloat)-8.915,(GLfloat)35);
	//		glRotatef(slo->DataESE[5],0,0,1);
	//	break;

	//	case 11:
	//		glTranslatef(0,0,(GLfloat)6);
	//		break;

	//	case 12:
	//		glTranslatef((GLfloat)142.696,(GLfloat)0,(GLfloat)10.645);
	//		break;

	//	case 13:
	//		glTranslatef((GLfloat)34,0,0);
	//		break;*/

	}
	LoaderObject::pintarse(slo->Stack[caso]);

	           //    GLdouble mModel[16];
	            //    glGetDoublev(GL_MODELVIEW_MATRIX,mModel);
				//	cout<<"x:"<<mModel[12]<<" y:"<<mModel[13]<<" z:"<<mModel[14]<<endl;
	
	
		
	 
	

} ;
	//////////////SETS//////////////////////////////
//	static void setAnguleArt1(GLfloat*DataESE,StackLoaderObject*slo){
//	//no hace falta explicar VERDAD?
//	slo->DataESE[0]=DataESE[0];
//	slo->DataESE[1]=DataESE[1];
//	slo->DataESE[2]=DataESE[2];
//	slo->DataESE[3]=DataESE[3];
//	slo->DataESE[4]=DataESE[4];
//	slo->DataESE[5]=DataESE[5];
//};
};

