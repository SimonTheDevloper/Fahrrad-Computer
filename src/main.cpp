#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include "gps_manager.h"
#include "trip_computer.h"
#include "display_ui.h"
#include "ride_session.h"

extern const bool TEST_MODE = true;

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

  if (!LittleFS.begin(true))
  {
    Serial.println("LittleFS could not be started");
    return;
  }
  ladeStatistiken();

  setNewScreen(SCREEN_MAIN);
}
void loop()
{
  uint16_t x = 0, y = 0;
  bool touch = tft.getTouch(&x, &y);

  if (touch)
  {
    static unsigned long letzteNavPressZeit = 0;

    if (pruefeNavigationButton(x, y))
    {
      if (millis() - letzteNavPressZeit > 500)
      {
        if (aktiverScreen == SCREEN_MAIN)
        {
          setNewScreen(SCREEN_SESSION);
        }
        else
        {
          setNewScreen(SCREEN_MAIN);
        }
        letzteNavPressZeit = millis();
      }
    }
    else
    {
      verarbeiteSessionTouchInput(x, y);
    }
  }

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
    berechneSessionDistanz();

    if (TEST_MODE)
    {
      currentSpeed = (distanzInMetern * 3.6);
      berechneDurschnittsSpeed(currentSpeed);
      berechneMaxSpeed();
    }

    berechneSessionAvgSpeed();
    berechneSessionMaxSpeed();
    verwalteSpeicherIntervall();
    berechneGesamtfahrzeit();
    berechneSessionFahrzeit();
  }
}
