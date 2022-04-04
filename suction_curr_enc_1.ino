 #include<TimerOne.h>
#include <Encoder.h>
#include <Wire.h>
#include "hsc_ssc_i2c.h"

#define PWM_PIN 9 
#define PWM_START 1 
#define SLAVE_ADDR 0x28
#define OUTPUT_MIN 0x666        // 10%
#define OUTPUT_MAX 0x399A       // 90% of 2^14 - 1
#define PRESSURE_MIN 0.0        // min is 0 for sensors that give absolute values
#define PRESSURE_MAX 15   // 30psi (and we want results in pascals)


int analogPin = 3;     // potentiometer wiper (middle terminal) connected to analog pin 3

Encoder myEnc(2, 3);
int pwm = 0;

                       
int val = 0;           // variable to store the value read

float voltage=0;

float average=0;

float pressure=0;

int count=0;

int flg=0;

int high_state=0;

int pwm_flg=0;

uint32_t prev = 0; 

int newp=0;

const uint32_t interval = 5000;


void setup()

{
  Timer1.initialize(40); // 40 us = 25 kHz
  Serial.begin(9600);  
  pinMode(13, OUTPUT);  //  setup serial
  Timer1.pwm(9, 0);  
  pwm=PWM_START;
  Wire.begin();
}


long oldPosition  =0;

void loop()

{
    unsigned long now = millis();
    struct cs_raw ps;
    char p_str[10], t_str[10];
    uint8_t el;
    float p, t;

    long newPosition=myEnc.read();
  if(newPosition != oldPosition){
   
    if(newPosition < 250 && newPosition>0){
      newp=(newPosition*12);
     Timer1.pwm ( PWM_PIN , newp);
    // Serial.println("PWM Value=");
    // Serial.println(newp);
     
    // if (pwm_flg==0)
    //  {Timer1.pwm ( PWM_PIN , newp);
    //   pwm_flg=1;
    //   delay(100);
    //  }
    // else
    //  {Timer1.pwm ( PWM_PIN , 912);
    //   pwm_flg=0;
    //   delay(100);
     // } 
    }      
     // delay(50);
      oldPosition=newPosition;
  }
  
 //------------------------------------------------------------------------
//if (pwm_flg==0)
//   {Timer1.pwm ( PWM_PIN , newp);
//    pwm_flg=1;
//    delay(10);
//   }
//   else
//   {Timer1.pwm ( PWM_PIN , 912);
//    pwm_flg=0;
//    delay(10 );
//   }  
  
//-------------------------------------------------------------------------
 if ((now - prev > interval) && (Serial.available() <= 0)) {
        prev = now;
        el = ps_get_raw(SLAVE_ADDR, &ps);
        if ( el == 4 ) {
            Serial.println("err sensor missing");
        } else {
            if ( el == 3 ) {
               // Serial.print("err diagnostic fault ");
               // Serial.println(ps.status, BIN);
            }
            if ( el == 2 ) {
                // if data has already been feched since the last
                // measurement cycle
              //Serial.print("warn stale data ");
                Serial.println(ps.status, BIN);
            }
            if ( el == 1 ) {
                // chip in command mode
                // no clue how to end up here
              //Serial.print("warn command mode ");
                Serial.println(ps.status, BIN);
            }
            
            ps_convert(ps, &p, &t, OUTPUT_MIN, OUTPUT_MAX, PRESSURE_MIN,
                   PRESSURE_MAX);
            // floats cannot be easily printed out
            dtostrf(p, 2, 2, p_str);
            dtostrf(t, 2, 2, t_str);
           // Serial.print("pressure    (psi) ");
           // Serial.println(p_str);
           // Serial.print("temperature (dC) ");
           // Serial.println(t_str);
           // Serial.println("");
        }
     } 
//-------------------------------------------------------------------------
 //val = analogRead(analogPin);    // read the input pin  
 // voltage=val*5;
 // voltage=voltage/1023;
//voltage=val/100;
  //Serial.println(voltage); 
  average=average+p;
  count=count+1;
  
  if (count==100)
   { 
     
   pressure=average/100;
   average=0;
   count=0;
   Serial.println(pressure);
   if(pressure>15)
     {
       if(high_state!=1)
         {
           Serial.println("OPEN");
          digitalWrite(13, LOW);
         }
        else
         {
           high_state=0;
         }       
     }
      
   else
     {
       Serial.println("BLOCK");
     digitalWrite(13, HIGH);
     high_state=1;
     }   
   }
  }


