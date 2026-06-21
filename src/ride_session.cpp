#include "ride_session.h"
#include "trip_computer.h"
#include "gps_manager.h"
#include "display_ui.h"
FahrtSate aktivFahrtState = GESTOPPT;

double sessionStrecke = 0.0;
unsigned long sessionFahrtZeit = 0.0;
float sessionAvgSpeed = 0.0;
float sessionMaxSpeed = 0.0;
float maxSpeed = 0.0;

bool letzterTouch = false;

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

void verarbeiteSessionTouchInput(uint16_t x, uint16_t y)
{

    if (!letzterTouch)
    {
        Serial.println("Touch detected");
        Serial.print("X: ");
        Serial.print(x);
        Serial.print(" Y: ");
        Serial.println(y);

        static unsigned long letztePressZeit = 0;
        if (aktivFahrtState == PAUSIERT)
        {
            if (pruefeWeiterButton(x, y) && (millis() - letztePressZeit > 500))
            {
                Serial.println("Pressed WEITER!");
                setNewFahrtState(LAEUFT);
                letztePressZeit = millis();
            }
            else if (pruefeStoppButton(x, y) && (millis() - letztePressZeit > 500))
            {
                Serial.println("Pressed STOPPEN!");
                setNewFahrtState(GESTOPPT);
                letztePressZeit = millis();
            }
        }
        else
        {
            if (pruefeStartButton(x, y) && (millis() - letztePressZeit > 500)) // damit es entprellt wird
            {
                Serial.println("Pressed on BTN!");
                if (aktivFahrtState == GESTOPPT)
                {
                    setNewFahrtState(LAEUFT);
                }
                else if (aktivFahrtState == LAEUFT)
                {
                    setNewFahrtState(PAUSIERT);
                }
                else if (aktivFahrtState == PAUSIERT)
                {
                    setNewFahrtState(LAEUFT);
                }

                letztePressZeit = millis();
            }
        }
        letzterTouch = true;
    }
    else
    {
        letzterTouch = false;
    }
}
