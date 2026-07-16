#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <Arduino.h>

#define SD_CS_PIN 15

void setup()
{
    Serial.begin(115200);
    SPI.begin(18, 19, 23, SD_CS_PIN);

    if (!SD.begin(SD_CS_PIN))
    {
        Serial.println("SD-Karte konnte nicht initialisiert werden!");
        return;
    }
    Serial.println("SD Karte ist bereit");

    File meineCooleDatei = SD.open("/test.txt", FILE_WRITE);

    if (meineCooleDatei)
    {
        meineCooleDatei.println("Hier steht was cooles!");
        meineCooleDatei.close();
        Serial.println("Fertig geschireben und geschlossen");
    }
    else
    {
        Serial.println("Fehler beim schreiben!");
    }
}
void loop()
{
}
