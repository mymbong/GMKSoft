#include <ESP8266WiFi.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>

#include "GMK_Font_Data.h"
#include "GMK_TIME.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW //PAROLA_HW
#define MAX_ZONES 1
#define ZONE_SIZE 4
#define MAX_DEVICES (MAX_ZONES * ZONE_SIZE)

#define ZONE_  0

#define  CLK_PIN  D5 
#define DATA_PIN  D7 
#define CS_PIN    D8 

#define SPEED_TIME  75
#define PAUSE_TIME  0

#define MAX_MESG  200

const char *ssid     = "your ssid";
const char *password = "your password";

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
bool invertUpperZone = false;
char  szTime[MAX_MESG]; 

void setup(void)
{ 
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  invertUpperZone = (HARDWARE_TYPE == MD_MAX72XX::FC16_HW);

  P.begin(MAX_ZONES);
  P.setZone(ZONE_, 0, ZONE_SIZE );
  P.setFont(GMK_Custom);

  P.setCharSpacing(P.getCharSpacing() * 1);

  if (invertUpperZone)
  {
    P.displayZoneText(ZONE_, szTime, PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT, PA_NO_EFFECT);
  }
}

void loop(void)
{
  static uint32_t  xTime = 60;  // millis() memory
  static uint32_t	lastTime = 0; // millis() memory
  static bool	flasher = false;  // seconds passing flasher

  P.displayAnimate();
  
  if (P.getZoneStatus(ZONE_))
  {
    if (millis() - lastTime >= 1000)
    {
      lastTime = millis();
      getTime(szTime, flasher);
      flasher = !flasher;
      P.displayReset();
      P.synchZoneStart();
    }
  }
}
