#include "trip_computer.h"
#include "gps_manager.h"
#include "debug_helper.h"

double gesamtStrecke = 0.0;
double distanzInMetern = 0.0;
unsigned long gesamtFahrtZeit = 0;
float durchschnittSpeed = 0.0;
float speedSum = 0.0;
int speedCount = 0;
int hour = 0;
int minute = 0;
int second = 0;
char uhrzeit[16];
double letzteLat = 0.0;
double letzteLong = 0.0;

String formatTime(unsigned long sek) // mit String am anfang sagt man schon am anfang das es einen String zurück gibt
{
    unsigned long stunden = sek / 3600;
    unsigned long minuten = (sek % 3600) / 60;
    unsigned long sekunden = sek % 60;

    char zeit[9];
    sprintf(zeit, "%02lu:%02lu:%02lu", stunden, minuten, sekunden); // // %02lu bedeutet unsigned long, mindestens 2 Stellen, mit führenden Nullen auffüllen
    return String(zeit);
}

double meterToKm(double meter)
{
    return meter / 1000.0;
}

void berechneGesamtDistanz()
{
    berechneDistanz();
    if (distanzInMetern > 1.5)
    {
        gesamtStrecke += distanzInMetern;
        Serial.print("Total distance in km: ");
        Serial.println(meterToKm(gesamtStrecke));
    }
    else
    {
        Serial.println("Distance too short. => Too slow. Probably stationary and GPS noise");
    }
}
void berechneGesamtfahrzeit()
{
    if (speed > 1.5)
    {
        gesamtFahrtZeit++;
        Serial.print("Gesmatfahrzeit: ");
        Serial.println(formatTime(gesamtFahrtZeit));
    }
}
void berechneDurschnittsSpeed(float currentspeed)
{
    speedSum += currentspeed;
    speedCount++;

    if (speedCount > 1)
    {
        durchschnittSpeed = speedSum / speedCount;
        // Serial.println(durchschnittSpeed);
    }
}

void berechneDistanz()
{
    if (letzteLat == 0.0 && letzteLong == 0.0)
    {
        letzteLat = latitude;
        letzteLong = longitude;
        distanzInMetern = 0.0;
        return;
    }
    distanzInMetern = TinyGPSPlus::distanceBetween( // das berechnet es einfach schon
        letzteLat, letzteLong,
        latitude, longitude);

    Serial.print("Distance in m: ");
    Serial.println(distanzInMetern);
    letzteLat = latitude;
    letzteLong = longitude;
}
void bekommeUhrzeit()
{
    sprintf(uhrzeit,          // sprintf() baut aus Variablen einen Text zusammen.
            "%02d:%02d:%02d", // das macht das es auch 04 statt einfach 4 sein kann und ist natührlich ein platzhalter
            hour,
            minute,
            second);
}

void speichereStatistiken()
{
    File datei = LittleFS.open("/statistiken.txt", "w");
    if (!datei)
    {
        Serial.println("Fehler beim Öffnen der Datei zum Schreiben");
        return;
    }
    datei.println(gesamtStrecke);
    datei.println(gesamtFahrtZeit);
    datei.println(maxSpeed);

    // showAutoSaveInfo();

    datei.close();
}

void ladeStatistiken()
{
    File datei = LittleFS.open("/statistiken.txt", "r");
    if (!datei)
    {
        Serial.println("Fehler beim Öffnen der Datei zum Lesen");
        return;
    }
    gesamtStrecke = datei.parseFloat();
    gesamtFahrtZeit = datei.parseInt();
    maxSpeed = datei.parseFloat();

    // showLoadStaticsInfo();

    datei.close();
}
