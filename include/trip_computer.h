// hier werden nur dinge "angekündigt"
#ifndef TRIP_COMPUTER_H // ist dafür da das der Compiler nur einmal diese Datei durchgeht
#define TRIP_COMPUTER_H

#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>

void berechneGesamtDistanz();
void berechneGesamtfahrzeit();
void berechneDurschnittsSpeed(float currentspeed);
void berechneDistanz();
void bekommeUhrzeit();
void speichereStatistiken();
void ladeStatistiken();
void berechneHour();
void berechneMaxSpeed();

void showLoadStaticsInfo();

extern double gesamtStrecke;
extern double distanzInMetern;
extern unsigned long gesamtFahrtZeit;
extern float durchschnittSpeed;
extern float speedSum;
extern int speedCount;
extern float maxSpeed;
extern char uhrzeit[16];
extern double letzteLat;
extern double letzteLong;

extern double sessionStrecke;
extern unsigned long sessionFahrtZeit;
extern float sessionAvgSpeed;
extern float sessionMaxSpeed;

#endif
