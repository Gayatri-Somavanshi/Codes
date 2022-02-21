#include <genieArduino.h>
#include <SSC.h>
#include <Encoder.h>                           
#include <Wire.h>

SSC ssc(0x28, 8);

//Encoder myEnc(5,6);
Genie genie;   

#define RESETLINE 4 

void setup()
{

  Serial.begin(200000);  // Serial0 @ 200000 (200K) Baud
  genie.Begin(Serial);   // Use Serial0 for talking to the Genie Library, and to the 4D Systems display
  Wire.begin();
  
   ssc.setMinRaw(0);
  ssc.setMaxRaw(16383);
  ssc.setMinPressure(0);
  ssc.setMaxPressure(10);
 
  
  genie.AttachEventHandler(myGenieEventHandler);
 
  // Attach the user function Event Handler for processing events
  
  pinMode(RESETLINE, OUTPUT);  // Set D4 on Arduino to Output (4D Arduino Adaptor V2 - Display Reset)
  digitalWrite(RESETLINE, 1);  // Reset the Display via D4
  delay(100);
  digitalWrite(RESETLINE, 0);  // unReset the Display via D4
  delay (3500); 

  genie.WriteContrast(15); // About 2/3 Max Brightness

}

void loop() 
{

    static  int waitPeriod = millis();
    
  Serial.print("update()\t");
  Serial.println(ssc.update());
  
  // print pressure
  Serial.print("pressure()\t");
  Serial.println(ssc.pressure());
  
  // print temperature
  Serial.print("temperature()\t");
  Serial.println(ssc.temperature());
delay(100);
// This calls the library each loop to process the queued responses from the display


  if (millis() >= waitPeriod)
  {
    genie.WriteObject(GENIE_OBJ_COOL_GAUGE, 1,ssc.pressure()); 
    waitPeriod = millis() + 10; // rerun this code to update Cool Gauge and Slider in another 50ms time.

  }

 
 
}

void myGenieEventHandler(void)
{
  genieFrame Event;
  genie.DequeueEvent(&Event); // Remove the next queued event from the buffer, and process it below


  //If the cmd received is from a Reported Object, which occurs if a Read Object (genie.ReadOject) is requested in the main code, reply processed here.
 /* if (Event.reportObject.cmd == GENIE_REPORT_OBJ)
  {
    if (Event.reportObject.object == GENIE_OBJ_USER_LED)              // If the Reported Message was from a User LED
    {
      if (Event.reportObject.index == 0)                              // If UserLed0 (Index = 0)
      {
        bool UserLed0_val = genie.GetEventData(&Event);               // Receive the event data from the UserLed0
        UserLed0_val = !UserLed0_val;                                 // Toggle the state of the User LED Variable
        genie.WriteObject(GENIE_OBJ_USER_LED, 0, UserLed0_val);       // Write UserLed0_val value back to UserLed0
      }
    }
  }
  */

}


