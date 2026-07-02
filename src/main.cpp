#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include "secrets.h"
#include <FS.h>
#include <LittleFS.h>

Preferences preferences;
String ssid;
String password;

WebServer server(80);

void ladeWifiConfig()
{
    preferences.begin("config", true); // damit öffnet es einen Namespace und nur im Lesemodus

    ssid = preferences.getString("ssid", "");
    password = preferences.getString("password", "");

    preferences.end(); // damit es auch wieder schließt um ressourchen zu sparen
}
void speicherWifiConfig(String newSsid, String newPassword)
{
    preferences.begin("config", false);

    if (!preferences.isKey("ssid")) // damit es nur einmal gespeichert wird
    {
        preferences.putString("ssid", WIFI_SSID);
    }

    if (!preferences.isKey("password"))
    {
        preferences.putString("password", WIFI_PASSWORD);
    }
}
void starteWifi()
{
    speicherWifiConfig(ssid, password);

    ladeWifiConfig();
    WiFi.mode(WIFI_AP_STA);                     // damiit wird dem Chip gesagt das er in beiden Modes mode sein soll
    WiFi.begin(ssid.c_str(), password.c_str()); // damit startet er dann fürs Heimnetzt

    WiFi.softAP("BikeComputer", "SimDev123");
}
void handleRoute()
{
    File datei = LittleFS.open("/index.html", "r");

    if (!datei)
    {
        server.send(404, "text/plain", "Datei nicht gefunden");
        return;
    }

    String inhalt = datei.readString();
    datei.close();

    server.send(200, "text/html", inhalt);
}

void setup()
{
    Serial.begin(115200);

    if (!LittleFS.begin(true))
    {
        Serial.println("LittleFS could not be started");
        return;
    }
    delay(1000);

    Serial.print("Acces mode wird gestartet");
    starteWifi();
    delay(100);

    Serial.println("WLAN erfolgreich gestartet.");
    Serial.print("IP-Adresse vom ESP32: ");

    Serial.println(WiFi.softAPIP()); // damit gibt er seine IP raus

    server.on("/", handleRoute);

    server.begin(); // damit wird dann der Webserver gestartet
    Serial.println("Webserver im AP und STA gestartet!");
}

void loop()
{
    server.handleClient(); // damit schaut der ob die ganze Zeit Clients sich verbinden wollen.
}