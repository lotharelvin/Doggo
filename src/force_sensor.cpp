#include "ChRt.h"
#include "Arduino.h"
#include "globals.h"
#include "config.h"
#include "force_sensor.h"
#include <queue>

THD_WORKING_AREA(waForcesensorThread,2048);

THD_FUNCTION(ForcesensorThread,arg){
	(void)arg;
    
    while(true){
        FS0S.TransferToForce(Fsensor0pin);
        FS1S.TransferToForce(Fsensor1pin);
        FS2S.TransferToForce(Fsensor2pin);
        FS3S.TransferToForce(Fsensor3pin);
        
        FS0S.InsertIntoQueue();
        FS1S.InsertIntoQueue();
        FS2S.InsertIntoQueue();
        FS3S.InsertIntoQueue();
        
        if(SensorDebug){
            FS0S.PrintRevisement();
            FS1S.PrintRevisement();
            FS2S.PrintRevisement();
            FS3S.PrintRevisement();
            Serial<<"\n";
        }
        chThdSleepMicroseconds(1000000/FSensor_FREQ);
    }

}

ForceSensor:: ForceSensor(){
    std::queue<float> Q;
    Force_vertical=0.00;
    Ydirect_revisement=0.00;
    AvgForce=0.00;
    TempForce=0.00;
}

void ForceSensor:: InsertIntoQueue() {
    if(Q.size()<6){
        //less than 5 elements in Queue
        Q.push(TempForce);
        AvgForce+=(float)TempForce/5;
    }
    else{
        //there are 5 elements in Q
        Q.push(TempForce);
        AvgForce+=(float)TempForce/5;

        TempForce=Q.front();
        Q.pop();
        AvgForce-=(float)TempForce/5;
    }
    Ydirect_revisement=AvgForce*FSensorparams.K;
    
}


void ForceSensor:: TransferToForce(int pin) {
	//The arduino analogread() return a number between 0-1023 we converit to 0.3.3V to get the force accodrindly
	float raw=analogRead(pin);
	float weight=(((raw/1024)*3.3)*6000-0.1)/3.2;//counts by gram
	float force=(float)(weight/1000)*9.8;
    TempForce=force>0?force:0;

}

float ForceSensor:: GetAvgForce() const{
    return AvgForce;
}

float ForceSensor:: GetYdirect_revisement()const{
    return Ydirect_revisement;
}

void ForceSensor:: PrintRevisement() const{
    Serial<<"Y revisement "<<Ydirect_revisement<<"\t";
}
