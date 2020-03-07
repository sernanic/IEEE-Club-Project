#include "Arduino.h"
#include "motors.h"
#include "MOTORS.h"
#include <SparkFun_TB6612.h> 
MOTORS::MOTORS(){
   
    //Declare all motors accordingly
   
}

/* The STOP function, as the name implies,
 simultaneously halts all motors*/
void MOTORS::STOP() {
  Motor motor1 = Motor(AIN1, AIN2, PWM, offset, STBY);//motor 1 is different model than other motors
    Motor motor2 = Motor(DIN1, DIN2, PWM, offset, STBY);
    Motor motor3 = Motor(CIN1, CIN2, PWM, offset, STBY);
    Motor motor4 = Motor(BIN1, BIN2, PWM, offset, STBY);
  brake(motor1, motor2);
  brake(motor3, motor4);
}

/*The simultaneous_motors function make all motors 
work cohesively and simultaneously*/
void MOTORS::simultaneous_motors(int direction1, int direction2, int direction3, int direction4) {
   Motor motor1 = Motor(AIN1, AIN2, PWM, offset, STBY);//motor 1 is different model than other motors
    Motor motor2 = Motor(DIN1, DIN2, PWM, offset, STBY);
    Motor motor3 = Motor(CIN1, CIN2, PWM, offset, STBY);
    Motor motor4 = Motor(BIN1, BIN2, PWM, offset, STBY);

  motor1.drive(SPEED * direction1);//.drive(speed, optional duration)
  motor2.drive(SPEED * direction2);
  motor3.drive(SPEED * direction3);
  motor4.drive(SPEED * direction4);
}

//Move motors; dependent to changeDirection and difference in IR
void MOTORS::adjust_motors(int currentDir, int diffIR){
  Motor motor1 = Motor(AIN1, AIN2, PWM, offset, STBY);//motor 1 is different model than other motors
    Motor motor2 = Motor(DIN1, DIN2, PWM, offset, STBY);
    Motor motor3 = Motor(CIN1, CIN2, PWM, offset, STBY);
    Motor motor4 = Motor(BIN1, BIN2, PWM, offset, STBY);
  int duration = 10 * diffIR;
  motor3.drive(SPEED * currentDir, duration);
  motor4.drive(SPEED * currentDir, duration);
}