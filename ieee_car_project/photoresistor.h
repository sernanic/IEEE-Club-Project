#ifndef photoresistor_h
#define  photoresistor_h
#include <Arduino.h>
class photoresistor
{
    public:
    photoresistor();
    void getLight();
    void printLight();
};
//extern photoresistor photoresistor;
#endif