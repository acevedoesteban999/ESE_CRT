#pragma once
#include <iostream>
#include <winsock.h>
#include <windows.h>
#include <string>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
enum ConnectionType
{
 CONNECTION,SERIAL_PORT//,SOCKET_SERVER,SOCKET_CLIENT,WEBSOCKET_CLIENT
};
class Connection
{
protected:
	ConnectionType t;
	bool IsConectado;
	bool error;
	char*errorstr,*message; 
public:
	Connection(){
		t=ConnectionType::CONNECTION;
		IsConectado=error=false;
		errorstr=new char[1];
		errorstr[0]=0;
		message=new char[1];
		message[0]=0;
	};
	virtual ~Connection()
	{
		delete[]errorstr;
		delete[]message;
	};
	virtual void CloseConnection(){};
	virtual bool inicializa(const char*Ip, unsigned long Port){return false;};
	virtual char* Recibir(SOCKET socket=NULL)
	{
		/*if(EstaConectado())
		{
			 memset(buffer,0,sizeof(buffer));
			 int n=recv(t==ConnectionType::SOCKET_SERVER?cliente:server,buffer,sizeof(buffer),0);
			 if(n==0)
			 {
				 string s("Error 0 ");
				 errorstr=new char[s.length()+1];
				 for(unsigned i=0;i<s.length();i++)
					 errorstr[i]=s[i];
				 error=true;
				 return NULL;
			 }
			 if(n==-1)
			 {
					string s("C_Error 1 ");
					errorstr=new char[s.length()+1];
					for(unsigned i=0;i<s.length();i++)
						errorstr[i]=s[i];
					error=true;
					return NULL;
			 }
			 return buffer;
		}*/
		return NULL;
	 };
	virtual void Trasmitir( char*buffer,SOCKET s=NULL){
		/*int n=send(t==ConnectionType::SOCKET_SERVER?cliente:server,buffer,strlen(buffer),0);
		 if(n==0)
		 {
		  string s("Error 0 ");
	      errorstr=new char[s.length()+1];
		  for(unsigned i=0;i<s.length();i++)
			 errorstr[i]=s[i];
		  error=true;
		  return;
		 }
		  if(n==-1)
		 {
			string s("Error 1 ");
			errorstr=new char[s.length()+1];
			for(unsigned i=0;i<s.length();i++)
				errorstr[i]=s[i];
		    error=true;
			return;
		 }*/
	 };
	virtual char*getChar(){return nullptr;};
	virtual unsigned getunsigned(){return 0;};
	virtual unsigned getContClientesServer(){return 0;};
	virtual bool GetCientesStatus(){return false;};
	bool Error(){return error;};
	bool EstaConectado(){return IsConectado;};
	char* ErrorStr(){return errorstr;};
	ConnectionType GetType(){return t;};
	static void SetType(ConnectionType CT,Connection&conn){conn.t=CT;};
	static char* GetMesage(Connection&conn){
		string s(string(conn.getChar())+":"+to_string(conn.getunsigned()));
		delete[]conn.message;
		conn.message=new char[s.length()+1];
		conn.message[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			conn.message[i]=s[i];
		return conn.message;
		
	};
};
class SerialPort:public Connection
{
	
private:
	HANDLE handler;
	char*Puerto;
	unsigned long Speed;
public:
	SerialPort():Connection()
	{
		Puerto=new char[1];
		this->t=ConnectionType::SERIAL_PORT;
	};
	//PuertoSerie(System::String^PuertoCom, unsigned long Velocidad);
	~SerialPort()
    {
		delete[]Puerto;
		CloseConnection();
    }
	void CloseConnection()
	{
		if(IsConectado)
		{
		   IsConectado=false;
		   CloseHandle(handler);
	    }
	
	}
	bool inicializa(const char* PuertoCom, unsigned long Velocidad)
{
	handler=CreateFile(PuertoCom,GENERIC_READ | GENERIC_WRITE,NULL,NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	if (handler==INVALID_HANDLE_VALUE)
	{
		string s("C_Error 0 :"+string(PuertoCom)+":"+to_string(Velocidad));
		delete[]errorstr;
		errorstr=new char[s.length()+1];
		errorstr[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			 errorstr[i]=s[i];
		error=true;
		return false;
	}
	DCB ParametrosTxSerie;
	if (!GetCommState(handler,&ParametrosTxSerie))
	{
		string s("Error 1 :"+string(PuertoCom)+":"+to_string(Velocidad));
		delete[]errorstr;
		errorstr=new char[s.length()+1];
		errorstr[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			errorstr[i]=s[i];
		error=true;
		return false;
	}
	ParametrosTxSerie.DCBlength=sizeof(DCB);
	ParametrosTxSerie.BaudRate=Velocidad;
	ParametrosTxSerie.ByteSize=8;
	ParametrosTxSerie.StopBits=TWOSTOPBITS;
	ParametrosTxSerie.Parity=(BYTE)PARITY_NONE;
	if(!SetCommState(handler,&ParametrosTxSerie))
	{
		string s("Error 2 :"+string(PuertoCom)+":"+to_string(Velocidad));
		delete[]errorstr;
		errorstr=new char[s.length()+1];
		errorstr[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			errorstr[i]=s[i];
		error=true;
		return false;
	}
	IsConectado=true;
	PurgeComm(handler,PURGE_RXCLEAR|PURGE_TXCLEAR);
	error=false;
	delete[]this->Puerto;
	this->Puerto=new char[strlen(PuertoCom)+1];
	this->Puerto[strlen(PuertoCom)]=0;
	for(unsigned i=0;i<strlen(PuertoCom);i++)
		this->Puerto[i]=PuertoCom[i];
	this->Speed=Velocidad;
	return true;
}
	char* Recibir(SOCKET socket=NULL)
	{
		char*cadena=NULL;
		if(EstaConectado())
		{
			DWORD leidos;
			COMSTAT cs;
			if(ClearCommError(handler,&leidos,&cs)==0)
			{
				this->error=true;
				string s("Error 0 ");
				delete[]errorstr;
				errorstr=new char[s.length()+1];
				errorstr[s.length()]=0;
				for(unsigned i=0;i<s.length();i++)
					 errorstr[i]=s[i];
				return cadena;
			}
			leidos=0;
			if(cs.cbInQue)
			{
				cadena=new char[cs.cbInQue+3];
				cadena[cs.cbInQue]=0;
				ReadFile(handler,cadena,cs.cbInQue,&leidos,NULL);
				return cadena;
			}
		}
		return cadena;
	};
	void Trasmitir(char *oBuffer,SOCKET s=NULL)
	{
	DWORD iBytesWritten;
	iBytesWritten=0;
	WriteFile(handler,oBuffer,strlen(oBuffer),&iBytesWritten,NULL);
	}
	//void Trasmitir(System::String^data);
	char*getChar(){return Puerto;};
	unsigned getunsigned(){return Speed;};
};
