#pragma once
#include "CRD.h"


//#include "Matriz.h"
enum ItemsType{
 ITEMS,POINTSS,LINES,LINE_STRIP,SPLINE,BSPLINE
};
class Items
{
public:
	CRD*PoIntS;
	ItemsType t;
	unsigned cont,cant;
	GLfloat*SPlinePoints;
	GLfloat asd[9];
	bool SplineAsignar;
	mutex m;
	Items()
	{
		cont=0;
		cant=100;
		PoIntS=new CRD[cant];
		t=ItemsType::ITEMS;
		SplineAsignar=true;
		SPlinePoints=new GLfloat[1];
	};
	~Items()
	{
		delete []PoIntS;
		delete []SPlinePoints;
	};
	void Draw(){
		
			glPointSize(5);
			glColor3f(0,1,0);
			glBegin(GL_POINTS);
			for(unsigned i=0;i<cont;i++)
				glVertex3f((GLfloat)PoIntS[i].x,(GLfloat)PoIntS[i].y,(GLfloat)PoIntS[i].z);
			glEnd();
			glPointSize(1);
			switch (t)
			{
			case ItemsType::LINES:
					if(cont>1)
					{
						glLineWidth(4);
						glBegin(GL_LINES);
						glColor3f((GLfloat)0.9,(GLfloat)0.9,(GLfloat)0.9);
						for(unsigned i=0;i<cont;i++)
							glVertex3f((GLfloat)PoIntS[i].x,(GLfloat)PoIntS[i].y,(GLfloat)PoIntS[i].z);
						glEnd();
						glLineWidth(1);
					}
			break;
			case ItemsType::LINE_STRIP:
				glLineWidth(4);
				glBegin(GL_LINE_STRIP);
				glColor3f((GLfloat)0.9,(GLfloat)0.9,(GLfloat)0.9);
				for(unsigned i=0;i<cont;i++)
					glVertex3f((GLfloat)PoIntS[i].x,(GLfloat)PoIntS[i].y,(GLfloat)PoIntS[i].z);
				glEnd();
				glLineWidth(1);
			break;
			case ItemsType::BSPLINE:
				glLineWidth(4);
				glColor3f((GLfloat)0.9,(GLfloat)0.9,(GLfloat)0.9);	
				if(this->SplineAsignar)
				{
					this->SplineAsignar=false;
					SPlinePoints=new GLfloat[this->cont*3];
					for(unsigned i=0;i<this->cont*3;i+=3)
					{
						SPlinePoints[i]=(GLfloat)PoIntS[unsigned(i/3)].x;
						SPlinePoints[i+1]=(GLfloat)PoIntS[unsigned(i/3)].y;
						SPlinePoints[i+2]=(GLfloat)PoIntS[unsigned(i/3)].z;
					}
				}
			

				glMap1f(GL_MAP1_VERTEX_3,0,100,3,cont,SPlinePoints);
				glEnable(GL_MAP1_VERTEX_3);
				glBegin(GL_LINE_STRIP); 
				for(unsigned i = 0; i <= 100; i++)
					glEvalCoord1d((GLfloat)i);
				glEnd();
				glLineWidth(1);

			break;
		
			case ItemsType::SPLINE:
				/*glLineWidth(4);
				glBegin(GL_LINE_STRIP);
				glColor3f((GLfloat)1,(GLfloat)0,(GLfloat)0);
				for(unsigned i=0;i<cont;i++)
					glVertex3f((GLfloat)PoIntS[i].x,(GLfloat)PoIntS[i].y,(GLfloat)PoIntS[i].z);
				glEnd();
				glLineWidth(1);*/
				glLineWidth(4);
				glColor3f((GLfloat)0.9,(GLfloat)0.9,(GLfloat)0.9);	
				if(this->SplineAsignar)
				{
					this->SplineAsignar=false;
					SPlinePoints=new GLfloat[this->cont*3];
					for(unsigned i=0;i<this->cont*3;i+=3)
					{
						SPlinePoints[i]=(GLfloat)PoIntS[unsigned(i/3)].x;
						SPlinePoints[i+1]=(GLfloat)PoIntS[unsigned(i/3)].y;
						SPlinePoints[i+2]=(GLfloat)PoIntS[unsigned(i/3)].z;
					}
				}


				for(unsigned i=0;i<cont;i+=3)
				{
					if(cont-i<3)
						break;
					asd[0]=SPlinePoints[2*i];
					asd[1]=SPlinePoints[2*i+1];
					asd[2]=SPlinePoints[2*i+2];

					asd[3]=SPlinePoints[2*i+3];
					asd[4]=SPlinePoints[2*i+4];
					asd[5]=SPlinePoints[2*i+5];

					asd[6]=SPlinePoints[2*i+6];
					asd[7]=SPlinePoints[2*i+7];
					asd[8]=SPlinePoints[2*i+8];
	

					glMap1f(GL_MAP1_VERTEX_3,0,100,3,3,asd);
					glEnable(GL_MAP1_VERTEX_3);
					glBegin(GL_LINE_STRIP); 
					for(unsigned ii = 0; ii <= 100; ii++)
						glEvalCoord1d((GLfloat)ii);
					glEnd();
				}	
				glLineWidth(1);

			break;
			}
		
	};
	void Add(CRD point)
	{
		
		if(cont>=cant)
		{
			CRD*newPoints=new CRD[cant+100];
			cant+=100;
			for(unsigned i=0;i<cont;i++)
				newPoints[i]=PoIntS[i];
			delete[]PoIntS;
			PoIntS=newPoints;
		}
		if(PoIntS[cont-1]==point)
		   return;
	   PoIntS[cont++]=point;
	   if(!this->SplineAsignar)
		   this->SplineAsignar=true;
	   
};
	void Sub()
	{
		
		if(cont>0)
		{
			PoIntS[--cont].~CRD();
		}
		
	}
	void SetType(ItemsType it)
	{
		this->t=it;
	}

};
//class Points:public Items
//{
//
//public:
//	Points():Items(){
//		t=ItemsType::POINTSS;
//	}
//	~Points(){};
//	void Pure(){};
//};
//class Strip_Line:public Items
//{
//public:
//	Strip_Line():Items()
//	{
//		t=ItemsType::LINE_STRIP;
//	};
//	~Strip_Line(){};
//	void Draw()
//	{
//		Items::Draw();
//		if(cont==1)
//		{
//			glPointSize(2);
//			glBegin(GL_POINTS);
//		    glVertex3f((GLfloat)PoIntS[0].x,(GLfloat)PoIntS[0].y,(GLfloat)PoIntS[0].z);
//			glEnd();
//			glPointSize(1);
//		}
//		else
//		{
//		   glLineWidth(2);
//		   glColor3f(1,1,1);
//		   glBegin(GL_LINE_STRIP);
//		   for(unsigned i=0;i<cont;i++)
//		      glVertex3f((GLfloat)PoIntS[i].x,(GLfloat)PoIntS[i].y,(GLfloat)PoIntS[i].z);
//		   glEnd();
//		   glLineWidth(1);
//		 }
//
//	};
//	void Pure(){};
//};
//class SplineCubico:public Items
//{
//  class Matriz
//	{
//	class fila
//		{
//		public:
//			float*elementsFila;
//			float result;
//			unsigned size;
//			fila()
//			{
//				size=0;
//				elementsFila=new float[1];
//				result=0;
//			};
//			~fila(){};
//			fila operator*(float num)
//			{
//				fila f=*this;
//				f.elementsFila=new float[this->size];
//				for(unsigned i=0;i<f.size;i++)
//				   f.elementsFila[i]=this->elementsFila[i];
//					
//				for(unsigned i=0;i<f.size;i++)
//				   f.elementsFila[i]*=num;
//				f.result*=num;
//				return f;
//			}
//			fila operator/(float num)
//			{
//				fila f=*this;
//				f.elementsFila=new float[this->size];
//				for(unsigned i=0;i<f.size;i++)
//				   f.elementsFila[i]=this->elementsFila[i];
//
//				for(unsigned i=0;i<f.size;i++)
//				   f.elementsFila[i]/=num;
//				f.result/=num;
//				return f;
//			}
//			fila operator+(fila f)
//			{
//				for(unsigned i=0;i<f.size;i++)
//					this->elementsFila[i]+=f.elementsFila[i];
//				this->result+=f.result;
//				return *this;
//			}
//			fila operator-(fila f)
//			{
//				for(unsigned i=0;i<f.size;i++)
//					this->elementsFila[i]-=f.elementsFila[i];
//				this->result-=f.result;
//				return *this;
//			}
//			void Cambiar(fila*f,fila*f1){
//				fila ff=*f;
//				*f=*f1;
//				*f1=ff;
//			};
//		};
//	private:
//		fila*Filas;
//		unsigned size;
//	public:
//		Matriz(unsigned Size,float*Elements,float*Result){
//			Filas=new fila[Size];
//			unsigned contE=0;
//			size=Size;
//			for(unsigned i=0;i<Size;i++)
//			{
//				Filas[i].result=Result[i];
//				Filas[i].elementsFila=new float[Size];
//				Filas[i].size=Size;
//				for(unsigned j=0;j<Size;j++)
//					Filas[i].elementsFila[j]=Elements[contE++];
//			}	
//		};
//		~Matriz(){};
//	float*Solucion_ReduccionFilas()
//	{
//		Matriz*m=new Matriz(*this);
//		for(unsigned i=0;i<m->size;i++)
//		{
//			for(unsigned j=0;j<m->size;j++)
//		    {
//			   if(j==i)
//				   continue;
//			   float Factor=m->Filas[j].elementsFila[i]/m->Filas[i].elementsFila[i];
//			   m->Filas[j]=(m->Filas[i]*Factor - m->Filas[j]);
//		    }
//		}
//		
//		float*toReturn=new float[size];
//		for(unsigned i=0;i<size;i++)
//			toReturn[i]=(float)(m->Filas[i].result/Filas[i].elementsFila[i]);
//		return toReturn;
//	}
//	static void MostrarMatriz(Matriz*m){
//	for(unsigned i=0;i<m->size;i++)
//		           {
//			          for(unsigned j=0;j<m->size;j++)
//			             std::cout<<m->Filas[i].elementsFila[j]<<" ";
//			           std::cout<<"["<<m->Filas[i].result<<"]"<<std::endl;
//		           }
//				   std::cout<<"|||||||||||||||||||||||||||||||||||||||||||||||||||"<<std::endl;
//	}
//};
//private:
//	float*h,*yi,*A,*B,*C,*D,*PUNTOSY;
//	unsigned cantPuntY,contPuntY;
//	Matriz*m;
//public:
//	SplineCubico():Items(){
//		//t=ItemsType::SPLINECUBICO;
//		h=new float[cont];
//		yi=new float[cant];
//		A=new float(0);
//		B=new float(0);
//		C=new float(0);
//		D=new float(0);
//		PUNTOSY=new float(0);
//		contPuntY=0;
//		cantPuntY=1;
//	}
//	~SplineCubico(){};
//	void Add(CRD*point)
//	{
//		Items::Add(point);
//		if(cant-cont==9&&cont!=1)
//		{
//			float*newh=new float[cant];
//			float*newyi=new float[cant];
//			for(unsigned i=0;i<cont;i++)
//			{
//				newh[i]=h[i];
//			    newyi[i]=yi[i];
//			}
//			h=newh;
//			yi=newyi;
//		} 
//		if(cont>1)
//		{
//			h[cont-2]=(float)(PoIntS[cont-1].x-PoIntS[cont-2].x);
//			yi[cont-2]=(float)((PoIntS[cont-1].y-PoIntS[cont-2].y)/h[cont-2]);
//			if(cont>2)
//			{
//			   float*Elements=new float[(unsigned)((cont-1)*(cont-1))];
//			   float*Result=new float[cont-1];
//			   unsigned contElements=0;
//			   for(unsigned i=0;i<cont-2;i++)
//			   {
//			      for(unsigned j=0;j<cont-2;j++)
//			      {
//			      	if(i==j)
//			   		Elements[contElements++]=2*(h[i]+h[i+1]);
//			   	else
//			   		Elements[contElements++]=h[1];
//			      }
//			      Result[i]=6*(yi[i+1]-yi[i]);
//		 	   }
//			   m=new Matriz(cont-2,Elements,Result);
//			   float*M1=m->Solucion_ReduccionFilas();
//			   float*M=new float[cont-1];
//			   M[0]=0;
//			   M[cont-1]=0;
//			   for(unsigned i=0;i<cont-2;i++)
//			      M[i+1]=M1[i];
//			   A=new float[cont-1];
//			   B=new float[cont-1];
//			   C=new float[cont-1];
//			   D=new float[cont-1];
//			   for(unsigned i=0;i<cont-1;i++)
//			   {
//				  A[i]=(M[i+1]-M[i])/(6*h[i]);
//				  B[i]=M[i]/2;
//				  C[i]=yi[i]-((M[i+1]+2*M[i])/6)*h[i];
//				  D[i]=(float)PoIntS[i].y;
//			   }
//			   cantPuntY=(unsigned)(PoIntS[cont-1].x - PoIntS[0].x);
//			   contPuntY=0;
//			   PUNTOSY=new float[cantPuntY+1];
//			   for(unsigned i=0;i<cont-1;i++)
//			      for(float j=(float)PoIntS[i].x;(i==cont-2?j<=(float)PoIntS[i+1].x:j<(float)PoIntS[i+1].x);j++)
//					  PUNTOSY[contPuntY++]=(float)(A[i]*pow(j-PoIntS[i].x,3)   +  B[i]*pow(j-PoIntS[i].x,2)   +   C[i]*(j-PoIntS[i].x)   +   D[i]);
//			}
//		}
//	}
//	void Draw()
//	{
//		Items::Draw();
//		if(cont>1)
//		{
//			glLineWidth(2);
//			glColor3f(1,1,1);
//			glBegin(GL_LINE_STRIP);
//			for(unsigned i=0;i<contPuntY;i++)
//			{
//				glVertex3f((GLfloat)i,(GLfloat)PUNTOSY[i],0);
//			}
//			glEnd();
//			glLineWidth(1);
//			
//		}
//		
//		/* if(cont>1)
//		 {
//			 for(unsigned i=0;i<cont-1;i++)
//			 {
//				 std::cout<<"S"<<i<<":"<<A[i]<<"(x"<<(PoIntS[i].x>=0?"+":"")<<PoIntS[i].x<<")^3"<<(B[i]>=0?"+":"");
//			     std::cout<<B[i]<<"(x"<<(PoIntS[i].x>=0?"+":"")<<PoIntS[i].x<<")^2"<<(C[i]>=0?"+":"");
//				 std::cout<<C[i]<<"(x"<<(PoIntS[i].x>=0?"+":"")<<PoIntS[i].x<<")"<<(D[i]>=0?"+":"");
//				 std::cout<<D[i]<<std::endl;
//			 }
//		 }*/
//	}
//	void Pure(){};
//};