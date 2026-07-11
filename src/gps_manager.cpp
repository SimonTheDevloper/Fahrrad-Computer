#include "gps_manager.h"
#include "trip_computer.h"
#include "display/display_ui.h"
#include "mock_daten.h"
#include "debug_helper.h"

TinyGPSPlus gps;
HardwareSerial gpsSerial(2); // Nutzt Serial 2 des ESP32

double latitude = 0.0;
double longitude = 0.0;
double altitude = 0.0;
float currentSpeed = 0.0;
int satellites = 0;
int day = 0;
int month = 0;
int year = 0;

int utcHour = 0;
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
        currentSpeed = gps.speed.kmph();

        berechneDurschnittsSpeed(currentSpeed);
        berechneMaxSpeed();

        satellites = gps.satellites.value();
        Serial.println(satellites);
        day = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();

        utcHour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();
        // showGPSDaten();
    }
}

void aendereTestGPSDaten()
{
    static int aktuelleKoordinatenIndex = 0;
    static bool vorwaers = true;
    latitude = MOCK_ROUTE[aktuelleKoordinatenIndex].lat;
    longitude = MOCK_ROUTE[aktuelleKoordinatenIndex].lon;

    if (vorwaers)
    {
        aktuelleKoordinatenIndex++;
        if (aktuelleKoordinatenIndex >= MOCK_ROUTE_LAENGE)
        {
            aktuelleKoordinatenIndex = MOCK_ROUTE_LAENGE - 2;
            vorwaers = false;
        }
    }
    else
    {
        aktuelleKoordinatenIndex--;
        if (aktuelleKoordinatenIndex < 0)
        {
            aktuelleKoordinatenIndex = 1;
            vorwaers = true;
        }
    }
    Serial.print("KoordIndex: ");
    Serial.println(aktuelleKoordinatenIndex);
}
