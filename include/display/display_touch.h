#ifndef DISPLAY_TOUCH_H
#define DISPLAY_TOUCH_H

#include <Arduino.h>
#include <TFT_eSPI.h>

bool pruefeStartButton(uint16_t x, uint16_t y);
bool pruefeWeiterButton(uint16_t x, uint16_t y);
bool pruefeStoppButton(uint16_t x, uint16_t y);
bool pruefeNavigationButton(uint16_t x, uint16_t y);
void zeigeZweiButtons();
void handleMenuTouch(uint16_t x, uint16_t y);
void handleMainTouch(uint16_t x, uint16_t y);
void handleSessionTouch(uint16_t x, uint16_t y);
bool darfTouchVerarbeitetWerden();
void verarbeiteGesamtenTouch(uint16_t x, uint16_t y);

#endif
