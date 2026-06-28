#ifndef DISPLAY_CONFIG_H
#define DISPLAY_CONFIG_H

#include <Arduino.h>

extern uint16_t FARBE_HINTERGRUND;
extern uint16_t FARBE_TEXT;
extern uint16_t FARBE_LINIEN;
extern uint16_t FARBE_SPEED;
extern uint16_t FARBE_EINHEITEN;
extern uint16_t FARBE_WERTE;
extern uint16_t FARBE_BUTTON;
extern uint16_t FARBE_BUTTON_TEXT;

extern const int BTN_X;
extern const int BTN_Y;
extern const int BTN_BREITE;
extern const int BTN_HOEHE;
extern const int BTN_RADIUS;

extern const int BTN_WEITER_X;
extern const int BTN_WEITER_BREITE;

extern const int BTN_STOPP_X;
extern const int BTN_STOPP_BREITE;

extern uint16_t FARBE_KACHEL_RAND; // fürs Menü sadsad
extern uint16_t FARBE_KACHEL_AUSSEN;
extern uint16_t FARBE_KACHEL_INNEN;
extern uint16_t FARBE_ICON;

extern uint16_t FARBE_TOGGLE_AN;
extern uint16_t FARBE_TOGGLE_AUS;
extern uint16_t FARBE_TOGGLE_KNOPF;

extern const int BTN_NAV_X;
extern const int BTN_NAV_Y;
extern const int BTN_NAV_BREITE;
extern const int BTN_NAV_HOEHE;
extern const int BTN_NAV_RADIUS;

void ladeFarbTheme();

extern bool highContrastAktiv;

#endif
