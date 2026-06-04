#include <Arduino.h>
#include "debug_helper.h"
#include "trip_computer.h"
#include "gps_manager.h"

extern double gesamtStrecke;
extern unsigned long gesamtFahrtZeit;
extern float maxSpeed;

void showAutoSaveInfo()
{
    Serial.println("\n=============================================================");
    Serial.print("[LittleFS saved that]:  ");
    Serial.print(gesamtStrecke);
    Serial.print(" m | ");
    Serial.print(gesamtFahrtZeit);
    Serial.print("s | Max: ");
    Serial.print(maxSpeed);
    Serial.println(" km/h");
    Serial.println("=============================================================\n");
}
void showLoadStaticsInfo()
{
    Serial.println("\n====================================");
    Serial.println("LittleFS has the statistics loaded successfully:");
    Serial.print(" Total distance: ");
    Serial.print(gesamtStrecke);
    Serial.println(" m");
    Serial.print(" Total travel time: ");
    Serial.print(gesamtFahrtZeit);
    Serial.println(" sec");
    Serial.print(" Max. speed: ");
    Serial.print(maxSpeed);
    Serial.println(" km/h");
    Serial.println("====================================\n");
}