#ifndef GLOBALS_H
#define GLOBALS_H
#include "cppQueue.h"
#include "globals.h"
#include "config.h"
#include "ChRt.h"
#include "Arduino.h"


extern THD_WORKING_AREA(waForcesensorThread,2048);
extern THD_FUNCTION(ForcesensorThread,arg);

class ForceSensor{
private:
    std::queue<float> Q;
    bool Onland=true;
    float Force_vertical=0.00;
    float Ydirect_revisement=0.00;
    float AvgForce=0.00;
    float TempForce=0.00;
public:
    ForceSensor();
    
    void TransferToForece(int pin) const;
    
    void InserIntoQueue() const;
    
    float GetAvgForce() const;
    
    
};

#endif
