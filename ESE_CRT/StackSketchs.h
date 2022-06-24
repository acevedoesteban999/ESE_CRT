#pragma once
#include "Plano.h"
class StackSketchs
{
public:
	Plano**bocetos;
	CRD coord,*coorNewPlano;
	TypePlano NewPlanoType;
	mutex m;
	unsigned contNPl,toDrawNPl,cantB,contB,PlanoCheckeeado;
	bool draw,drawAll;
	StackSketchs()
	{
		contB=contNPl=0;
		toDrawNPl=3;
		cantB=10;
		bocetos=new Plano*[cantB];
		//bocetos[contB++]=new Plano("Principal Sketch");
		PlanoCheckeeado=0;
		coorNewPlano=new CRD[4];
		draw=true;
		drawAll=false;
		NewPlanoType=TypePlano::SPECIFICPLANE;
	};
	~StackSketchs()
	{
		delete[]coorNewPlano;
		for(unsigned i=0;i<contB;i++)
			delete bocetos[i];
		delete[]bocetos;
	};
	static void SetDrawAll(bool drawall,StackSketchs*sb){
		
		sb->drawAll=drawall;
		
	};
	static void Add(Plano*p,StackSketchs*sb)
	{
		
		for(unsigned i=0;i<sb->contB;i++)
			if(!strcmp(sb->bocetos[i]->name,p->name))
				sb->Sub(sb->bocetos[i]->name,sb);

		if(sb->contB>=sb->cantB-1)
		{
			Plano**Newp=new Plano*[sb->cantB+10];
			sb->cantB+=10;
			for(unsigned i=0;i<sb->contB;i++)
				Newp[i]=sb->bocetos[i];
			delete[]sb->bocetos;
			sb->bocetos=Newp;
		}
		sb->bocetos[sb->contB++]=p;
		
	
	}
	static void Pintar_NoPintar_LineaSuspensiva(bool pintarNoPintar,StackSketchs*sb){
//		sb->bocetos[sb->PlanoCheckeeado]->Pintar_NoPintar_LineaSuspensiva(pintarNoPintar,sb->bocetos[sb->PlanoCheckeeado]);
	}
	static void ActualizaLastCood(CRD coord,StackSketchs*sb)
	{
		sb->coord=coord;
		if(sb->contB)
			sb->BocetoActual(sb)->ActualiWidthHeight(Plano::CoordRestringida(sb->coord,sb->BocetoActual(sb)),sb->BocetoActual(sb));
	}
	static void AddPoint(CRD coord,StackSketchs*sb)
	{
		sb->BocetoActual(sb)->add(coord,sb->BocetoActual(sb));
	}
	static void Sub(char*name,StackSketchs*sb)
	{
		sb->m.lock();
		for(int i=(int)sb->contB-1;i>=0;i--)
		{
			if(!strcmp(name,sb->bocetos[i]->name))
			{
				delete sb->bocetos[i];
				for(unsigned ii=i;ii<sb->contB-1;ii++)
					sb->bocetos[ii]=sb->bocetos[ii+1];
				sb->contB--;
				if(sb->contB)
					sb->bocetos[sb->contB]->~Plano();
				break;
			}
		}
		sb->m.unlock();
	}
	static void Draw(StackSketchs*sb,bool proyectpunt=false)
	{

			if(sb->contNPl)
			{
				glColor3f(1,1,1);
				glPointSize(4);
				glLineWidth(3);
				if(sb->contNPl==1)
				{
					if(sb->toDrawNPl==3)
					{
						glBegin(GL_POINTS);
						glVertex3f((GLfloat)sb->coorNewPlano[0].x,(GLfloat)sb->coorNewPlano[0].y,(GLfloat)sb->coorNewPlano[0].z);
					}
				}
				else
				{
				glBegin(GL_LINE_LOOP);
				for(unsigned i=0;i<sb->contNPl;i++)
					glVertex3f((GLfloat)sb->coorNewPlano[i].x,(GLfloat)sb->coorNewPlano[i].y,(GLfloat)sb->coorNewPlano[i].z);
				}
				if(sb->toDrawNPl<3)
				{
					glEnd();
					glPointSize(5);
					glColor3f(0,0,1);
					glBegin(GL_POINTS);
					glVertex3f((GLfloat)sb->coorNewPlano[sb->toDrawNPl].x,(GLfloat)sb->coorNewPlano[sb->toDrawNPl].y,(GLfloat)sb->coorNewPlano[sb->toDrawNPl].z);	
					glPointSize(1);
				}
				glEnd();
				glPointSize(1);
				glLineWidth(1);
			
			}
			if(sb->draw)
			{
			if(sb->drawAll)
			{
				sb->m.lock();
				 for(unsigned i=0;i<sb->contB;i++)
					 sb->bocetos[i]->Draw(sb->coord,sb->bocetos[i],false,false,true);
				sb->m.unlock();
			}
			else if(sb->contB&&sb->PlanoCheckeeado!=sb->contB)
				sb->bocetos[sb->PlanoCheckeeado]->Draw(sb->coord,sb->bocetos[sb->PlanoCheckeeado],true,proyectpunt);
			}
	};
	static void SetPlanoCheckeeado(unsigned plano,StackSketchs*sb){
		sb->PlanoCheckeeado=plano;
	};
	static Plano*BocetoActual(StackSketchs*sb){return sb->bocetos[sb->PlanoCheckeeado];};
	static void SetDraw(bool draw,StackSketchs*sb)
	{
		
		sb->draw=draw;
		
	}
	static void AddPuntoNewPlano(CRD coord,StackSketchs*sb,unsigned ACambiar=3){
		
		if(ACambiar!=3)
		{
			sb->coorNewPlano[ACambiar]=coord;
			return;
		}
		switch (sb->contNPl)
		{
		case 0:
			sb->coorNewPlano=new CRD[4];
			sb->coorNewPlano[sb->contNPl++]=coord;
			break;
		case 1:
			sb->coorNewPlano[sb->contNPl++]=coord;
			break;
		case 2:
			sb->coorNewPlano[sb->contNPl++]=coord;
			break;
		case 3:
			sb->coorNewPlano[sb->contNPl++]=coord;
			break;
		}
		
	};
	static void ResetNewPlano(StackSketchs*sb)
	{
		
		sb->contNPl=0;
		
	};
	static void AddNewType(TypePlano tp,StackSketchs*sb){sb->NewPlanoType=tp;};
	static void ActualizaNewPlanoToCreate(CRD newCoorPlano,StackSketchs*sb,bool defAult)
	{
		
		for(unsigned i=0;i<sb->contNPl;i++)
		{
			switch (sb->NewPlanoType)
			{
				case TypePlano::XY:
					if(defAult==true)
					{
						switch (i)
						{
						case 0:
							sb->coorNewPlano[i].z=0;
							sb->coorNewPlano[i].x=200;
							sb->coorNewPlano[i].y=200;
							break;
						case 1:
							sb->coorNewPlano[i].z=0;
							sb->coorNewPlano[i].x=200;
							sb->coorNewPlano[i].y=-200;
							break;
						case 2:
							sb->coorNewPlano[i].z=0;
							sb->coorNewPlano[i].x=-200;	
							sb->coorNewPlano[i].y=-200;
							break;
						case 3:
							sb->coorNewPlano[i].z=0;
							sb->coorNewPlano[i].x=-200;
							sb->coorNewPlano[i].y=200;
							break;
						}
					}
					else
					{
						switch (i)
						{
						case 0:
							sb->coorNewPlano[i].z=newCoorPlano.z;
							sb->coorNewPlano[i].x=200+newCoorPlano.x;
							sb->coorNewPlano[i].y=200+newCoorPlano.y;
							break;
							
						case 1:
							sb->coorNewPlano[i].z=newCoorPlano.z;
							sb->coorNewPlano[i].x=200+newCoorPlano.x;
							sb->coorNewPlano[i].y=-200+newCoorPlano.y;
							break;
							
						case 2:
							sb->coorNewPlano[i].z=newCoorPlano.z;
							sb->coorNewPlano[i].x=-200+newCoorPlano.x;
							sb->coorNewPlano[i].y=-200+newCoorPlano.y;
							break;
							
						case 3:
							sb->coorNewPlano[i].z=newCoorPlano.z;
							sb->coorNewPlano[i].x=-200+newCoorPlano.x;
							sb->coorNewPlano[i].y=200+newCoorPlano.y;
							break;
						}
						
					}
				break;
				case TypePlano::XZ:
					if(defAult==true)
					{
						switch (i)
						{
						case 0:
							sb->coorNewPlano[i].y=0;
							sb->coorNewPlano[i].x=200;
							sb->coorNewPlano[i].z=200;
							break;
						case 1:
							sb->coorNewPlano[i].y=0;
							sb->coorNewPlano[i].x=200;
							sb->coorNewPlano[i].z=-200;
							break;
						case 2:
							sb->coorNewPlano[i].y=0;
							sb->coorNewPlano[i].x=-200;	
							sb->coorNewPlano[i].z=-200;
							break;
						case 3:
							sb->coorNewPlano[i].y=0;
							sb->coorNewPlano[i].x=-200;
							sb->coorNewPlano[i].z=200;
							break;
						}
					}
					else
					{
						switch (i)
						{
						case 0:
							sb->coorNewPlano[i].y=newCoorPlano.y;
							sb->coorNewPlano[i].x=200+newCoorPlano.x;
							sb->coorNewPlano[i].z=200+newCoorPlano.z;
							break;
							
						case 1:
							sb->coorNewPlano[i].y=newCoorPlano.y;
							sb->coorNewPlano[i].x=200+newCoorPlano.x;
							sb->coorNewPlano[i].z=-200+newCoorPlano.z;
							break;
							
						case 2:
							sb->coorNewPlano[i].y=newCoorPlano.y;
							sb->coorNewPlano[i].x=-200+newCoorPlano.x;
							sb->coorNewPlano[i].z=-200+newCoorPlano.z;
							break;
							
						case 3:
							sb->coorNewPlano[i].y=newCoorPlano.y;
							sb->coorNewPlano[i].x=-200+newCoorPlano.x;
							sb->coorNewPlano[i].z=200+newCoorPlano.z;
							break;
						}
						
					}
					/*if(defAult==true)
					{
						sb->coorNewPlano[i].y=0;
						sb->coorNewPlano[i].x=200;
						sb->coorNewPlano[i].z=200;
					}
					else
					{
						sb->coorNewPlano[i].y=newCoorPlano->y;
						sb->coorNewPlano[i].x=200+newCoorPlano->x;
						sb->coorNewPlano[i].z=200+newCoorPlano->z;
					}*/
				break;
				case TypePlano::YZ:
					if(defAult==true)
					{
						switch (i)
						{
						case 0:
							sb->coorNewPlano[i].x=0;
							sb->coorNewPlano[i].y=200;
							sb->coorNewPlano[i].z=200;
							break;
						case 1:
							sb->coorNewPlano[i].x=0;
							sb->coorNewPlano[i].y=200;
							sb->coorNewPlano[i].z=-200;
							break;
						case 2:
							sb->coorNewPlano[i].x=0;
							sb->coorNewPlano[i].y=-200;	
							sb->coorNewPlano[i].z=-200;
							break;
						case 3:
							sb->coorNewPlano[i].x=0;
							sb->coorNewPlano[i].y=-200;
							sb->coorNewPlano[i].z=200;
							break;
						}
					}
					else
					{
						switch (i)
						{
						case 0:
							sb->coorNewPlano[i].x=newCoorPlano.x; 
							sb->coorNewPlano[i].y=200+newCoorPlano.y;
							sb->coorNewPlano[i].z=200+newCoorPlano.z;
							break;
							
						case 1:
							sb->coorNewPlano[i].x=newCoorPlano.x;
							sb->coorNewPlano[i].y=200+newCoorPlano.y;
							sb->coorNewPlano[i].z=-200+newCoorPlano.z;
							break;
							
						case 2:
							sb->coorNewPlano[i].x=newCoorPlano.x;
							sb->coorNewPlano[i].y=-200+newCoorPlano.y;
							sb->coorNewPlano[i].z=-200+newCoorPlano.z;
							break;
							
						case 3:
							sb->coorNewPlano[i].x=newCoorPlano.x;
							sb->coorNewPlano[i].y=-200+newCoorPlano.y;
							sb->coorNewPlano[i].z=200+newCoorPlano.z;
							break;
						}
						
					}
					/*if(defAult==true)
					{
						sb->coorNewPlano[i].x=0;
						sb->coorNewPlano[i].y=200;
						sb->coorNewPlano[i].z=200;
					}
					else
					{
						sb->coorNewPlano[i].x=newCoorPlano->x;
						sb->coorNewPlano[i].y=200+newCoorPlano->y;
						sb->coorNewPlano[i].z=200+newCoorPlano->z;
					}*/
				break;
			}
		}
		
	}
	static void SetToDrawNPl(unsigned ToDraw,StackSketchs*sb)
	{
		sb->toDrawNPl=ToDraw;
	}
};