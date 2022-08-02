#pragma once
#include "GL\freeglut.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <thread>
#include <mutex>
#include <string.h>
#include "LoaderObject.h"
#include "StackLoaderObject.h"
#include <string>
#include "CRD.h"
#include "DataProcessor.h"
#include "TimeDuration.h"
#include "MeSSenger.h"
#include "StackForms.h"
#include "Plano.h"
#include "StackSketchs.h"
#include "Box.h"
#include "Animacion.h"
#include "StackAnimation.h"
#include "Connection.h"
#include "XLSClass.h"
#include <mmsystem.h>
#include "Container.h"
#include "StackMessenger.h"
#define RazonDeAumento 1

using namespace std;
enum Language
{
	ENGLISH	,SPANISH
};
 class ESE_CRT

{
public:
	ESE_CRT();
	~ESE_CRT();
	////////////DIBUJAR
	static void display();
	static void Entorno();
	static void text(char*c,GLfloat x,GLfloat y,GLfloat z,GLfloat R=1.0,GLfloat G=1.0,GLfloat B=1.0,bool big=false,bool moreBig=false);
	static void smallEjeCoord(GLfloat size=10);
	static void ShowAngules(bool IsAtCreate=false,bool IsAtReciv=false);
	static Box* Interfaz(unsigned interfz=0,INTERFZType Buttom=INTERFZType::SPECIFIC);
	///////////DEFAULTGLUTS
	static void movRaton(GLsizei x,GLsizei y);
	static void movPasiveRaton(GLsizei x,GLsizei y);
	static void teclaRaton(int boton,int state,int x,int y);
	static void reshape(int x,int y);
	static void initProyecc();
	static void wheelAndRotate();
	static void Idle();
	static void Inicializar();
	static bool IniciarCargObjetos();
	static void wheel(int boton,int direcc,int x,int y);
	static void keyboard(unsigned char tecla,int x,int y );
	static void SpecialKeys(int tecla,int x,int y );
	///////////MENUS
	static void InitMenu();
	static void MenuPuertoSeie(int caso);
	static void MenuVista(int opcion);
	static void MenuToDraw(int caso);
	static void default_menu(int opcion);
	static void MenuIdioma(int opcion);
	//////////////DATOS
   	static void cargarInitDatos();
	static void salvarInitDatos();
	static void recivirDatosCOM();
	//static char* VerificacionDatos(char*cc,unsigned&strleN);
	//static void Acceso(bool acceso);
	//static bool ChekEntada(char*c,unsigned&i);
	static bool VerificacionSeguridad(char c);
	static bool CodigoCliente(char c,bool&pintar);
	static bool SetAnglesREdirecc();
	//HILOS
	static void ThreadCOM();
	static void ThreadCargObject();
 };

