#include "ride_session.h"
#include "trip_computer.h"
#include "gps_manager.h"
FahrtSate aktivFahrtState = GESTOPPT;

double sessionStrecke = 0.0;
unsigned long sessionFahrtZeit = 0.0;
float sessionAvgSpeed = 0.0;
float sessionMaxSpeed = 0.0;
float maxSpeed = 0.0;

void setNewFahrtState(FahrtSate neuerState)
{
    aktivFahrtState = neuerState;
}

void berechneSessionDistanz()
{
    if (aktivFahrtState == LAEUFT)
    {
        sessionStrecke += distanzInMetern;
    }
}

void berechneSessionFahrzeit()
{
    if (aktivFahrtState == LAEUFT)
    {
        sessionFahrtZeit++;
    }
}

void berechneSessionAvgSpeed()
{
    if (aktivFahrtState == LAEUFT)
    {
        static float sessionSpeedSum = 0.0;
        static int sessionSpeedCount = 0;

        if (currentSpeed > 1.5)
        {
            sessionSpeedSum += currentSpeed;
            sessionSpeedCount++;
            sessionAvgSpeed = sessionSpeedSum / sessionSpeedCount;
        }
    }
}

void berechneSessionMaxSpeed()
{

    if (aktivFahrtState == LAEUFT)
    {
        if (currentSpeed > sessionMaxSpeed)
        {
            sessionMaxSpeed = currentSpeed;
        }
    }
}
