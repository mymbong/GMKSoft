#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include "NTPClient.h"

#ifndef GMK_TIME_H
#define GMK_TIME_H

const long utcOffsetInSeconds = 28800; // google it according to your country

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds, 6000);

void getTime(char *psz, bool f = true)
{

  //Serial.begin(9600);

  timeClient.begin();

  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }

  /////////////////////////////////////////////////////////////

  char *am = "  A";
  char *pm = "  P";

  /////////////////////////////////////////////////////////////

  char *jan = "JAN";
  char *feb = "FEB";
  char *mar = "MAR";
  char *apr = "APR";
  char *may = "MAY";
  char *jun = "JUN";
  char *jul = "JUL";
  char *aug = "AUG";
  char *sep = "SEP";
  char *oct = "OCT";
  char *nov = "NOV";
  char *dec = "DEC";

  /////////////////////////////////////////////////////////////
  // MONTH
  /////////////////////////////////////////////////////////////

  char *mon_ = "   MON";
  char *tue = "    TUE";
  char *wed = "    WED";
  char *thu = "    THU";
  char *fri = "    FRI";
  char *sat = "    SAT";
  char *sun = "    SUN";

  /////////////////////////////////////////////////////////////
  // FOR SPACING CHAR
  /////////////////////////////////////////////////////////////

  char *y = "   ";

  uint16_t  h, m, s, day_, month_, year_, date_;

  month_ = timeClient.getMonth();
  //Serial.println(month_);

  day_ = timeClient.getDay();
  //Serial.println(day_);

  year_ = timeClient.getYear();
  //Serial.println(year_);

  date_ = timeClient.getDate();
  //Serial.println(date_);

  h = timeClient.getHours();
  m = timeClient.getMinutes();
  s = timeClient.getSeconds();


  if (h > 12)
  {
    h = h - 12;
    sprintf(psz, "%02d%c%02d%s", h, (f ? ':' : ' '), m, pm);

    if (h == 0)
    {
      h = 12;
      sprintf(psz, "%02d%c%02d%s", h, (f ? ':' : ' '), m, pm);
    }
  }
  else
  {
    if (h == 0)
    {
      h = 12; 
    }
    sprintf(psz, "%02d%c%02d%s", h, (f ? ':' : ' '), m, am);
  }

  /////////////////////////////////////////////////////////////

  if (s == 10 || s == 40)
  {
    if (day_ == 0)
    {
      sprintf(psz, "%s", sun);
    }
    if (day_ == 1)
    {
      sprintf(psz, "%s", mon_);
    }
    if (day_ == 2)
    {
      sprintf(psz, "%s", tue);
    }
    if (day_ == 3)
    {
      sprintf(psz, "%s", wed);
    }
    if (day_ == 4)
    {
      sprintf(psz, "%s", thu);
    }
    if (day_ == 5)
    {
      sprintf(psz, "%s", fri);
    }
    if (day_ == 6)
    {
      sprintf(psz, "%s", sat);
    }
  }

  /////////////////////////////////////////////////////////////

  if (s == 11 || s == 41)
  {
    if (month_ == 1)
    {
      sprintf(psz, "%s %d", jan, date_);
    }
    if (month_ == 2)
    {
      sprintf(psz, "%s %d", feb, date_);
    }
    if (month_ == 3)
    {
      sprintf(psz, "%s %d", mar, date_);
    }
    if (month_ == 4)
    {
      sprintf(psz, "%s %d", apr, date_);
    }
    if (month_ == 5)
    {
      sprintf(psz, "%s %d", may, date_);
    }
    if (month_ == 6)
    {
      sprintf(psz, "%s", jun, date_);
    }
    if (month_ == 7)
    {
      sprintf(psz, "%s %d", jul, date_);
    }
    if (month_ == 8)
    {
      sprintf(psz, "%s %d", aug, date_);
    }
    if (month_ == 9)
    {
      sprintf(psz, "%s %d", sep, date_);
    }
    if (month_ == 10)
    {
      sprintf(psz, "%s %d", oct, date_);
    }
    if (month_ == 11)
    {
      sprintf(psz, "%s %d", nov, date_);
    }
    if (month_ == 12)
    {
      sprintf(psz, "%s %d", dec, date_);
    }
  }

  /////////////////////////////////////////////////////////////

  if (s == 12 || s == 42)
  {
    sprintf(psz, "%s%4d", y, year_);
  }
}
#endif
