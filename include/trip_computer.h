// hier werden nur dinge "angekündigt"
#ifndef TRIP_COMPUTER_H // ist dafür da das der Compiler nur einmal diese Datei durchgeht
#define TRIP_COMPUTER_H

#include <Arduino.h>

void berechneGesamtDistanz();
void berechneGesamtfahrzeit();
void berechneDurschnittsSpeed(float currentspeed);
void berechneDistanz();
void bekommeUhrzeit();

extern double gesamtStrecke;
extern double distanzInMetern;
extern unsigned long gesamtFahrtZeit;
extern float durchschnittSpeed;
extern float speedSum;
extern int speedCount;
extern int hour;
extern int minute;
extern int second;
extern char uhrzeit[16];
extern double letzteLat;
extern double letzteLong;

#endif