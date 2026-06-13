#ifndef DISPLAY_UI_H
#define DISPLAY_UI_H

#include <Arduino.h>

class TFT_eSPI;
extern TFT_eSPI tft;
enum Screen // macht einen neuen Datentyp Screen wo man dann mehrer zustände definieren kann was Screen sein kann
{
    SCREEN_MAIN, // so kann man mit Wörtern auch Zahlen machen. Intern würde hier 0 stehen
    SCREEN_SESSION
};
extern Screen aktiverScreen;

void initDisplay();
void zeichneGrundLayout();
void aktualisiereWerte();
void zeichneSessionLayout();
void aktualisiereSessionScreenWerte();
void updateAktivenScreen();
void setNewScreen(Screen neuerScreen);

uint16_t gpsColor();

#endif