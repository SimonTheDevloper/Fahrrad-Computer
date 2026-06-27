#ifndef DISPLAY_UI_H
#define DISPLAY_UI_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "display_config.h"
#include "display_layouts.h"
#include "display_werte.h"
#include "display_touch.h"

extern TFT_eSPI tft;

enum Screen
{
    SCREEN_MAIN, // so kann man mit Wörtern auch Zahlen mache eigentlich würde hier 0 stehen
    SCREEN_SESSION,
    SCREEN_MENU,
    SCREEN_SETTINGS
};

extern Screen aktiverScreen;
extern bool screenChanged;
extern const bool TEST_MODE;

void initDisplay();
void updateAktivenScreen();
void setNewScreen(Screen neuerScreen);
uint16_t gpsColor();

#endif
