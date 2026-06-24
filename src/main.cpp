#include <Arduino.h>
#include <Wire.h>

void setup()
{
    Serial.begin(115200);
    delay(2000);

    Wire.begin(21, 22); // ggf. auch 25,26 testen
    Serial.println("I2C Scanner startet...");
}

void loop()
{

    bool found = false;

    for (byte addr = 1; addr < 127; addr++)
    {
        Wire.beginTransmission(addr);
        byte error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("Gefunden: 0x");
            Serial.println(addr, HEX);
            found = true;
        }
    }

    if (!found)
    {
        Serial.println("Kein Gerät gefunden");
    }

    Serial.println("----------------------");
    delay(2000); // alle 2 Sekunden neu scannen
}