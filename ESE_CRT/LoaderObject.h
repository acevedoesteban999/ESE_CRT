#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class LoaderObject
{
public:
	class VERTs
    {
    public:
		GLfloat *v;
    	VERTs()
		{
			v=new GLfloat[1];
		};
    	~VERTs()
		{
			delete[]v;
		};
    };
	//////////////////////////////////////////////VARIABLES//////////////////////////////////
	GLdouble R,G,B;
	//int contHastak,contvf,contvn;
	int contv,contf,cantv,cantf;
	unsigned contVERTs;
	string nameStr;
	bool empty;
	/////DINAMICOS/////
	GLfloat *vertvCargX,*vertvCargY,*vertvCargZ;
	VERTs*veRts;
	////////////////////////////////////////////////METODOS//////////////////////

	///////////////CONSTRUCTORES Y DESTUCTOR//////
	LoaderObject(){
	contv=0;
	contf=0;
	cantv=10;
	cantf=10;
	vertvCargX=new GLfloat[cantv];
	vertvCargY=new GLfloat[cantv];
	vertvCargZ=new GLfloat[cantv];
	veRts=new VERTs[3];
	veRts[0].v=new GLfloat[cantf];
	veRts[1].v=new GLfloat[cantf];
	veRts[2].v=new GLfloat[cantf];
	contVERTs=0;
	R=G=B=0.2;

};
	LoaderObject(char*name,double R,double G,double B)
{
	this->R=R;
	this->G=G;
	this->B=B;
	this->vertvCargX=new GLfloat[1];
	this->vertvCargY=new GLfloat[1];
	this->vertvCargZ=new GLfloat[1];
	this->veRts=new VERTs[1];
	contv=0;
	contf=0;
	cargarObject(name,this);//Cargo el objeto en la direccion q contiene *name
	string s(name);
	nameStr=string(s.substr(s.find_last_of(92)+1,s.find_last_of(".")-s.find_last_of(92)-1)).c_str();//Para ponerle de nombre a cada LoaderObjec el nombre pero sin la direccion ni formato o sea:esta en "obj\brazo1.obj" pero el nombre q se guarda es "brazo1" 

}
	~LoaderObject()
	{		
		delete[]vertvCargX;
		delete[]vertvCargY;
		delete[]vertvCargZ;
		delete[]veRts;
	}
	//////////////////CARGAR//////////////////////
	static void cargarObject(char*name,LoaderObject*l){
	fstream f;
	char c[100];
	f.open(name,ios::in);
	   if(f.is_open())
	      {
		      while (!f.eof())
		         {
			         f.getline(c,100);
			         recorrerArchiv(c,l);//recorro el archivo para saber el tamaño para poder crear las variables dinamicas de un tamaño correcto
	             }
		      f.clear();
		      f.seekg(0,ios::beg);
		      l->vertvCargX=new GLfloat[l->contv];//creo todas las variables dinamicas para cargar el .obj
		      l->vertvCargY=new GLfloat[l->contv];
		      l->vertvCargZ=new GLfloat[l->contv];
		      //l->vertvnCargX=new GLfloat[l->contvn];
		      //l->vertvnCargY=new GLfloat[l->contvn];
		      //l->vertvnCargZ=new GLfloat[l->contvn];
		      //l->vertvfCargX=new GLfloat[l->contvf];
	          //l->vertvfCargY=new GLfloat[l->contvf];
      		  //l->vertvfCargZ=new GLfloat[l->contvf];
			  l->veRts=new VERTs[3];
			  for(int i=0;i<3;i++)
			  {
				  l->veRts[i].v=new GLfloat[l->contf];
				  //l->veRts[i].Ys=new GLfloat[l->contf];
				  //l->veRts[i].Zs=new GLfloat[l->contf];
			  }
			 

		 
		      int v=0,ff=0;
			 // int vn=0,vf=0;
	  	      while (!f.eof())
		        {
			        f.getline(c,100);
			        string s(c);
			        switch (s[0])
		     	       {
				
			             case 'v':
					
				                   switch (s[1])
				                      {
				                       case ' ':
					                            l->vertvCargX[v]=(GLfloat)atof(findd(s,1).c_str());
						                       
				                                s=findd(s);
				                                l->vertvCargY[v]=(GLfloat)atof(findd(s,1).c_str());
						                        
				                                s=findd(s);
				                                l->vertvCargZ[v]=(GLfloat)atof(findd(s,1).c_str());
						                       
						                        v++;
					                            break;

				                       case 'f':
						                       // l->vertvfCargX[vf]=(GLfloat)atof(findd(s,1).c_str());
				                               // s=findd(s);
				                               // l->vertvfCargY[vf]=(GLfloat)atof(findd(s,1).c_str());
				                               // s=findd(s);
				                               // l->vertvfCargZ[vf]=(GLfloat)atof(findd(s,1).c_str());
					                            break;

					                   case 'n':
						                      //  l->vertvnCargX[vn]=(GLfloat)atof(findd(s,1).c_str());
				                              //  s=findd(s);
				                              //  l->vertvnCargY[vn]=(GLfloat)atof(findd(s,1).c_str());
				                              // s=findd(s);
				                              //  l->vertvnCargZ[vn]=(GLfloat)atof(findd(s,1).c_str());
                                              // vn++;
					                            break;
								    }
				               break;

			             case'f':
				             
								
								for(int i=0;i<3;i++)
								{
					            s=findd(s);
								l->veRts[i].v[ff]=(GLfloat)atof(findd(s,2).c_str());
					            s=findd(s,3);
					           // l->veRts[i].Ys[ff]=(GLfloat)atof(findd(s,2).c_str());
					            s=findd(s,3);
					           // l->veRts[i].Zs[ff]=(GLfloat)atof(findd(s,2).c_str());
								}
					            ff++;
				                break;
			      }//end switch
	         }//end while(!f.eof())
		 cout<<"----OK---->: "<<name<<endl;
		   l->empty=false;
	      }//end if(is_open())
	  else 
	     {
		 cout<<"-----X---->: "<<name<<endl;
	      l->empty=true; 
	     }
	   f.close();
};
	static string findd(string s,int caso=0){
	//Encontrar los valores a cargar en una cadena de caracteres a traves de las funciones del string 


   if(!caso)    //case 0: recive una cadena(por entrada de la funcion)y devuelve desde el primer espacio en blanco hasta el final de la cadena
      { 
	   string ss=s.substr(s.find_first_of(" ")+1,s.length()-s.find_first_of(" "));
	   return ss;	
      }
   else if(caso==1)//case 1:obtine una cadena a partir de la funcionalidad del case 0,y devuelve lo q quedo hasta el proximo espacio en blanco;o sea devuelve el  numero q esta entre espacios en blanco  
      {
	   string ss=findd(s);
	   ss=ss.substr(0,ss.find_first_of(" ")-1);
	   return ss;
       }
   else if(caso==2)//case 2:recive una cadena y devuelve todo lo q contiene antes de encontrar el primer '/' 
	   {
		if(s[0]!='/')
		   {
	       string ss=s.substr(0,s.find_first_of('/'));
		   return ss;
	       }
        else 
		   return string("0.8");//este tengo q ponerlo para  q el visual studio no me de un warning!! porq tiene q devolver algo
	   

   
	   }
   else if(caso==3)//case 3:recive una cadena y devuelve desde el primer'/'hasta el final de la cadena 
	 {	
		string ss=s.substr(s.find_first_of("/")+1,s.length()-s.find_first_of("/")+1);
		return ss;
     }
  
   string ss="NO HAY CASO";//este tengo q ponerlo para  q el visual studio no me de un warning!! porq tiene q devolver algo
   return ss;
};
	static void LoaderObject::recorrerArchiv(char*c,LoaderObject*l){
	//recorrer el archivo a cargar e ir contando las catidades de datos de v,vf,vn,f para asi crear variables dinamicas con un tamaño exacto 
	 switch (c[0])
		   {
		   case '#':
			       // l->contHastak++;
			        break;
		    case 'v':
				     switch (c[1])
				        {
					     case' ':
						         l->contv++;
					             break;
				         case'f':
					          //  l->contvf++;
					             break;
					      case'n':
							    //  l->contvn++;
					              break;
				        }
			           break;
			
		
			case 'f':
				    l->contf++;
			        break;
		   }



};
	//////////////////GUARDAR///////////////////////////
	static void Add(GLfloat*Vertices,LoaderObject*l){
	if(l->contv>=l->cantv)
	{
		GLfloat*NewX=new GLfloat[l->cantv+10];
		GLfloat*NewY=new GLfloat[l->cantv+10];
		GLfloat*NewZ=new GLfloat[l->cantv+10];
		l->cantv+=10;
		for(int i=0;i<l->contv;i++)
		{
			NewX[i]=l->vertvCargX[i];
			NewY[i]=l->vertvCargY[i];
			NewZ[i]=l->vertvCargZ[i];
		}
		delete l->vertvCargX,l->vertvCargY,l->vertvCargZ;
		l->vertvCargX=NewX;
		l->vertvCargY=NewY;
		l->vertvCargZ=NewZ;

	}
	l->vertvCargX[l->contv]=Vertices[0];
	l->vertvCargY[l->contv]=Vertices[1];
	l->vertvCargZ[l->contv]=Vertices[2];
	l->contv++;
	if(l->contf>=l->cantf)
	   {
		   VERTs*newData=new VERTs[3];
		   newData[0].v=new GLfloat[l->contf+10];
		   newData[1].v=new GLfloat[l->contf+10];
		   newData[2].v=new GLfloat[l->contf+10];
		   l->cantf+=10;
		   for(int i=0;i<l->contf;i++)
		   {
			   newData[0].v[i]=l->veRts[0].v[i];
			   newData[1].v[i]=l->veRts[1].v[i];
			   newData[2].v[i]=l->veRts[2].v[i];	   
		   }
		   delete l->veRts;
		   l->veRts=newData;
	   }
	l->veRts[l->contVERTs++].v[l->contf]=(GLfloat)l->contv;	
	if(l->contVERTs==3)
	{
		l->contVERTs=0;
		l->contf++;
	}
};
	//////////////////DRAW//////////////////////////////
	static void pintarse(LoaderObject*l){
	//Dibujar los vertices q tengo en el orden q indica f(dato del arcivo de carga .obj) de forma GL_TRIANGLES
		glColor3f((GLfloat)l->R,(GLfloat)l->G,(GLfloat)l->B);
	for(int i=0;i<l->contf;i++)
	   {
	    glBegin(GL_TRIANGLES);
		glVertex3f(l->vertvCargX[(GLint)l->veRts[0].v[i]-1],l->vertvCargY[(GLint)l->veRts[0].v[i]-1],l->vertvCargZ[(GLint)l->veRts[0].v[i]-1]);   
		glVertex3f(l->vertvCargX[(GLint)l->veRts[1].v[i]-1],l->vertvCargY[(GLint)l->veRts[1].v[i]-1],l->vertvCargZ[(GLint)l->veRts[1].v[i]-1]); 
		glVertex3f(l->vertvCargX[(GLint)l->veRts[2].v[i]-1],l->vertvCargY[(GLint)l->veRts[2].v[i]-1],l->vertvCargZ[(GLint)l->veRts[2].v[i]-1]); 
	glEnd();
	}//end for
	
	

}; 
	static void pintarNewBoj(LoaderObject*l){
	//glColor3f((GLfloat)l->R,(GLfloat)l->G,(GLfloat)l->B);
	glColor3f((GLfloat)1,(GLfloat)1,(GLfloat)1);
	for(int i=0;i<l->contf;i++)
	   {
	    glBegin(GL_TRIANGLES);
		glVertex3f(l->vertvCargX[(GLint)l->veRts[0].v[i]-1],l->vertvCargY[(GLint)l->veRts[0].v[i]-1],l->vertvCargZ[(GLint)l->veRts[0].v[i]-1]);   
		glVertex3f(l->vertvCargX[(GLint)l->veRts[1].v[i]-1],l->vertvCargY[(GLint)l->veRts[1].v[i]-1],l->vertvCargZ[(GLint)l->veRts[1].v[i]-1]); 
		glVertex3f(l->vertvCargX[(GLint)l->veRts[2].v[i]-1],l->vertvCargY[(GLint)l->veRts[2].v[i]-1],l->vertvCargZ[(GLint)l->veRts[2].v[i]-1]); 
		glEnd();

	}//end for
	



};

	
};

