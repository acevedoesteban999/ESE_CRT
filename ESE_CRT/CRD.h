#pragma once
class CRD
{
public:
	double x,y,z;
	CRD(void)
	{
		this->x=0;
		this->y=0;
		this->z=0;
	};
	CRD(double x,double y,double z)
	{
		this->x=x;this->y=y;this->z=z;
	}
	CRD(double*coords)
	{
		 this->x=coords[0];
		 this->y=coords[1];
		 this->z=coords[2];
	}
	~CRD(){};
	static void set(float x,float y,float z,CRD*crd)
	{
		crd->x=x;
		crd->y=y;
		crd->z=z;
	}
	CRD operator +(const CRD c)
	{
		return CRD(this->x+c.x,this->y+c.y,this->z+c.z); 
	};
	CRD operator -(const CRD c)
	{
		return CRD(this->x-c.x,this->y-c.y,this->z-c.z); 
	};
	CRD operator *(const double c)
	{
		return CRD(this->x*c,this->y*c,this->z*c); 
	};
	CRD operator /(const double c)	   
	{
		if(c==0)
			return CRD(0,0,0); 
		return CRD(this->x/c,this->y/c,this->z/c); 
	};
	bool operator ==(CRD&crd)
	{
		if(this->x!=crd.x||this->y!=crd.y||this->z!=crd.z)
			return false;
		return true;
	}
	bool operator !=(CRD&crd)
	{
		if(*this==crd)
			return false;
		return true;
	}
};

