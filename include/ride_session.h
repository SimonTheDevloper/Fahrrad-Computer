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
void verarbeiteSessionTouchInput(uint16_t x, uint16_t y);

extern FahrtSate aktivFahrtState;

extern double sessionStrecke;
extern unsigned long sessionFahrtZeit;
extern float sessionAvgSpeed;
extern float sessionMaxSpeed;

#endif
