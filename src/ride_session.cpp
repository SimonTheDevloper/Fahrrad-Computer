#include "ride_session.h"
#include "trip_computer.h"
#include "gps_manager.h"
#include "display/display_ui.h"
FahrtSate aktivFahrtState = GESTOPPT;

LogData currentLog;
LogData logPuffer[10];
int logPufferIndex = 0;

unsigned long letzteLogZeit = 0;
bool darfLoggen = false;

int logHaefigkeit = 1000;

double sessionStrecke = 0.0;
unsigned long sessionFahrtZeit = 0;
float sessionAvgSpeed = 0.0;
float sessionMaxSpeed = 0.0;
float maxSpeed = 0.0;

static float sessionSpeedSum = 0.0;
static int sessionSpeedCount = 0;

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
                darfLoggen = true;
            }
            else if (pruefeStoppButton(x, y) && (millis() - letztePressZeit > 500))
            {
                Serial.println("Pressed STOPPEN!");
                setNewFahrtState(GESTOPPT);
                resetSessionWerte();
                letztePressZeit = millis();
                darfLoggen = false;
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
                    darfLoggen = true;
                }
                else if (aktivFahrtState == LAEUFT)
                {
                    setNewFahrtState(PAUSIERT);
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

void resetSessionWerte()
{
    sessionStrecke = 0.0;
    sessionFahrtZeit = 0.0;
    sessionAvgSpeed = 0.0;
    sessionMaxSpeed = 0.0;
    maxSpeed = 0.0;
    sessionSpeedSum = 0.0;
    sessionSpeedCount = 0;
}

void handleLogging()
{
    if (!darfLoggen)
        return;

    if (millis() - letzteLogZeit >= logHaefigkeit)
    {
        bekommeUhrzeit();

        currentLog.time = int(uhrzeit);
        currentLog.altitude = altitude;
        currentLog.latitude = latitude;
        currentLog.longitude = longitude;

        schreibeLogs();

        letzteLogZeit = millis();
    }
}

void schreibeLogs()
{

    String line = String(currentLog.time) + "," +
                  String(currentLog.altitude) + "," +
                  String(currentLog.latitude) + "," +
                  String(currentLog.longitude);

    Serial.println(line);
    logPuffer[logPufferIndex++] = currentLog;

    if (logPufferIndex >= 10)
    {
        saveLogs();
        logPufferIndex = 0;
    }
}

void saveLogs()
{
    File datei = LittleFS.open("/fahrten.csv", "a"); // das a ist für append das es nicht immer alles überschreibt also löscht
    if (!datei)
    {
        Serial.println("Fehler beim Öffnen der Datei zum Schreiben");
        return;
    }
    Serial.println("Der ganze Puffer an daten wird nun gespeichert");
    for (int i = 0; i < logPufferIndex; i++)
    {
        datei.print(logPuffer[i].time);
        datei.print(",");
        datei.print(logPuffer[i].latitude, 6);
        datei.print(",");
        datei.print(logPuffer[i].longitude, 6);
        datei.print(",");
        datei.println(logPuffer[i].altitude);
    }

    datei.close();
}
