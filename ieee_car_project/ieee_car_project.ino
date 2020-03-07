/* The IR sensor circuit:
 * - Arduino 5V -> Sensor's pin 1 (Vcc)
 * - Arduino GND -> Sensor's pin 2 (GND)
 * - Arduino pin A0 -> Sensor's pin 3 (Output)
*/
#include <SparkFun_TB6612.h> //This libary is from https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library
//#include <SharpIR.h>
#include "photoresistor.h"
#include "motors.h"

#define LIROUT A0
#define RIROUT A1



//Create a new instance of the library, give name infraL(model,sensor output pin)
//SharpIR infraL( 1080, LIROUT );//model(SharpIR::GP2Y0A41SK0F)->"1080"
//SharpIR infraR( 1080, RIROUT );

//These are the states
const int TERMINATE = 0;
const int RIGHT = 1;
const int LEFT = -1;
const int piAr[] = {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,0,2,8,8,4,1,9,7,1,6,9,3,9,9,3,7,5,1,0,5,8,2,0,9,7,4,9,4,4,5,9,2,3,0,7,8,1,6,4,0,6,2,8,6,2,0,8,9,9,8,6,2,8,0,3,4,8,2,5,3,4,2,1,1,7,0,6,7,9,8,2,1,4,8,0,8,6,5,1,3,2,8,2,3,0,6,6,4,7,0,9,3,8,4,4,6,0,9,5,5,0,5,8,2,2,3,1,7,2,5,3,5,9,4,0,8,1,2,8,4,8,1,1,1,7,4,5,0,2,8,4,1,0,2,7,0,1,9,3,8,5,2,1,1,0,5,5,5,9,6,4,4,6,2,2,9,4,8,9,5,4,9,3,0,3,8,1,9,6,4,4,2,8,8,1,0,9,7,5,6,6,5,9,3,3,4,4,6,1,2,8,4,7,5,6,4,8,2,3,3,7,8,6,7,8,3,1,6,5,2,7,1,2,0,1,9,0,9,1,4,5,6,4,8,5,6,6,9,2,3,4,6,0,3,4,8,6,1,0,4,5,4,3,2,6,6,4,8,2,1,3,3,9,3,6,0,7,2,6,0,2,4,9,1,4,1,2,7,3,7,2,4,5,8,7,0,0,6,6,0,6,3,1,5,5,8,8,1,7,4,8,8,1,5,2,0,9,2,0,9,6,2,8,2,9,2,5,4,0,9,1,7,1,5,3,6,4,3,6,7,8,9,2,5,9,0,3,6,0,0,1,1,3,3,0,5,3,0,5,4,8,8,2,0,4,6,6,5,2,1,3,8,4,1,4,6,9,5,1,9,4,1,5,1,1,6,0,9,4,3,3,0,5,7,2,7,0,3,6,5,7,5,9,5,9,1,9,5,3,0,9,2,1,8,6,1,1,7,3,8,1,9,3,2,6,1,1,7,9,3,1,0,5,1,1,8,5,4,8,0,7,4,4,6,2,3,7,9,9,6,2,7,4,9,5,6,7,3,5,1,8,8,5,7,5,2,7,2,4,8,9,1,2,2,7,9,3,8,1,8,3,0,1,1,9,4,9,1,2,9,8,3,3,6,7,3,3,6,2,4,4,0,6,5,6,6,4,3,0,8,6,0,2,1,3,9,4,9,4,6,3,9,5,2,2,4,7,3,7,1,9,0,7,0,2,1,7,9,8,6,0,9,4,3,7,0,2,7,7,0,5,3,9,2,1,7,1,7,6,2,9,3,1,7,6,7,5,2,3,8,4,6,7,4,8,1,8,4,6,7,6,6,9,4,0,5,1,3,2,0,0,0,5,6,8,1,2,7,1,4,5,2,6,3,5,6,0,8,2};

//########################################piAr is 621 digits of pi##########################
//Start with a right direction
int changeDirection = RIGHT;
int lightLL=0;
int lightL=0;
int lightM=0;
int lightR=0;
int lightRR=0;
int i,j=0;//currPi and prevPi
int currPi,prevPi = piAr [0];


//Interval for each state
const long interval = 500;//Milliseconds
unsigned long previousMillis = 0;



// difference between left and right IR
/*int getIR(){
  int distL = infraL.getDistance();
  int distR = infraR.getDistance();
  return distL - distR;
  /*Positive -> Left side is closer to wall
    Negative -> Right side is closer to wall
    Correct with motors 3/4 spinning and motors 1/2 inactive 
}
*/



void setup() {
  Serial.begin(9600);
  photoresistor photoResistor;
  MOTORS Motors;
}

void loop() {
  photoResistor.printLight();
  if(i==j){//#run initial motor command
    Serial.print("initial");
    Serial.print("\n");
    j--;  
  }
  else if(currPi==prevPi){//#run duplicate number motor command
    Serial.print("duplicate");
    Serial.print("\n");
    Serial.print(i);
    Serial.print("\n");
  }
  else if(i>(sizeof(piAr)/sizeof(int))){//stops after reaching end of array of digits, spam wrong button????
    return;
  }
    else if(currPi>prevPi){//#make robot go right
    changeDirection=RIGHT;
    //Serial.print(changeDirection,"\n");
  }
  else{//#make robot go left
    changeDirection=LEFT;
    //Serial.print(changeDirection,"\n");
  }
  i++;
  j++;
  currPi=piAr[i];
  prevPi=piAr[j];
}
/*
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
*/
