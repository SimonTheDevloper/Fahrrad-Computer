#include "display/display_config.h"

const uint16_t FARBE_HINTERGRUND = 0x0000; // Schwarz
const uint16_t FARBE_TEXT_WEISS = 0xFFFF;  // Weiß
const uint16_t FARBE_LINIEN = 0x73AF;      // Grau
const uint16_t FARBE_SPEED = 0xFF8D;       // Orange
const uint16_t FARBE_EINHEITEN = 0xFDED;   // Helles Graublau
const uint16_t FARBE_WERTE = 0xE521;       // Goldgelb

const int BTN_X = 80;
const int BTN_Y = 180;
const int BTN_BREITE = 160;
const int BTN_HOEHE = 45;
const int BTN_RADIUS = 8;

const int BTN_WEITER_X = 18;
const int BTN_WEITER_BREITE = 175;

const int BTN_STOPP_X = 220;
const int BTN_STOPP_BREITE = 80;

const int BTN_NAV_X = 5;
const int BTN_NAV_Y = 2;
const int BTN_NAV_BREITE = 85;
const int BTN_NAV_HOEHE = 20;
const int BTN_NAV_RADIUS = 4;

bool highContrastAktiv = false;
