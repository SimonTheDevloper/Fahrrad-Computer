#ifndef DISPLAY_UI_H
#define DISPLAY_UI_H

#include <Arduino.h>

class TFT_eSPI;
extern TFT_eSPI tft;
extern enum Screen;

void initDisplay();
void zeichneGrundLayout();
void aktualisiereWerte();
void zeichneSessionLayout();
void aktualisiereSessionScreenWerte();
void updateAktivenScreen();
void setNewScreen(String neuerScreen);

uint16_t gpsColor();

#endif