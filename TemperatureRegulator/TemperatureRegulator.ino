/*
   -- New project by sechkin remzi --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 2.4.3 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.7.12 or later version;
     - for iOS 1.4.7 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT
#include <ESP8266WiFi.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "RemoteXY"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377
#define REMOTEXY_ACCESS_PASSWORD "1234"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,5,0,29,0,123,1,11,139,0,
  130,1,74,15,25,25,17,68,18,1,
  1,72,39,8,36,135,1,1,75,31,
  11,8,2,31,43,0,1,1,87,31,
  11,8,2,31,45,0,2,1,74,2,
  25,11,2,26,31,31,79,78,0,79,
  70,70,0,65,4,92,41,6,6,65,
  1,92,55,6,6,65,2,92,48,6,
  6,130,1,1,41,60,7,17,129,0,
  19,43,20,4,24,208,152,208,183,208,
  188,208,181,209,128,208,181,208,189,208,
  176,58,0,67,4,41,42,12,5,2,
  26,6,130,1,1,48,60,7,17,67,
  4,41,49,9,5,2,26,6,129,0,
  54,42,6,5,24,194,176,67,0,129,
  0,2,50,38,4,24,208,146,209,128,
  208,181,208,188,208,181,32,208,183,208,
  176,32,208,183,208,176,208,179,209,128,
  208,178,208,176,208,189,208,181,58,0,
  129,0,51,50,9,4,24,208,188,208,
  184,208,189,46,0,130,1,1,55,60,
  7,17,67,4,41,56,9,5,2,26,
  6,129,0,2,57,38,4,24,208,146,
  209,128,208,181,208,188,208,181,32,208,
  189,208,176,32,208,191,209,128,208,190,
  209,134,208,181,209,129,208,176,58,0,
  129,0,51,57,9,4,24,208,188,208,
  184,208,189,46,0,129,0,72,56,19,
  4,24,208,152,208,183,208,186,208,187,
  209,142,209,135,208,181,208,189,0,129,
  0,71,49,20,4,24,208,151,208,176,
  208,179,209,128,208,176,208,178,208,176,
  208,189,208,181,0,129,0,80,42,11,
  4,24,208,147,208,190,209,130,208,190,
  208,178,0,129,0,75,16,23,5,24,
  208,151,208,176,208,180,208,176,208,189,
  208,184,208,181,58,0,129,0,91,23,
  7,6,24,194,176,67,0,7,22,75,
  22,15,7,2,26,2 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t button_plus; // =1 if button pressed, else =0 
  uint8_t button_minus; // =1 if button pressed, else =0 
  uint8_t switch_main; // =1 if switch ON and =0 if OFF 
  int16_t edit_setpoint;  // 32767.. +32767 

    // output variables
  float onlineGraph_temp_var1;
  float onlineGraph_temp_var2;
  uint8_t led_busy_r; // =0..255 LED Red brightness 
  uint8_t led_standby_b; // =0..255 LED Blue brightness 
  uint8_t led_ready_g; // =0..255 LED Green brightness 
  char text_temperature[6];  // string UTF8 end zero 
  char text_heatingTime[6];  // string UTF8 end zero 
  char text_processTime[6];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup() 
{
  RemoteXY_Init (); 
  
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}
