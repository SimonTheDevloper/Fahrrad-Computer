#include "gps_manager.h"
#include "trip_computer.h"
#include "display_ui.h"
#include "mock_daten.h"

TinyGPSPlus gps;
HardwareSerial gpsSerial(2); // Nutzt Serial 2 des ESP32

double latitude = 0.0;
double longitude = 0.0;
double altitude = 0.0;
float speed = 0.0;
float maxSpeed = 0.0;
int satellites = 0;
int day = 0;
int month = 0;
int year = 0;
void verarbeiteGPS()
{
    while (gpsSerial.available() > 0)
    {
        gps.encode(gpsSerial.read());
    }

    if (gps.location.isValid() && gps.location.isUpdated())
    {
        latitude = gps.location.lat();
        longitude = gps.location.lng();
        altitude = gps.altitude.meters();
        speed = gps.speed.kmph();

        berechneDurschnittsSpeed(speed);

        if (speed > maxSpeed)
            maxSpeed = speed;

        satellites = gps.satellites.value();
        Serial.println(satellites);
        day = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();

        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();
        aktualisiereWerte();
    }
}
void aendereTestGPSDaten()
{
    static int aktuelleKoordinatenIndex = 0;
    static bool vorwaers = true;
    latitude = MOCK_ROUTE[aktuelleKoordinatenIndex].lat;
    longitude = MOCK_ROUTE[aktuelleKoordinatenIndex].lon;

    berechneDurschnittsSpeed(speed);

    if (speed > maxSpeed)
        maxSpeed = speed;

    if (vorwaers)
    {
        aktuelleKoordinatenIndex++;
    }
    else
    {
        aktuelleKoordinatenIndex--;
    }

    if (aktuelleKoordinatenIndex >= MOCK_ROUTE_LAENGE)
    {
        aktuelleKoordinatenIndex = MOCK_ROUTE_LAENGE - 1;
        vorwaers = false;
    }

    if (aktuelleKoordinatenIndex < 0)
    {
        aktuelleKoordinatenIndex = 0;
        vorwaers = true;
    }
    Serial.print("KoordIndex: ");
    Serial.println(aktuelleKoordinatenIndex);
    aktualisiereWerte();
}
