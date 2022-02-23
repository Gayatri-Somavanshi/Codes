#include<TimerOne.h>
#include <Encoder.h>
#define PWM_PIN 9 
#define PWM_START 1 
Encoder myEnc(5, 6);
int pwm = 0;

void setup(void)
{
   Timer1.initialize(40); // 40 us = 25 kHz
   Serial.begin(9600);
   Timer1.pwm(9, 0);  
   pwm=PWM_START;    // setup pwm on pin 9, 0% duty cycle
    // attaches callback() as a timer overflow interrup               
}
long oldPosition  = 0;

void loop(void)
{
  long newPosition=myEnc.read();
  if(newPosition != oldPosition){
   
    if(newPosition < 500 && newPosition>0){
     int newp=(newPosition*4);
      Timer1.pwm ( PWM_PIN , newp);
      
    }      
      delay(50);
      oldPosition=newPosition;
      Serial.println(newPosition);
   }
   

}
 
  



 


