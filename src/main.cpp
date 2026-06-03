#include <Arduino.h>
#include "gps_manager.h" //hier müssen alle header geladen werden
#include "trip_computer.h"
#include "display_ui.h"

extern const bool TEST_MODE = true;

#define GPS_RX 32
#define GPS_TX 33

unsigned long letztesSekunde = 0;

void setup()
{
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);

  tft.init();
  tft.setRotation(3);

  zeichneGrundLayout();
}

void loop()
{
  if (!TEST_MODE)
  {
    verarbeiteGPS();
  }

  if (millis() - letztesSekunde >= 1000)
  {
    letztesSekunde = millis();

    if (TEST_MODE)
    {
      aendereTestGPSDaten();
      aktualisiereWerte();
    }

    berechneGesamtfahrzeit();
    berechneGesamtDistanz();
  }
}