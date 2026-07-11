#include <Arduino.h>
#include "debug_helper.h"
#include "trip_computer.h"
#include "gps_manager.h"
#include "bmp_manager.h"

extern double gesamtStrecke;
extern unsigned long gesamtFahrtZeit;
extern float maxSpeed;
unsigned long letztesPrintZeit = 0;

void showAutoSaveInfo()
{
    if (millis() - letztesPrintZeit < 200)
        return;
    Serial.println("\n=============================================================");
    Serial.print("[LittleFS saved that]:  ");
    Serial.print(gesamtStrecke);
    Serial.print(" m | ");
    Serial.print(gesamtFahrtZeit);
    Serial.print(" s | ");
    Serial.print(maxSpeed);
    Serial.println(" km/h");
    Serial.println("=============================================================\n");

    letztesPrintZeit = millis();
}
void showLoadStaticsInfo()
{
    if (millis() - letztesPrintZeit < 200)
        return;

    Serial.println("\n====================================");
    Serial.println("LittleFS has the statistics loaded successfully:");
    Serial.print(" Total distance: ");
    Serial.print(gesamtStrecke);
    Serial.println(" m");
    Serial.print(" Total travel time: ");
    Serial.print(gesamtFahrtZeit);
    Serial.println(" sec");
    Serial.print(" Max. speed: ");
    Serial.print(maxSpeed);
    Serial.println(" km/h");
    Serial.println("====================================\n");

    letztesPrintZeit = millis();
}

void showGPSDaten()
{
    if (millis() - letztesPrintZeit < 200)
        return;

    Serial.print("Latitude: ");
    Serial.println(latitude, 6);

    Serial.print("Longitude: ");
    Serial.println(longitude, 6);

    Serial.print("Altitude: ");
    Serial.print(altitude);
    Serial.println(" m");

    Serial.print("Satalites: ");
    Serial.println(satellites);

    letztesPrintZeit = millis();
}
void showBmpData()
{
    if (millis() - letztesPrintZeit < 200)
        return;

    Serial.print("Temperature: ");
    Serial.print(currentTemperature, 2);
    Serial.println("°C");

    Serial.print("Luftdruck: ");
    Serial.print(currentLuftDruck);
    Serial.println("hPa");

    Serial.print("Baro-Hoehe: ");
    Serial.print(currentHoeheBaro);
    Serial.println("m");

    letztesPrintZeit = millis();
}