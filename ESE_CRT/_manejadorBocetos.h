#pragma once
#include "_boceto.h"
class _manejadorBocetos
{
	friend class _boxInterfazPrincipal;
private:
	_boceto**bocetos;
	unsigned cont,cant;
	int BocetoAPintar;
public:
	_manejadorBocetos()
	{
		BocetoAPintar=-1;
		cont=0;
		cant=5;
		bocetos=new _boceto*[cant];
	}
	~_manejadorBocetos()
	{
		for(unsigned i=0;i<cont;i++)
			delete bocetos[i];
		delete[]bocetos;
	}
	//ADD//
	void Add_Boceto(_boceto*boceto)
	{
		if(cont>=cant)
		{
			cant+=5;
			_boceto**newBocetos=new _boceto*[cant];
			for(unsigned i=0;i<cont;i++)
				newBocetos[i]=bocetos[i];
			delete[]bocetos;
			bocetos=newBocetos;
		}
		bocetos[cont++]=boceto;
	}
	void Add_Boceto3D(char*name)
	{
		_boceto3D*b3d=new _boceto3D(name);
		Add_Boceto(b3d);
	}
	//SUB//
	void  Sub_Boceto(unsigned bocetoPosition)
	{
		if(bocetoPosition>=cont)
			return;
		delete bocetos[bocetoPosition];
		for(unsigned i=bocetoPosition;i<cont-1;i++)
			bocetos[i]=bocetos[i+1];
		cont--;
		if(!cont)
			BocetoAPintar=-1;
	
	
	}
	//SET//
	void Add_Point_to_BocetoAPintar(CRD crd)
	{
		if(BocetoAPintar==-1)
			return;
		bocetos[(unsigned)BocetoAPintar]->Add_Point(crd);
	}
	void Sub_Point_to_BocetoAPintar()
	{
		if(BocetoAPintar==-1)
			return;
		bocetos[(unsigned)BocetoAPintar]->Sub_Point();
	
	}
	void Set_DrawType(_drawType dt)
	{
		if(BocetoAPintar==-1)
			return;
		bocetos[(unsigned)BocetoAPintar]->Set_DrawType(dt);
	}
	void Set_DrawPlane(bool DrawPlane)
	{
		if(BocetoAPintar==-1)
			return;
		bocetos[(unsigned)BocetoAPintar]->Set_DrawPlane(DrawPlane);
	}
	//-1 para reiniciar
	void Set_BocetoAPintar(int BocetoAPintar=-1)
	{
		if((int)cont>BocetoAPintar)
			this->BocetoAPintar=BocetoAPintar;
	}
	//GET//
	char*Get_BocetoAPintarName()
	{
		if(BocetoAPintar==-1)
			return "No asigando BocetoAPintar";
		return bocetos[(unsigned)BocetoAPintar]->Get_Name();
	}
	_drawType Get_DrawType()
	{
		if(BocetoAPintar==-1)
			return _drawType::_POINTS;
		return bocetos[(unsigned)BocetoAPintar]->Get_DrawType();
	}
	//DRAW//
	void _draw()
	{
		if(BocetoAPintar==-1)
			return;
			bocetos[BocetoAPintar]->_draw();

		
	}
};