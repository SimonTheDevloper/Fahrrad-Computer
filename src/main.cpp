#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <Arduino.h>

#define SD_CS_PIN 13

void setup()
{
    Serial.begin(115200);

    delay(500);

    SPI.begin(18, 19, 23, SD_CS_PIN);

    if (!SD.begin(SD_CS_PIN, SPI, 4000000))
    {
        Serial.println("SD-Karte konnte nicht initialisiert werden!");
        return;
    }
    Serial.println("SD-Karte ist bereit.");

    File mapDatei = SD.open("/testMap.jpg", FILE_READ);

    if (mapDatei)
    {
        Serial.println("Datei 'testMap.jpg' erfolgreich geöffnet!");
        Serial.print("Dateigröße: ");
        Serial.print(mapDatei.size());
        Serial.println(" Bytes");

                /*
        while (mapDatei.available()) {
        hier könnte ich es dann mit den TFT display coden.
        }
        */

        mapDatei.close();
        Serial.println("Datei erfolgreich gelesen und geschlossen.");
    }
    else
    {
        Serial.println("Fehler: Datei 'testMap' wurde nicht auf der SD-Karte gefunden!");
    }
}

void loop()
{
}