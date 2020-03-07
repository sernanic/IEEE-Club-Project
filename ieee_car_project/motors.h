
#ifndef motors_h
#define  motors_h
#include <Arduino.h>

class MOTORS
{
    public:
    MOTORS();
    void simultaneous_motors(int direction1, int direction2, int direction3, int direction4);
    void STOP();
    void adjust_motors(int currentDir, int diffIR);
}
#endif
