#include <Arduino.h>
#include <WiFi.h>

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("Wlan wird gestartet");

    WiFi.softAP("BikeComputer", "SimDev123"); // damit er den Acces Point startet mit Name, Passwort
    Serial.println("Wlan erfolgreich gestartet.");

    Serial.print("IP adresse vom ESP32: ");
    Serial.println(WiFi.softAPIP()); // damit gibt er die IP
}

void loop()
{
}
