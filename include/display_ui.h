#ifndef DISPLAY_UI_H
#define DISPLAY_UI_H

#include <Arduino.h>
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

void drawLabel(int x, int y, const char *label, uint16_t color);
void drawValue(int x, int y, String value, uint16_t color);
void zeichneGrundLayout();
void aktualisiereWerte();
uint16_t gpsColor();

#endif