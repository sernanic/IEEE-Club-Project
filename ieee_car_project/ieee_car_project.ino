#include <SparkFun_TB6612.h> //This libary is from https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library

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

//Declare all motors accordingly
Motor motor1 = Motor(AIN1, AIN2, PWM, offset, STBY);
Motor motor2 = Motor(DIN1, DIN2, PWM, offset, STBY);
Motor motor3 = Motor(CIN1, CIN2, PWM, offset, STBY);
Motor motor4 = Motor(BIN1, BIN2, PWM, offset, STBY);

//These are the states
const int TERMINATE = 0;
const int RIGHT = 1;
const int LEFT = 2;

//Start with a right direction
int changeDirection = RIGHT;

//Interval for each state
const long interval = 5000;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
}

/*The simultaneous_motors function make all motors 
work cohesively and simultaneously*/
void simultaneous_motors(int direction1, int direction2, int direction3, int direction4) {
  motor1.drive(255 * direction1);
  motor2.drive(255 * direction2);
  motor3.drive(255 * direction3);
  motor4.drive(255 * direction4);
}

/* The STOP function, as the name implies,
 simultaneously halts all motors*/
void STOP() {
  brake(motor1, motor2);
  brake(motor3, motor4);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {

    // save the last time
    previousMillis = currentMillis;

    if (changeDirection == RIGHT) {
      
      //Run right
      simultaneous_motors(-1, -1, 1, 1);
      changeDirection = LEFT;
    }
    else if (changeDirection == LEFT)
    {
      //Run left
      simultaneous_motors(1, 1, -1, -1);
      changeDirection = TERMINATE;
    }
    else {
      STOP();
      changeDirection = RIGHT;
    }
  }
}
