#pragma  once
#include "CRD.h"
enum _bocetoType
{
	_BOCETO,
	_BOCETO3D,
	_PLANO
};
enum  _drawType
{
	_POINTS,
	_LINES,
	_STRIPLINES,
	_BSPLINE
};
class _boceto
{
protected:
	char*name;
	CRD*points;
	GLfloat*SPlinePoints;
	bool SplineAsignar;
	unsigned cont,cant;
	_bocetoType bocetoType;
	_drawType drawType;
public:
	_boceto(char*name)
	{
		cont=0;
		cant=10;
		points=new CRD[cant];
		SPlinePoints=new GLfloat[1];
		bocetoType=_BOCETO;
		drawType=_POINTS;
		SplineAsignar=false;
		this->name=new char[strlen(name)+1];
		this->name[strlen(name)]=0;
		for(unsigned i=0;i<strlen(name);i++)
			this->name[i]=name[i];
	}
	~_boceto()
	{
		delete[]name;
		delete[]points;
		delete[]SPlinePoints;
	}
	//ADD//
	void Add_Point(CRD crd)
	{
		if(cont>=cant)
		{
			cant+=10;
			CRD*newPoints=new CRD[cant];
			for(unsigned i=0;i<cont;i++)
				newPoints[i]=points[i];
			delete[]points;
			points=newPoints;
		}
		points[cont++]=crd;
	}
	//SUB//
	void Sub_Point()
	{
		cont--;
	}
	//SET//
	void Set_DrawType(_drawType dt)
	{
		drawType=dt;
	}
	virtual void Set_DrawPlane(bool DrawPlane)
	{
	}
	//GET//
	char*Get_Name()
	{
		return name;
	}
	_drawType Get_DrawType()
	{
		return  drawType;
	}
	//DRAW//
	virtual void _draw()
	{
		glPointSize(4);
		glColor3f(0,1,0);
		glBegin(GL_POINTS);
		for(unsigned i=0;i<cont;i++)
		{
			glVertex3f((GLfloat)points[i].x,(GLfloat)points[i].y,(GLfloat)points[i].z);
		}
		glEnd();
		glPointSize(1);
		switch (drawType)
		{
		case _POINTS:
			break;
		case _LINES:
		case _STRIPLINES:
			glLineWidth(3);
			glColor3f((GLfloat)0.8,(GLfloat)0.8,(GLfloat)0.8);
			if(drawType==_LINES)
				glBegin(GL_LINES);
			else 
				glBegin(GL_LINE_STRIP);
			for(unsigned i=0;i<cont;i++)
			{
				glVertex3f((GLfloat)points[i].x,(GLfloat)points[i].y,(GLfloat)points[i].z);
			}
			glEnd();
			glLineWidth(1);
			break;
		case _BSPLINE:
			glLineWidth(3);
				glColor3f((GLfloat)0.9,(GLfloat)0.9,(GLfloat)0.9);	
				if(SplineAsignar)
				{
					SplineAsignar=false;
					delete[]SPlinePoints;
					SPlinePoints=new GLfloat[cont*3];
					for(unsigned i=0;i<this->cont*3;i+=3)
					{
						SPlinePoints[i]=(GLfloat)points[unsigned(i/3)].x;
						SPlinePoints[i+1]=(GLfloat)points[unsigned(i/3)].y;
						SPlinePoints[i+2]=(GLfloat)points[unsigned(i/3)].z;
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

		}

	};
	//PURAS//
	virtual void PURA()=0;
	
};

class _boceto3D:public  _boceto
{
public:
	_boceto3D(char*name):_boceto(name)
	{
		bocetoType=_BOCETO3D;
	}
	~_boceto3D(){}
	//PURAS//
	void Add_Point(CRD crd)
	{
		_boceto::Add_Point(crd);
	}
	//PURAS//
	void PURA(){}
};