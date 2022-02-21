
  #define DisplaySerial Serial




#include "Picaso_Serial_4DLib.h"
#include "BigDemo.h" 
#include "Picaso_Const4D.h"

Picaso_Serial_4DLib Display(&DisplaySerial);

void setup() {
  Display.TimeLimit4D   = 50 ;
  DisplaySerial.begin(9600) ;
  
 Display.gfx_Cls(); 
 Display.gfx_BGcolour(WHITE) ;
 Display.gfx_ScreenMode(PORTRAIT);  
   int i ;
  int k ;
  int l ;
  k = 120 ;
  l = 120 ;
  word orbitx ;
  word orbity ;
  Display.gfx_MoveTo(k, l);
  Display.gfx_CircleFilled(k,l,5,WHITE) ;
  i = -90;   // 12 o'clock position  
 Display.gfx_Cls(); 
 Display.gfx_BGcolour(WHITE) ;
 Display.gfx_ScreenMode(PORTRAIT);  

 for(i=0;i<360;i++)
{
  Display.gfx_Orbit(i, 117, &orbitx, &orbity);
   k = 5;
   Display.gfx_CircleFilled(orbitx , orbity, k, RED);
}
for(i=0;i<360;i--)
{
  Display.gfx_Orbit(i, 117, &orbitx, &orbity);
   k = 5;
   Display.gfx_CircleFilled(orbitx , orbity, k, WHITE);
}

}
  
void loop(void)
{
  
delay(50);

 
}

