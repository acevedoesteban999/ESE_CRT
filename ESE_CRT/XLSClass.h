#pragma once
#include <direct.h>
#include <ostream>
#include "libxl.h"
#include "StackSketchs.h"
#include "DataProcessor.h"
using namespace libxl;
using namespace std;
class XLSClass
{	
public:
	XLSClass(){
	};
	~XLSClass(){};
	static bool Salvar(Plano**Planos,unsigned*elements,unsigned cantElements,bool All=false,unsigned allCont=0)
	{
		Book*book=xlCreateBook();
		if(book)
		{
			Sheet*sheet=book->addSheet("Sheet1");
			if(sheet)
			{
				mkdir("ESE_CRT-XLS");
				for(unsigned i=0;i<cantElements;i++)
				{
					sheet->writeStr(1,0,"X");
					sheet->writeStr(1,1,"Y");
					sheet->writeStr(1,2,"Z");
					unsigned row=2;
					for(unsigned j=0;j<Planos[elements[i]]->items->cont;j++)
					{	
						sheet->writeNum(row,0,Planos[elements[i]]->items->PoIntS[j].x);
						sheet->writeNum(row,1,Planos[elements[i]]->items->PoIntS[j].y);
						sheet->writeNum(row++,2,Planos[elements[i]]->items->PoIntS[j].z);
					}
					
					string s="ESE_CRT-XLS/";
					s+=Planos[elements[i]]->name;
					s+=".xls";
					fstream f;
					bool exist;
					unsigned cont=0;
					do
					{
					f.open((char*)s.c_str(),ios::in);
					exist=f.is_open();
					if(exist)
					{
						s=s.substr(0,s.length()-4-(cont==0?0:cont<10?2:3));
						s+=string("_")+to_string(cont);
						s+=".xls";
						cont++;
					}
					f.close();
					}while (exist);
					book->save((char*)s.c_str());
					book->release();
					book=xlCreateBook();
					sheet=book->addSheet("Sheet1");
					
				}
				if(All)
				{
					sheet->writeStr(1,0,"X");
					sheet->writeStr(1,1,"Y");
					sheet->writeStr(1,2,"Z");
					unsigned row=2;
					for(unsigned i=0;i<allCont;i++)
					{
						for(unsigned j=0;j<Planos[i]->items->cont;j++)
						{	
							sheet->writeNum(row,0,Planos[elements[i]]->items->PoIntS[j].x);
							sheet->writeNum(row,1,Planos[elements[i]]->items->PoIntS[j].y);
							sheet->writeNum(row++,2,Planos[elements[i]]->items->PoIntS[j].z);
						}
					}
					string s="ESE_CRT-XLS/";
					s+="All_Sketchs";
					s+=".xls";
					fstream f;
					bool exist;
					unsigned cont=0;
					do
					{
					f.open((char*)s.c_str(),ios::in);
					exist=f.is_open();
					if(exist)
					{
						s=s.substr(0,s.length()-4-(cont==0?0:cont<10?2:3));
						s+=string("_")+to_string(cont);
						s+=".xls";
						cont++;
					}
					f.close();
					}while (exist);
					

					
					
					
					
					book->save((char*)s.c_str());
				}
				book->release();	
			}
			else
				return false;
		}
		else 
			return false;
		return true;
	};
	static void SalvarGrabar(float GrabarAngles[6],char*bytes,unsigned GrabarCont,double AnglulesRediredireccionarGrabar[6])
	{
		Book*book=xlCreateBook();
		if(book)
		{
			Sheet*sheet=book->addSheet("Sheet1");
			if(sheet)
			{
					mkdir("ESE_CRT-XLS");
					sheet->writeStr(1,0,"Higt Byte");
					sheet->writeStr(1,1,"Low Byte");
					sheet->writeStr(1,2,"X");
					sheet->writeStr(1,3,"Y");
					sheet->writeStr(1,4,"Z");
					
					sheet->writeStr(1,5,"Q1");
					sheet->writeStr(1,6,"Q2");
					sheet->writeStr(1,7,"Q3");
					sheet->writeStr(1,8,"Q4");
					sheet->writeStr(1,9,"Q5");
					sheet->writeStr(1,10,"Q6");


					sheet->writeStr(2,0," ");
					sheet->writeStr(2,1," ");
					sheet->writeNum(2,5,GrabarAngles[0]);
					sheet->writeNum(2,6,GrabarAngles[1]);
					sheet->writeNum(2,7,GrabarAngles[2]);
					sheet->writeNum(2,8,GrabarAngles[3]);
					sheet->writeNum(2,9,GrabarAngles[4]);
					sheet->writeNum(2,10,GrabarAngles[5]);
					unsigned row=3;
					CRD crd;
					for(unsigned j=0;j<GrabarCont;j++)
					{	
						if(!DataProcessor::CodigoCliente(bytes[j])&&!DataProcessor::CodigoSeguridad(bytes[j]))
						{
							DataProcessor::PorcesarDatos(bytes[j],GrabarAngles,(GLfloat)1);
						}
						else if(bytes[j]==7)
						{
							GrabarAngles[0]=(float)AnglulesRediredireccionarGrabar[0];
							GrabarAngles[1]=(float)AnglulesRediredireccionarGrabar[1];
							GrabarAngles[2]=(float)AnglulesRediredireccionarGrabar[2];
							//GrabarAngles[3]=(float)AnglulesRediredireccionarGrabar[3];
							//GrabarAngles[4]=(float)AnglulesRediredireccionarGrabar[4];
							//GrabarAngles[5]=(float)AnglulesRediredireccionarGrabar[5];
						}
						DataProcessor::CalcularCoordenadas(crd,GrabarAngles);
						char*f=DataProcessor::GetByteStr(bytes[j+1]);
						sheet->writeStr(row,0,f);
						delete[]f;
						f=DataProcessor::GetByteStr(bytes[j]);
						sheet->writeStr(row,1,f);
						delete[]f;
						
						sheet->writeNum(row,2,crd.x);
						sheet->writeNum(row,3,crd.y);
						sheet->writeNum(row,4,crd.z);
						sheet->writeNum(row,5,GrabarAngles[0]);
						sheet->writeNum(row,6,GrabarAngles[1]);
						sheet->writeNum(row,7,GrabarAngles[2]);
						/*sheet->writeNum(row,8,GrabarAngles[3]);
						sheet->writeNum(row,9,GrabarAngles[4]);
						sheet->writeNum(row++,10,GrabarAngles[5]);*/
					}
					unsigned contttttt=0;
					string s="ESE_CRT-XLS/";
					s+="Grabar";
					s+=".xls";
					fstream f;
					bool exist;
					unsigned cont=0;
					do
					{
						f.open((char*)s.c_str(),ios::in);
						exist=f.is_open();
						if(exist)
						{
							s=s.substr(0,s.length()-4-(contttttt==0?0:contttttt<10?2:3));
							s+=string("_")+to_string(contttttt++);
							s+=".xls";
						}
						f.close();
					}while (exist);
					book->save((char*)s.c_str());
					book->release();
			}
		}
	}

};

