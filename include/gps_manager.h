#ifndef GPS_MANAGER_H
#define GPS_MANAGER_H

#include <TinyGPS++.h>
#include <Arduino.h>

extern TinyGPSPlus gps;
extern HardwareSerial gpsSerial;
void verarbeiteGPS();
void aendereTestGPSDaten();

extern double latitude;
extern double longitude;
extern double altitude;
extern float speed;
extern float maxSpeed;
extern int satellites;
extern int day;
extern int month;
extern int year;

#endif