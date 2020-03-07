#include "Arduino.h"
#include "motors.h"

MOTORS::motors(){
    #define AIN1 5 //For first driver, motors 1 (A) and 4 (B)
    #define AIN2 4
    #define BIN1 7
    #define BIN2 8
    #define CIN1 9 //For second driver, motors 2 (C) and 3 (D)
    #define CIN2 10
    #define DIN1 11
    #define DIN2 12
    #define PWM 6 //this is a common PWM
    #define STBY 13
    int offset = 1;
    #define SPEED 255 //between -255 and 255
    //Declare all motors accordingly
    Motor motor1 = Motor(AIN1, AIN2, PWM, offset, STBY);//motor 1 is different model than other motors
    Motor motor2 = Motor(DIN1, DIN2, PWM, offset, STBY);
    Motor motor3 = Motor(CIN1, CIN2, PWM, offset, STBY);
    Motor motor4 = Motor(BIN1, BIN2, PWM, offset, STBY);

}

/* The STOP function, as the name implies,
 simultaneously halts all motors*/
void MOTORS::STOP() {
  brake(motor1, motor2);
  brake(motor3, motor4);
}

/*The simultaneous_motors function make all motors 
work cohesively and simultaneously*/
void MOTORS::simultaneous_motors(int direction1, int direction2, int direction3, int direction4) {
  motor1.drive(SPEED * direction1);//.drive(speed, optional duration)
  motor2.drive(SPEED * direction2);
  motor3.drive(SPEED * direction3);
  motor4.drive(SPEED * direction4);
}

//Move motors; dependent to changeDirection and difference in IR
void MOTORS::adjust_motors(int currentDir, int diffIR){
  int duration = 10 * diffIR;
  motor3.drive(SPEED * currentDir, duration);
  motor4.drive(SPEED * currentDir, duration);
}
