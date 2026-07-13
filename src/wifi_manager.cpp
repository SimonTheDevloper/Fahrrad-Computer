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

    if (!preferences.isKey("ssid")) // damit es nur einmal gespeichert wird
    {
        preferences.putString("ssid", newSsid);
    }

    if (!preferences.isKey("password"))
    {
        preferences.putString("password", newPassword);
    }
}
void verbindeMitHeimnetz()
{
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.println("Versuche, mit dem Heimnetz zu verbinden...");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("Erfolgreich mit dem Heimnetz verbunden!");
    Serial.print("IP-Adresse (Heimnetz): ");
    Serial.println(WiFi.localIP());
}
void starteAccesPoint()
{
    WiFi.softAP("BikeComputer", "SimDev123");

    Serial.println("Access Point erfolgreich gestartet.");
    Serial.print("IP-Adresse (AP): ");
    Serial.println(WiFi.softAPIP());
}
void handleStartseite()
{
    sendeDatei("/index.html", "text/html");
}
void handleCSS()
{
    sendeDatei("/style.css", "text/css");
}
void registriereWebsitenRouten()
{
    server.on("/", handleStartseite);
    server.on("/style.css", handleCSS);
}
void registriereServerRouten()
{
    registriereWebsitenRouten();
    server.on("/letzteFahrt", handleLetzteFahrt);
}

void sendeDatei(String pfad, String typ)
{
    File datei = LittleFS.open(pfad, "r");

    if (!datei)
    {
        server.send(404, "text/plain", "Datei nicht gefunden");
        return;
    }

    server.streamFile(datei, typ); // dadurch wird  die datei direkt aus dem LittleFS geschickt

    datei.close();
}
void starteWifi()
{
    speicherWifiConfig(ssid, password);
    ladeWifiConfig();

    WiFi.mode(WIFI_AP_STA);

    verbindeMitHeimnetz();
    starteAccesPoint();

    registriereServerRouten();

    server.begin();
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