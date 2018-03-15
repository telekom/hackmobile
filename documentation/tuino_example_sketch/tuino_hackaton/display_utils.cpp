/*
 *  General SeedOled Display Utility functions 
 */

#include "SeeedOLED.h"

 void centerString(char *string )
{
  String tmpString;
  int len,spaces,i;
  
  len = strlen(string);

  spaces = 0;
  if ( len < 16 ) 
    spaces = ( 16 - len ) / 2;

  for (i=0;i<spaces;i++)
    tmpString = tmpString + " ";
    
 tmpString = tmpString + string;
 tmpString.toCharArray(string, 16);
 
}

void splashScreen() {

  char string[16];
  
  SeeedOled.clearDisplay();   

  SeeedOled.setTextXY(0,0);        
  SeeedOled.putString("Austria T-Mobile"); 

  SeeedOled.setTextXY(1,0);  
  sprintf(string," ");
  centerString(string);
  SeeedOled.putString(string);
  SeeedOled.setTextXY(2,0);  
  sprintf(string,"NBIoT Hackaton");
  centerString(string);
  SeeedOled.putString(string);
  

  SeeedOled.setTextXY(5,0);  
  sprintf(string,"NBIoT Demo");
  centerString(string);
  SeeedOled.putString(string);
 }


 void displayTemp(float temp ) {

  SeeedOled.setTextXY(0,0);        
  SeeedOled.putString("Temp: ");
  SeeedOled.putFloat(temp);
 
 }


 void displayTime2TX(long int time_ms) {

  char buf[32];
  int time_sec;

  time_sec = time_ms / 1000;

  sprintf(buf,"Time to TX: %3d",time_sec);
  
  SeeedOled.setTextXY(7,0);    
  SeeedOled.putString(buf); 
  
 }
 void displayTX(bool status) {
  SeeedOled.setTextXY(7,0);    
  if ( status )    
    SeeedOled.putString(" ***NBIoT TX*** "); 
  else
    SeeedOled.putString("                "); 
 }


