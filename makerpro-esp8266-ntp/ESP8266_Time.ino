#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <time.h>
#include "timezone.h"

const char *WIFI_NETWORK_NAME = "xxxxxxxxxxx"; // Change to your wifi network name
const char *WIFI_PASSWORD = "xxxxxxxxxx";      // Change to your wifi password

const char *TIME_SERVER = "pool.ntp.org";
int myTimeZone = UTC; // change this to your time zone (see in timezone.h)

time_t now;

void setup()
{
  Serial.begin(115200); 

  WiFi.begin(WIFI_NETWORK_NAME, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  configTime(myTimeZone, 0, TIME_SERVER);

  while (now < EPOCH_1_1_2019)
  {
    now = time(nullptr);
    delay(500);
    Serial.print("*");
  }
}

// toStringAddZero()
// this function adds a zero to a date string if its a single digit
// for example if data = 1, then the function will return 01
// this makes the date and time string's consistant size for display
String toStringAddZero(int data)
{
  String st = "";
  if (data < 10)
  {
    st = "0" + String(data);
  }
  else
  {
    st = String(data);
  }
  return st;
}

void loop()
{
  
  struct tm *timeinfo;

  time(&now);
  timeinfo = localtime(&now);

  int year = timeinfo->tm_year + 1900;
  int month = timeinfo->tm_mon;
  int day = timeinfo->tm_mday;
  int hour = timeinfo->tm_hour;
  int mins = timeinfo->tm_min;
  int sec = timeinfo->tm_sec;
  int day_of_week = timeinfo->tm_wday;

  Serial.print("Date = " + toStringAddZero(day) + "/" + toStringAddZero(month) + "/" + String(year));
  Serial.println(" Time = " + toStringAddZero(hour) + ":" + toStringAddZero(mins) + ":" + toStringAddZero(sec));
  Serial.print("Day is " + String(DAYS_OF_WEEK[day_of_week]));
  Serial.println(" or " + String(DAYS_OF_WEEK_3[day_of_week]));
  
  delay(1000);
}
