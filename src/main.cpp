#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include "gps_manager.h"
#include "trip_computer.h"
#include "display/display_ui.h"
#include "ride_session.h"
#include "wifi_manager.h"
#include "bmp_manager.h"

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
    initBmp();

    if (!LittleFS.begin(true))
    {
        Serial.println("LittleFS could not be started");
        return;
    }

    void erstelleFilesOrdner();

    ladeFarbTheme();
    ladeStatistiken();

    setNewScreen(SCREEN_MENU);

    starteWifi();
    server.begin();
    Serial.println("Webserver bereit!");
}
void loop()
{

    server.handleClient();
    uint16_t x = 0, y = 0;
    if (tft.getTouch(&x, &y))
    {
        verarbeiteGesamtenTouch(x, y);
        delay(150);
    }

    if (!TEST_MODE)
    {
        verarbeiteGPS();
        verarbeiteBmp();
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

        handleLogging();
        berechneSessionAvgSpeed();
        berechneSessionMaxSpeed();
        verwalteSpeicherIntervall();
        berechneGesamtfahrzeit();
        berechneSessionFahrzeit();
    }
}
