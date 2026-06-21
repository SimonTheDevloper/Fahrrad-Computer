#ifndef RIDE_SESSION_H
#define RIDE_SESSION_H

#include <Arduino.h>
enum FahrtSate
{
    UNBEKANNT,
    GESTOPPT,
    PAUSIERT,
    LAEUFT
};
void setNewFahrtState(FahrtSate neuerState);
void berechneSessionDistanz();
void berechneSessionFahrzeit();
void berechneSessionAvgSpeed();
void berechneSessionMaxSpeed();

extern FahrtSate aktivFahrtState;

extern double sessionStrecke;
extern unsigned long sessionFahrtZeit;
extern float sessionAvgSpeed;
extern float sessionMaxSpeed;

#endif
