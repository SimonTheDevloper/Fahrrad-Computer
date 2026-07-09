#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <FS.h>
#include <LittleFS.h>
#include "wifi_manager.h"
#include "secrets.h"

Preferences preferences;
String ssid;
String password;

WebServer server(80);

void ladeWifiConfig()
{
    preferences.begin("config", true); // Öffnet den Speicher im Lesemodus
    ssid = preferences.getString("ssid", WIFI_SSID);
    password = preferences.getString("password", WIFI_PASSWORD);
    preferences.end();
}

void speicherWifiConfig(String newSsid, String newPassword)
{
    preferences.begin("config", false);
    preferences.putString("ssid", newSsid);
    preferences.putString("password", newPassword);
    preferences.end();
}

void starteWifi()
{
    ladeWifiConfig();

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.println("versuche mit Heimnetzt zu verbinde");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("Erfolgreich mit Heimnetz verbunden!");
    Serial.print("IP-Adresse: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleLetzteFahrt);
}

void handleLetzteFahrt()
{
    File dir = LittleFS.open("/fahrten");
    File file = dir.openNextFile();
    int hoechsteNummer = 0;

    while (file)
    {
        String name = file.name();
        int start = name.indexOf("-") + 1;
        int ende = name.indexOf(".");
        int nummer = name.substring(start, ende).toInt();

        if (nummer > hoechsteNummer)
        {
            hoechsteNummer = nummer;
        }
        file = dir.openNextFile();
    }

    if (hoechsteNummer == 0)
    {
        server.send(404, "text/plain", "Noch keine Fahrten aufgezeichnet!");
        return;
    }

    String neuesteDateiPfad = "/fahrten/fahrt-" + String(hoechsteNummer) + ".csv";

    File fahrtDatei = LittleFS.open(neuesteDateiPfad, "r");
    if (!fahrtDatei)
    {
        server.send(500, "text/plain", "Fehler beim Öffnen der Datei");
        return;
    }

    server.streamFile(fahrtDatei, "text/csv"); // das checke ich nicht für was bracuche ich das und brauche ich es wirklich 100% und wie funktioniert es
    fahrtDatei.close();
}