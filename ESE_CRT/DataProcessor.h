#pragma once
#define PI 3.14159265
#include "ESE_CRT.h"
class DataUnion
{
	union Union
{
public:
	double Double;
	float Float;
	int Int;
	unsigned Unsigned;
	short Short;
	char Char;
	char String[sizeof(double)];
};
public:
	Union u;
	unsigned Ultim,lengthDescodif;
	char*str;
public:
	DataUnion()
	{
		ResetStr();
		str=new char[1];
		lengthDescodif=0;
	}
	~DataUnion()
	{
		delete []str;
	}
	void ResetStr()
	{
		for(unsigned i=0;i<8;i++)
			u.String[i]=(char)0;
		Ultim=0;
	}
	void SetStr(const char*data,unsigned i,unsigned typeDato)
	{
		/*
		
		1: char
		2: short
	    4: int ; unsigned
		5: float
		8: double
		*/
		ResetStr();
		if(i<=8)
		{
			unsigned j=0;
			switch (typeDato)
			{
			case 1:
				if(i==1)
					u.String[0]=data[0];
				break;
			case 2:
			case 4:
				for(unsigned ii=0;ii<i;ii++)
					u.String[ii]=data[ii];
				break;
			case 5:
				for(unsigned ii=4-i;ii<4;ii++)
					u.String[ii]=data[j++];
				break;
			case 8:
				for(unsigned ii=8-i;ii<8;ii++)
					u.String[ii]=data[j++];
				break;
			default:
				break;
			}
			/*unsigned j=0;
			int k=7-(8-typeDato);
			for(unsigned ii=0;ii<i;ii++)
			{
				if(k<0||j>7)
					break;
				String[(unsigned)k--]=data[j++];
			}*/
		}
	}
	void SetDouble(double d)
	{
		ResetStr();
		if(d==0)
			return;
		u.Double=d;
		Ultim=6;
	}
	void SetFloat(float f)
	{
		ResetStr();
		if(f==0)
			return;
		u.Float=f;
		Ultim=5;
	}
	void SetInt(int i)
	{
		ResetStr();
		if(i==0)
			return;
		u.Int=i;
		Ultim=4;
	}
	void SetUnsigned(unsigned un)
	{
		ResetStr();
		if(un==0)
			return;
		u.Unsigned=un;
		Ultim=3;
	}
	void SetShort(short s)
	{
		ResetStr();
		if(s==0)
			return;
		u.Short=s;
		Ultim=2;
	}
	void SetChar(char ch)
	{
		ResetStr();
		if(ch==0)
			return;
		u.Char=ch;
		Ultim=1;
	}
	////////CODIF////////////
	char* GetStrCodif()
	{
		delete[]str;
		str=new char[10];
		if(Ultim==0)
		{
			str[0]=(char)1;
			str[1]=0;
			return str;
		}
		str[0]=(char)Ultim;
		unsigned j=1;
		for(unsigned i=0;i<8;i++)
		{
			if(u.String[i]!=(char)0)
			{
				str[0]+=(char)10;
				str[j++]=u.String[i];
			}
		}
		str[j]=0;
		return str;
	}
	void SetStrCodif(const char s[])
	{
		lengthDescodif=0;
		ResetStr();
		if(strlen(s))
		{
			char toDec[8];
			lengthDescodif=1;
			if(s[0]==(char)1)
			{
				return;
			}
			for(unsigned i=0;i<(unsigned)(s[0]/(char)10);i++)
			{
				toDec[i]=s[i+1];
				lengthDescodif++;
			}
			switch ((s[0]%(char)10))
			{
			case 1:
				SetStr(toDec,(s[0]/(char)10),sizeof(char));
				break;
			case 2:
				SetStr(toDec,(s[0]/(char)10),sizeof(short));
				break;
			case 3:
			case 4:
				SetStr(toDec,(s[0]/(char)10),sizeof(unsigned));
				break;
			case 5:
				SetStr(toDec,(s[0]/(char)10),sizeof(float)+1);
				break;
			case 6:
				SetStr(toDec,(s[0]/(char)10),sizeof(double));
				break;
			default:
				return;
				break;
			}
		}
	}
};
class DataProcessor
{
public:
	DataProcessor(){};
	~DataProcessor(){};
	static bool BitData(char Byte,unsigned posttion)
    {
	if((Byte & 0x01<<posttion)==0)
		return 0;
	return 1;

    };
	static void PorcesarDatos(char Byte,GLfloat DataESE[3],GLfloat RazonDeAumento)
   {

	if(BitData(Byte,7))
	{
		if(BitData(Byte,4))
			DataESE[0]-=RazonDeAumento;
		else
			DataESE[0]+=RazonDeAumento;
	}
	if(BitData(Byte,6))
	{
		if(BitData(Byte,3))
			DataESE[1]-=RazonDeAumento;
		else
			DataESE[1]+=RazonDeAumento;
	}
	if(BitData(Byte,5))
	{
		if(BitData(Byte,2))
			DataESE[2]-=RazonDeAumento;
		else
			DataESE[2]+=RazonDeAumento;
	}


	//for(int i=2;i<8;i++)
	//{
	//	switch (i)
	//	{
	//	  case 2:
	//	  case 3:
	//	  case 4:
	//	  case 5:
	//	  case 6:
	//	  case 7:
	//		    if(BitData(Byte,i)==1)
	//		       {
	//			     if(BitData(Byte,i)==1)
	//					 angles[i-2]+=(GLfloat)0.9;
	//				 else
	//					 angles[i-2]-=(GLfloat)0.9;

	//				 if(angles[i-2]>=360)
	//					angles[i-2]-=360;
	//				else if(angles[i-2]<=-360)
	//					angles[i-2]+=360;
	//				else if (angles[i-2]==-0)
	//					angles[i-2]=0;

	//				angles[i-2]=(GLfloat)std::floor(100*(double)angles[i-2]+0.5)/100;
	//				 
	//		       }	
	//	         break;      	
	//   }//end switch
	//
	//}//end for


	

};
	static void RectificarAngules(GLfloat*angles){
	
	//comprobar angulos
		for(unsigned i=0;i<6;i++)
		{
			if(angles[i]>=360  )
				angles[i]-=360;
			else if(angles[i]<=-360)
				angles[i]+=360;
			else if (angles[i]==-0)
				angles[i]=0;
			
			angles[i-2]=(GLfloat)std::floor(100*(double)angles[i-2]+0.5)/100;
					 
		}
	
	

};
	static char* GetByteStr(char c)
	{
	char*f=new char[9];
	f[8]=0;
	for(int i=0;i<8;i++)
	{
		 if(BitData(c,i)==0)
			 f[7-i]='0';
		 else
			 f[7-i]='1';
	 }
	return f;
};
	static bool CodigoCliente(char Byte)
	{
		if(CodigoESE(Byte)&&DataProcessor::BitData(Byte,1)==1)
			return true;
		return false;	
	}
	/*static bool CodigoServer(char lowByte,char hightByte)
	{
		
		if(CodigoESE(lowByte,hightByte)&&DataProcessor::BitData(lowByte,1)==1&&lowByte>=(char)35)
			return true;
		if(lowByte==(char)59||lowByte==(char)115)
			return true;
		return false;	
	}*/
	static bool CodigoSeguridad(char Byte)
	{
		return (Byte==(char)19);
	}
	static bool CodigoESE(char Byte)
	{
		return DataProcessor::BitData(Byte,0);
			
	}	
	/*static bool ExistMensage59(char*mensajes)
	{
		for(unsigned i=0;i<strlen(mensajes);i+=2)
			if(mensajes[i]==(char)59)
				return true;
		return false;
	}*/
	/*static unsigned CantMensajes(char*mensajes)
	{
		unsigned cont=0;
		for(unsigned i=0;i<strlen(mensajes);i=+2)
			if(mensajes[i]==(char)59)
			{
				DataUnion du;

				du.SetStrCodif(&mensajes[i+1]);
				cont+=du.u.Unsigned+strlen(du.u.String)+1;
				i+=cont-2;
			}
			else
				cont++;
		return cont;

	}*/
	/////WebSocket
	static bool GetBit(char Byte,unsigned posittion)
    {
	if((Byte & 0x01<<posittion)==0)
		return 0;
	return 1;

    };
	static void printByte(char c,bool endL=true)
	{
		char*f=GetByteStr(c);
		if(endL)
			cout<<f<<endl;
		else
			printf(f);
		delete[]f;
	};
	static void SetBit(char&Byte,unsigned posittion,bool bit)
	{
		if(bit)
			Byte=(Byte | (0x01<<posittion));
		else
		{
			char _256=(char)255;
			_256=(_256^(0x01<<posittion));
			Byte=(Byte & _256);
		}
	}
	static char SetByte(char Byte[8])
	{
	char By=0x00;
	if(strlen(Byte)==8)
	{
		for(int i=7;i>=0;i--)
		{
			if(Byte[7-i]=='1')
				SetBit(By,i,true);
		}
	}
	return By;
	}
	static unsigned GetDataByStr(char*Str,unsigned CantBytes)
	{

	unsigned multip=1,ToReturn=0;
	int i=7*CantBytes;
	for(i;i>=0;i--)
	{
		if(Str[i]=='1')
			ToReturn+=multip;
		multip*=2;
	}
	return ToReturn;
	}
	static unsigned  GetDataByBinary(char*Binary,unsigned CantBytes)
	{

	unsigned multip=1,ToReturn=0;
	int i=7;
	for(int ii=(int)(CantBytes-1);ii>=0;ii--)
		for(i;i>=0;i--)
		{
			if(GetBit(Binary[ii],7*CantBytes-i))
				ToReturn+=(unsigned)multip;
			multip*=2;
		}
	return ToReturn;
	}
	static double Sin(double ang)
	{
		return sin(ang*PI/180);
	}
	static double Cos(double ang)
	{
		return cos(ang*PI/180);
	}
	static void CalcularCoordenadas(CRD&cooRd,GLfloat angles[6])
    {
	 // double cosFi1,senFi1,cosFi2,senFi2,cosFi3,senFi3,cosFi4,senFi4,cosFi5,senFi5,cosFi6,senFi6;  
	 // /*double q1=angles[0];
	 // double q2=angles[1];
	 // double q3=angles[2];
	 // double q4=angles[3];
	 // double q5=angles[4];
	 // double q6=angles[5];*/
  //	  cosFi1=cos((angles[0])*PI/180);
  //    senFi1=sin((angles[0])*PI/180);
  //    cosFi2=cos(angles[1]*PI/180);
  //    senFi2=sin(angles[1]*PI/180);
  //    cosFi3=cos((angles[2])*PI/180);
  //    senFi3=sin((angles[2])*PI/180);
  //    cosFi4=cos(angles[3]*PI/180);
  //    senFi4=sin(angles[3]*PI/180);
  //    cosFi5=cos((angles[4]-90)*PI/180);
  //    senFi5=sin((angles[4]-90)*PI/180);
	 // cosFi6=cos((angles[5])*PI/180);
  //    senFi6=sin((angles[5])*PI/180);
	
	 //cooRd.x=  (12901*senFi1)/500 + 150*cosFi1*cosFi2 - (1223*cosFi5*senFi1)/20 + 177*senFi6*(senFi1*senFi5 - cosFi5*(cosFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3) - senFi4*(cosFi1*cosFi2*senFi3 + cosFi1*cosFi3*senFi2))) - 177*cosFi6*(cosFi4*(cosFi1*cosFi2*senFi3 + cosFi1*cosFi3*senFi2) + senFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3)) - (1223*senFi5*(cosFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3) - senFi4*(cosFi1*cosFi2*senFi3 + cosFi1*cosFi3*senFi2)))/20 + (4027889324543443*cosFi1*cosFi2*cosFi3)/17592186044416 - (4027889324543443*cosFi1*senFi2*senFi3)/17592186044416;
	 //cooRd.y=(1223*cosFi1*cosFi5)/20 - 177*cosFi6*(cosFi4*(cosFi2*senFi1*senFi3 + cosFi3*senFi1*senFi2) + senFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3)) - (12901*cosFi1)/500 - (1223*senFi5*(cosFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3) - senFi4*(cosFi2*senFi1*senFi3 + cosFi3*senFi1*senFi2)))/20 + 150*cosFi2*senFi1 - 177*senFi6*(cosFi5*(cosFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3) - senFi4*(cosFi2*senFi1*senFi3 + cosFi3*senFi1*senFi2)) + cosFi1*senFi5) + (4027889324543443*cosFi2*cosFi3*senFi1)/17592186044416 - (4027889324543443*senFi1*senFi2*senFi3)/17592186044416;
  //   cooRd.z=(1223*senFi5*(cosFi4*(cosFi2*senFi3 + cosFi3*senFi2) + senFi4*(cosFi2*cosFi3 - senFi2*senFi3)))/20 - (4027889324543443*cosFi2*senFi3)/17592186044416 - (4027889324543443*cosFi3*senFi2)/17592186044416 - 177*cosFi6*(cosFi4*(cosFi2*cosFi3 - senFi2*senFi3) - senFi4*(cosFi2*senFi3 + cosFi3*senFi2)) - 150*senFi2 + 177*cosFi5*senFi6*(cosFi4*(cosFi2*senFi3 + cosFi3*senFi2) + senFi4*(cosFi2*cosFi3 - senFi2*senFi3)) + 883/10;
  //    
	 
	  //cooRd.x=(233*Sin(q1))/10 - (12181*Sin(q1)*Sin(q5))/200 + (6*Cos(q1)*(191*Cos((q2 + q3)) + 125*Cos(q2)))/5 + 177*Cos(q6)*(Cos(q5)*Sin(q1) + Cos((q2 + q3 + q4))*Cos(q1)*Sin(q5)) + (12181*Cos((q2 + q3 + q4))*Cos(q1)*Cos(q5))/200 + 177*Sin((q2 + q3 + q4))*Cos(q1)*Sin(q6);
	  //cooRd.y=(12181*Cos(q1)*Sin(q5))/200 - (233*Cos(q1))/10 - 177*Cos(q6)*(Cos(q1)*Cos(q5) - Cos((q2 + q3 + q4))*Sin(q1)*Sin(q5)) + (6*Sin(q1)*(191*Cos((q2 + q3)) + 125*Cos(q2)))/5 + (12181*Cos((q2 + q3 + q4))*Cos(q5)*Sin(q1))/200 + 177*Sin((q2 + q3 + q4))*Sin(q1)*Sin(q6);
	  //cooRd.z= (1146*Sin((q2 + q3)))/5 + 150*Sin(q2) + (12181*Sin((q2 + q3 + q4))*Cos(q5))/200 - 177*Cos((q2 + q3 + q4))*Sin(q6) + 177*Sin((q2 + q3 + q4))*Cos(q6)*Sin(q5) + (double)469/5;

} 
//    static void CalcularCoordenadas()
//  {
//	  CalcularCoordenadasEnviandoleDinamicamente(cooRd,angles);
//	 // double cosFi1,senFi1,cosFi2,senFi2,cosFi3,senFi3,cosFi4,senFi4,cosFi5,senFi5,cosFi6,senFi6,cosAlfa7,senAlfa7,senFi7,cosFi7;
//	 // double q1=angles[0];
//	 // double q2=angles[1];
//	 // double q3=angles[2];
//	 // double q4=angles[3];
//	 // double q5=angles[4];
//	 // double q6=angles[5];	  
//	 // cosFi1=cos((angles[0])*PI/180);
//  //    senFi1=sin((angles[0])*PI/180);
//  //    cosFi2=cos(angles[1]*PI/180);
//  //    senFi2=sin(angles[1]*PI/180);
//  //    cosFi3=cos((angles[2])*PI/180);
//  //    senFi3=sin((angles[2])*PI/180);
//  //    cosFi4=cos(angles[3]*PI/180);
//  //    senFi4=sin(angles[3]*PI/180);
//  //    cosFi5=cos((angles[4]-90)*PI/180);
//  //    senFi5=sin((angles[4]-90)*PI/180);
//	 // cosFi6=cos((angles[5])*PI/180);
//  //    senFi6=sin((angles[5])*PI/180);
//	 // cosAlfa7=cos( 0 *PI/180);
//	 // senAlfa7=sin( 0 *PI/180);
//	 // senFi7=sin( 90 *PI/180);
//	 // cosFi7=cos(90 *PI/180);
//	
//	 ////cooRd.x=  (12901*senFi1)/500 + 150*cosFi1*cosFi2 - (1223*cosFi5*senFi1)/20 + 177*senFi6*(senFi1*senFi5 - cosFi5*(cosFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3) - senFi4*(cosFi1*cosFi2*senFi3 + cosFi1*cosFi3*senFi2))) - 177*cosFi6*(cosFi4*(cosFi1*cosFi2*senFi3 + cosFi1*cosFi3*senFi2) + senFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3)) - (1223*senFi5*(cosFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3) - senFi4*(cosFi1*cosFi2*senFi3 + cosFi1*cosFi3*senFi2)))/20 + (4027889324543443*cosFi1*cosFi2*cosFi3)/17592186044416 - (4027889324543443*cosFi1*senFi2*senFi3)/17592186044416;
//	 ////cooRd.y=(1223*cosFi1*cosFi5)/20 - 177*cosFi6*(cosFi4*(cosFi2*senFi1*senFi3 + cosFi3*senFi1*senFi2) + senFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3)) - (12901*cosFi1)/500 - (1223*senFi5*(cosFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3) - senFi4*(cosFi2*senFi1*senFi3 + cosFi3*senFi1*senFi2)))/20 + 150*cosFi2*senFi1 - 177*senFi6*(cosFi5*(cosFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3) - senFi4*(cosFi2*senFi1*senFi3 + cosFi3*senFi1*senFi2)) + cosFi1*senFi5) + (4027889324543443*cosFi2*cosFi3*senFi1)/17592186044416 - (4027889324543443*senFi1*senFi2*senFi3)/17592186044416;
//  //   //cooRd.z=(1223*senFi5*(cosFi4*(cosFi2*senFi3 + cosFi3*senFi2) + senFi4*(cosFi2*cosFi3 - senFi2*senFi3)))/20 - (4027889324543443*cosFi2*senFi3)/17592186044416 - (4027889324543443*cosFi3*senFi2)/17592186044416 - 177*cosFi6*(cosFi4*(cosFi2*cosFi3 - senFi2*senFi3) - senFi4*(cosFi2*senFi3 + cosFi3*senFi2)) - 150*senFi2 + 177*cosFi5*senFi6*(cosFi4*(cosFi2*senFi3 + cosFi3*senFi2) + senFi4*(cosFi2*cosFi3 - senFi2*senFi3)) + 883/10;
//  //    
//	 // cooRd.x=(233*sin(q1*PI/180))/10 - (12181*sin(q1*PI/180)*sin(q5*PI/180))/200 + (6*cos(q1*PI/180)*(191*cos((q2 + q3)*PI/180) + 125*cos(q2*PI/180)))/5 + 177*cos(q6*PI/180)*(cos(q5*PI/180)*sin(q1) + cos((q2 + q3 + q4)*PI/180)*cos(q1*PI/180)*sin(q5*PI/180)) + (12181*cos((q2 + q3 + q4)*PI/180)*cos(q1*PI/180)*cos(q5*PI/180))/200 + 177*sin((q2 + q3 + q4)*PI/180)*cos(q1*PI/180)*sin(q6*PI/180);
//		//cooRd.y=(12181*cos(q1*PI/180)*sin(q5*PI/180))/200 - (233*cos(q1*PI/180))/10 - 177*cos(q6*PI/180)*(cos(q1*PI/180)*cos(q5*PI/180) - cos((q2 + q3 + q4)*PI/180)*sin(q1*PI/180)*sin(q5*PI/180)) + (6*sin(q1*PI/180)*(191*cos((q2 + q3)*PI/180) + 125*cos(q2*PI/180)))/5 + (12181*cos((q2 + q3 + q4)*PI/180)*cos(q5*PI/180)*sin(q1*PI/180))/200 + 177*sin((q2 + q3 + q4)*PI/180)*sin(q1*PI/180)*sin(q6*PI/180);
//		//cooRd.z= (1146*sin((q2 + q3)*PI/180))/5 + 150*sin(q2*PI/180) + (12181*sin((q2 + q3 + q4)*PI/180)*cos(q5*PI/180))/200 - 177*cos((q2 + q3 + q4)*PI/180)*sin(q6*PI/180) + 177*sin((q2 + q3 + q4)*PI/180)*cos(q6*PI/180)*sin(q5*PI/180) + 469/5;
//		////cooRd.x=(233*sin(q1))/10 - (12181*sin(q1)*sin(q5))/200 + (6*cos(q1)*(191*cos((q2 + q3)) + 125*cos(q2)))/5 + 177*cos(q6)*(cos(q5)*sin(q1) + cos((q2 + q3 + q4))*cos(q1)*sin(q5)) + (12181*cos((q2 + q3 + q4))*cos(q1)*cos(q5))/200 + 177*sin((q2 + q3 + q4))*cos(q1)*sin(q6);
//		////cooRd.y=(12181*cos(q1)*sin(q5))/200 - (233*cos(q1))/10 - 177*cos(q6)*(cos(q1)*cos(q5) - cos((q2 + q3 + q4))*sin(q1)*sin(q5)) + (6*sin(q1)*(191*cos((q2 + q3)) + 125*cos(q2)))/5 + (12181*cos((q2 + q3 + q4))*cos(q5)*sin(q1))/200 + 177*sin((q2 + q3 + q4))*sin(q1)*sin(q6);
//		////cooRd.z= (1146*sin((q2 + q3)))/5 + 150*sin(q2) + (12181*sin((q2 + q3 + q4))*cos(q5))/200 - 177*cos((q2 + q3 + q4))*sin(q6) + 177*sin((q2 + q3 + q4))*cos(q6)*sin(q5) + 469/5;
//
//}
};

