#ifndef DISPLAY_UI_H
#define DISPLAY_UI_H

#include <Arduino.h>

class TFT_eSPI;
extern TFT_eSPI tft;

void initDisplay();
void drawLabel(int x, int y, const char *label, uint16_t color);
void drawValue(int x, int y, String value, uint16_t color);
void drawScreen_1();
void zeichneGrundLayout();
void aktualisiereWerte();
uint16_t gpsColor();

#endif