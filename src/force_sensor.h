#ifndef FORCE_SENSOR_H
#define FORCE_SENSOR_H

#include "config.h"
#include "ChRt.h"
#include "Arduino.h"
#include <queue>

extern THD_WORKING_AREA(waForcesensorThread,2048);
extern THD_FUNCTION(ForcesensorThread,arg);


class ForceSensor{
private:
    std::queue<float> Q;
    float Force_vertical;
    float Ydirect_revisement;
    float AvgForce;
    float TempForce;
public:
    ForceSensor();
    
    void TransferToForce(int pin) ;
    
    void InsertIntoQueue() ;
    
    float GetAvgForce() const;
    
    float GetYdirect_revisement() const;
    
    void PrintRevisement() const;
};


#endif
