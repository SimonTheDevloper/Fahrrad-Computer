#ifndef DISPLAY_UI_H
#define DISPLAY_UI_H

#include <Arduino.h>
#include <TFT_eSPI.h>

extern TFT_eSPI tft;
enum Screen // macht einen neuen Datentyp Screen wo man dann mehrer zustände definieren kann was Screen sein kann
{
    SCREEN_MAIN, // so kann man mit Wörtern auch Zahlen machen. Intern würde hier 0 stehen
    SCREEN_SESSION,
    SCREEN_MENU
};
extern Screen aktiverScreen;

void initDisplay();
void zeichneGrundLayout();
void aktualisiereWerte();
void zeichneSessionLayout();
void aktualisiereSessionScreenWerte();
void updateAktivenScreen();
void setNewScreen(Screen neuerScreen);
bool pruefeStartButton(uint16_t x, uint16_t y);
bool pruefeWeiterButton(uint16_t x, uint16_t y);
bool pruefeStoppButton(uint16_t x, uint16_t y);
bool pruefeNavigationButton(uint16_t x, uint16_t y);
void zeigeZweiButtons();
void zeichneMenuLayout();
void handleMenuTouch(uint16_t x, uint16_t y);
void verarbeiteGesamtenTouch(uint16_t x, uint16_t y);
void handleMainTouch(uint16_t x, uint16_t y);
uint16_t gpsColor();

#endif