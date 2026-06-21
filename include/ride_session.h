#ifndef RIDE_SESSION_H
#define RIDE_SESSION_H

#include <Arduino.h>

void setNewFahrtState(FahrtSate neuerState);

enum FahrtSate
{
    GESTOPPT,
    PAUSIERT,
    LAEFT
};
extern FahrtSate aktivFahrtState;

extern double sessionStrecke;
extern unsigned long sessionFahrtZeit;
extern float sessionAvgSpeed;
extern float sessionMaxSpeed;
extern bool isSessionRunning;

#endif
