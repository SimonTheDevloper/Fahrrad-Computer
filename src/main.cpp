#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.print("Acces mode wird gestartet");

    WiFi.mode(WIFI_AP); // damiit wird dem Chip gesagt das er im Acces Point mode sein soll

    WiFi.softAP("BikeComputer", "SimDev123");
    delay(100);

    Serial.println("WLAN erfolgreich gestartet.");
    Serial.print("IP-Adresse vom ESP32: ");

    Serial.println(WiFi.softAPIP()); // damit gibt er seine IP raus

    server.on("/", []()
              { server.send(200, "text/plain", "HELLO client! Ich bin im AP mdus!"); });

    server.begin(); // damit wird dann der Webserver gestartet
    Serial.println("Webserver im AP-Modus gestartet!");
}

void loop()
{
    server.handleClient(); // damit schaut der ob die ganze Zeit Clients sich verbinden wollen.
}