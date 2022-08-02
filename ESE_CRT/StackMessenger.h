#include "MeSSenger.h"

class StackMessenger
{
    private:
        unsigned cont,cant;
        MeSSenger**Messenger;
        mutex m;

    public:
        StackMessenger()
        {
            cont=0;
            cant=10;
			Messenger=new MeSSenger*[cant];
        }
        ~StackMessenger()
        {
            for(unsigned i=0;i<cont;i++)
                delete Messenger[i];
            delete[]Messenger;
        }
		void Add(char*text,position Position,GLfloat wigth,GLfloat height,float Time=3,GLfloat R=1,GLfloat G=1,GLfloat B=1,unsigned BigLV=0,GLfloat x=0,GLfloat y=0,GLfloat z=0)
		{
			MeSSenger*m=new MeSSenger(text,Position,wigth,height,Time,R,G,B,BigLV,x,y,z);
			Add(m);
		}
        void Add(MeSSenger*messenger)
        {
            m.lock();
            if(cont>=cant)
            {
                cant+=10;
                MeSSenger**NewMessenger=new MeSSenger*[cant];
                for(unsigned i=0;i<cont;i++)
                    NewMessenger[i]=Messenger[i];
                delete[]Messenger;
                Messenger=NewMessenger;
            }
            Messenger[cont++]=messenger;
            m.unlock();
        }
        bool Draw()
        {
            if(m.try_lock())
            { 
                for(int i=0;i<(int)cont;i++)
                {
                    //Inicio en 1 el for para el caso que el elemento[0] tenga q ser borrado pueda reiniciar el cont a i=0 con un i--, sino seria 0-- y se iria del rango del unsigned
                    MeSSenger::Drawing_and_Decremt(Messenger[i],i);
                    if(Messenger[i]->Finish)
                    {
                        //SUB
                        delete Messenger[i];
                        for(unsigned ii=i;ii<cont-1;ii++)
                        {
                            Messenger[ii]=Messenger[ii+1];
                        }
						cont--;
						i--;
                    }
                }
				m.unlock();
                if(cont)
                    return true;                    
            }
			return false;
        }
};