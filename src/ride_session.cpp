#include <vector>
#include <LittleFS.h>
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

String aktuelleFahrtDatei = "";

bool letzterTouch = false;

void erstelleFilesOrdner()
{
    if (!LittleFS.mkdir("/fahrten"))
    {
        Serial.print("beim erstellen des Ordners: fahrten fehlgeschlagen");
    }
}

String erstelleNeueFahrtDatei()
{
    std::vector<String> files;
    File dir = LittleFS.open("/fahrten");
    File file = dir.openNextFile();

    while (file)
    {
        files.push_back(file.name());
        file = dir.openNextFile();
    }

    int hoechsteNummer = 0;

    for (const auto &name : files)
    {
        int start = name.indexOf("-") + 1;
        int ende = name.indexOf(".");
        int nummer = name.substring(start, ende).toInt();

        if (nummer > hoechsteNummer)
        {
            hoechsteNummer = nummer;
        }
    }

    hoechsteNummer++;
    String neuerName = "fahrt-" + String(hoechsteNummer) + ".csv";
    File datei = LittleFS.open("/fahrten/" + neuerName, "w");

    if (datei)
    {
        Serial.println("Neue Datei erstellt: " + neuerName);
        datei.close();
    }
    else
    {
        Serial.println("Datei konnte nicht erstellt werden.");
    }
    return neuerName;
}

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

                saveLogs();
                logPufferIndex = 0;
                aktuelleFahrtDatei = "";

                resetSessionWerte();
                letztePressZeit = millis();
                darfLoggen = false;
            }
        }
        else
        {
            if (pruefeStartButton(x, y) && (millis() - letztePressZeit > 500))
            {
                Serial.println("Pressed on BTN!");
                if (aktivFahrtState == GESTOPPT)
                {
                    setNewFahrtState(LAEUFT);
                    aktuelleFahrtDatei = erstelleNeueFahrtDatei();
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
    if (aktuelleFahrtDatei == "")
    {
        aktuelleFahrtDatei = erstelleNeueFahrtDatei();
    }

    String ganzerPfad = "/fahrten/" + aktuelleFahrtDatei;
    File datei = LittleFS.open(ganzerPfad, "a");

    if (!datei)
    {
        Serial.println("Fehler beim Oeffnen der Datei zum Schreiben");
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