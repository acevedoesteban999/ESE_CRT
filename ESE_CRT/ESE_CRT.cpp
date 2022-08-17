#include "ESE_CRT.h"
////////////////////////////////////////////////////////////////VERSION//////////////////////////////////////////////////////////
														char*ESE_CRT_Version="1.2.0";
///////////////////////////////////////////////////////////VARIABLES GLOBALES////////////////////////////////////////////////////
bool recibir_serie=false;
bool CargObjct=false,cargMenu=false;
bool EsperandoReedireccionar=true;
bool threaDCOM=false,MostrarAngules=false,SeguirPuntoFinal=false;
bool SetAngules=false;
bool RotarAlPlanoContrar=false;
bool boolMenuToDraw=false;
bool cursor=false;
bool deFult=true;
bool Boxf1=false;
bool BoxAbout=false;
bool BoxReconnect=false;
bool BoxExit=false;
bool StopThread=false;
bool ErrorConnect=false;
bool ActiveDesactAcept=false;
bool ActiveDesactCancel=false;
bool ModoSonido=false;
bool ModoLogger=true;
bool bytBool=false;
bool Acces=false;
bool PlanoAcceso=false;
bool VariablesDestruidas=false;
bool AceptCancelButtonDesdeThread=false;
bool IsRedireccDraw=false;
//////////////GRABAR///////////
unsigned connstGrab=10000;
bool GrabarBool=false;
char Grabar[10000];
unsigned GrabarCont=0;
float GrabarAngle[3];
/////////////////////////////
char byt;
char*toSaveCOM="COM2",*toSaveIp="127.0.0.1",*toSaveHost="localhost";
unsigned toSaveSpeed=9600,toSavePort=55555,toSavePortWeb=8080;
unsigned STRLEN,BoxInterfazPricipalL=0,RadioButtonRestriccion=0;
unsigned bocetoARemover=0,RadioButtomPintar=0,PlanoChecket=0,bocetoACrear=0,BoxInterfaz0=0;
unsigned CambiarPointSpecificPlano=3;
unsigned contClientesServer=0,contAngleRedirecc=0;
int interfaz=0;
int contMenuToDraw=-1;
int contt=0;
int Window=0;
int Initheight,Initwigth;
int MenuCD,SubMenuVista,subMenuIdioma,subMenuToDraw;
int height,wigth;
float movRatXinit=25,movRatYinit=0,movRatX=10,movRatY=0;
float velGiro=3;
float &movESE_CRTX=movRatX,&movESE_CRTY=movRatY,movESE_CRTZ=25;
double trasladarX=0,trasladarY=0,trasladarZ=0;
double anglesRedirecc[3]={0,0,0};
GLfloat DataESE[3]={0,0,0};
GLfloat heightOrtho,wigthOrtho;
GLdouble movWheel=1;
Language idioma=SPANISH;
ConnectionType Connecttype=ConnectionType::SERIAL_PORT;
///////////////////OBJECTS//////////////////////////////////////
//CRD cooRd(0,0,0);
CRD cooRd()
{
	return CRD(DataESE[0],DataESE[1],DataESE[2]);
}
StackLoaderObject*ManejadorObject=new StackLoaderObject(DataESE);
SerialPort serialPort;
TimeDuration tCOM(true);
StackSketchs*ManejadorSketchs=new StackSketchs();
thread*ThreadLoadObject=new thread();
thread*ThreadSerialPort=new thread();
//mutex MutexManejadorForms,MutexManejadorSketchs;
//MeSSenger*messeng=new MeSSenger();
StackForms*ManejadorForms=new StackForms();
_manejadorForms _ManejadorForms;
//NO DELETE(MAMEJADORFORMS DELETE)
_containerPrincipal*ContainerPrincipal=new _containerPrincipal("ContainerPrincipal",ESE_CRT_Version,&wigth,&height);
_boxInterfazPrincipal*BoxInterfazPricipal=new _boxInterfazPrincipal("BoxInterfazPricipal",CRD(300,100,0),&wigth,&height);
_boxConnection*BoxConnection=new _boxConnection("BoxConnection",CRD(500,100),toSaveIp,&toSavePort,&wigth,&height,ESE_CRT::IniciarConnection,ESE_CRT::DetenerConnection);
///////////////////////////////////////////////////////////METODOS//////////////////////////////////////////////////////////////
StackMessenger*ManejadorMensajes=new StackMessenger();
///////////////////FUNCIONES GLOBALES/////////////////////////////////////////////////
void sonidos(unsigned sonido)
{
	switch (sonido)
	{
	case 1:
		PlaySound("data/audio/1.wav",NULL,SND_FILENAME |SND_ASYNC);
	break;
	case 2:
		PlaySound("data/audio/2.wav",NULL,SND_FILENAME |SND_ASYNC);
	break;
	case 3:
		PlaySound("data/audio/3.wav",NULL,SND_FILENAME |SND_ASYNC);
	break;
	case 4:
		PlaySound("data/audio/4.wav",NULL,SND_FILENAME |SND_ASYNC);
	break;
	case 5:
		PlaySound("data/audio/5.wav",NULL,SND_FILENAME |SND_ASYNC);
	break;
	case 6:
		PlaySound("data/audio/6.wav",NULL,SND_FILENAME |SND_ASYNC);
	break;
	case 7:
		PlaySound("data/audio/7.wav",NULL,SND_FILENAME |SND_ASYNC);
	break;
	case 8:
		PlaySound("data/audio/8.wav",NULL,SND_FILENAME |SND_ASYNC);
	break;
	case 9:
		PlaySound("data/audio/9.wav",NULL,SND_FILENAME |SND_ASYNC);
	break;
	case 10:
		PlaySound("data/audio/10.wav",NULL,SND_FILENAME |SND_ASYNC);
	break;
	}
		
	
		//PlaySound("data/audio/4.wav",NULL,SND_FILENAME |SND_ASYNC);
}
char*Frases(unsigned frase)
{
	string s;
	char*toReturn;
	switch (frase)
	{
	case 300:
		return "Ang_REdirecc";
	case 400:
		return "Objetos Cargados Correctamente";
	case 301:
		return "AngulosRedirecc Actualizados";
	case 302:
		return "Error al Actualizar AngulosRedirecc";
	case 100:
		return ESE_CRT_Version;
	case 84:
		s="ESE_CRT version ";
		s+=Frases(100);
		toReturn=new char[s.length()];
		toReturn[s.length()]=0;
		for (unsigned i=0;  i < s.length(); i++)
			toReturn[i]=s[i];
		return toReturn;
	case 86:
		return "https://github.com/Esteban191900/ESE_CRT-Class/";
	}
	switch (idioma)
	{
		case SPANISH:
			switch (frase)
			{
			   case 0:
				return "Editar Bocetos";
				
		       case 1:
				return "Salvar Bocetos";
				
			   case 2:
				return "Bocetos:" ;
				
			   case 3:
				return "Vista Total" ;
				
				case 4:
				return "Agregar" ;
				
				case 5:
				return "Quitar" ;
				
				case 6:
				return "English" ;
				
				case 7:
				return "Puntos" ;
				
				case 8:
				return "Lineas" ;
				
				case 9:
				return "StripLine" ;
				
				case 10:
				return "Splines" ;
				
				case 11:
				return "Cancelar" ;
				
				case 12:
				return "Mostrar" ;
				
				case 13:
				return "A Crear: " ;
				
				case 14:
				return "Plano Nuevo" ;
				
				case 15:
				return "Plano Libre" ;
				
				case 16:
				return "Plano XY" ;
				
				case 17:
				return "Plano XZ" ;
				
				case 18:
				return "Plano YZ" ;
				
				case 19:
				return "Por defecto" ;
				
				case 20:
				return "Punto Fianal" ;
				
				case 21:
				return "Boceto_" ;
				
				case 22:
				return "Fboceto_" ;
				
				case 23:
				return "Puntos:" ;
				
				case 24:
				return "A Remover:  " ;
				
				case 25:
				return "Unirse al Host" ;
				
				case 26:
				return "Puerto Serie" ;
				
				case 27:
				return "Terminar?" ;
				
				case 28:
				return "A Salvar:" ;
				
				case 29:
				return "Todos los Bocetos" ;
				
				case 30:
				return "Panoramica" ;
				
				case 31:
				return "Frontal(XY)" ;
				
				case 32:
				return "Posterior(-XY)" ;
				
				case 33:
				return "Derecha(ZY)" ;
				
				case 34:
				return "Izquierda(-ZY)" ;
				
				case 35:
				return "Superior(X-Z)";
				
				case 36:
				return "Inferior(XZ)";
				
				case 37:
				return "Unir Piezas";
				
				case 38:
				return "Inicar Conexion";
				
				case 39:
				return "Vista";
				
				case 40:
				return "Modelo a Pintar";
				
				case 41:
				return "Establecer Angulos";
				
				case 42:
				return "Idioma";
				
				case 43:
				return "Detener Conexion";
				
				case 44:
				return "Error; nombre en uso";
				
				case 45:
				return "Conexion finalizada";  
				
				case 46:
				return "Salvado en  .../ESE_CRT-XLS/";
				
				case 47:
				return "Error tratando de salvar los archivos";
				
				case 48:
				return "Error; Entrada Incorrecta";
				
				case 49:
				return "Se ha cargado correctamente";
				
				case 50:
				return "Error; Conexion ya Establecida";
				
				case 51:
				return "Redireccionado correctamente";
				
				case 52:
				return "Detalles";
				
				case 53:
				return "->Verificacion";
				
				case 54:
				return "->Error:Verificacion Adelantada";
				
				case 55:
				return "->Error:Verificacion Atrasada";
				
				case 56:
				return "Codigo:";
				
				case 57:
				return "->Redireccionamiento";
				
				case 58:
				return "->Siguiente Focus";
				
				case 59:
				return "->Focus Click";
				
				case 60:
				return "->Boton Aceptar";

				case 61:
				return "->Boton Cancelar";
				
				case 62:
				return "Algunos cambios de idoma no se aplicaran hasta el reinicio";
				
				case 63:
				return ":Error;No hay Funcionaidad para dicha Entrada";
				
				case 64:
				return "!!Esperando Referenaciar!!";
				
				case 65:
				return "Esperando Referenaciar";
				
				case 66:
				return "Idioma cambiado a Spanish";
				
				case 67:
				return "Spanish";
				
				case 68:
				return "Habilitar Modo Registro";
				
				case 69:
				return "Deshabilitar Modo Registro";
				
				case 70:
				return "BSpline";
				
				case 71:
				return "F1-Ayuda";
				
				case 72:
				return "F2-Mostrar / Ocultar Piezas (.obj)";
				
				case 73:
				return "F3-Rotar al plano (Solo para interfaz de dibujo)";
				
				case 74:
				return "F4-Vista panoramica con angulos de articulacion en 0 (Sin conexion establecida)";
				
				case 75:
				return "F5-Vista panoramica con Redireccionamiento (Sin conexion establecida)";
				
				case 76:
				return "F6-Ir al punto final del brazo";
				
				case 77:
				return "F7-Seguir al punto final del brazo";
				
				case 78:
				return "F8-Ir a una 'Media' entre todos los punto de un plano (Solo para interfaz de dibujo)";
				
				case 79:
				return "Conexion Finalizada";
				
				case 80:
				return "Modo Registro Desactivado";
				
				case 81:
				return "Modo Registro Activado";
				
				case 82:
				return "Cuidado, se ha producido un error al cargar los ficheros";
				
				case 83:
				return "Sobre ESE_CRT";
				
				case 85:
				return "Enlace del Github:";
				
				case 87:
				return "Copiar Enlace";
				
				case 88:
				return "El Enlace se ha Copiado";
				
				case 89:
				return "Reconectando con el servidor";
				
				case 90:
				return "Desconectar";
				
				case 91:
					return "Conexion Reestablecida";

				case 92:
					return "Cargando Objetos ";

				case 93:
					return "Habilitar Sonido";

				case 94:
					return "Deshabilitar Sonido";
				
				case 95:
					return "Sonido Activado";

				case 96:
					return "Sonido Desactivado";

				case 97:
					return "Salir?";

				case 98:
					return "Salir";
				
				case 99:
					return "Error al Conectar con ";

				case 101:
					return "Conexion Perdida";

				case 102:
					return "Servidor Cerrado";

				case 103:
					return "Acceso";

				case 104:
					return "Sin Acceso";

				case 105:
					return "Acceso Concedido";

				case 106:
					return "Acceso Denegado";

				case 107:
					return "Solicitar Acceso";

				case 108:
					return "Quitar Acceso";

				case 109:
					return "Se tiene Acceso";

				case 110:
					return "No se tiene Acceso";

				case 111:
					return "Web Host";

				case 112:
					return "Esperando Referenaciar para transmitir boceto";

				case 113:
					return "Boceto Transmitido";

				case 114:
					return "Referenciado";

				case 115:
					return "Sin Referenaciar";

				case 116:
					return "Quitar Boceto";

				case 117:
					return "Agregar Boceto";

				case 118:
					return "Item:Puntos";

				case 119:
					return "Item:Lineas";
				
				case 120:
					return "Item:StripLineas";
				
				case 121:
					return "Item:SpLines";
				
				case 122:
					return "Item:Bspline";
				
				case 123:
					return "Cancelar ultimo punto";
				
				case 124:
					return "Mostrar Plano";
				
				case 125:
					return "Ocultar Plano";
				
				case 126:
					return "Obtener USER";

				case 127:
					return "Perder USER";
				
				case 128:
					return "Iniciar Host";
				default:
				return "No Encontrado";	

			}
		break;
	case ENGLISH:
			switch (frase)
			{
			   case 0:
				return "Edit Sketchs";
				
		       case 1:
				return "Save Sketchs";
				
			   case 2:
				return "Sketchs:" ;
				
			   case 3:
				return "Total View" ;
				
				case 4:
				return "Add" ;
				
				case 5:
				return "Sub" ;
				
				case 6:
				return "English" ;
				
				case 7:
				return "Points" ;
				
				case 8:
				return "Lines" ;
				
				case 9:
				return "StripLine" ;
				
				case 10:
				return "Splines" ;
				
				case 11:
				return "Cancel" ;
				
				case 12:
				return "Show" ;
				
				case 13:
				return "To Create: " ;
				
				case 14:
				return "New Plane" ;
				
				case 15:
				return "Free Plane" ;
				
				case 16:
				return "Plane XY" ;
				
				case 17:
				return "Plane XZ" ;
				
				case 18:
				return "Plane YZ" ;
				
				case 19:
				return "Default" ;
				
				case 20:
				return "End Point" ;
				
				case 21:
				return "Sketch_" ;
				
				case 22:
				return "Fsketch_" ;
				
				case 23:
				return "Points:" ;
				
				case 24:
				return "To Remove:  " ;
				
				case 25:
				return "TCP_IP" ;
				
				case 26:
				return "Serial Port" ;
				
				case 27:
				return "Finish?" ;
				
				case 28:
				return "To Save:" ;
				
				case 29:
				return "All Sketchs" ;
				
				case 30:
				return "Panoramic" ;
				
				case 31:
				return "Frontal(XY)" ;
				
				case 32:
				return "Posterior(-XY)" ;
				
				case 33:
				return "Rigth(ZY)" ;
				
				case 34:
				return "Left(-ZY)" ;
				
				case 35:
				return "Top(X-Z)";
				
				case 36:
				return "Bottom (XZ)";
				
				case 37:
				return "Join Pieces";
				
				case 38:
				return "Star Connection";
				
				case 39:
				return "View";
				
				case 40:
				return "Model to Draw";
				
				case 41:
				return "Set Angles";
				
				case 42:
				return "Language";
				
				case 43:
				return "Stop Connection";
				
				case 44:
				return "Error, name in use";
								 
				case 45:
				return "Finish Connection";  
				
				case 46:
				return "Saved at .../ESE_CRT-XLS/";
				
				case 47:
				return "Error trying to save files";
				
				case 48:
				return "Error ,wrong inmput";
				
				case 49:
				return "Has been loaded successfully";
				
				case 50:
				return "Error ;Connection already established";
				
				case 51:
				return "Correct Redirection";
				
				case 52:
				return "Details";
				
				case 53:
				return "->Check";
				
				case 54:
				return "->Error:Advance verification";
				
				case 55:
				return "->Error:Delayed verification";
				
				case 56:
				return "Code:";
				
				case 57:
				return "->Redirection";
				
				case 58:
				return "->Next Focus";
				
				case 59:
				return "->Focus Click";
				
				case 60:
				return "->Button Acept";

				case 61:
				return "->Button Cancel";
				
				case 62:
				return "Some language changes will not be applied until reboot"; 
				
				case 63:
				return ":Error;there is no functionality programmed for that input";
				
				case 64:
				return "!!Waiting for Redirection!!";
				
				case 65:
				return "Waiting for Redirection";
				
				case 66:
				return "Language changed to English";
				
				case 67:
				return "Spanish";
				
				case 68:
				return "Enable record mode";
				
				case 69:
				return "Disable record mode";
				
				case 70:
				return "BSpline";
				
				case 71:
				return "F1-Help";
				
				case 72:
				return "F2-Show / Hide Pices(.obj)";
				
				case 73:
				return "F3-Rotate to Plane (Only for drawing interface)";
				
				case 74:
				return "F4-Panoramic view with articulation angles at 0 (No connection established)";
				
				case 75:
				return "F5-Panoramic view with Redirection (No connection established)";
				
				case 76:
				return "F6-Go to the end point of the arm";
				
				case 77:
				return "F7-Follow to end point of arm";
				
				case 78:
				return "F8-Go to a 'Average' between all the points of a plane (Only for drawing interface)";
				
				case 79:
				return "Ends Connection";
				
				case 80:
				return "Record Mode Off";
				
				case 81:
				return "Record Mode On";
				
				case 82:
				return "Be careful, there was an error loading the files";
				
				case 83:
				return "About ESE_CRT";
								
				case 85:
				return "Github link:";
				
				case 87:
				return "Copy Link";
				
				case 88:
				return "The Link has been Copied";
				
				case 89:
				return "Reconnecting to the server";
				
				case 90:
				return "Disconnect";
				
				case 91:
					return "Connection Reestablished";

				case 92:
					return "Loading Objects ";
					
				case 93:
					return "Enable Sound";

				case 94:
					return "Disable Sound";

				case 95:
					return "Sound Activated";

				case 96:
					return "Sound Deactivated";
				
				case 97:
					return "Exit?";

				case 98:
					return "Exit";

				case 99:
					return "Error to Connect to ";

				case 101:
					return "Lost Connection";

				case 102:
					return "Server Closed";

				case 103:
					return "Access";

				case 104:
					return "No Access";

				case 105:
					return "Access Granted";

				case 106:
					return "Access Denied";

				case 107:
					return "Request Access";

				case 108:
					return "Remove Access";

				case 109:
					return "You have access";

				case 110:
					return "No Access";

				case 111:
					return "Web Host";

				case 112:
					return "Waiting for Redirect to transmit sketch";

				case 113:
					return "Sketch Transmitted";

				case 114:
					return "Redirected";

				case 115:
					return "Without Redirection";

				case 116:
					return "Remove Sketch";

				case 117:
					return "Add Sketch";

				case 118:
					return "Item: Points";

				case 119:
					return "Item: Lines";
				
				case 120:
					return "Item: StripLines";
				
				case 121:
					return "Item: SpLines";
				
				case 122:
					return "Item: Bspline";
				
				case 123:
					return "Cancel last point";
				
				case 124:
					return "Show Plane";
				
				case 125:
					return "Hide Plane";
				
				case 126:
					return "Get USER";

				case 127:
					return "Lose USER";
				
				case 128:
					return "Start Host";
					///////////!!!!!!!!!!!?////////////////////////////



				default:
				   return "Not Find";
		break;
				
			}
		
	
	}
	///////////////////////////////////////////////////////////
	return "NULL";
	
}
void DestruirVariablesGlobales()
{
	if(!VariablesDestruidas)
	{
		VariablesDestruidas=true;
		if(recibir_serie)
		{
			recibir_serie=false;
			serialPort.CloseConnection();
			ThreadSerialPort->join();				 
		}
		if(!ManejadorObject->Salir)
		{
			ManejadorObject->Salir=true;
			ThreadLoadObject->join();
		}
		
		if(ThreadLoadObject->joinable())
			ThreadLoadObject->join();
		delete ThreadLoadObject;

		if(ThreadSerialPort->joinable())
			ThreadSerialPort->join();
		delete ThreadSerialPort;
		delete ManejadorForms;
		delete ManejadorMensajes;
		delete ManejadorSketchs;
		delete ManejadorObject;
		delete[]toSaveCOM;
		delete[]toSaveIp;
		delete[]toSaveHost;
		glutDestroyMenu(MenuCD);
		glutDestroyMenu(SubMenuVista);
		glutDestroyMenu(subMenuIdioma);
		glutDestroyMenu(subMenuToDraw);
		
	}
}	
void Exit()
{
	exit(0);
}
///////////////////CLASS/////////////////////////////////////////////////////////////
ESE_CRT::ESE_CRT(){
	atexit(Exit);
	//Constructor
	//funciones d inicialiacion del GLUT(OPENGL)
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);//inicio con cloes del rgb,doble buffer y buffer de profundidad
	Initheight=GetSystemMetrics (SM_CYSCREEN);//obtener tama�o y de pantalla
	Initwigth=GetSystemMetrics (SM_CXSCREEN);//obtener tama�o x de pantalla
	glutInitWindowPosition(0,0);//inicio de ventana de glut en 0,0 
	glutInitWindowSize(Initwigth-100,Initheight-100);//tama�o de la ventana
	height=Initheight-100;
	wigth=Initheight-100;
	
	Window=glutCreateWindow("ESE_CRT");//creo e inicio la ventana
	glEnable(GL_DEPTH_TEST);//acivo el buffer de profundidad
	/////////////////////////FUNCIONES POR DEFECTO/////////////////

	//funciones pedfinidad por el usuario para q GLUT las llame al realiarse un evento  
	glutDisplayFunc(display);//refescar pantalla
	glutMotionFunc(movRaton);//movimiento del raton
	glutMouseFunc(teclaRaton);//clics del raton
	glutReshapeFunc(reshape);//cambiar tama�o de pantalla
	glutMouseWheelFunc(wheel);//ruedita del mouse
	glutKeyboardFunc(keyboard);//teclado con teclas ASCLL
	glutSpecialFunc(SpecialKeys);//teclado con teclas speciales(Contl,Space,flechitas entre otras)
	glutIdleFunc(Idle);//al no recivir eventos
	glutCloseFunc(salvarInitDatos);//al cerrarse
	glutPassiveMotionFunc(movPasiveRaton);	//al moverse pasivamente el mause(al desplazar emouse por la ventana de la app)
	//glutMainLoop();
	//////////////////////////INICIO MATRISES///////////////////////////////
	initProyecc();//inicializo el tipo de proyeccion y sus dimenciones
	cargarInitDatos();//cargar datos q se guardaron en un archivo .onrn q se guarda al cerrarse y hace q inicie donde lo dejastes(inicie el rotado lo demas tengo q programarlo)
	//InitMenu();
	delete ThreadLoadObject;
	ThreadLoadObject=new thread(ThreadCargObject);

	/*Container*ct=new Container("ESE_CRTContainer");
	ct->AddForms(new Label("labelESE_CRT","ESE_CRT",CRD(0,0,0),1,(GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7,(float)wigth,(float)height));
	ct->AddForms(new Label("labelVersion",Frases(100),CRD(0,0,0),1,(GLfloat)0.6,(GLfloat)0.6,(GLfloat)0.6,(float)wigth,(float)height));
	ct->AddForms(new Label("labelChar","aaaaaaa",CRD(97,-5,0),0,0,1,0,(float)wigth,(float)height));
	ct->AddForms(new Label("labelUnsigned","bbbbbbb",CRD(97,5,0),0,0,1,0,(float)wigth,(float)height));
	ct->AddForms(new Label("labelReferenaciar","cccccc",CRD(0,19,0),1,0,1,0,(float)wigth,(float)height));
	ct->ContainerGetForms("labelChar")->SetDraw(true);
	ct->ContainerGetForms("labelUnsigned")->SetDraw(true);
	ct->ContainerGetForms("labelReferenaciar")->SetDraw(true);
	ManejadorForms->Add(ct,ManejadorForms);*/

	ManejadorForms->Add(new Button("ButtonExit",Type::BUTTONEXIT,CRD(0,0,0),1,0,0,15,15,(float)wigth,(float)height),ManejadorForms);
	ManejadorForms->Add(Interfaz(0),ManejadorForms);
	
	InitMenu();
	///////////////////////_NEW////////////////////
	_ManejadorForms.Add_Element(ContainerPrincipal);
	_ManejadorForms.Add_Element(BoxInterfazPricipal);
	_ManejadorForms.Add_Element(BoxConnection);
	glutPostRedisplay();
}
ESE_CRT::~ESE_CRT(){
	//no hace falta explicar VERDAD?
	DestruirVariablesGlobales();
}
////////////////INICIALIZADORES//////////////////////////////////////////////////////
void ESE_CRT::initProyecc(){
	//inicio el tipo y dimenciones de la proyeccion
	glClearColor((GLclampf)0.3,(GLclampf)0.3,(GLclampf)0.3,1);//color de fondo
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-wigth/2,wigth/2,-height/2,height/2,-2*wigth,2*wigth);
	glMatrixMode(GL_MODELVIEW);

}
void ESE_CRT::Inicializar(){
	 glLoadIdentity();//cargo identidad
	 //inicio la proyeccion
	 initProyecc();
	 //ManejadorObject->setAnguleArt1(DataESE,ManejadorObject);////agrego los angulos de rotacion a mi ManejadorObject
	 wheelAndRotate();//me giro y acerco o alejo 
}
bool ESE_CRT::IniciarCargObjetos()
	{
		if(!CargObjct)
		{
			glPushMatrix();
			glLoadIdentity();
			string h=string(Frases(92));
			string g=string(to_string(ManejadorObject->contLoaderObject)+string("/16 (")+to_string(ManejadorObject->contLoaderObject*100/16)+string("%)"));
			//ManejadorForms->GetForm("StackAnimation1",ManejadorForms)->NewTotalProp(0,0);
			//ManejadorForms->GetForm("StackAnimation1",ManejadorForms)->Draw();
			text("ESE_CRT"       ,(GLfloat)(-40,height/2-75,2*wigth-1),(GLfloat)0.9,(GLfloat)0.9,(GLfloat)0.9,true,true);
			text((char*)h.c_str(),(GLfloat)(-60,height/2-100,2*wigth-1),(GLfloat)0.9,(GLfloat)0.9,(GLfloat)0.9,true);
			text((char*)g.c_str(),(GLfloat)(-35,height/2-125,2*wigth-1),(GLfloat)0.8,(GLfloat)0.8,(GLfloat)0.8,true);
			glPopMatrix();
			glutPostRedisplay();
			glLoadIdentity();
			return false;
		}   
		else
			{
			   InitMenu();
			   glutPostRedisplay();
			   cargMenu=true;
			   return true;
			}
}
void ESE_CRT::InitMenu()
	{
	glutDestroyMenu(MenuCD);
	glutDestroyMenu(SubMenuVista);
	glutDestroyMenu(subMenuIdioma);
	glutDestroyMenu(subMenuToDraw);
	//inicializo y configuro los munu y subenu
	SubMenuVista=glutCreateMenu(MenuVista);//Inicio de Submenus
	glutAddMenuEntry(Frases(30),-1);
	glutAddMenuEntry(Frases(31),0);
	glutAddMenuEntry(Frases(32),1);
	glutAddMenuEntry(Frases(33),2);
	glutAddMenuEntry(Frases(34),3);
	glutAddMenuEntry(Frases(35),4);
	glutAddMenuEntry(Frases(36),5);
	
	subMenuIdioma=glutCreateMenu(MenuIdioma);
	glutAddMenuEntry(Frases(6), 0);
	glutAddMenuEntry(Frases(67), 1);

	subMenuToDraw=glutCreateMenu(MenuToDraw);
	glutAddMenuEntry(Frases(37), - 1);
	for (int ii=0;ii<ManejadorObject->contLoaderObject;ii++)
	glutAddMenuEntry(ManejadorObject->Stack[ii]->nameStr.c_str(),ii);

	MenuCD=glutCreateMenu(default_menu);//aqui creo el menu general donde van todos los submenus
	if(!recibir_serie)
	{
		glutAddMenuEntry(Frases(38),0);//iniicar conexion

		//glutAddMenuEntry(Frases(41),4);//set angules
		//glutAddMenuEntry(Frases(300),-15);//set angulesRedirecc
		glutAddSubMenu(Frases(39),SubMenuVista);//Vista
		if(cargMenu)
			glutAddSubMenu(Frases(40),subMenuToDraw);//To draw
		if(ModoSonido)
		   glutAddMenuEntry(Frases(94),-11);//desact modo mute
		else
			glutAddMenuEntry(Frases(93),-12);//activ modo mute
		if(ModoLogger)
		   glutAddMenuEntry(Frases(69),-8);//desact modo registro
		else
			glutAddMenuEntry(Frases(68),-9);//activ modo registro
		glutAddSubMenu(Frases(42),subMenuIdioma);//idioma	
		glutAddMenuEntry(Frases(83),-10);//About
		glutAddMenuEntry(Frases(98),-14);//Salir
	}
	else


	{
		glutAddSubMenu(Frases(39),SubMenuVista);//Vista
		if(ModoSonido)
		   glutAddMenuEntry(Frases(94),-11);//desact modo mute
		else
			glutAddMenuEntry(Frases(93),-12);//activ modo mute
		if(ModoLogger)
		   glutAddMenuEntry(Frases(69),-8);//descat modo registro
		else
			glutAddMenuEntry(Frases(68),-9);//avtiv modo registro
		glutAddSubMenu(Frases(42),subMenuIdioma);//Idioma
		glutAddMenuEntry(Frases(43),1);//Detener Conexion
	}
	glutAttachMenu(GLUT_RIGHT_BUTTON);//espaecifico con q tecla se activa el evento
}
void ESE_CRT::wheelAndRotate(){
	//procedimientos de rotacion y acercamiento y alejamiento de la camara con el mouse
	glScalef((GLfloat)movWheel,(GLfloat)movWheel,(GLfloat)movWheel);
	glRotatef((GLfloat)movRatX/velGiro,1.0,0.0,0.0);
	glRotatef((GLfloat)movRatY/velGiro,0.0,0.0,1.0);
	glRotatef((GLfloat)movESE_CRTZ/velGiro,0.0,0.0,1.0);

	//
}
///////////////////DIBUJAR////////////////////////////////////////////////////////////
void ESE_CRT::display(){
	glMatrixMode(GL_MODELVIEW);//cargo martiz de vista
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//borro todo 
	if(!CargObjct||!cargMenu)
		IniciarCargObjetos();

    Inicializar();//iniciaizo proyeccion y pongo los angulos del brazo 
	Entorno();//Cargo los objetos, forms y demas elementos

	_ManejadorForms._draw();

    glFlush();//siempre lleva esto  (asegura que los comandos anteriores de OpenGL debe completarse en un tiempo finito)
	glutSwapBuffers();
	//FPS
	//tl.Incrementa(&tl);
	//cout<<1/tl.TimE<<endl;
	//tl.ResettIncrementa(&tl);

}
void ESE_CRT::Entorno(){
	  glPushMatrix();
	  glLoadIdentity();
	  if(SeguirPuntoFinal)//F7 Seguir punto final
	  {
		 trasladarX=-DataESE[0];
	     trasladarY=-DataESE[1];
	     trasladarZ=-DataESE[2];
	  }

	  //ManejadorMensajes->Draw();//Textos de los mensajes superiores centrados
	  if(ManejadorMensajes->Draw())
		  glutPostRedisplay();
	  if(!BoxAbout&&!Boxf1&&!BoxReconnect&&!BoxExit)
		text("o",(GLfloat)(-2.0,-1.5,2*wigth-1),(GLfloat)0.8,(GLfloat)0.8,(GLfloat)0.8);
	  
	  ManejadorForms->DrawForms(ManejadorForms);//Dibujo los Forms
	  
	  
	  glPopMatrix();
	  //pinto el eje de coordenadas del systema
	  glPushMatrix();//Dibujo el eje de coordenadas del sistema
		  glLoadIdentity();
		  glTranslatef((GLfloat)-wigth*2/5,(GLfloat)-height*2/5,0.0);
		  wheelAndRotate();
		  text("x",(GLfloat)(50/movWheel),0,0);
		  text("y",0,(GLfloat)(50/movWheel),0);
		  text("z",0,0,(GLfloat)(50/movWheel));
		  smallEjeCoord((GLfloat)(50/movWheel));
	  glPopMatrix();
	  glTranslatef((GLfloat)trasladarX,(GLfloat)trasladarY,(GLfloat)trasladarZ);//desplazamiento de la vista
	  
	  ManejadorSketchs->Draw(ManejadorSketchs,(interfaz==2)?true:false);//Dibujo los Bocetos con sus planos e Items
	  
	  ManejadorObject->draw(ManejadorObject,contMenuToDraw);//Dibujo los Objetos .obj

	  if(contMenuToDraw<0)//Si estoy en modo ensamblaje con o sin visulaizacion de las piezas(-1)(-2) dibujo el punto final con un Punto Negro
	  {
		  //es neceario el PuShMatrix para q la coordenada del OpenGL quede donde va,y no desplazada segun la coordenad del matlab
		  //No inicamos el LoadIdentity porq ya la matriz llega a aki vacia,pero rotalda y escladada por whellAndRotate();
		  glPushMatrix();
			  glPointSize((GLfloat)(contMenuToDraw==-1?(GLfloat)2:5));
			  glColor3f(0,0,0);
			  glBegin(GL_POINTS);
				glVertex3f((GLfloat)DataESE[0],(GLfloat)DataESE[1],(GLfloat)DataESE[2]);
			  glEnd();
			  glBegin(GL_LINES);
				glVertex3f(0,0,0);
				glVertex3f((GLfloat)DataESE[0],(GLfloat)DataESE[1],(GLfloat)DataESE[2]);
			  glEnd();
		  glPopMatrix();
	  }	
}
void ESE_CRT::text(char*c,GLfloat x,GLfloat y,GLfloat z,GLfloat R,GLfloat G,GLfloat B,bool big,bool moreBig){
	//dibujo el char c en la posicion x,y,z con color RGB
	
	glColor3f(R,G,B);
	glRasterPos3f(x,y,z);					  
	for(unsigned int i=0;i<strlen(c);i++){
        if(moreBig)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		else if(big)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c[i]);
	    else 
	 	    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c[i]);
		
		
	}
}
void ESE_CRT::smallEjeCoord(GLfloat size){
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
void ESE_CRT::ShowAngules(bool IsAtCreate,bool IsAtReciv){
	
	     //             if(MostrarAngules)
						//{
						//	//Verificar si el angulo coincide con  el de redireccionar
						//	try
						//		{
						//		for(unsigned i=0;i<6;i++)
						//		{
						//			if((float)DataESE[i]!=anglesRedirecc[i])
						//			{
						//				if(IsRedireccDraw)
						//				{
						//					
						//					ManejadorForms->SetlabelColor("radioButtonMostrarAngules",(GLfloat)0.8,(GLfloat)0.8,(GLfloat)0.8,ManejadorForms);										
						//					IsRedireccDraw=false;											
						//					if(MostrarAngules)
						//					{
						//						ManejadorForms->GetForm("labelAngule0",ManejadorForms)->SetColor((GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4);
						//						ManejadorForms->GetForm("labelAngule1",ManejadorForms)->SetColor((GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4);
						//						ManejadorForms->GetForm("labelAngule2",ManejadorForms)->SetColor((GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4);
						//						ManejadorForms->GetForm("labelAngule3",ManejadorForms)->SetColor((GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4);
						//						ManejadorForms->GetForm("labelAngule4",ManejadorForms)->SetColor((GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4);
						//						ManejadorForms->GetForm("labelAngule5",ManejadorForms)->SetColor((GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4);
						//						ManejadorForms->GetForm("labelCoordX",ManejadorForms)->SetColor((GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4);
						//						ManejadorForms->GetForm("labelCoordY",ManejadorForms)->SetColor((GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4);
						//						ManejadorForms->GetForm("labelCoordZ",ManejadorForms)->SetColor((GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4);
						//					}
						//					
						//				}
						//				
						//				throw(true);
						//			}
						//		}

						//		if(!IsRedireccDraw||IsAtCreate)
						//		{
						//			if(IsAtReciv)
						//				if(ModoSonido)sonidos(3);
						//			
						//			ManejadorForms->SetlabelColor("radioButtonMostrarAngules",0,(GLfloat)1,0,ManejadorForms);
						//			IsRedireccDraw=true;
						//			if(MostrarAngules)
						//			{
						//			ManejadorForms->GetForm("labelAngule0",ManejadorForms)->SetColor(0,(GLfloat)1,0);
						//			ManejadorForms->GetForm("labelAngule1",ManejadorForms)->SetColor(0,(GLfloat)1,0);
						//			ManejadorForms->GetForm("labelAngule2",ManejadorForms)->SetColor(0,(GLfloat)1,0);
						//			ManejadorForms->GetForm("labelAngule3",ManejadorForms)->SetColor(0,(GLfloat)1,0);
						//			ManejadorForms->GetForm("labelAngule4",ManejadorForms)->SetColor(0,(GLfloat)1,0);
						//			ManejadorForms->GetForm("labelAngule5",ManejadorForms)->SetColor(0,(GLfloat)1,0);
						//			ManejadorForms->GetForm("labelCoordX",ManejadorForms)->SetColor(0,(GLfloat)1,0);
						//			ManejadorForms->GetForm("labelCoordY",ManejadorForms)->SetColor(0,(GLfloat)1,0);
						//			ManejadorForms->GetForm("labelCoordZ",ManejadorForms)->SetColor(0,(GLfloat)1,0);
						//			}
						//			
						//		}
						//		
						//	}catch(bool)
						//	{
						//	};

						//	 
						//	 ManejadorForms->GetForm("labelAngule0",ManejadorForms)->AddNewText((char*)to_string(DataESE[0]).c_str());
						//	 ManejadorForms->GetForm("labelAngule1",ManejadorForms)->AddNewText((char*)to_string(DataESE[1]).c_str());
						//	 ManejadorForms->GetForm("labelAngule2",ManejadorForms)->AddNewText((char*)to_string(DataESE[2]).c_str());
						//	 ManejadorForms->GetForm("labelAngule3",ManejadorForms)->AddNewText((char*)to_string(DataESE[3]).c_str());
						//	 ManejadorForms->GetForm("labelAngule4",ManejadorForms)->AddNewText((char*)to_string(DataESE[4]).c_str());
						//	 ManejadorForms->GetForm("labelAngule5",ManejadorForms)->AddNewText((char*)to_string(DataESE[5]).c_str());
						//	 ManejadorForms->GetForm("labelCoordX",ManejadorForms)->AddNewText((char*)(string("x:")+to_string(DataESE[0])).c_str());	
						//	 ManejadorForms->GetForm("labelCoordY",ManejadorForms)->AddNewText((char*)(string("y:")+to_string(DataESE[1])).c_str());
						//	 ManejadorForms->GetForm("labelCoordZ",ManejadorForms)->AddNewText((char*)(string("z:")+to_string(DataESE[2])).c_str());
						//	 
						//}
}
Box* ESE_CRT::Interfaz(unsigned interfzAponer,INTERFZType t) {
	Box*box=new Box("BoxInterfazPricipal",CRD(10,170,0),(float)wigth,(float)height);
	Forms*f;
	ManejadorSketchs->Pintar_NoPintar_LineaSuspensiva(false,ManejadorSketchs);
	bool desactivaAcept=false,desactiaCancel=false;
	string s;
	unsigned LastInterfaz=interfaz;
	switch(t)
	{
	case INTERFZType::ACEPT:////////////////////////////////ACEPT//////////////////////////////////
		switch (interfaz)
		{
		case 0:	 ////////INTERFAZ0///////////
			if(BoxInterfaz0==0)
				interfaz=1;
			else
				interfaz=6;
			break;
		case -5: /////////////Add menu bocetos////
			bool Err;
			if(bocetoACrear==0)
			{
				ManejadorSketchs->contNPl=0;
				ManejadorForms->Add(Interfaz(-1),ManejadorForms);
				break;
			}
			
		//////No pongo break para el case -5 para q entre en el case -1 y ejecute su contenindo

		case -1:////////////////ADD BOCETO///////////////
			ManejadorSketchs->SetToDrawNPl(3,ManejadorSketchs);
			CambiarPointSpecificPlano=3;
			Err=false;
			for(unsigned i=0;i<ManejadorSketchs->contB;i++)
			{
				if(!strcmp(ManejadorSketchs->bocetos[i]->name,ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetEscritura("textBoxNewBoceto")))
				{
					
					ManejadorMensajes->Add(Frases(44),CENTER_TOP,(float)wigth,(float)height,3,1,0,0,2);
					ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxSetFocusColorTimer("textBoxNewBoceto");
					box->Cancelar(box);
					Err=true;
					break;
				}
			}
			if(Err)
				break;

			if(bocetoACrear==0)
				ManejadorSketchs->Add(new Plano(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetEscritura("textBoxNewBoceto"),ManejadorSketchs->coorNewPlano[0],ManejadorSketchs->coorNewPlano[1],ManejadorSketchs->coorNewPlano[2],TypePlano::SPECIFICPLANE),ManejadorSketchs);
			else if(bocetoACrear==1)
				ManejadorSketchs->Add(new Plano(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetEscritura("textBoxNewBoceto")),ManejadorSketchs);
			else
				ManejadorSketchs->Add(new Plano(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetEscritura("textBoxNewBoceto"),ManejadorSketchs->coorNewPlano[0],ManejadorSketchs->coorNewPlano[1],ManejadorSketchs->coorNewPlano[2],ManejadorSketchs->NewPlanoType),ManejadorSketchs);
			if(ModoSonido)sonidos(8);
			interfaz=1;
			ManejadorForms->ActivateRB("BoxInterfazPricipal","radioButonRemoveBoceto",ManejadorForms);
			ManejadorSketchs->ResetNewPlano(ManejadorSketchs);
			ManejadorSketchs->PlanoCheckeeado=ManejadorSketchs->contB-1;
		break;

		case -2:////////////////REMOVE BOCETO///////////////
		 	ManejadorSketchs->Sub(ManejadorSketchs->bocetos[bocetoARemover]->name,ManejadorSketchs);
			ManejadorSketchs->PlanoCheckeeado=ManejadorSketchs->contB;
		    interfaz=1;
			if(ModoSonido)sonidos(6);
		break;

		case 3:////////////////INIT CONNECTION///////////////
			default_menu(-1);
		    box->SetName("BoxInterfazConnections",box);
		    box->Destruir(box);
		    ManejadorForms->Sub("BoxInterfazConnectionsButtonAcept",ManejadorForms);
		    ManejadorForms->Sub("BoxInterfazConnectionsButtonCancel",ManejadorForms);
			if(Connecttype==ConnectionType::SERIAL_PORT)
				ManejadorForms->Add(Interfaz(0),ManejadorForms);
		    return box;
		break;

		case 4:////////////////STOP CONNECTION///////////////
			if(BoxReconnect)
				 ManejadorForms->Add(Interfaz(9),ManejadorForms);
			default_menu(-2);
		    box->SetName("BoxInterfazDetenerConnection",box);
		    box->Destruir(box);
	 	    ManejadorForms->Sub("BoxInterfazDetenerConnectionButtonAcept",ManejadorForms);
		    ManejadorForms->Sub("BoxInterfazDetenerConnectionButtonCancel",ManejadorForms);
		    ManejadorForms->Add(Interfaz(0),ManejadorForms);
			default_menu(-5);
			ManejadorMensajes->Add(Frases(45),position::CENTER_TOP,(float)wigth,(float)height,3,1,1,0,2);
		    return box;
		break;
		case 6:
			unsigned u1,cOnT,*u;
			u1=0;
			cOnT=ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetCont()-1;
			u=new unsigned[cOnT];
			u1=0;
			for(unsigned i=0;i<cOnT;i++)
			{
				s="RadioButtonSketch"+i;
				if(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBChecket((char*)s.c_str()))
					u[u1++]=i;
			}
			bool All;
			
			if(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBChecket("RadioButtonAllSketchs"))
				All=true;
			else
				All=false;
			if(XLSClass::Salvar(ManejadorSketchs->bocetos,u,u1,All,All?ManejadorSketchs->contB:0))
			{
				ManejadorMensajes->Add( Frases(46),position::CENTER_TOP,(float)wigth,(float)height,3,0,1,0,2);
			}
			else
			{
				ManejadorMensajes->Add( Frases(112),position::CENTER_TOP,(float)wigth,(float)height,5,1,1,0,2);
				if(ModoSonido)sonidos(2);
			}
			delete[]u;
			interfaz=0;
			if(ModoSonido)sonidos(8);
			break;

		default:
			if(interfaz<2)
			   interfaz++;
			break;
		}	
		break;
	case INTERFZType::CANCEL://////////////////////////////CANCEL//////////////////////////////
		switch (interfaz)
		{
		case -5:
			interfaz=1;
			ManejadorSketchs->ResetNewPlano(ManejadorSketchs);
			break;
		case -1:////////////////ADD BOCETO///////////////
			ManejadorSketchs->SetToDrawNPl(3,ManejadorSketchs);
			CambiarPointSpecificPlano=3;
			interfaz=-5;
			ManejadorSketchs->ResetNewPlano(ManejadorSketchs);
			break;

		case -2:////////////////REMOVE BOCETO///////////////
			interfaz=1;
			break;

		case 3:////////////////INIT CONNECTION///////////////
			box->SetName("BoxInterfazConnections",box);
			box->Destruir(box);
			ManejadorForms->Sub("BoxInterfazConnectionsButtonAcept",ManejadorForms);
		    ManejadorForms->Sub("BoxInterfazConnectionsButtonCancel",ManejadorForms);
			ManejadorForms->Add(Interfaz(0),ManejadorForms);
			if(serialPort.GetType()==ConnectionType::SERIAL_PORT)
				default_menu(-5);
			return box;
			break;

		case 4:////////////////STOP CONNECTION///////////////
			box->SetName("BoxInterfazDetenerConnection",box);
			box->Destruir(box);
			ManejadorForms->Sub("BoxInterfazDetenerConnectionButtonAcept",ManejadorForms);
		    ManejadorForms->Sub("BoxInterfazDetenerConnectionButtonCancel",ManejadorForms);
			ManejadorForms->Add(Interfaz(0),ManejadorForms);
			if(serialPort.GetType()==ConnectionType::SERIAL_PORT)
				default_menu(-5);
			else
				default_menu(-6);
			return box;
			break;
		case 6:
			interfaz=0;
			break;

		default:
			if(interfaz>0)
			   interfaz--;
			break;
		}
	break;

	case INTERFZType::SPECIFIC:	/////////////////////////////////SPECIFIC/////////////////////////////
			interfaz=interfzAponer;
		break;
	}
	switch (interfaz)
	{
	case 0://///////////////////////////INTERFAZ_0////////////////////////
		ManejadorSketchs->SetDraw(false,ManejadorSketchs);
		f=new Label("LabelInterfaz0","ESE_CRT:", CRD(0,0,0),2,0,0,0,(float)wigth,(float)height);
		box->AddForm(f,box);
		f=new RadioButtonGroup("radioButtonGroupInterfaz0", CRD(0,0,0),(float)wigth,(float)height);
		f->RBGAddRB("radioButtonEditSketchs",Frases(0),BoxInterfaz0==0?true:false);
		f->RBGAddRB("radioButtonSaveSketchs",Frases(1),BoxInterfaz0==1?true:false);
		if(ManejadorSketchs->contB==0)
			f->RBGActivDesactRB("radioButtonSaveSketchs",false);
		desactiaCancel=true;
		box->AddForm(f,box);
	
		break;
	case 1://///////////////////////////INTERFAZ_1////////////////////////
		ManejadorSketchs->SetDrawAll(false,ManejadorSketchs);
		ManejadorSketchs->SetDraw(true,ManejadorSketchs);
		f=new Label("LabelInterfaz1",Frases(2), CRD(0,0,0),2,0,0,0,(float)wigth,(float)height);
		box->AddForm(f,box);
		f=new RadioButtonGroup("radioButtonGroupInterfaz1", CRD(10,150,0),(float)wigth,(float)height);
		f->RBGAddRB("RadioButtonVistaGeneral",Frases(3),true);
		for(unsigned i=0;i<ManejadorSketchs->contB;i++)
		{
			s="radioButtonBoceto"+to_string(i);
			f->RBGAddRB((char*)s.c_str(),ManejadorSketchs->bocetos[i]->name,(ManejadorSketchs->PlanoCheckeeado==i && ManejadorSketchs->PlanoCheckeeado!=ManejadorSketchs->contB)?true:false);
		}
		if(f->RBGGetRBChecket("RadioButtonVistaGeneral"))
			desactivaAcept=true;
		box->AddForm(f,box);
		f=new RadioButton("radioButtonAgregarBoceto", CRD(0,0,0),Frases(4),(float)wigth,(float)height);
		if(!recibir_serie)
		   f->ActivateDesactivate(false);															
		box->AddForm(f,box,10);
		f=new RadioButton("radioButtonRemoverBoceto", CRD(0,0,0),Frases(5),(float)wigth,(float)height);
		if(ManejadorSketchs->contB==0)
			f->ActivateDesactivate(false);
		box->AddForm(f,box,10);
		if(!recibir_serie)
			desactivaAcept=true;
		break;
	case 2://///////////////////////////INTERFAZ_2////////////////////////
		ManejadorSketchs->ActualizaLastCood(cooRd(),ManejadorSketchs); 
		Plano::ActualiWidthHeight(cooRd(),ManejadorSketchs->BocetoActual(ManejadorSketchs));
		ManejadorSketchs->SetDraw(true,ManejadorSketchs);
		RadioButtomPintar=0;
		s=(ManejadorSketchs->BocetoActual(ManejadorSketchs)->name);
		s+=":";
		f=new Label("LabelInterfaz2",(char*)s.c_str(), CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
		box->AddForm(f,box);
		f=new RadioButtonGroup("radioButtonGroupInterfaz2", CRD(10,150,0),(float)wigth,(float)height);
		ItemsType checket;
		checket=ManejadorSketchs->BocetoActual(ManejadorSketchs)->items->t;
		f->RBGAddRB("radioButonAddPunto",Frases(7),checket==ItemsType::POINTSS||checket==ItemsType::ITEMS?true:false);
		f->RBGAddRB("radioButonAddLines",Frases(8),checket==ItemsType::LINES?true:false);
		f->RBGAddRB("radioButonAddStipLine",Frases(9),checket==ItemsType::LINE_STRIP?true:false);
		f->RBGAddRB("radioButonAddSpline",Frases(10),checket==ItemsType::SPLINE?true:false);
		f->RBGAddRB("radioButonAddBSpline",Frases(70),checket==ItemsType::BSPLINE?true:false);
		box->AddForm(f,box);
		f=new RadioButton("RadioButtomCancelLast", CRD(0,0,0),Frases(11),(float)wigth,(float)height);
		if(!ManejadorSketchs->BocetoActual(ManejadorSketchs)->items->cont)
			f->ActivateDesactivate(false);
		box->AddForm(f,box,10);
		if(Plano::IsRestring(ManejadorSketchs->BocetoActual(ManejadorSketchs)))
		{
			f=new RadioButton("RadioButtomMostrarPlano", CRD(0,0,0),Frases(12),(float)wigth,(float)height,true);
			box->AddForm(f,box,10);
		}
		desactivaAcept=true;
		break;
	case -5://///////////////////////////////////INTERFAZ_-5/////////////////////////
		ManejadorSketchs->SetDraw(false,ManejadorSketchs);
		f=new Label("LabelInterfaz-5",Frases(13), CRD(0,0,0),2,0,0,0,(float)wigth,(float)height);
		box->AddForm(f,box);
		f=new RadioButtonGroup("RadioButtonInterfaz-5", CRD(0,0,0),(float)wigth,(float)height);
		f->RBGAddRB("RadioButtonPlanoXY",Frases(14),bocetoACrear==0?true:false);
		f->RBGAddRB("RadioButtonPlanoFree",Frases(15),bocetoACrear==1?true:false);
		f->RBGAddRB("RadioButtonPlanoXY",Frases(16),bocetoACrear==2?true:false);
		f->RBGAddRB("RadioButtonPlanoXY",Frases(17),bocetoACrear==3?true:false);
		f->RBGAddRB("RadioButtonPlanoXY",Frases(18),bocetoACrear==4?true:false);
		box->AddForm(f,box);
		
		if(bocetoACrear!=0)
		{
			if(bocetoACrear>1)
			{
				f=new RadioButtonGroup("RadioButtonGroupPlanoPosittion",CRD(0,0,0),(float)wigth,(float)height);
				f->RBGAddRB("RadioButtonDefault",Frases(19),deFult?true:false);
				f->RBGAddRB("RadioButtonEndPoint",Frases(20),!deFult?true:false);
				box->AddForm(f,box);
			}
			s=(bocetoACrear==1?Frases(22):Frases(21))+to_string(ManejadorSketchs->contB);
			f=new TextBox("textBoxNewBoceto", CRD(0,0,0),box->Wigth-10,(float)wigth,(float)height,(char*)s.c_str(),10);
			box->AddForm(f,box);
		}
		box->BoxSetFocus(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetFocus());
		break;
	case -1:////////////////////////////////////////INTERFAZ_-1//////////////////////Add New Specific Boceto
		ManejadorSketchs->SetDraw(false,ManejadorSketchs);
		s=Frases(23)+to_string(ManejadorSketchs->contNPl)+"/3";
		f=new Label("LabelInterfaz-1",(char*)s.c_str(), CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
		box->AddForm(f,box);
		f=new RadioButtonGroup("RadioButtonGroupPuntosNewBoceto",CRD(0,0,0),(float)wigth,(float)height);
		ManejadorSketchs->SetToDrawNPl(3,ManejadorSketchs);
		CambiarPointSpecificPlano=3;
		for(unsigned i=0;i<ManejadorSketchs->contNPl;i++)
		{
			s=("["+to_string(ManejadorSketchs->coorNewPlano[i].x)+";"+to_string(ManejadorSketchs->coorNewPlano[i].y)+";"+to_string(ManejadorSketchs->coorNewPlano[i].z)+"]");
			f->RBGAddRB((char*)(string("RadioButtonPunto")+to_string(i)).c_str(),(char*)s.c_str());
		}
		box->AddForm(f,box);
		if(ManejadorSketchs->contNPl==3)
		{
			s=Frases(21)+to_string(ManejadorSketchs->contB);
			f=new TextBox("textBoxNewBoceto", CRD(0,0,0),box->Wigth-10,(float)wigth,(float)height,(char*)s.c_str());
		    box->AddForm(f,box);
		}
		desactivaAcept=true;
		break;
	case -2://///////////////////////////INTERFAZ_-2////////////////////////REMOVE BOCETO
		bocetoARemover=0;
		ManejadorSketchs->SetDraw(true,ManejadorSketchs);
		s=Frases(24);
		f=new Label("LabelInterfaz-2",(char*)s.c_str(), CRD(0,0,0),2,0,0,0,(float)wigth,(float)height);
		box->AddForm(f,box);
		f=new RadioButtonGroup("radioButtonGroupInterfaz-2", CRD(10,150,0),(float)wigth,(float)height);
		for(unsigned i=0;i<ManejadorSketchs->contB;i++)
		{
			s="radioButtonBoceto"+to_string(i);
			f->RBGAddRB((char*)s.c_str(),ManejadorSketchs->bocetos[i]->name,i==0?1:0);
		}
		ManejadorSketchs->PlanoCheckeeado=0;
		box->AddForm(f,box);
		break;
	case 3://///////////////////////////INTERFAZ_3////////////////////////
		box->SetName("BoxInterfazConnections",box);
		box->SetCRD(CRD(10,40,0),box);
		glutDestroyMenu(MenuCD);
		
		f=new TextBox("textBoxChar",CRD(0,0,0),100,(float)wigth,(float)height,toSaveCOM,15);
		
		box->AddForm(f,box);
		
		f=new TextBox("textBoxUnsigned",CRD(0,0,0),100,(float)wigth,(float)height,(char*)to_string(toSaveSpeed).c_str(),10,TextBoxType::UNSIGNEDCONTENT);
		
		
		box->AddForm(f,box);
		f=new RadioButtonGroup("RadioButtonGroupConnectionType", CRD(0,0,0),(float)wigth,(float)height);
		f->RBGAddRB("RadioButtomSerialPort",Frases(26),1);


		box->AddForm(f,box);
		break;
	case 4://///////////////////////////INTERFAZ_4////////////////////////
		box->SetName("BoxInterfazDetenerConnection",box);
		box->SetCRD(CRD(10,100,0),box);
		f=new Label("LabelInterfaz4",Frases(27), CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
		box->AddForm(f,box);
		
		break;
	case 6:
		ManejadorSketchs->SetDraw(false,ManejadorSketchs);
		f=new Label("labelSelectSketsh",Frases(28),CRD(0,0,0),2,0,0,0,(float)wigth,(float)height);
		box->AddForm(f,box);
		for(unsigned i=0;i<ManejadorSketchs->contB;i++)
		{
			s="RadioButtonSketch"+i;
			f=new RadioButton((char*)s.c_str(),CRD(0,0,0),ManejadorSketchs->bocetos[i]->name,(float)wigth,(float)height,true);
			box->AddForm(f,box);
		}
		if(ManejadorSketchs->contB>1)
		{
			f=new RadioButton("RadioButtonAllSketchs",CRD(0,0,0),Frases(29),(float)wigth,(float)height);
		box->AddForm(f,box);
		}
		break; 
	case 7:	  //F1
		interfaz=LastInterfaz;
		if(!Boxf1)
		{
			if(BoxReconnect||BoxExit)
			{
				 Forms::Cancelar(box);
			 	 return box;
			}
			if(BoxAbout)
				ManejadorForms->Add(Interfaz(8),ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipal",false,ManejadorForms);
			ActiveDesactAcept=ManejadorForms->GetForm("BoxInterfazPricipalButtonAcept",ManejadorForms)->GetActiveDesavt();
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonAcept",false,ManejadorForms);
			ActiveDesactCancel=ManejadorForms->GetForm("BoxInterfazPricipalButtonCancel",ManejadorForms)->GetActiveDesavt();
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonCancel",false,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("radioButtonMostrarAngules",false,ManejadorForms);
			Boxf1=true;
			box=new Box("BoxHelp",CRD(0,0,0),(float)wigth,(float)height);
			box->Wigth=100;
			f=new Label("Labelf1",Frases(71),CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new Label("Labelf2",Frases(72),CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new Label("Labelf3",Frases(73),CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new Label("Labelf4",Frases(74),CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new Label("Labelf5",Frases(75),CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new Label("Labelf6",Frases(76),CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new Label("Labelf7",Frases(77),CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new Label("Labelf8",Frases(78),CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new Button("ButonCancelHelp",Type::BUTTON,CRD(0,0,0),1,0,0,box->Wigth,25,(float)wigth,(float)height);
			box->AddForm(f,box);
			box->SetCoordElementProp("Labelf1",box->BoxGetElementCoord("Labelf1")+CRD(box->Wigth/2,0,0)-CRD(strlen(Frases(71))*4.5,0,0));
			box->SetCoordElementProp("Labelf2",box->BoxGetElementCoord("Labelf2")+CRD(box->Wigth/2,0,0)-CRD(strlen(Frases(72))*4.5,0,0));
			box->SetCoordElementProp("Labelf3",box->BoxGetElementCoord("Labelf3")+CRD(box->Wigth/2,0,0)-CRD(strlen(Frases(73))*4.5,0,0));
			box->SetCoordElementProp("Labelf4",box->BoxGetElementCoord("Labelf4")+CRD(box->Wigth/2,0,0)-CRD(strlen(Frases(74))*4.5,0,0));
			box->SetCoordElementProp("Labelf5",box->BoxGetElementCoord("Labelf5")+CRD(box->Wigth/2,0,0)-CRD(strlen(Frases(75))*4.5,0,0));
			box->SetCoordElementProp("Labelf6",box->BoxGetElementCoord("Labelf6")+CRD(box->Wigth/2,0,0)-CRD(strlen(Frases(76))*4.5,0,0));
			box->SetCoordElementProp("Labelf7",box->BoxGetElementCoord("Labelf7")+CRD(box->Wigth/2,0,0)-CRD(strlen(Frases(77))*4.5,0,0));
			box->SetCoordElementProp("Labelf8",box->BoxGetElementCoord("Labelf8")+CRD(box->Wigth/2,0,0)-CRD(strlen(Frases(78))*4.5,0,0));
			box->SetWigthElementProp("ButonCancelHelp",box->Wigth-5);
			box->NewCRD(CRD(wigth/2-box->Wigth/2,height/2-box->Height/2,0));
			box->SetProfundidad(1);
			box->BoxSetDrawLineForElement(false);
			return box;
		}
		else
		{
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipal",true,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonAcept",ActiveDesactAcept,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonCancel",ActiveDesactCancel,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("radioButtonMostrarAngules",true,ManejadorForms);
			Boxf1=false;
			Forms::SetName("BoxHelp",box);
			Forms::Destruir(box);
			return box;
		}
		//break; no break por returns
	case 8:	//About
		interfaz=LastInterfaz;
		if(!BoxAbout)
		{
			if(BoxExit)
			{
				 Forms::Cancelar(box);
			 	 return box;
			}
			if(Boxf1)
				ManejadorForms->Add(Interfaz(7),ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipal",false,ManejadorForms);
			ActiveDesactAcept=ManejadorForms->GetForm("BoxInterfazPricipalButtonAcept",ManejadorForms)->GetActiveDesavt();
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonAcept",false,ManejadorForms);
			ActiveDesactCancel=ManejadorForms->GetForm("BoxInterfazPricipalButtonCancel",ManejadorForms)->GetActiveDesavt();
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonCancel",false,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("radioButtonMostrarAngules",false,ManejadorForms);
			BoxAbout=true;
			box=new Box("BoxAbout",CRD(0,0,0),(float)wigth,(float)height);
			box->Wigth=100;
			f=new Label("Label1",Frases(84),CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new Label("Label2",Frases(85),CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new Label("Label3",Frases(86),CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new Button("ButonCopiarEnlace",Type::BUTTON,CRD(0,0,0),1,0,1,50,25,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new Label("Label4",Frases(87),CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
			box->AddForm(f,box);
		
			f=new Button("ButonCancelAbout",Type::BUTTON,CRD(0,0,0),1,0,0,box->Wigth,25,(float)wigth,(float)height);
			box->AddForm(f,box);
			box->SetCoordElementProp("Label1",box->BoxGetElementCoord("Label1")+CRD(box->Wigth/2,0,0)-CRD(strlen(Frases(84))*4.5,0,0));
			box->SetCoordElementProp("Label2",box->BoxGetElementCoord("Label2")+CRD(box->Wigth/2,0,0)-CRD(strlen(Frases(85))*4.5,0,0));
			box->SetCoordElementProp("Label3",box->BoxGetElementCoord("Label3")+CRD(box->Wigth/2,0,0)-CRD(strlen(Frases(86))*4.5,0,0));
			box->SetCoordElementProp("Label4",box->BoxGetElementCoord("Label4")+CRD(box->Wigth/2,0,0)-CRD(strlen(Frases(87))*4.5,0,0));
			box->SetCoordElementProp("ButonCopiarEnlace",box->BoxGetElementCoord("ButonCopiarEnlace")+CRD(box->Wigth/2,0,0)-CRD(25,0,0));
			box->SetWigthElementProp("ButonCancelAbout",box->Wigth-5);
			box->NewCRD(CRD(wigth/2-box->Wigth/2,height/2-box->Height/2,0));
			box->SetProfundidad(1);
			box->BoxSetDrawLineForElement(false);
			return box;
		}
		else
		{
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipal",true,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonAcept",ActiveDesactAcept,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonCancel",ActiveDesactCancel,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("radioButtonMostrarAngules",true,ManejadorForms);
			BoxAbout=false;
			Forms::SetName("BoxAbout",box);
			Forms::Destruir(box);
			return box;
		}
		//break; no break por returns
	case 9:	//Reconexion
		interfaz=LastInterfaz;
		if(!BoxReconnect)
		{
			if(BoxExit)
			{
				 Forms::Cancelar(box);
			 	 return box;
			}
			if(Boxf1)
				ManejadorForms->Add(Interfaz(7),ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipal",false,ManejadorForms);
			ActiveDesactAcept=ManejadorForms->GetForm("BoxInterfazPricipalButtonAcept",ManejadorForms)->GetActiveDesavt();
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonAcept",false,ManejadorForms);
			ActiveDesactCancel=ManejadorForms->GetForm("BoxInterfazPricipalButtonCancel",ManejadorForms)->GetActiveDesavt();
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonCancel",false,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("radioButtonMostrarAngules",false,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("StackAnimationsConnection",false,ManejadorForms);

			BoxReconnect=true;
			box=new Box("BoxReconnect",CRD(0,0,0),(float)wigth,(float)height);
			box->Wigth=100;
			f=new Label("Label1",Frases(89),CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new StackAnimation("StackAnimationsBoxREconnect");
			f->STANSetAnimation("AnimacionRoja", CRD(0,0,0),100,(float)wigth,(float)height,-25,1,0,0,1.5);
			f->STANSetAnimation("AnimacionVerde", CRD(0,0,0),100,(float)wigth,(float)height,0,0,1,0,1.5);
			f->STANSetAnimation("AnimacionAzul", CRD(0,0,0),100,(float)wigth,(float)height,25,0,0,1,1.5);
			box->AddForm(f,box);
			f=new Label("Label2",Frases(90),CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new Button("ButonDesconectar",Type::BUTTON,CRD(0,0,0),1,0,0,box->Wigth,25,(float)wigth,(float)height);
			box->AddForm(f,box);
			box->SetCoordElementProp("Label1",box->BoxGetElementCoord("Label1")+CRD(box->Wigth/2,0,0)-CRD(strlen(Frases(89))*4.5,0,0));
			box->SetCoordElementProp("Label2",box->BoxGetElementCoord("Label2")+CRD(box->Wigth/2,0,0)-CRD(strlen(Frases(90))*4.5,0,0));
			box->SetCoordElementProp("StackAnimationsBoxREconnect",box->BoxGetElementCoord("StackAnimationsBoxREconnect")+CRD(box->Wigth/2,box->GetHeightElement("StackAnimationsBoxREconnect")/2,0));
			box->SetWigthElementProp("ButonDesconectar",box->Wigth-5);
			box->SetHeightElementProp("StackAnimationsBoxREconnect",box->GetHeightElement("StackAnimationsBoxREconnect")/2);
			box->NewCRD(CRD(wigth/2-box->Wigth/2,height/2-box->Height/2,0));
			box->SetProfundidad(1);
			box->BoxSetDrawLineForElement(false);
			return box;
		}
		else
		{
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipal",true,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonAcept",ActiveDesactAcept,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonCancel",ActiveDesactCancel,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("radioButtonMostrarAngules",true,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("StackAnimationsConnection",true,ManejadorForms);
			BoxReconnect=false;
			Forms::SetName("BoxReconnect",box);
			Forms::Destruir(box);
			return box;
		}
		//break; no break por returns
	case 10:   //Salir
		interfaz=LastInterfaz;
		if(!BoxExit)
		{
			if(Boxf1)
				ManejadorForms->Add(Interfaz(7),ManejadorForms);
			if(BoxAbout)
				ManejadorForms->Add(Interfaz(8),ManejadorForms);
			StopThread=true;
			if(BoxReconnect)
			{
				ManejadorForms->Add(Interfaz(9),ManejadorForms);
			}
			EsperandoReedireccionar=true;	
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipal",false,ManejadorForms);
			ActiveDesactAcept=ManejadorForms->GetForm("BoxInterfazPricipalButtonAcept",ManejadorForms)->GetActiveDesavt();
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonAcept",false,ManejadorForms);
			ActiveDesactCancel=ManejadorForms->GetForm("BoxInterfazPricipalButtonCancel",ManejadorForms)->GetActiveDesavt();
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonCancel",false,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("radioButtonMostrarAngules",false,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("ButtonExit",false,ManejadorForms);
			BoxExit=true;
			glutDestroyMenu(MenuCD);
			box=new Box("BoxExit",CRD(0,0,0),(float)wigth,(float)height);
			box->Wigth=100;
			f=new Label("Label1",Frases(97),CRD(0,0,0),1,0,0,0,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new Button("ButonAceptExit",Type::BUTTON,CRD(0,0,0),0,1,0,50,25,(float)wigth,(float)height);
			box->AddForm(f,box);
			f=new Button("ButonCancelExit",Type::BUTTON,CRD(0,0,0),1,0,0,50,25,(float)wigth,(float)height);
			box->AddForm(f,box);
			box->SetCoordElementProp("Label1",box->BoxGetElementCoord("Label1")+CRD(box->Wigth/2,0,0)-CRD(strlen(Frases(97))*4.5,0,0));
			box->SetWigthElementProp("ButonAceptExit",box->Wigth-5);
			box->SetWigthElementProp("ButonCancelExit",box->Wigth-5);
			box->NewCRD(CRD(wigth/2-box->Wigth/2,height/2-box->Height/2,0));
			box->SetProfundidad(1);
			box->BoxSetDrawLineForElement(false);
			return box;
		}
		else
		{
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipal",true,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonAcept",ActiveDesactAcept,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("BoxInterfazPricipalButtonCancel",ActiveDesactCancel,ManejadorForms);
			ManejadorForms->ActvDesactOnlyForm("radioButtonMostrarAngules",true,ManejadorForms);
			BoxExit=false;
			StopThread=false;
			Forms::SetName("BoxExit",box);
			Forms::Destruir(box);
			return box;
		}
		//break; no break por returns
	}
	//////////////////////////////////////////////////////BUTTONS////////////////////////////////////////////////////
	string ss,ss1;
	ss=ss1=box->name;
	ss+="ButtonAcept";
	ss1+="ButtonCancel";
	ManejadorForms->Add(new Button((char*)ss.c_str(),Type::BUTTONACEPTRB,CRD(box->coord.x-6,box->coord.y+box->Height+5,box->coord.z),0,1,0,box->Wigth+6,10,box->TotalWigth,box->TotalHeight),ManejadorForms);
	ManejadorForms->Add(new Button((char*)ss1.c_str(),Type::BUTTONCANCELRB,CRD(box->coord.x+box->Wigth,box->coord.y-6,box->coord.z),1,0,0,10,box->Height+21,box->TotalWigth,box->TotalHeight),ManejadorForms);
	if(desactivaAcept)
		ManejadorForms->DesactivateForm((char*)ss.c_str(),ManejadorForms);
	if(desactiaCancel)
		ManejadorForms->DesactivateForm((char*)ss1.c_str(),ManejadorForms);
	return box;
}
/////////////////////FUNCIONES DE GLUT A LLAMAR POR DEFECTO////////////////////////////
void ESE_CRT::reshape(int x,int y){
	wigth=x;height=y;
	ManejadorForms->NewTotalsProp((float)x,(float)y,ManejadorForms);
	ContainerPrincipal->New_CRD("labelVersion",CRD(wigth-50,height-20,0));
	//ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelVersion")->NewCRD(CRD(wigth-50,height-20,0));
	ManejadorForms->GetForm("ButtonExit",ManejadorForms)->NewCRD(CRD(wigth-25,8,0));
	//ManejadorForms->GetForm("radioButtonMostrarAngules",ManejadorForms)->NewCRD(CRD(wigth-120,8,0));
	//ManejadorForms->GetForm("labelAngule0",ManejadorForms)->NewCRD(CRD(wigth-120,25,0));
	//ManejadorForms->GetForm("labelAngule1",ManejadorForms)->NewCRD(CRD(wigth-120,40,0));
	//ManejadorForms->GetForm("labelAngule2",ManejadorForms)->NewCRD(CRD(wigth-120,55,0));
	//ManejadorForms->GetForm("labelAngule3",ManejadorForms)->NewCRD(CRD(wigth-120,70,0));
	//ManejadorForms->GetForm("labelAngule4",ManejadorForms)->NewCRD(CRD(wigth-120,85,0));
	//ManejadorForms->GetForm("labelAngule5",ManejadorForms)->NewCRD(CRD(wigth-120,100,0));
	//ManejadorForms->GetForm("labelCoordX",ManejadorForms)->NewCRD(CRD(wigth-120,115,0));
	//ManejadorForms->GetForm("labelCoordY",ManejadorForms)->NewCRD(CRD(wigth-120,130,0));
	//ManejadorForms->GetForm("labelCoordZ",ManejadorForms)->NewCRD(CRD(wigth-120,145,0));
	glViewport(0,0,x,y);//creo una zona de la ventana con el contenido  
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
void ESE_CRT::movRaton(GLsizei x,GLsizei y){
   movRatY+=(float)x-movRatXinit;
   movRatX+=(float)y-movRatYinit;
   movRatXinit=(float)x;
   movRatYinit=(float)y;
   if(ManejadorSketchs->contB)
	   Plano::verPlanoRotado(0,ManejadorSketchs->BocetoActual(ManejadorSketchs));
   glutPostRedisplay();//refresco y ejecuto el displayFunc()
}
void ESE_CRT::movPasiveRaton(GLsizei x,GLsizei y)
{
	switch (ManejadorForms->FormsPasiveMouse((int)x,(int)y,ManejadorForms))
	{
	case Type::BUTTONACEPTRB:
	case Type::BUTTONINITSETANGULES:	
	case Type::RADIOBUTTON:
	case Type::BUTTONCANCELSETANGULES:
	case Type::BUTTONCANCELRB:
	case Type::BUTTONEXIT:
	case Type::BUTTON:
		if(!cursor)
		{
			glutSetCursor( GLUT_CURSOR_HELP);
			cursor=true;
		}
	break;
	case Type::TEXTBOX:
		glutSetCursor( GLUT_CURSOR_TEXT);
		cursor=true;
		break;
	default:
		if(cursor)
		{
			glutSetCursor(GLUT_CURSOR_INHERIT);
			cursor=false;
		}
	break;
	} 
};
void ESE_CRT::Idle(){
  // if(recibir_serie||ManejadorForms->GetEstoyEscribindo()||!CargObjct)
	 // glutPostRedisplay();
	//cout<<"|"<<endl;
}
void ESE_CRT::teclaRaton(int boton,int state,int x,int y){
	if(boton==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
	   bool eRror=false;
	   string s;
	   cout<<x<<":"<<y<<endl; 
	   
	   if(_ManejadorForms.Pulsado(x,y))
	   {
	   }
	   
	   switch (ManejadorForms->PresionarForm((float)x,(float)y,ManejadorForms))
	   {
	   case 0:
		   break;
	   case Type::BOX:
		   if(ModoSonido)sonidos(9);
		   if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("BoxInterfazConnections",ManejadorForms)))
		   {
			   if(interfaz==3)//interfaz 3
			   {
				  if(ManejadorForms->GetForm("BoxInterfazConnections",ManejadorForms)->BoxGetElemChecket()==2)
				  {
					  ManejadorForms->Add(Interfaz(3),ManejadorForms);
				  }
			   }
		   }	
		   else if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("BoxHelp",ManejadorForms)))
		   {
			   if(ManejadorForms->GetForm("BoxHelp",ManejadorForms)->BoxGetElemChecket()==ManejadorForms->GetForm("BoxHelp",ManejadorForms)->BoxGetCont()-1)
			   {
				   SpecialKeys(GLUT_KEY_F1,0,0);
			   }
		   }
		    else if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("BoxReconnect",ManejadorForms)))
		   {
			   if(ManejadorForms->GetForm("BoxReconnect",ManejadorForms)->BoxGetElemChecket()==ManejadorForms->GetForm("BoxReconnect",ManejadorForms)->BoxGetCont()-1)
			   {
				   interfaz=4;
				   ManejadorForms->Add(Interfaz(4,INTERFZType::ACEPT),ManejadorForms);
			   }
		   }
		   else if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("BoxAbout",ManejadorForms)))
		   {
			   if(ManejadorForms->GetForm("BoxAbout",ManejadorForms)->BoxGetElemChecket()==ManejadorForms->GetForm("BoxAbout",ManejadorForms)->BoxGetCont()-1)
			   {
				   ManejadorForms->Add(Interfaz(8),ManejadorForms);
			   }
			   else if(ManejadorForms->GetForm("BoxAbout",ManejadorForms)->BoxGetElemChecket()==3)
			   {
				
					OpenClipboard(0);
					EmptyClipboard();
					const char*op=(const char*)Frases(86);
					const size_t ln=strlen(op)+1;
					HGLOBAL h=GlobalAlloc(GMEM_MOVEABLE,ln);
				    memcpy(GlobalLock(h),op,ln);
					GlobalUnlock(h);
					SetClipboardData(CF_TEXT,h);
					CloseClipboard();
					if(ModoSonido)sonidos(7);
					if(ModoLogger)cout<<Frases(88)<<"->"<<Frases(86)<<endl;
					ManejadorMensajes->Add(Frases(88),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,0,1,0,2);
			   }  
		   }
		   else if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("BoxExit",ManejadorForms)))
		   {
			   if(ManejadorForms->GetForm("BoxExit",ManejadorForms)->BoxGetElemChecket()==ManejadorForms->GetForm("BoxExit",ManejadorForms)->BoxGetCont()-1)
			   {
				   ManejadorForms->Add(Interfaz(10),ManejadorForms);
				   if(ErrorConnect)
				   {
					   ManejadorForms->Add(Interfaz(9),ManejadorForms);
					   StopThread=false;
				   }
				   InitMenu();
				   ManejadorForms->ActvDesactOnlyForm("ButtonExit",true,ManejadorForms);
			   }
			   else if(ManejadorForms->GetForm("BoxExit",ManejadorForms)->BoxGetElemChecket()==1)
			   {
				   
				   
				   default_menu(-13);
			   }
		   }
		   else if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)))
		   {
			   BoxInterfazPricipalL=ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetElemChecket();
			   ManejadorSketchs->Pintar_NoPintar_LineaSuspensiva(false,ManejadorSketchs);
			   switch (interfaz)
			   {
			   case -1://///////////////////////INTERFAZ -1 AddPoints Specific Plano
				   CambiarPointSpecificPlano=ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBGChecket("RadioButtonGroupPuntosNewBoceto");
				   ManejadorSketchs->SetToDrawNPl(CambiarPointSpecificPlano,ManejadorSketchs);
				   break;
			   case 0: //////////////////////////INTERFAZ 0
					if(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetElemChecket()==1)
						BoxInterfaz0=ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBGChecket("radioButtonGroupInterfaz0");
					break;
			   case 1://////////////////////////INTERFAZ 1
				   switch (BoxInterfazPricipalL)
				   {
				   case 1:////////////SELECC BOCETO
					   PlanoChecket=ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBGChecket("radioButtonGroupInterfaz1");
					   if(PlanoChecket==0)
					   {
						    ManejadorSketchs->SetDrawAll(true,ManejadorSketchs);
							ManejadorForms->DesactivateForm("BoxInterfazPricipalButtonAcept",ManejadorForms);
					   }
					   else
					   {
						    if(recibir_serie)
								ManejadorForms->ActivateForm("BoxInterfazPricipalButtonAcept",ManejadorForms);
							ManejadorSketchs->SetDrawAll(false,ManejadorSketchs);
							ManejadorSketchs->PlanoCheckeeado=PlanoChecket-1;
							ManejadorSketchs->BocetoActual(ManejadorSketchs)->pintarPlano=true;
					   }
					   break;
				   case 2:///////////////////// ADD BOCETO
					   if(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetActiveDesact("radioButtonAgregarBoceto"))
					   {
					      ManejadorSketchs->contNPl=0;
						  bocetoACrear=0;
					      ManejadorForms->Add(Interfaz(-5),ManejadorForms);
					   }
					   break;
				   case 3://////////////REMOVE BOCETO
					   if(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetActiveDesact("radioButtonRemoverBoceto"))
					     {
							 PlanoChecket=ManejadorSketchs->PlanoCheckeeado;
							 ManejadorForms->Add(Interfaz(-2),ManejadorForms);
					     }
					   break;
				   }
				   break;
			   case 2://///////////////////////INTERFAZ 2/////
				    switch (BoxInterfazPricipalL)
					{
					case 1:////////////RADIOBUTTONGROUP ITEMS
						RadioButtomPintar=ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBGChecket("radioButtonGroupInterfaz2");
						if(RadioButtomPintar==0)///POINTS
						{
							Plano::ActualizaItem(ItemsType::POINTSS,ManejadorSketchs->BocetoActual(ManejadorSketchs));
						}
						else if(RadioButtomPintar==1)//LINES
						{
							Plano::ActualizaItem(ItemsType::LINES,ManejadorSketchs->BocetoActual(ManejadorSketchs));
						}
						else if(RadioButtomPintar==2)//STRIP_LINE
						{
							Plano::ActualizaItem(ItemsType::LINE_STRIP,ManejadorSketchs->BocetoActual(ManejadorSketchs));
						}
						else if(RadioButtomPintar==3)//SPLINE
						{
							Plano::ActualizaItem(ItemsType::SPLINE,ManejadorSketchs->BocetoActual(ManejadorSketchs));
						}
						else if(RadioButtomPintar==4)//BSPLINE
						{
							Plano::ActualizaItem(ItemsType::BSPLINE,ManejadorSketchs->BocetoActual(ManejadorSketchs));
						}
						break;
					case 2:///////CANCEL Point
						if(	ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetActiveDesact("RadioButtomCancelLast"))
						{
							Plano::CancelLastPoint(ManejadorSketchs->BocetoActual(ManejadorSketchs));
							if(ModoSonido)sonidos(6);
							if(!ManejadorSketchs->BocetoActual(ManejadorSketchs)->items->cont)
								ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxSetActivateDesactivate("RadioButtomCancelLast",false);
						}
						ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxCambiarChecketRB("RadioButtomCancelLast");
						break;
					case 3://Mostrar\ocultar Plano
						ManejadorSketchs->Pintar_NoPintar_LineaSuspensiva(true,ManejadorSketchs);
						if(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBChecket("RadioButtomMostrarPlano"))
						{
							ManejadorSketchs->BocetoActual(ManejadorSketchs)->pintarPlano=true;
						}
						else
						{
							ManejadorSketchs->BocetoActual(ManejadorSketchs)->pintarPlano=false;
						}
						break;
					}
				   break;
			   case -2:   /////////////REMOVER BOCETO///////INTEFAZ-2////
				    bocetoARemover=ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBGChecket("radioButtonGroupInterfaz-2");
					ManejadorSketchs->PlanoCheckeeado=bocetoARemover;
				break;
			   case -5:	///////////////SELECT NEW PLANO/////////
				   switch (BoxInterfazPricipalL)
				   {
					 case 1:
						   bocetoACrear=ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBGChecket("RadioButtonInterfaz-5");
						   switch (bocetoACrear)
						   {
							   
							   case 0:///NEW PLANO////
										ManejadorSketchs->AddNewType(TypePlano::SPECIFICPLANE,ManejadorSketchs);
										ManejadorSketchs->ResetNewPlano(ManejadorSketchs);
								   break;
							   case 1:///FREE Plano///
										ManejadorSketchs->AddNewType(TypePlano::FREE,ManejadorSketchs);
										ManejadorSketchs->ResetNewPlano(ManejadorSketchs);
								   break;
							   case 2:////XY//////
										ManejadorSketchs->ResetNewPlano(ManejadorSketchs);
										ManejadorSketchs->contNPl=4;	    
										ManejadorSketchs->AddNewType(TypePlano::XY,ManejadorSketchs);
										ManejadorSketchs->ActualizaNewPlanoToCreate(cooRd(),ManejadorSketchs,deFult);
								   break;
								case 3:///XZ//////
										ManejadorSketchs->AddNewType(TypePlano::XZ,ManejadorSketchs);
										ManejadorSketchs->ResetNewPlano(ManejadorSketchs);
										ManejadorSketchs->contNPl=4;
										ManejadorSketchs->ActualizaNewPlanoToCreate(cooRd(),ManejadorSketchs,deFult);
								   break;
								case 4:///YZ//////
										ManejadorSketchs->AddNewType(TypePlano::YZ,ManejadorSketchs);
										ManejadorSketchs->ResetNewPlano(ManejadorSketchs);
										ManejadorSketchs->contNPl=4;
										ManejadorSketchs->ActualizaNewPlanoToCreate(cooRd(),ManejadorSketchs,deFult);
								   break;
						   }
						   ManejadorForms->Add(Interfaz(-5),ManejadorForms); 
						break;
					 case 2:
						 if(bocetoACrear>1)
						 {
							 deFult= ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBGChecket("RadioButtonGroupPlanoPosittion")==0?true:false;
							 ManejadorSketchs->ActualizaNewPlanoToCreate(cooRd(),ManejadorSketchs,deFult);
						 }
						 break;
					}
				   break;
				} 
			}

		   break;
												  
			 /////////////////////////////////////////////////////////RADIOBUTTON//////////////////////////////////////////////////////////
		     case Type::RADIOBUTTON:
				   /*if(ModoSonido)sonidos(9);
			       if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("radioButtonMostrarAngules",ManejadorForms)))
				   {
					   if(!MostrarAngules)
					   {   
							MostrarAngules=true;
							 ManejadorForms->Add(new Label("labelAngule1",(char*)to_string(DataESE[1]).c_str(), CRD(wigth-120,40,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,(float)wigth,(float)height),ManejadorForms);
							ManejadorForms->Add(new Label("labelAngule2",(char*)to_string(DataESE[2]).c_str(), CRD(wigth-120,55,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,(float)wigth,(float)height),ManejadorForms);
							ManejadorForms->Add(new Label("labelAngule3",(char*)to_string(DataESE[3]).c_str(), CRD(wigth-120,70,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,(float)wigth,(float)height),ManejadorForms);
							ManejadorForms->Add(new Label("labelAngule4",(char*)to_string(DataESE[4]).c_str(), CRD(wigth-120,85,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,(float)wigth,(float)height),ManejadorForms);
							ManejadorForms->Add(new Label("labelAngule5",(char*)to_string(DataESE[5]).c_str(), CRD(wigth-120,100,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,(float)wigth,(float)height),ManejadorForms);
							ManejadorForms->Add(new Label("labelCoordX",(char*)(string("x:")+to_string(DataESE[0])).c_str(), CRD(wigth-120,115,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,(float)wigth,(float)height),ManejadorForms);
							ManejadorForms->Add(new Label("labelCoordY",(char*)(string("y:")+to_string(DataESE[1])).c_str(), CRD(wigth-120,130,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,(float)wigth,(float)height),ManejadorForms);
							ManejadorForms->Add(new Label("labelCoordZ",(char*)(string("z:")+to_string(DataESE[2])).c_str(), CRD(wigth-120,145,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,(float)wigth,(float)height),ManejadorForms);
							
							ShowAngules(true);
							
					  }
				else
				   {
						ManejadorForms->Sub("labelAngule0",ManejadorForms);
						ManejadorForms->Sub("labelAngule1",ManejadorForms);
						ManejadorForms->Sub("labelAngule2",ManejadorForms);
						ManejadorForms->Sub("labelAngule3",ManejadorForms);
						ManejadorForms->Sub("labelAngule4",ManejadorForms);
						ManejadorForms->Sub("labelAngule5",ManejadorForms);
						ManejadorForms->Sub("labelCoordX",ManejadorForms);
						ManejadorForms->Sub("labelCoordY",ManejadorForms);
						ManejadorForms->Sub("labelCoordZ",ManejadorForms);
						MostrarAngules=false;
					   }
				   }		*/
		   break;
		                                //////////////////////////////BUTTONS////////////////////
		    case Type::BUTTONACEPTRB:
				if(Boxf1)
					ManejadorForms->Add(Interfaz(7),ManejadorForms);
				if(BoxAbout)
					ManejadorForms->Add(Interfaz(8),ManejadorForms);
				if(ModoSonido)sonidos(9);
				ManejadorForms->Add(Interfaz(0,INTERFZType::ACEPT),ManejadorForms);	
				if(!AceptCancelButtonDesdeThread)

				{
					InitMenu();
				}
				else
					AceptCancelButtonDesdeThread=false;
			break;

			case Type::BUTTONCANCELRB:
				if(Boxf1)
					ManejadorForms->Add(Interfaz(7),ManejadorForms);
				if(BoxAbout)
					ManejadorForms->Add(Interfaz(8),ManejadorForms);
				if(ModoSonido)sonidos(9);
				ManejadorForms->Add(Interfaz(0,INTERFZType::CANCEL),ManejadorForms);
				if(!AceptCancelButtonDesdeThread)
					InitMenu();
				else
					AceptCancelButtonDesdeThread=false;
			break;

			case Type::BUTTONEXIT:
				if(ModoSonido)sonidos(9);
				default_menu(-14);
				break;

	        case Type::BUTTONCANCELSETANGULES:
				if(ModoSonido)sonidos(9);
			default_menu(3);
		   break;

	       case Type::BUTTONINITSETANGULES:
			 //  if(ModoSonido)sonidos(9);
			 //  for(unsigned i=0;i<6;i++)
			 //  {
				//   s=("textBoxsSetAngules");
				//   if(eRror)
				//   {
				//		break;
				//   }
				//   s+=to_string(i);
				//   char*datA=ManejadorForms->GetForm((char*)s.c_str(),ManejadorForms)->GetEscritura();
				//   bool negtv=false,punto=false;
				//   for(unsigned i=0;i<strlen(datA);i++)
				//		{
				//		  if(!isdigit(datA[i]))
				//			 {
				//			  if(datA[i]=='.'&&punto==false)
				//			  {
				//				  punto=true;
				//			  }
				//			  else if(datA[i]=='-'&&negtv==false&&i==0)
				//				 {
				//				  negtv=true;
				//				 }
				//			  else
				//				 {
				//				  eRror=true;
				//				  break;
				//				 }
				//			 }
				//	   }
				//   s.clear();
			 //  }
			 //  if(eRror)
			 //  {
				//   ManejadorMensajes->Add(Frases(48),position::CENTER_TOP,(float)wigth,(float)height,3,1,0,0,2);
				//  if(ModoSonido)sonidos(6);
			 //  }
			 //  else
			 //  {
				//   ManejadorMensajes->Add(Frases(49),position::CENTER_TOP,(float)wigth,(float)height,3,0,1,0,2);
				//   for(unsigned i=0;i<6;i++)
				//   {
				//   s=("textBoxsSetAngules");
				//   s+=to_string(i);
				//	if(strlen(ManejadorForms->GetForm((char*)s.c_str(),ManejadorForms)->GetEscritura()))
				//	   DataESE[i]=(GLfloat)atof(ManejadorForms->GetForm((char*)s.c_str(),ManejadorForms)->GetEscritura());
				//	s.clear();
				//
				//   }
				//   // DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
				//   DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
				//   	
				//   ShowAngules();
				//   	
				//   if(ModoSonido)sonidos(8);
				//}
			 break;     
	   }
	   
	   	
	}
   
  
   else if(boton==GLUT_LEFT_BUTTON && state==GLUT_DOWN )//girar al puslar clik dercho con el mouse(misma opcion q el movRat para el primer clic no te varie la rotacion)
   {
	movRatXinit=(float)x;
	movRatYinit=(float)y;
   }
	glutPostRedisplay();
}
void ESE_CRT::keyboard(unsigned char tecla,int x,int y )
{
	if(_ManejadorForms.TextBox_Get_Escribiendo())
	{
		if(tecla!=8)
			_ManejadorForms.TextBox_Add_Caracter(tecla);
		else
			_ManejadorForms.TextBox_Sub_Caracter();
	}//return;

	/*if(tb.TextBox_Get_Escribiendo())
    {
	if(tecla==8)
		tb.TextBox_Sub_Caracter();
	 else
		tb.TextBox_Add_Caracter(tecla);*/
  //}

	if(tecla=='q')
		BoxInterfazPricipal->Set_Draw(true); 
	if(tecla=='w')
		BoxInterfazPricipal->Set_Draw(false); 
	if(tecla=='g'||tecla=='G')
   {
	   ManejadorMensajes->Add("Se ha tocado la letra 'g' o 'G'",CENTER_TOP,(float)wigth,(float)height,5,1,1,1);
	   /*if(GrabarBool)
	  {
		GrabarBool=false;


		XLSClass asd;
		asd.SalvarGrabar(GrabarAngle,Grabar,GrabarCont,anglesRedirecc);

		ManejadorMensajes->Add("Grabacion Terminada",position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,2,0,1,0,2);
	  }
	  else
	  {
		for(unsigned i=0;i<3;i++)
		   GrabarAngle[i]=(float)DataESE[i];
		GrabarCont=0;
		GrabarBool=true;
		ManejadorMensajes->Add("Grabando",position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,100,1,1,1,2);
	  }*/
  }
  if(ManejadorForms->GetEstoyEscribindo())
  {
	if(tecla==8)
	    ManejadorForms->SubText(ManejadorForms);
	else
		ManejadorForms->AddText(tecla,ManejadorForms);
  }
  else
  {
	if(!recibir_serie&&!SetAngules)
	{
	  CRD CoordElement;
	  double*ElementCoord;
	  switch (tecla)
	    {
        case '1':
			DataESE[0]+=(GLfloat)RazonDeAumento;
			 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		break;

		case '2':
			DataESE[0]-=(GLfloat)RazonDeAumento;	
			 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		break;

		case '3':
			DataESE[1]+=(GLfloat)RazonDeAumento;
			 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		break;

		case '4':
			DataESE[1]-=(GLfloat)RazonDeAumento;
			 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		break;

		case '5':
			DataESE[2]+=(GLfloat)RazonDeAumento;
			 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		break;

		case '6':
			DataESE[2]-=(GLfloat)RazonDeAumento;
			 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		break;

		/*case '7':
			DataESE[3]+=(GLfloat)0.9;
			 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		break;

		case '8':
			DataESE[3]-=(GLfloat)0.9;
			 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		break;

		case '9':	
			DataESE[4]+=(GLfloat)0.9;
			 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		break;

		case '0':
			DataESE[4]-=(GLfloat)0.9;
			 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		break;

		case '-':			
			DataESE[5]+=(GLfloat)0.9;
			 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		break;

		case '=':
			DataESE[5]-=(GLfloat)0.9;
			 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		break;*/

		case '<':
			 trasladarY+=5;
			 SeguirPuntoFinal=false;
			break;

		case '>':
			 trasladarY-=5;
			 SeguirPuntoFinal=false;
			break;
		case 's':
			if(ModoSonido)sonidos(9);
 			ManejadorForms->NextFocus("BoxInterfazPricipal",ManejadorForms);
	 	break;

		case 'w':
			ElementCoord=ManejadorForms->FocusClick("BoxInterfazPricipal",ManejadorForms);
			teclaRaton(GLUT_LEFT_BUTTON,GLUT_UP,(int)ElementCoord[0],(int)ElementCoord[1]);
			delete[]ElementCoord;
		break;

		case 'q':
			CoordElement=ManejadorForms->GetForm("BoxInterfazPricipalButtonAcept",ManejadorForms)->GetCoord(ManejadorForms->GetForm("BoxInterfazPricipalButtonAcept",ManejadorForms));
			teclaRaton(GLUT_LEFT_BUTTON,GLUT_UP,(int)CoordElement.x,(int)CoordElement.y);
		break;

		case 'e':
			CoordElement=ManejadorForms->GetForm("BoxInterfazPricipalButtonCancel",ManejadorForms)->GetCoord(ManejadorForms->GetForm("BoxInterfazPricipalButtonCancel",ManejadorForms));
			teclaRaton(GLUT_LEFT_BUTTON,GLUT_UP,(int)CoordElement.x,(int)CoordElement.y);
		break;
	    }
	    DataProcessor::RectificarAngules(DataESE);
	    ShowAngules();
	   

	 }
	 else
     {
	    //messeng=new MeSSenger("Accion no valida ;Conexion por puerto serie ya iniciada",position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,1,0,0,2);
     } 
   }
   glutPostRedisplay();//refresco y ejecuto el displayFunc()
}
void ESE_CRT::wheel(int boton,int direcc,int x,int y){
	
	if(direcc>0) {
		if(movWheel<20) 
			movWheel+=0.1;
	
	}else {
		
	
	 if(movWheel>1) 
		 movWheel-=0.3;
	
	
	}
		glutPostRedisplay();//refresco y ejecuto el displayFunc()

}
void ESE_CRT::SpecialKeys(int tecla,int x,int y ){
	switch (tecla)
	{
	case -1:
		DataESE[0]=(GLfloat)anglesRedirecc[0];
		DataESE[1]=(GLfloat)anglesRedirecc[1];
		DataESE[2]=(GLfloat)anglesRedirecc[2];
		 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		ShowAngules();
	break;

	case GLUT_KEY_F1:
		ManejadorForms->Add(Interfaz(7),ManejadorForms);
		break;
	case GLUT_KEY_F2:	 //Ocultar Piezas
			if(!boolMenuToDraw)
			{
			   contMenuToDraw=-2;
			   boolMenuToDraw=true;
			}
			else
			{
			   contMenuToDraw=-1;
			   boolMenuToDraw=false;
			}
	break;

	case GLUT_KEY_F3:	  //Girar al Plano(Solo interfaz 2 && boceto!=0)
		if((interfaz==2||PlanoAcceso)&&Plano::IsRestring(ManejadorSketchs->BocetoActual(ManejadorSketchs)))
		{
			CRD toMove=Plano::RotarAlPlano(ManejadorSketchs->BocetoActual(ManejadorSketchs));
			movESE_CRTX=(float)toMove.x*velGiro;
			movESE_CRTY=(float)toMove.y*velGiro;
			movESE_CRTZ=(float)toMove.z*velGiro;
			if(RotarAlPlanoContrar)
			{
				movESE_CRTX+=180*velGiro;
				movESE_CRTY+=180*velGiro;
				movESE_CRTZ+=180*velGiro;
				RotarAlPlanoContrar=false;
				Plano::verPlanoRotado((float)0.1,ManejadorSketchs->BocetoActual(ManejadorSketchs));
			}
			else
			{
				RotarAlPlanoContrar=true;
				Plano::verPlanoRotado((float)-0.1,ManejadorSketchs->BocetoActual(ManejadorSketchs));
			}

		}
	break;

	case GLUT_KEY_F4:	//"Referenciar"
		if(!recibir_serie)
		{
			trasladarX=0;
			trasladarY=0;
			trasladarZ=0;
			DataESE[0]=(GLfloat)anglesRedirecc[0];
			DataESE[1]=(GLfloat)anglesRedirecc[1];
			DataESE[2]=(GLfloat)anglesRedirecc[2];
			 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
			ShowAngules();
		}
		else
		{
			trasladarX=0;
			trasladarY=0;
			trasladarZ=0;
			MenuVista(-1);
			SeguirPuntoFinal=false;
		}
	break;

	case GLUT_KEY_F5:	   //Todos los angulos a 0
		if(!recibir_serie)
		{
		   trasladarX=0;
		   trasladarY=0;
		   trasladarZ=0;
		   DataESE[0]=0;
           DataESE[1]=0;
           DataESE[2]=0;
          /* DataESE[3]=0;
	 	   DataESE[4]=0;
		   DataESE[5]=0;*/
		   SeguirPuntoFinal=false;
		   MenuVista(-1);
		   DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		   ShowAngules();
		}
		else
		{
			trasladarX=0;
			trasladarY=0;
			trasladarZ=0;
			MenuVista(-1);
			SeguirPuntoFinal=false;
		}
	break;

	case GLUT_KEY_F6:	//Ir al punto final del brazo
		trasladarX=-DataESE[0];
		trasladarY=-DataESE[1];
		trasladarZ=-DataESE[2];
		SeguirPuntoFinal=false;
	break;

	case GLUT_KEY_F7:	 //Seguir el punto final del brazo
		if(!SeguirPuntoFinal)
		{   
			SeguirPuntoFinal=true;
			 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		}
		break;
	case GLUT_KEY_F8:
		if(interfaz==2)
		{
			CRD*toTraslated;
			toTraslated=new CRD(Plano::Media(ManejadorSketchs->BocetoActual(ManejadorSketchs)));
			trasladarX=-toTraslated->x;
			trasladarY=-toTraslated->y;
			trasladarZ=-toTraslated->z;
		}
		break;
	     
		case GLUT_KEY_LEFT:	
			trasladarX+=5;
			SeguirPuntoFinal=false;
		break;

		case GLUT_KEY_RIGHT:
			trasladarX-=5;
			SeguirPuntoFinal=false;
		break;

		case GLUT_KEY_UP:
	           trasladarZ-=5;
			SeguirPuntoFinal=false;
		break;

		case GLUT_KEY_DOWN:
			trasladarZ+=5;
			SeguirPuntoFinal=false;
	break;			
	}
	glutPostRedisplay();//refresco y ejecuto el displayFunc()
}
//////////////////////////MENUS////////////////////////////////////////////////////////
void ESE_CRT::default_menu(int opcion){
	switch (opcion)
	{
	case 4:///SET DataESE
		/*if(ModoSonido)sonidos(9);
	    default_menu(-6);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules0",CRD(0,175,0),110,(float)wigth,(float)height,(char*)to_string(DataESE[0]).c_str(),9,TextBoxType::FLOATCONTENT),ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules1",CRD(0,200,0),110,(float)wigth,(float)height,(char*)to_string(DataESE[1]).c_str(),9,TextBoxType::FLOATCONTENT),ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules2",CRD(0,225,0),110,(float)wigth,(float)height,(char*)to_string(DataESE[2]).c_str(),9,TextBoxType::FLOATCONTENT),ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules3",CRD(0,250,0),110,(float)wigth,(float)height,(char*)to_string(DataESE[3]).c_str(),9,TextBoxType::FLOATCONTENT),ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules4",CRD(0,275,0),110,(float)wigth,(float)height,(char*)to_string(DataESE[4]).c_str(),9,TextBoxType::FLOATCONTENT),ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules5",CRD(0,300,0),110,(float)wigth,(float)height,(char*)to_string(DataESE[5]).c_str(),9,TextBoxType::FLOATCONTENT),ManejadorForms);
		ManejadorForms->Add(new Button("buttonInitSetAngules",Type::BUTTONINITSETANGULES, CRD(0,325,0),0,1,0,80,10,(float)wigth,(float)height),ManejadorForms);
		ManejadorForms->Add(new Button("buttonCancelSetAngules",Type::BUTTONCANCELSETANGULES, CRD(80,325,0),1,0,0,30,10,(float)wigth,(float)height),ManejadorForms);
		SetAngules=true;*/
		break;
	case 3://Cancel setangules
			if(ModoSonido)sonidos(9);
		    default_menu(-5);
		break;

	case 0://inicializo botones para INIT CONNECTION
		  /*if(ModoSonido)sonidos(9);
		  default_menu(-5);
		   if(Boxf1)
					ManejadorForms->Add(Interfaz(7),ManejadorForms);
		   if(BoxAbout)
					ManejadorForms->Add(Interfaz(8),ManejadorForms);
		  default_menu(-6); 
		  ManejadorForms->Add(Interfaz(3),ManejadorForms);*/
		  BoxConnection->Set_Draw(true);
	break;


	case 1://inicializo botonos para el STOP CONNECTION
			/*if(ModoSonido)sonidos(9);
		    ManejadorForms->Add(Interfaz(4),ManejadorForms);
			 if(Boxf1)
					ManejadorForms->Add(Interfaz(7),ManejadorForms);
			default_menu(-6);*/
			BoxConnection->Set_Draw(true);
	break;


	case -1://Inicio la conexion
		
		if(!serialPort.inicializa( ManejadorForms->GetForm("BoxInterfazConnections",ManejadorForms)->BoxGetEscritura("textBoxChar"),atol(ManejadorForms->GetForm("BoxInterfazConnections",ManejadorForms)->BoxGetEscritura("textBoxUnsigned"))))
		  {
			  if(ModoSonido)sonidos(1);
			  string f;
			  if(serialPort.ErrorStr()[0]=='C')
				  f=string(Frases(99))+string(ManejadorForms->GetForm("BoxInterfazConnections",ManejadorForms)->BoxGetEscritura("textBoxChar"))+string(":")+string(ManejadorForms->GetForm("BoxInterfazConnections",ManejadorForms)->BoxGetEscritura("textBoxUnsigned"));
			  else
				  f=string(serialPort.ErrorStr());
			  if(ModoLogger)cout<<f.c_str()<<endl;
			   char*msg=new char[f.length()+1];
			   msg[f.length()]=0;
			   for(unsigned i=0;i<f.length();i++)
				   msg[i]=f[i]; 
			   ManejadorMensajes->Add((char*)f.c_str(),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,5,1,0,0,2);
		   }
		else 
		   {
			   char*msg=serialPort.GetMesage(serialPort);
			   if(ModoLogger)cout<<endl<<serialPort.getChar()<<":"<<serialPort.getunsigned()<<endl;
		      //add
			   ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelESE_CRT")->SetColor(0,(GLfloat)1,0);
			   ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelChar")->AddNewText(serialPort.getChar());
			   ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelUnsigned")->AddNewText((char*)to_string(serialPort.getunsigned()).c_str());
			   ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelChar")->SetDraw(false);
			   ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelUnsigned")->SetDraw(false);
			   ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->AddNewText(Frases(115));
			   ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->SetColor(1,1,0);
			   ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->SetDraw(false);
			  

			    /*ManejadorForms->Add(new Label("labelChar",serialPort.getChar(),*(new CRD(97,-5,0)),0,0,1,0,(float)wigth,(float)height),ManejadorForms);
			    ManejadorForms->Add(new Label("labelUnsigned",(char*)to_string(serialPort.getunsigned()).c_str(),*(new CRD(97,5,0)),0,0,1,0,(float)wigth,(float)height),ManejadorForms);
			    ManejadorForms->SetColor("labelESE_CRT",0,1,0,ManejadorForms);
			    ManejadorForms->Add(new Label("labelReferenaciar",Frases(115),*(new CRD(0,19,0)),1,0,1,0,(float)wigth,(float)height),ManejadorForms);
				ManejadorForms->GetForm("labelReferenaciar",ManejadorForms)->SetColor(1,1,0);*/
			    StackAnimation*sa=new StackAnimation("StackAnimationsConnection");
			    sa->STANSetAnimation("AnimacionRoja", CRD(wigth-100,height-50,0),75,(float)wigth,(float)height,-25,1,0,0,1.5);
			    sa->STANSetAnimation("AnimacionVerde", CRD(wigth-100,height-50,0),75,(float)wigth,(float)height,0,0,1,0,1.5);
			    sa->STANSetAnimation("AnimacionAzul", CRD(wigth-100,height-50,0),75,(float)wigth,(float)height,25,0,0,1,1.5);
			    ManejadorForms->Add(sa,ManejadorForms);
			    ManejadorForms->MoveOnReshape("StackAnimationsConnection",true,ManejadorForms);


		        recibir_serie=true;
				delete ThreadSerialPort;
			    ThreadSerialPort=new thread(ThreadCOM);
			    contMenuToDraw=-1;
			    ManejadorMensajes->Add(msg,position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,0,1,0,2);
				delete[]toSaveCOM;
				toSaveCOM=new char[strlen(serialPort.getChar())+1];
				toSaveCOM[strlen(serialPort.getChar())]=0;
				for(unsigned i=0;i<strlen(serialPort.getChar());i++)
					toSaveCOM[i]=serialPort.getChar()[i];
				toSaveSpeed=serialPort.getunsigned();
			   ESE_CRT::InitMenu();
			   if(Boxf1)
					ManejadorForms->Add(Interfaz(7),ManejadorForms);
			   if(BoxAbout)
					ManejadorForms->Add(Interfaz(8),ManejadorForms);
			   if(ModoSonido)sonidos(5);
		}
	break;


	case -2://detengo la conexion 
			recibir_serie=false;
			if(PlanoAcceso)
			{
				PlanoAcceso=false;
				ManejadorSketchs->Sub("PlanoAcceso",ManejadorSketchs);
				ManejadorSketchs->SetDraw(false,ManejadorSketchs);
			}
			ThreadSerialPort->join();
			serialPort.CloseConnection();
			ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelChar")->SetDraw(true);
			ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelUnsigned")->SetDraw(true);
			ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->SetDraw(true);
			ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelESE_CRT")->SetColor((GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7);
			
			ManejadorForms->Sub("StackAnimationsConnection",ManejadorForms);
			EsperandoReedireccionar=true;
			ErrorConnect=false;
			Acces=false;
			ESE_CRT::InitMenu();
			//if(serialPort.GetType()==ConnectionType::SERIAL_PORT)
			 default_menu(-5);
			 if(Boxf1)
					ManejadorForms->Add(Interfaz(7),ManejadorForms);
			if(ModoSonido)sonidos(10);
			if(ModoLogger)cout<<endl<<Frases(79)<<endl;
	break;
	case -5:    //Muestro Menu
		    default_menu(-7);
			ManejadorForms->SetDraw(false,"BoxInterfazPricipal",ManejadorForms);
			ManejadorForms->SetDraw(false,"BoxInterfazPricipalButtonAcept",ManejadorForms);
			ManejadorForms->SetDraw(false,"BoxInterfazPricipalButtonCancel",ManejadorForms);
		    //InitMenu();
		break;

	case -6:	//Oculto Menu
			ManejadorForms->SetDraw(true,"BoxInterfazPricipal",ManejadorForms);
			ManejadorForms->SetDraw(true,"BoxInterfazPricipalButtonAcept",ManejadorForms);
			ManejadorForms->SetDraw(true,"BoxInterfazPricipalButtonCancel",ManejadorForms);
		    //InitMenu();
		break;
	case -7:	//Oculto SetAngules
			if(SetAngules)
			   {
			   ManejadorForms->Sub("textBoxsSetAngules0",ManejadorForms);
			   ManejadorForms->Sub("textBoxsSetAngules1",ManejadorForms);
			   ManejadorForms->Sub("textBoxsSetAngules2",ManejadorForms);
	   		   ManejadorForms->Sub("textBoxsSetAngules3",ManejadorForms);
			   ManejadorForms->Sub("textBoxsSetAngules4",ManejadorForms);
			   ManejadorForms->Sub("textBoxsSetAngules5",ManejadorForms);
			   ManejadorForms->Sub("buttonInitSetAngules",ManejadorForms);
			   ManejadorForms->Sub("buttonCancelSetAngules",ManejadorForms);
			   SetAngules=false;
			   }
		break;
	case -8: //desact modo logger
			ModoLogger=false;
			if(ModoSonido)sonidos(7);
			ManejadorMensajes->Add(Frases(80),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,1,1,0,2);
			cout<<Frases(80)<<endl;
			InitMenu();
		break;
	case -9:  //activ modo logger
			if(ModoSonido)sonidos(7);
			ModoLogger=true;
			ManejadorMensajes->Add(Frases(81),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,1,1,0,2);
			cout<<Frases(81)<<endl;
			InitMenu();
		break;
	case -10:  //mostrar ESE_CRT About
			if(ModoSonido)sonidos(9);
			ManejadorForms->Add(Interfaz(8),ManejadorForms);
		break;
	case -11: //descat modo mute
		ModoSonido=false;
		ManejadorMensajes->Add(Frases(96),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,1,1,0,2);
		if(ModoLogger)cout<<Frases(96)<<endl;
		InitMenu();
		break;
	case -12: //activ modo mut
		ModoSonido=true;
		if(ModoSonido)sonidos(7);
		ManejadorMensajes->Add(Frases(95),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,1,1,0,2);
		if(ModoLogger)cout<<Frases(95)<<endl;
		InitMenu();
		break;

		case -13:
		salvarInitDatos();
		exit(0);
		break;

		case -14:
			ManejadorForms->Add(Interfaz(10),ManejadorForms);
		break;
		case -15:
			/*if(SetAnglesREdirecc())
			{
				ManejadorMensajes->Add(Frases(301),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,0,1,0,2);
				SpecialKeys(GLUT_KEY_F4,0,0);
			}
			else
			{
				ManejadorMensajes->Add(Frases(302),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,1,0,0,2);
			}*/
			break;
	}
	
	
	glutPostRedisplay();
}
void ESE_CRT::MenuVista(int opcion){
	if(ModoSonido)sonidos(9);
	switch(opcion){
	case -1://Panoramica
		movESE_CRTX=-45*velGiro;
		movESE_CRTY=-45*velGiro;
		movESE_CRTZ=0*velGiro;
		break;
	case 0://FRONTAl
		movESE_CRTX=-90*velGiro;
		movESE_CRTY=0;
		movESE_CRTZ=-90*velGiro;
		break;
	case 1://TRASERA
		movESE_CRTX=-90*velGiro;
		movESE_CRTY=0;
		movESE_CRTZ=90*velGiro;
		break;
	case 2://Derecha
		movESE_CRTX=-90*velGiro;
		movESE_CRTY=0;
		movESE_CRTZ=180*velGiro;
		break;
	case 3://Izquierda
		movESE_CRTX=-90*velGiro;
		movESE_CRTY=0;
		movESE_CRTZ=0;
		break;
	case 4://Superior
		movESE_CRTX=0;
		movESE_CRTY=0;
		movESE_CRTZ=0;
		break;
	case 5://inferior
		movESE_CRTX=180*velGiro;
		movESE_CRTY=0;
		movESE_CRTZ=0;
		break;
	
	
	
	}	
	glutPostRedisplay();
}
void ESE_CRT::MenuToDraw(int caso){
  if(ModoSonido)sonidos(9);
  if(!recibir_serie)
    {
		if(caso!=-1)
		{
			trasladarY=trasladarX=trasladarZ=0;
		}
     contMenuToDraw=caso;
     }
  else
  {
	  ManejadorMensajes->Add(Frases(50),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,1,0,0,2);
  }
glutPostRedisplay();//refresco y ejecuto el displayFunc()
}
void ESE_CRT::MenuPuertoSeie(int opcion){
	
		
}
void ESE_CRT::MenuIdioma(int opcion)
{
	switch (opcion)
	{
	case 0:
		idioma=Language::ENGLISH;
		break;
	case 1:
		idioma=Language::SPANISH;
		break;
	default:
		idioma=Language::ENGLISH;
		break;
	}
	ManejadorMensajes->Add(Frases(62),position::CENTER_TOP,(float)wigth,(float)height,3,1,1,0,2);
	if(ModoSonido)sonidos(7);
	if(ModoLogger)cout<<Frases(66)<<endl;
	glutPostRedisplay();

}
///////////////////////// DATOS//////////////////////////////////////////////////

bool ESE_CRT::IniciarConnection(char*Char,unsigned Unsigned)
{
	if(!serialPort.inicializa( Char,Unsigned))
	{
		if(ModoSonido)sonidos(1);
		string f;
		if(serialPort.ErrorStr()[0]=='C')
			f=string(Frases(99))+string(Char)+to_string(Unsigned);
		else
			f=string(serialPort.ErrorStr());
		if(ModoLogger)cout<<f.c_str()<<endl;
		char*msg=new char[f.length()+1];
		msg[f.length()]=0;
		for(unsigned i=0;i<f.length();i++)
			msg[i]=f[i]; 
		ManejadorMensajes->Add((char*)f.c_str(),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,5,1,0,0,2);
		return false;
	}
	else 
	{
		char*msg=serialPort.GetMesage(serialPort);
		if(ModoLogger)cout<<endl<<serialPort.getChar()<<":"<<serialPort.getunsigned()<<endl;
		//add
		ManejadorMensajes->Add("Conectado Correctamente",position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,5,0,1,0,2);
		ContainerPrincipal->LabelsInicarConeccion(Char,(char*)to_string(Unsigned).c_str(),"No Referenciado");
		
		
		/*ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelESE_CRT")->SetColor(0,(GLfloat)1,0);
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelChar")->AddNewText(serialPort.getChar());
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelUnsigned")->AddNewText((char*)to_string(serialPort.getunsigned()).c_str());
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelChar")->SetDraw(false);
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelUnsigned")->SetDraw(false);
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->AddNewText(Frases(115));
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->SetColor(1,1,0);
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->SetDraw(false);
		*/	  

		/*ManejadorForms->Add(new Label("labelChar",serialPort.getChar(),*(new CRD(97,-5,0)),0,0,1,0,(float)wigth,(float)height),ManejadorForms);
		ManejadorForms->Add(new Label("labelUnsigned",(char*)to_string(serialPort.getunsigned()).c_str(),*(new CRD(97,5,0)),0,0,1,0,(float)wigth,(float)height),ManejadorForms);
		ManejadorForms->SetColor("labelESE_CRT",0,1,0,ManejadorForms);
		ManejadorForms->Add(new Label("labelReferenaciar",Frases(115),*(new CRD(0,19,0)),1,0,1,0,(float)wigth,(float)height),ManejadorForms);
		ManejadorForms->GetForm("labelReferenaciar",ManejadorForms)->SetColor(1,1,0);*/
		
		/*StackAnimation*sa=new StackAnimation("StackAnimationsConnection");
		sa->STANSetAnimation("AnimacionRoja", CRD(wigth-100,height-50,0),75,(float)wigth,(float)height,-25,1,0,0,1.5);
		sa->STANSetAnimation("AnimacionVerde", CRD(wigth-100,height-50,0),75,(float)wigth,(float)height,0,0,1,0,1.5);
		sa->STANSetAnimation("AnimacionAzul", CRD(wigth-100,height-50,0),75,(float)wigth,(float)height,25,0,0,1,1.5);
		ManejadorForms->Add(sa,ManejadorForms);
		ManejadorForms->MoveOnReshape("StackAnimationsConnection",true,ManejadorForms);
*/

		recibir_serie=true;
		delete ThreadSerialPort;
		ThreadSerialPort=new thread(ESE_CRT::ThreadCOM);
		contMenuToDraw=-1;
		ManejadorMensajes->Add(msg,position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,0,1,0,2);
		delete[]toSaveCOM;
		toSaveCOM=new char[strlen(serialPort.getChar())+1];
		toSaveCOM[strlen(serialPort.getChar())]=0;
		for(unsigned i=0;i<strlen(serialPort.getChar());i++)
			toSaveCOM[i]=serialPort.getChar()[i];
		toSaveSpeed=serialPort.getunsigned();
		ESE_CRT::InitMenu();
		/*if(Boxf1)
			ManejadorForms->Add(Interfaz(7),ManejadorForms);
		if(BoxAbout)
			ManejadorForms->Add(Interfaz(8),ManejadorForms);
		if(ModoSonido)sonidos(5);*/
		return true;
	}
}
bool ESE_CRT::DetenerConnection()
{
		recibir_serie=false;
		if(PlanoAcceso)
		{
			PlanoAcceso=false;
			ManejadorSketchs->Sub("PlanoAcceso",ManejadorSketchs);
			ManejadorSketchs->SetDraw(false,ManejadorSketchs);
		}
		ThreadSerialPort->join();
		serialPort.CloseConnection();
		ContainerPrincipal->LabelsDetenerConeccion();
		/*ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelChar")->SetDraw(true);
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelUnsigned")->SetDraw(true);
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->SetDraw(true);
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelESE_CRT")->SetColor((GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7);*/
			
		//ManejadorForms->Sub("StackAnimationsConnection",ManejadorForms);
		EsperandoReedireccionar=true;
		ErrorConnect=false;
		Acces=false;
		ESE_CRT::InitMenu();
		//if(serialPort.GetType()==ConnectionType::SERIAL_PORT)
		//default_menu(-5);
		//if(Boxf1)
			//ManejadorForms->Add(Interfaz(7),ManejadorForms);
		ManejadorMensajes->Add("Desconectado Correctamente",position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,5,0,1,0,2);
		if(ModoSonido)sonidos(10);
		if(ModoLogger)cout<<endl<<Frases(79)<<endl;
		return true;
}

void ESE_CRT::recivirDatosCOM(){
	if(recibir_serie)
	   {
					/*COMANDOS
		///////////////////////////////Comando de Cliente///////////////////////
		(7)-00000111->Referenaciar
		(11)00001111->CambiarFocus de la caja
		(15)00001011->Click al Focus
		(19)00010011->AceptButton
		(23)00010111->CancelButton
		///////////////////////////////Comando Seguridad////////////////////////
		((1)000000001 + (4)00000100)->Seguridad 
		/////////////////////////////////Comando ESE////////////////////////////
		(LowByte[bit0]==1 && HightByte[bit0]==1)->ESE
		//////////////////////////////////Comando de Servidor///////////////////
		(35)00100011->ESE_CRT ESE_CRT_BRAZO
		(39)00100111->ESE_CRT WINDOWS
		(43)00101011->ESE_CRT WEB
		(47)00101111->ESE_CRT HTML
		(51)00110011->ESE_CRT USER
		(55)00110111->ESE_CRT!USER
		(59)00111011->ESE_CRT ADD BOCETO
		(63)00111111->ESE_CRT REMOVE BOCETO
		(67)01000011->ESE_CRT POINT
		(71)01000111->ESE_CRT LINE
		(75)01001011->ESE_CRT STRIPLINE
		(79)01001111->ESE_CRT SPLINE
		(83)01010011->ESE_CRT BSPLINE
		(85)01010111->ESE_CRT CANCEL
		(91)01011011->ESE_CRT MOSTRAR_PLANO
		(95)01011111->ESE_CRT!MOSTRAR_PLANO
		(99)01100011->ESE_CRT PUENTE_WEB
	   (103)01100111->ESE_CRT !!!!!!!!!!!!!!!!!!!!!!!!!!TANSMITE_PLANO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   (107)01101011->ESE_CRT PUENTE_WEB_CON_DATOS_A_LA_WEB
	   (111)01101111->ESE_CRT PERDER ESE
		(115)01110011->ESE_CRT RESPUESTA_PUETE_WEB
		(119)01110100->CLIENTE DESCONECTADO
						*/

										/*
                                      Comandos
                                00000111-7   (Referenciar)
                                00001011-11  (Pintar)
                                00010011-19  (Codigo Verificacion)
                                         */
		  if(StopThread)
			   return;
			////////////////////////////////////////////////////ERROR:RECONECTAR/////////////////////////////////////////////////////////////
		  if(ErrorConnect)
		  {
			 if(serialPort.inicializa(toSaveCOM,toSaveSpeed))
			 {
				ErrorConnect=false;
				ManejadorForms->Add(Interfaz(9),ManejadorForms);
				if(ModoSonido)sonidos(5);
				ManejadorMensajes->Add(Frases(91),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,0,1,0,2);
				if(ModoLogger)cout<<Frases(91)<<endl;
			}  
		  	return;
		  }
			///////////////////////////////////////////////////////RECIVO DATOS/////////////////////////////////////////////////////////////////////////
		  char*c=serialPort.Recibir();//Recivo un dato
		  if(!recibir_serie)
			  return;
			/////////////////////////////////////////////////////////ERROR CONEXION////////////////////////////////////////////////////////////////////
		  if(serialPort.Error())	 //Si algo dio error
		  {
				if(ModoLogger)cout<<serialPort.ErrorStr()<<endl<<Frases(89);
				if(serialPort.ErrorStr()[0]=='C')
				{
					ManejadorMensajes->Add(Frases(102),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,1,0,0,2);
				}
				else
				{
					ManejadorMensajes->Add(Frases(101),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,1,0,0,2);
				}
				ErrorConnect=true;
				EsperandoReedireccionar=true;
				serialPort.CloseConnection();
				ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->AddNewText(Frases(115));
				ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->SetColor(1,1,0);
				/*ManejadorForms->GetForm("labelReferenaciar",ManejadorForms)->AddNewText(Frases(115));
				ManejadorForms->GetForm("labelReferenaciar",ManejadorForms)->SetColor(1,1,0);*/
				ManejadorForms->GetForm("BoxInterfazPricipalButtonCancel",ManejadorForms)->ActivateDesactivate(false);
				ManejadorForms->GetForm("BoxInterfazPricipalButtonAcept",ManejadorForms)->ActivateDesactivate(true);
				ManejadorForms->Add(Interfaz(9),ManejadorForms);
		
				
				/*Acces=false;
				Acceso(Acces);
				if(PlanoAcceso)
				{
					PlanoAcceso=false;
					
					ManejadorSketchs->Sub("PlanoAcceso",ManejadorSketchs);
					ManejadorSketchs->SetDraw(false,ManejadorSketchs);
					
				}*/
				if(ModoSonido)sonidos(1);
				delete[]c;
				return;
		  }
		   if(c!=NULL)///////si no esta vacio////////// 
		   {
		      for(unsigned i=0;i<strlen(c);i++)	//Un 'for' por si llegan mas de 1 byte
			  {
				bool pintar=false;
				contt++;
				if(ModoLogger)
				{
					DataProcessor::printByte(c[i],false);
					cout<<"-["<<contt<<"]";
				}
				if(GrabarBool)
				{
					if(GrabarCont==connstGrab)
						connstGrab=0;
					Grabar[GrabarCont++]=c[i];
				}
				/////////////////////////////////////////////////////VERIFICACION DE SEGURIDAD////////////////////////////////////////////////////////
				if(c[i]!=7)
				{
					if(VerificacionSeguridad(c[i]))
						continue;
				}
				////////////////////////////////////////////////////CODIGO DE DIBUJO//////////////////////////////////////////////////////////////
				 if(DataProcessor::CodigoCliente(c[i]))
				 {
					 ESE_CRT::CodigoCliente(c[i],pintar);
			     }
				 else if(EsperandoReedireccionar)///////PARA Q NO SE EJECUTE NADA HASTA Q NO SE REDIRECCIONE///////
				 {
					 ManejadorMensajes->Add(Frases(65),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,2,1,1,0,2);
					 if(ModoLogger)cout<<Frases(64);
					 if(ModoSonido)sonidos(6);
				 }
				//////////////////////////////////////////////////////////////MOVER Y/O PINTAR///////////////////////////////////////////////////////////
				 else if(DataProcessor::CodigoESE(c[i]))
			     {
					if(!pintar)
					{
						DataProcessor::PorcesarDatos(c[i],DataESE,(GLfloat)RazonDeAumento);//ejecuto la lectura de los bits y muevo los angulos(true es pintar)
						DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
						ShowAngules(false,true);
					}
					if(interfaz==2)///////Actualizo la ultima coordenada en el StackBoceto///////
				       ManejadorSketchs->ActualizaLastCood(cooRd(),ManejadorSketchs);
					else if(interfaz==-5)
						ManejadorSketchs->ActualizaNewPlanoToCreate(cooRd(),ManejadorSketchs,deFult);
					
					if(pintar) 
					{ 
					   if(interfaz==-1) ///////interfaz de Add new Boceto////////
					   {
						   
						   if(ManejadorSketchs->contNPl<3||CambiarPointSpecificPlano!=3)
						   {
							   ManejadorSketchs->AddPuntoNewPlano(cooRd(),ManejadorSketchs,CambiarPointSpecificPlano);
							   
							   ManejadorForms->Add(Interfaz(-1),ManejadorForms);
							   
							   if(ManejadorSketchs->contNPl==3)
								   ManejadorForms->ActivateForm("BoxInterfazPricipalButtonAcept",ManejadorForms);
						   }
						   
					   }
					   else if(interfaz==2||PlanoAcceso)/////////////Interfaz de Dibujo////////////
				       {
						  
						  ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxSetActivateDesactivate("RadioButtomCancelLast",true); 
						  
						  
						  ManejadorSketchs->AddPoint(cooRd(),ManejadorSketchs);
						  
						  if(ModoSonido)sonidos(4);
					   }
			        }//end if(pintar)		
			     }//end else
				 else
				 {
					 if(ModoLogger)
					 {
						cout<<"!!!!!CUIDADO";
						DataProcessor::printByte(c[i+1]);
						cout<<"-";
						DataProcessor::printByte(c[i]);
						cout<<"-["<<contt<<"]-No es un codigo ESE, Bytes no procesados(Tal vez ocurra un error en la seguridad del protocolo)";
					 }
				 }
				 if(ModoLogger)cout<<"("<<tCOM.Incrementa(&tCOM)<<")"<<endl;
		         tCOM.ResettIncrementa(&tCOM);
		      }//end for
		   }//end if(!NULL)
	    }//end recivir serie	
}
void ESE_CRT::salvarInitDatos(){
	fstream f;
	f.open("ESE_CRT.onrn",ios::out|ios::binary);
	f.write((char*)&ModoSonido,sizeof(bool));
	f.write((char*)&ModoLogger,sizeof(bool));
	f.write((char*)&movRatXinit,sizeof(int));
	f.write((char*)&movRatYinit,sizeof(int));
	f.write((char*)&movRatX,sizeof(int));
	f.write((char*)&movRatY,sizeof(int));
	f.write((char*)&movESE_CRTZ,sizeof(int));
	f.write((char*)&DataESE[0],sizeof(GLfloat));
	f.write((char*)&DataESE[1],sizeof(GLfloat));
	f.write((char*)&DataESE[2],sizeof(GLfloat));
	/*f.write((char*)&DataESE[3],sizeof(GLfloat));
	f.write((char*)&DataESE[4],sizeof(GLfloat));
	f.write((char*)&DataESE[5],sizeof(GLfloat));*/
	f.write((char*)&movWheel,sizeof(GLdouble));
	f.write((char*)&trasladarX,sizeof(double));
	f.write((char*)&trasladarY,sizeof(double));
	f.write((char*)&trasladarZ,sizeof(double));

	char*a=new char[strlen(toSaveCOM)+1];
	a[strlen(toSaveCOM)]=0;
	for(unsigned i=0;i<strlen(toSaveCOM);i++)
	   a[i]=toSaveCOM[i];
	unsigned b=strlen(a);
	f.write((char*)&b,sizeof(unsigned));
	f.write((char*)a,b);
	f.write((char*)&toSaveSpeed,sizeof(unsigned));
	delete[]a;
	a=new char[strlen(toSaveIp)+1];
	a[strlen(toSaveIp)]=0;
	for(unsigned i=0;i<strlen(toSaveIp);i++)
	   a[i]=toSaveIp[i];
	b=strlen(a);
	f.write((char*)&b,sizeof(unsigned));
	f.write((char*)a,b);
	f.write((char*)&toSavePort,sizeof(unsigned));
	delete[]a;
	a=new char[strlen(toSaveHost)+1];
	a[strlen(toSaveHost)]=0;
	for(unsigned i=0;i<strlen(toSaveHost);i++)
	   a[i]=toSaveHost[i];
	b=strlen(a);
	f.write((char*)&b,sizeof(unsigned));
	f.write((char*)a,b);
	f.write((char*)&toSavePortWeb,sizeof(unsigned));
	
	f.write((char*)&idioma,sizeof(Language));
	f.close();
	DestruirVariablesGlobales();
}
void ESE_CRT::cargarInitDatos(){
	fstream f;
	f.open("ESE_CRT.onrn",ios::in|ios::binary);
	if(f.is_open())
	{
	   f.read((char*)&ModoSonido,sizeof(bool));
	   f.read((char*)&ModoLogger,sizeof(bool));
	   f.read((char*)&movRatXinit,sizeof(int));
	   f.read((char*)&movRatYinit,sizeof(int));
	   f.read((char*)&movRatX,sizeof(int));
	   f.read((char*)&movRatY,sizeof(int));
	   f.read((char*)&movESE_CRTZ,sizeof(int));
	   f.read((char*)&DataESE[0],sizeof(GLfloat));
	   f.read((char*)&DataESE[1],sizeof(GLfloat));
	   f.read((char*)&DataESE[2],sizeof(GLfloat));
	   //f.read((char*)&DataESE[3],sizeof(GLfloat));
	   //f.read((char*)&DataESE[4],sizeof(GLfloat));
	   //f.read((char*)&DataESE[5],sizeof(GLfloat));
	   f.read((char*)&movWheel,sizeof(GLdouble));
	   f.read((char*)&trasladarX,sizeof(double));
	   f.read((char*)&trasladarY,sizeof(double));
	   f.read((char*)&trasladarZ,sizeof(double));
	   char*a=new char[1024];
	   unsigned b=0,c=0;
	   char*d=new char[1024];
	   unsigned e=0,g=0;
	   char*h=new char[1024];
	   unsigned ii,jj;
	   f.read((char*)&b,sizeof(unsigned));
	   f.read(a,b);
	   a[b]=0;
	   f.read((char*)&c,sizeof(unsigned));

	   f.read((char*)&e,sizeof(unsigned));
	   f.read(d,e);
	   d[e]=0;
	    f.read((char*)&g,sizeof(unsigned));

	   f.read((char*)&ii,sizeof(unsigned));
	   f.read(h,ii);
	   h[ii]=0;
	    f.read((char*)&jj,sizeof(unsigned));
		toSaveCOM=new char[strlen(a)+1];
		toSaveCOM[strlen(a)]=0;
		for(unsigned i=0;i<strlen(a);i++)
			toSaveCOM[i]=a[i];
		toSaveSpeed=c;
		toSaveIp=new char[strlen(d)+1];
		toSaveIp[strlen(d)]=0;
		for(unsigned i=0;i<strlen(d);i++)
			toSaveIp[i]=d[i];
		toSavePort=g;

		toSaveHost=new char[strlen(h)+1];
		toSaveHost[strlen(h)]=0;
		for(unsigned i=0;i<strlen(h);i++)
			toSaveHost[i]=h[i];
		toSavePortWeb=jj;
		delete[]a;
		delete[]d;
		delete[]h;
	    DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		f.read((char*)&idioma,sizeof(Language));
		//f.read((char*)&Connecttype,sizeof(ConnectionType));
	    f.close();
		SetAnglesREdirecc();
	}
	else
	{
		char*newdata=new char[strlen(toSaveCOM)+1];
		newdata[strlen(toSaveCOM)]=0;
			for(unsigned i=0;i<strlen(toSaveCOM);i++)
				newdata[i]=toSaveCOM[i];
			toSaveCOM=newdata; 

		newdata=new char[strlen(toSaveIp)+1];
		newdata[strlen(toSaveIp)]=0;
		for(unsigned i=0;i<strlen(toSaveIp);i++)
			newdata[i]=toSaveIp[i];
		toSaveIp=newdata; 

		newdata=new char[strlen(toSaveHost)+1];
		newdata[strlen(toSaveHost)]=0;
		for(unsigned i=0;i<strlen(toSaveHost);i++)
			newdata[i]=toSaveHost[i];
		toSaveHost=newdata; 

		SpecialKeys(GLUT_KEY_F4,0,0);
	}
	
	}
//char* ESE_CRT::VerificacionDatos(char*cc,unsigned&strleN){
//		unsigned RealStrleN=strleN;
//		bool adjunt=false;
//		if(bytBool)
//		{
//			if(strleN%2==0)
//				adjunt=true;
//			if(ModoLogger)
//			{
//				cout<<"Se ha adjuntado {";
//				DataProcessor::printByte(byt,false);
//				printf("} a {");
//				DataProcessor::printByte(cc[0],false);
//				printf("}\n");
//			}
//			char*newc=new char[strleN+2];
//			newc[strleN+1]=0;
//			newc[0]=byt;
//			newc[1]=cc[0];
//			for(unsigned i=1;i<strleN;i++)
//				newc[i+1]=cc[i];
//			delete[]cc;
//			cc=newc;
//			strleN=strlen(cc);
//			bytBool=false;
//		}
//		//if(!DataProcessor::ExistMensage59(cc))
//		if((strleN)%2!=0)
//		{
//			if(!bytBool)
//			{
//				if(ModoLogger)
//				{
//					cout<<"Cuidado,ha llegado "<<RealStrleN<<" bytes"<<(adjunt?"(+1)porque se ha adjuntado un elemento q estaba en espera,":",")<<"{";
//					DataProcessor::printByte(cc[strleN-1],false);
//					printf("}=>esperando a adjuntarse\n");
//				}	
//				adjunt=false;
//				byt=cc[strleN-1];
//				cc[strleN-1]=0;
//				strleN=strlen(cc);
//				bytBool=true;
//			}
//		}
//		return cc;
//}
bool ESE_CRT::VerificacionSeguridad(char c)
{
	if(contt%10==0&&!EsperandoReedireccionar)///////////VERIFICACION//////////
	{
		if(DataProcessor::CodigoSeguridad(c))
		{
			if(ModoLogger)cout<<Frases(53)<<endl;
			return true;
		}
		if(ModoLogger)cout<<Frases(55)<<endl;
		ManejadorMensajes->Add(Frases(55),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,20,1,0,0,2);
		
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->AddNewText(Frases(115));
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->SetColor(1,1,0);
		//ManejadorForms->GetForm("labelReferenaciar",ManejadorForms)->AddNewText(Frases(115));
		//ManejadorForms->GetForm("labelReferenaciar",ManejadorForms)->SetColor(1,1,0);
		
		EsperandoReedireccionar=true;
		if(ModoSonido)sonidos(1);
		return true;
	}
	if(!EsperandoReedireccionar&&DataProcessor::CodigoSeguridad(c))	///////////VERIFICACION//////////
	{
		if(ModoLogger)cout<<Frases(54)<<endl;
		ManejadorMensajes->Add(Frases(54),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,20,1,0,0,2);
		
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->AddNewText(Frases(115));
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->SetColor(1,1,0);
		EsperandoReedireccionar=true;
		if(ModoSonido)sonidos(1);
		return true;
	}
	return false;
}
bool ESE_CRT::CodigoCliente(char c,bool&pintar)
{
	if(ModoLogger)cout<<Frases(56)<<(unsigned)c;
	switch (c)
	{
	case 11:////////////////////Pintar/////////////////////////
		pintar=true;
	case 7: ////////////////////REDIRECCIONAR//////////////////
		SpecialKeys(-1,0,0);
		ManejadorMensajes->Add(Frases(51),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,2,0,1,0,2);
		EsperandoReedireccionar=false;
		
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->AddNewText(Frases(114));
		ManejadorForms->GetForm("ESE_CRTContainer",ManejadorForms)->ContainerGetForms("labelReferenaciar")->SetColor(0,1,0);
		
		if(ModoLogger)cout<<Frases(57);
		if(ModoSonido)sonidos(3);
		 DataProcessor::CalcularCoordenadas(cooRd(),DataESE);
		ShowAngules();
		
		ManejadorSketchs->ActualizaLastCood(cooRd(),ManejadorSketchs); 
		if(interfaz==-5)
			ManejadorSketchs->ActualizaNewPlanoToCreate(cooRd(),ManejadorSketchs,deFult);
		
		contt=0;
		if(PlanoAcceso)
		{
			PlanoAcceso=false;
			
			ManejadorSketchs->Sub("PlanoAcceso",ManejadorSketchs);
			ManejadorSketchs->SetDraw(false,ManejadorSketchs);
			
		}
		return true;				
	default:
		if(ModoLogger)cout<<Frases(63);
	break;
	}
	return false;
}
//void ESE_CRT::Acceso(bool acceso)
//{
//	if(interfaz)
//		ManejadorForms->Add(Interfaz(0),ManejadorForms);
//	if(acceso)
//		default_menu(-5);
//	else
//		default_menu(-6);
//}
//bool ESE_CRT::ChekEntada(char*c,unsigned&i)
//{
//	if(c[i]==(char)63)/////////////////QUITAR BOCETO//////////////
//	{
//		if(PlanoAcceso)
//		{
//			if(ModoLogger)cout<<Frases(116)<<endl;
//			PlanoAcceso=false;
//			
//			ManejadorSketchs->Sub("PlanoAcceso",ManejadorSketchs);
//			ManejadorSketchs->SetDraw(false,ManejadorSketchs);
//			
//		}
//	}
//	else if(c[i]==(char)59)/////////////////ADD BOCETO//////////////////
//	{
//		if(ModoLogger)cout<<Frases(117)<<endl;
//		string data(c);
//		DataUnion du;
//		unsigned uns;
//		CRD crd[3];
//		CRD*crd1=new CRD[1];
//		if(i+1>data.length())
//		{
//			return false;
//		}
//		data=data.substr(i+1,data.length()-1);
//		du.SetStrCodif(data.c_str());
//		uns=du.u.Unsigned;
//		i+=uns+du.lengthDescodif-2;
//		if(uns>data.length())
//			return false;
//		data=data.substr(du.lengthDescodif,data.length()-1);
//
//		if(PlanoAcceso)
//		{
//			
//			ManejadorSketchs->Sub("PlanoAcceso",ManejadorSketchs);
//			
//		}
//		for(unsigned ii=0;ii<3;ii++)
//		{
//			du.SetStrCodif(data.c_str());
//			crd[ii].x=du.u.Double;
//			data=data.substr(du.lengthDescodif,data.length()-1);
//			du.SetStrCodif(data.c_str());
//			crd[ii].y=du.u.Double;
//			data=data.substr(du.lengthDescodif,data.length()-1);
//			du.SetStrCodif(data.c_str());
//			crd[ii].z=du.u.Double;
//			data=data.substr(du.lengthDescodif,data.length()-1);
//		}
//		TypePlano t=(TypePlano)(unsigned)(char)(data[0]-1);
//		data=data.substr(1,data.length()-1);
//		bool pintPlano=(data[0]-1)?true:false;
//		data=data.substr(1,data.length()-1);
//		ItemsType it=(ItemsType)(unsigned)(char)(data[0]-1);
//		data=data.substr(1,data.length()-1);
//		du.SetStrCodif(data.c_str());
//		uns=du.u.Unsigned;
//		data=data.substr(du.lengthDescodif,data.length()-1);
//		if(uns)
//		{
//			delete[]crd1;
//			crd1=new CRD[uns];
//			for(unsigned ii=0;ii<uns;ii++)
//			{
//				du.SetStrCodif(data.c_str());
//				crd1[ii].x=du.u.Double;
//				data=data.substr(du.lengthDescodif,data.length()-1);
//				du.SetStrCodif(data.c_str());
//				crd1[ii].y=du.u.Double;
//				data=data.substr(du.lengthDescodif,data.length()-1);
//				du.SetStrCodif(data.c_str());
//				crd1[ii].z=du.u.Double;
//				data=data.substr(du.lengthDescodif,data.length()-1);
//			}
//		}
//		Plano*pl=new Plano("PlanoAcceso",crd[1],crd[2],crd[0],t);
//		pl->items->t=it;
//		ManejadorSketchs->Add(pl,ManejadorSketchs);
//		for(unsigned ii=0;ii<uns;ii++)
//		{
//			ManejadorSketchs->bocetos[ManejadorSketchs->contB-1]->items->Add(crd1[ii]);
//		}
//		PlanoAcceso=true;
//		ManejadorSketchs->bocetos[ManejadorSketchs->contB-1]->pintarPlano=true;
//		ManejadorSketchs->SetDraw(true,ManejadorSketchs);
//		ManejadorSketchs->SetDrawAll(false,ManejadorSketchs);
//		ManejadorSketchs->PlanoCheckeeado=ManejadorSketchs->contB-1;
//		ManejadorSketchs->BocetoActual(ManejadorSketchs)->pintarPlano=pintPlano;
//		
//		return true;
//	}
//	else if(c[i]==(char)67)/////////////////DRAW POINTS//////////////////
//	{
//		if(ModoLogger)cout<<Frases(118)<<endl;
//		
//		Plano::ActualizaItem(ItemsType::POINTSS,ManejadorSketchs->BocetoActual(ManejadorSketchs));
//		
//	}
//	else if(c[i]==(char)71)/////////////////DRAW LINES//////////////////
//	{
//		if(ModoLogger)cout<<Frases(119)<<endl;
//		
//		Plano::ActualizaItem(ItemsType::LINES,ManejadorSketchs->BocetoActual(ManejadorSketchs));
//		
//	}
//	else if(c[i]==(char)75)/////////////////DRAW STRPLINES//////////////////
//	{
//		if(ModoLogger)cout<<Frases(120)<<endl;
//		
//		Plano::ActualizaItem(ItemsType::LINE_STRIP,ManejadorSketchs->BocetoActual(ManejadorSketchs));
//		
//	}
//	else if(c[i]==(char)79)/////////////////DRAW SPLINES//////////////////
//	{
//		if(ModoLogger)cout<<Frases(121)<<endl;
//		
//		Plano::ActualizaItem(ItemsType::SPLINE,ManejadorSketchs->BocetoActual(ManejadorSketchs));
//		
//	}
//	else if(c[i]==(char)83)/////////////////DRAW BSPLINES//////////////////
//	{
//		if(ModoLogger)cout<<Frases(122)<<endl;
//		
//		Plano::ActualizaItem(ItemsType::BSPLINE,ManejadorSketchs->BocetoActual(ManejadorSketchs));
//		
//	}
//	else if(c[i]==(char)87)/////////////////CANCEL POINT//////////////////
//	{
//		if(ModoLogger)cout<<Frases(123)<<endl;
//		
//		Plano::CancelLastPoint(ManejadorSketchs->BocetoActual(ManejadorSketchs));
//		if(ModoSonido)sonidos(6);
//		
//	}
//	else if(c[i]==(char)91)/////////////////MOSTRAR PLANO//////////////////
//	{
//		if(ModoLogger)cout<<Frases(124)<<endl;
//		
//		ManejadorSketchs->Pintar_NoPintar_LineaSuspensiva(true,ManejadorSketchs);
//		ManejadorSketchs->BocetoActual(ManejadorSketchs)->pintarPlano=true;
//		
//	}
//	else if(c[i]==(char)95)/////////////////NO MOSTRAR PLANO//////////////////
//	{
//		if(ModoLogger)cout<<Frases(125)<<endl;
//		
//		ManejadorSketchs->Pintar_NoPintar_LineaSuspensiva(true,ManejadorSketchs);
//		ManejadorSketchs->BocetoActual(ManejadorSketchs)->pintarPlano=false;
//		
//	}
//	return false;
//};

bool ESE_CRT::SetAnglesREdirecc()
{
	fstream f;
    f.open("ESE_CRT.oninit",ios::in);
	contAngleRedirecc=0;
    char c[100];
    if(f.is_open())
    {
		while(!f.eof())
		{
	        f.getline(c,100);
			if(c[0]=='%')
			{
				string angle(c);
				angle=angle.substr(1,angle.find_first_of(" "));
				anglesRedirecc[contAngleRedirecc++]=(double)atof((char*)angle.c_str());
				if(contAngleRedirecc==3)
					return true;
			}
		}
	 }
	return false;
	
	 
}
/////////////////////////THREADS//////////////////////////////////////////////////
void ESE_CRT::ThreadCOM()
{
	while(recibir_serie)
 	 recivirDatosCOM();
}
void ESE_CRT::ThreadCargObject()
{
	ManejadorObject->pushByTxt("ESE_CRT.oninit",ManejadorObject);//cargo el txt con las direcciones de los .obj
	CargObjct=true;
	ManejadorObject->Salir=true;
	if(ManejadorObject->errorCarga)
	{
		if(ModoSonido)sonidos(10);
		ManejadorMensajes->Add(Frases(82),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,1,1,0,0,2);
	}
	else
	{
		if(ModoSonido)sonidos(2);
		ManejadorMensajes->Add(Frases(400),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,1,0,1,0,2);
	}
}






				













