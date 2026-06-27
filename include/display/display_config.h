#ifndef DISPLAY_CONFIG_H
#define DISPLAY_CONFIG_H

#include <Arduino.h>
#include <TFT_eSPI.h>

extern const uint16_t FARBE_HINTERGRUND;
extern const uint16_t FARBE_TEXT_WEISS;
extern const uint16_t FARBE_LINIEN;
extern const uint16_t FARBE_SPEED;
extern const uint16_t FARBE_EINHEITEN;
extern const uint16_t FARBE_WERTE;

extern const int BTN_X;
extern const int BTN_Y;
extern const int BTN_BREITE;
extern const int BTN_HOEHE;
extern const int BTN_RADIUS;

extern const int BTN_WEITER_X;
extern const int BTN_WEITER_BREITE;

extern const int BTN_STOPP_X;
extern const int BTN_STOPP_BREITE;

extern const int BTN_NAV_X;
extern const int BTN_NAV_Y;
extern const int BTN_NAV_BREITE;
extern const int BTN_NAV_HOEHE;
extern const int BTN_NAV_RADIUS;

#define SETTINGS_ROW_H 48     // Höhe einer Settings-Zeile
#define SETTINGS_ROW_START 35 // Y-Start erste Zeile (nach Header-Linie)
#define SETTINGS_LABEL_X 18   // X-Position der Labels
#define SETTINGS_TOGGLE_X 255 // X-Position der Toggle-Buttons (rechtsbündig)
#define SETTINGS_TOGGLE_W 52  // Toggle-Breite
#define SETTINGS_TOGGLE_H 26  // Toggle-Höhe
#define SETTINGS_TOGGLE_R 13  // Toggle Border-Radius (= halbe Höhe → Pill-Form)

// Toggle-Farben
#define FARBE_TOGGLE_AN 0x07E0    // Grün  → AN
#define FARBE_TOGGLE_AUS 0x4228   // Grau  → AUS
#define FARBE_TOGGLE_KNOPF 0xFFFF // Weiß  → Schieber-Kreis

extern bool highContrastAktiv;

#endif
