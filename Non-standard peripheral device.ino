#include "IRremote.h"
#define PIN_IN1 4 
 #define PIN_IN2 5 
 #define PIN_ENA 6
 uint8_t power = 1;
 
IRrecv irrecv(2); 
decode_results results;

#define PIN_LED 13
#define PIN_PHOTO_SENSOR A1

int flag=0;

void setup()
{
  pinMode(PIN_ENA, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);

  Serial.begin(9600); 
  irrecv.enableIRIn();
}
 
void loop() {
   if (Serial.available()>0){
    if(Serial.read()!=48) flag=1;
    else flag=0;
   }
   //Serial.println(flag);
   if (flag==1)
   {
   if (irrecv.decode(&results)) 
  { 
    int res = results.value;
    //Serial.println(res, HEX);
    if (res==0xFF and flag==1)
    {
      int val = analogRead(PIN_PHOTO_SENSOR);
      //Serial.println(val);
      if (val < 300) {
        Serial.println("Left");
        analogWrite(PIN_ENA, power);
        digitalWrite(PIN_IN1, HIGH);
        digitalWrite(PIN_IN2, LOW);
        
      }
      else if (val > 300)
      {
        Serial.println("Right");
        analogWrite(PIN_ENA, power);
        digitalWrite(PIN_IN1, LOW);
        digitalWrite(PIN_IN2, HIGH);
      }   
    }
    else if (res==0x20DF)
    {
      //Serial.println(results.value, HEX);
      digitalWrite(PIN_IN1, LOW);
      digitalWrite(PIN_IN2, LOW);
    }
     irrecv.resume();
}
}
else if (flag==0){
   //Serial.println(results.value, HEX);
      digitalWrite(PIN_IN1, LOW);
      digitalWrite(PIN_IN2, LOW);
}
}
