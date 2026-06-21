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

bool letzterTouch = false;

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

  setNewScreen(SCREEN_SESSION);
}
void loop()
{
  uint16_t x = 0, y = 0;
  bool touch = tft.getTouch(&x, &y);

  if (touch)
  {
    if (!letzterTouch)
    {
      Serial.println("Touch detected");
      Serial.print("X: ");
      Serial.print(x);
      Serial.print(" Y: ");
      Serial.println(y);

      static unsigned long letztePressZeit = 0;
      if (pruefeStartButton(x, y) && (millis() - letztePressZeit > 500)) // damit es entprellt wird
      {
        Serial.println("Pressed on BTN!");
        setNewFahrtState(LAEFT);
        letztePressZeit = millis();
      }
    }
    letzterTouch = true;
  }
  else
  {
    letzterTouch = false;
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

    if (TEST_MODE)
    {
      currentSpeed = (distanzInMetern * 3.6);

      berechneDurschnittsSpeed(currentSpeed);
      berechneMaxSpeed();
    }

    verwalteSpeicherIntervall();
    berechneGesamtfahrzeit();
  }
}
