#include Arduino.h
#include photoresistor.h



photoresistor:photoresistor(){}

void photoresistor:SETUP(){
    #define LLM 56
    #define LM 57
    #define MM 58
    #define RM 59
    #define RRM 60
}
void photoresistor:getLight(){
  lightLL=analogRead(LLM);  
  lightL=analogRead(LM);  
  lightM=analogRead(MM);  
  lightR=analogRead(RM);  
  lightRR=analogRead(RRM);  
}

void photoresistor:printLight(){
  getLight();
  Serial.print(lightLL);
  Serial.print(lightL);
  Serial.print(lightM);
  Serial.print(lightR);
  Serial.print(lightRR);
  Serial.print("\n");
}

photoresistor photoresistor = photoresistor();