#include "ChRt.h"
#include "Arduino.h"
#include "globals.h"
#include "config.h"
#include "force_sensor.h"


THD_WORKING_AREA(waForcesensorThread,2048);

THD_FUNCTION(ForcesensorThread,arg){
	(void)arg;
    
    while(true){
  
        chThdSleepMicroseconds(1000000/FSensor_FREQ);
    }

}


void ForceSensor:: InsertIntoQueue() const {
    if(Q.size()<6){
        //less than 5 elements in Queue
        Q.push(TempForce);
        AvgForce+=TempForce;
    }
    else{
        //there are 5 elements in Q
        Q.push(TempForce);
        AvgForce+=TempForce;

        TempForce=Q.front();
        Q.pop();
        AvgForce-=TempForce;
    }
}


void ForceSensor:: TransferToForce(int pin) const{
	//The arduino analogread() return a number between 0-1023 we converit to 0.3.3V to get the force accodrindly
	float raw=analogRead(pin);
	float weight=(((raw/1024)*3.3)*6000-0.1)/3.2;//counts by gram
	float force=(float)(weight/1000)*9.8;
    TempForce=force>0?force:0;

}


