#include "Arduino.h"
#include "photoresistor.h"



//photoresistor::photoresistor(){}

photoresistor::photoresistor(){
    #define LLM 56
    #define LM 57
    #define MM 58
    #define RM 59
    #define RRM 60
}

void photoresistor::printLight(){
  int lightLL=analogRead(LLM);  
  int lightL=analogRead(LM);  
  int lightM=analogRead(MM);  
  int lightR=analogRead(RM);  
  int lightRR=analogRead(RRM);  
  Serial.print(lightLL);
  Serial.print(lightL);
  Serial.print(lightM);
  Serial.print(lightR);
  Serial.print(lightRR);
  Serial.print("\n");
}

//photoresistor myPhotoresistor;