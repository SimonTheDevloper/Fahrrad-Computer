#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include "gps_manager.h" //hier müssen alle header geladen werden
#include "trip_computer.h"
#include "display_ui.h"

extern const bool TEST_MODE = false;

#define GPS_RX 32
#define GPS_TX 33

unsigned long letztesSekunde = 0;
unsigned long letzteDisplayUpdateZeit = 0;
int speicherZaeler = 0;

void verwalteSpeicherIntervall()
{
  speicherZaeler++;
  if (speicherZaeler >= 5)

  {
    speicherZaeler = 0;
    speichereStatistiken();
  }
}
void setup()
{
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);

  initDisplay();

  if (!LittleFS.begin(true)) // startet LittleFS
  {
    Serial.println("LittleFS could not be started");
    return;
  }
  // LittleFS.format();
  ladeStatistiken();
  setNewScreen(SCREEN_SESSION);
}

void loop()
{
  if (!TEST_MODE)
  {
    verarbeiteGPS();
  }

  if (millis() - letzteDisplayUpdateZeit >= 200)
  {
    letzteDisplayUpdateZeit = millis();
    updateAktivenScreen();
  }
  if (millis() - letztesSekunde >= 1000)
  {
    letztesSekunde = millis();
    if (TEST_MODE)
    {
      aendereTestGPSDaten();
    }
    berechneGesamtDistanz();

    if (TEST_MODE)
    {
      currentSpeed = (distanzInMetern * 3.6);
    }

    verwalteSpeicherIntervall();
    berechneGesamtfahrzeit();
  }
}
