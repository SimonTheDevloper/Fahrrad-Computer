#include "display/display_config.h"

bool highContrastAktiv = false;

uint16_t FARBE_HINTERGRUND;
uint16_t FARBE_TEXT;
uint16_t FARBE_LINIEN;
uint16_t FARBE_SPEED;
uint16_t FARBE_EINHEITEN;
uint16_t FARBE_WERTE;

uint16_t FARBE_BUTTON;
uint16_t FARBE_BUTTON_TEXT;

uint16_t FARBE_KACHEL_RAND;
uint16_t FARBE_KACHEL_AUSSEN;
uint16_t FARBE_KACHEL_INNEN;
uint16_t FARBE_ICON;

uint16_t FARBE_TOGGLE_AN;
uint16_t FARBE_TOGGLE_AUS;
uint16_t FARBE_TOGGLE_KNOPF;

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

void ladeFarbTheme()
{
    if (highContrastAktiv)
    {
        FARBE_HINTERGRUND = 0x0000;
        FARBE_TEXT = 0xFFFF;
        FARBE_LINIEN = 0xFFFF;
        FARBE_SPEED = 0xFFE0;
        FARBE_EINHEITEN = 0x07FF;
        FARBE_WERTE = 0xFFE0;

        FARBE_BUTTON = 0xFFFF;
        FARBE_BUTTON_TEXT = 0x0000;

        FARBE_KACHEL_RAND = 0xFFFF;
        FARBE_KACHEL_AUSSEN = 0xFFFF;
        FARBE_KACHEL_INNEN = 0x0000;

        FARBE_ICON = 0xFFFF;

        FARBE_TOGGLE_AN = 0xFFFF;
        FARBE_TOGGLE_AUS = 0x7BEF;
        FARBE_TOGGLE_KNOPF = 0x0000;
    }
    else
    {
        FARBE_HINTERGRUND = 0x0000;
        FARBE_TEXT = 0xFFFF;
        FARBE_LINIEN = 0x73AF;
        FARBE_SPEED = 0xFF8D;
        FARBE_EINHEITEN = 0xFDED;
        FARBE_WERTE = 0xE521;

        FARBE_BUTTON = FARBE_WERTE;
        FARBE_BUTTON_TEXT = FARBE_HINTERGRUND;

        FARBE_KACHEL_RAND = 0x2924;
        FARBE_KACHEL_AUSSEN = 0x2924;
        FARBE_KACHEL_INNEN = 0x18A1;

        FARBE_ICON = 0x07EA;

        FARBE_TOGGLE_AN = 0x07E0;
        FARBE_TOGGLE_AUS = 0x4228;
        FARBE_TOGGLE_KNOPF = 0xFFFF;
    }
}
