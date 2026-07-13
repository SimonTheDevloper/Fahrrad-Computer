#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WebServer.h>

extern WebServer server;

void starteWifi();
void ladeWifiConfig();
void speicherWifiConfig(String newSsid, String newPassword);
void handleLetzteFahrt();
void verbindeMitHeimnetz();
void starteAccesPoint();
void registriereServerRouten();
void sendeDatei(String pfad, String typ);
void registriereWebsitenRouten();
void handleCSS();
void handleJS();

#endif