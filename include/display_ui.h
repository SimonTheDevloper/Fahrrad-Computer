#ifndef DISPLAY_UI_H
#define DISPLAY_UI_H

#include <Arduino.h>

class TFT_eSPI;
extern TFT_eSPI tft;

void initDisplay();
void zeichneGrundLayout();
void aktualisiereWerte();
void zeichneSessionLayout();
void aktualisiereSessionScreenWerte();

uint16_t gpsColor();

#endif