#pragma once
#include <ctime>
class TimeDuration
{
public:
	bool tBool;
	float TimE,TimeClock;
	TimeDuration(void)
{
	TimE=0;
	tBool=false;
};
	TimeDuration(bool InitIncrementa){if(InitIncrementa)this->tBool=true;this->TimeClock=(float)clock();};
	TimeDuration(float t){this->tBool=true,this->TimE=t;TimeClock=(float)clock();};
	~TimeDuration(){};
	static float Incrementa(TimeDuration*TimeDurat){
	if(TimeDurat->tBool)
	      {
			  TimeDurat->TimE+=(((float)clock()-TimeDurat->TimeClock)/CLOCKS_PER_SEC);
			  TimeDurat->TimeClock=(float)clock();
			 return (float)TimeDurat->TimE; 
	       }
	 else
		 {
			TimeDurat->TimeClock=(float)clock();
			TimeDurat->tBool=true;
			return 0;
	     }
};
	static bool  Decrementa(TimeDuration*TimeDurat)
{	
	if(TimeDurat->tBool)
	{
		TimeDurat->TimE-=(((float)clock()-TimeDurat->TimeClock)/CLOCKS_PER_SEC);	
			 if(TimeDurat->TimE>0)
			 {
				 TimeDurat->TimeClock=(float)clock();
				return false;
			 }
				TimeDurat->ResetT(TimeDurat);
	
	}
	return true;
};
	static void  InitDecrementa(TimeDuration*TimeDurat,float tiMe){
		TimeDurat->tBool=true;
		TimeDurat->TimE=tiMe;
};
	static void ResetT(TimeDuration*TimeDurat){TimeDurat->TimeClock=0;TimeDurat->tBool=false;TimeDurat->TimE=0;};
	static void ResettIncrementa(TimeDuration*TimeDurat){TimeDurat->TimE=0;};

};

