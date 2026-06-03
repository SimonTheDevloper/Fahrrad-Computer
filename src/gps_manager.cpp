#include "gps_manager.h"
#include "trip_computer.h"
#include "display_ui.h"

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
    static float fakeSpeed = 0;
    fakeSpeed += 0.5;

    if (fakeSpeed > 30)
        fakeSpeed = 0;

    speed = fakeSpeed;

    berechneDurschnittsSpeed(speed);
    if (speed > maxSpeed)
        maxSpeed = speed;
    altitude = 500 + fakeSpeed;

    static int testSatellitesVal = 0;
    testSatellitesVal += 1;

    if (testSatellitesVal > 16)
        testSatellitesVal = 0;
    satellites = testSatellitesVal;

    latitude = 22.34556 + fakeSpeed * 0.0001;
    longitude = 32.5654 + fakeSpeed * 0.0001;
}