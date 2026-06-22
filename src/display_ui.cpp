#include <TFT_eSPI.h>
#include "display_ui.h"
#include "gps_manager.h"
#include "trip_computer.h"
#include "ride_session.h"

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

extern double meterToKm(double meter);
extern String formatTime(unsigned long sek);

TFT_eSPI tft = TFT_eSPI();

Screen aktiverScreen = SCREEN_SESSION;

void initDisplay()
{
    tft.init();
    tft.setRotation(3);

    uint16_t calData[5] = {275, 3620, 264, 3532, 1}; // fürs kalibrieren
    tft.setTouch(calData);
}

extern const bool TEST_MODE;

uint16_t gpsColor()
{
    if (satellites >= 6)
        return TFT_GREEN;
    if (satellites >= 3)
        return TFT_ORANGE;
    return TFT_RED;
}

void zeichneGrundLayout(void)
{
    tft.fillScreen(FARBE_HINTERGRUND);

    tft.fillRoundRect(BTN_NAV_X, BTN_NAV_Y, BTN_NAV_BREITE, BTN_NAV_HOEHE, BTN_NAV_RADIUS, FARBE_EINHEITEN);
    tft.setTextColor(FARBE_HINTERGRUND);
    tft.setFreeFont(NULL);
    tft.setTextSize(1);
    tft.drawString("SESSION >", BTN_NAV_X + 14, BTN_NAV_Y + 6);

    if (TEST_MODE)
    {
        tft.setTextColor(TFT_RED);
        tft.setTextSize(1);
        tft.drawString("TEST", 100, 6);
    }

    tft.drawLine(1, 24, 319, 24, FARBE_LINIEN);
    tft.drawLine(195, 1, 195, 239, FARBE_LINIEN);
    tft.drawLine(195, 95, 319, 95, FARBE_LINIEN);
    tft.drawLine(195, 166, 319, 166, FARBE_LINIEN);

    tft.setTextColor(FARBE_TEXT_WEISS);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.setTextSize(1);
    tft.drawString("Speed", 70, 34);

    tft.setTextColor(FARBE_EINHEITEN);
    tft.setFreeFont(&FreeSerif12pt7b);
    tft.drawString("km/h", 70, 195);

    tft.setTextColor(FARBE_TEXT_WEISS);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("Mileage", 220, 34);

    tft.setTextColor(FARBE_EINHEITEN);
    tft.drawString("km", 265, 62);

    tft.setTextColor(FARBE_TEXT_WEISS);
    tft.drawString("Total Time", 205, 105);

    tft.setTextColor(FARBE_TEXT_WEISS);
    tft.setFreeFont(&FreeSerif9pt7b);
    tft.drawString("Max", 238, 176);

    tft.setTextColor(FARBE_EINHEITEN);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("km/h", 258, 205);

    tft.setTextColor(FARBE_LINIEN);
    tft.setFreeFont(NULL);
    tft.drawString("v0.4", 292, 229);
}

void aktualisiereWerte()
{
    static String letzteUhrzeit = ""; // Wie eine globale Variable, die aber sicher verpackt nur innerhalb dieser Funktion existiert
    static int letztesSpeedInt = -1;
    static String letzteGesamtStrecke = "";
    static String letzteGesamtFahrzeit = "";
    static String letztesMaxSpeed = "";

    bekommeUhrzeit();

    tft.setFreeFont(NULL);
    tft.setTextSize(2);
    tft.setTextColor(FARBE_TEXT_WEISS, FARBE_HINTERGRUND);
    if (letzteUhrzeit != String(uhrzeit))
    {
        tft.drawString(uhrzeit, 260, 5);

        letzteUhrzeit = String(uhrzeit);
    }

    tft.setTextColor(FARBE_SPEED);
    tft.setTextSize(6);
    tft.setFreeFont(&FreeSansBold9pt7b);

    int speedInt = (int)currentSpeed; // dadurch gehen die kommazahlen weg
    String speedText = String(speedInt);

    if (letztesSpeedInt != speedInt)
    {
        tft.fillRect(5, 50, 165, 110, FARBE_HINTERGRUND);

        if (speedInt < 10)
        {
            tft.drawString(speedText, 50, 70);
        }
        else
        {
            tft.drawString(speedText, 25, 70);
        }
        letztesSpeedInt = speedInt;
    }

    tft.setTextSize(1);
    tft.setFreeFont(&FreeSansBold9pt7b);
    tft.setTextColor(FARBE_WERTE, FARBE_HINTERGRUND);

    String kmText = String(meterToKm(gesamtStrecke), 1);
    if (letzteGesamtStrecke != kmText)
    {
        tft.drawString(kmText, 205, 62);

        letzteGesamtStrecke = kmText;
    }

    String zeitText = formatTime(gesamtFahrtZeit);
    if (letzteGesamtFahrzeit != zeitText)
    {
        tft.drawString(zeitText, 205, 133);

        letzteGesamtFahrzeit = zeitText;
    }

    String maxSpeedText = String(maxSpeed, 1);

    if (letztesMaxSpeed != maxSpeedText)
    {

        tft.drawString(maxSpeedText, 205, 205);

        letztesMaxSpeed = maxSpeedText;
    }
}

void aktualisiereSessionScreenWerte()
{
    static String letzteDistanz = "";
    static String letzteZeit = "";
    static String letzterAvgSpeed = "";
    static String letzterMaxSpeed = "";
    static FahrtSate letzterState = UNBEKANNT;

    String distanzText = String(meterToKm(sessionStrecke), 1);

    if (distanzText != letzteDistanz)
    {
        tft.fillRect(20, 50, 40, 25, FARBE_HINTERGRUND);

        tft.setTextColor(FARBE_WERTE);
        tft.setFreeFont(&FreeSansBold9pt7b);
        tft.drawString(distanzText, 20, 60);

        letzteDistanz = distanzText;
    }

    String zeitText = formatTime(sessionFahrtZeit);

    if (zeitText != letzteZeit)
    {
        tft.fillRect(180, 50, 120, 25, FARBE_HINTERGRUND);

        tft.setTextColor(FARBE_WERTE);
        tft.setFreeFont(&FreeSansBold9pt7b);
        tft.drawString(zeitText, 180, 60);

        letzteZeit = zeitText;
    }

    String avgText = String(sessionAvgSpeed, 1);

    if (avgText != letzterAvgSpeed)
    {
        tft.fillRect(20, 129, 40, 22, FARBE_HINTERGRUND);

        tft.setTextColor(FARBE_WERTE);
        tft.setFreeFont(&FreeSansBold9pt7b);
        tft.drawString(avgText, 20, 135);

        letzterAvgSpeed = avgText;
    }
    String maxText = String(sessionMaxSpeed, 1);

    if (maxText != letzterMaxSpeed)
    {
        tft.fillRect(180, 125, 40, 25, FARBE_HINTERGRUND);

        tft.setTextColor(FARBE_WERTE);
        tft.setFreeFont(&FreeSansBold9pt7b);
        tft.drawString(maxText, 180, 135);

        letzterMaxSpeed = maxText;
    }

    if (aktivFahrtState != letzterState)
    {
        tft.fillRect(BTN_WEITER_X, BTN_Y, 310, BTN_HOEHE, FARBE_HINTERGRUND);

        uint16_t btnFarbe;
        String btnText;
        int btnX;

        switch (aktivFahrtState)
        {
        case GESTOPPT:
            btnFarbe = FARBE_WERTE;
            btnText = "START";
            btnX = 80;

            tft.fillRoundRect(btnX, BTN_Y, 160, BTN_HOEHE, BTN_RADIUS, btnFarbe);
            tft.setTextColor(FARBE_HINTERGRUND);
            tft.setFreeFont(&FreeSansBold9pt7b);
            tft.setTextDatum(MC_DATUM);
            tft.drawString(btnText, btnX + 80, BTN_Y + BTN_HOEHE / 2);
            tft.setTextDatum(TL_DATUM);
            break;

        case LAEUFT:
            btnFarbe = TFT_RED;
            btnText = "PAUSE";
            btnX = 80;

            tft.fillRoundRect(btnX, BTN_Y, 160, BTN_HOEHE, BTN_RADIUS, btnFarbe);
            tft.setTextColor(FARBE_HINTERGRUND);
            tft.setFreeFont(&FreeSansBold9pt7b);
            tft.setTextDatum(MC_DATUM);
            tft.drawString(btnText, btnX + 80, BTN_Y + BTN_HOEHE / 2);
            tft.setTextDatum(TL_DATUM);
            break;

        case PAUSIERT:
            zeigeZweiButtons();
            break;

        default:
            btnFarbe = FARBE_WERTE;
            btnText = "START";
            btnX = 80;

            tft.fillRoundRect(btnX, BTN_Y, 160, BTN_HOEHE, BTN_RADIUS, btnFarbe);
            tft.setTextColor(FARBE_HINTERGRUND);
            tft.setFreeFont(&FreeSansBold9pt7b);
            tft.setTextDatum(MC_DATUM);
            tft.drawString(btnText, btnX + 80, BTN_Y + BTN_HOEHE / 2);
            tft.setTextDatum(TL_DATUM);
            break;
        }

        letzterState = aktivFahrtState;
    }
}

void zeigeZweiButtons()
{
    tft.fillRoundRect(
        BTN_WEITER_X,
        BTN_Y,
        BTN_WEITER_BREITE,
        BTN_HOEHE,
        BTN_RADIUS,
        TFT_GREEN);

    tft.setTextColor(FARBE_HINTERGRUND);
    tft.setFreeFont(&FreeSansBold9pt7b);
    tft.setTextDatum(MC_DATUM);

    tft.drawString(
        "Weiter",
        BTN_WEITER_X + BTN_WEITER_BREITE / 2,
        BTN_Y + BTN_HOEHE / 2);

    tft.fillRoundRect(
        BTN_STOPP_X,
        BTN_Y,
        BTN_STOPP_BREITE,
        BTN_HOEHE,
        BTN_RADIUS,
        TFT_RED);

    tft.drawString(
        "STOPP",
        BTN_STOPP_X + BTN_STOPP_BREITE / 2,
        BTN_Y + BTN_HOEHE / 2);

    tft.setTextDatum(TL_DATUM);
}

void zeichneSessionLayout()
{
    tft.fillScreen(FARBE_HINTERGRUND);

    tft.fillRoundRect(BTN_NAV_X, BTN_NAV_Y, BTN_NAV_BREITE, BTN_NAV_HOEHE, BTN_NAV_RADIUS, FARBE_EINHEITEN);
    tft.setTextColor(FARBE_HINTERGRUND);
    tft.setFreeFont(NULL);
    tft.setTextSize(1);
    tft.drawString("< Zurueck", BTN_NAV_X + 14, BTN_NAV_Y + 6);

    if (TEST_MODE)
    {
        tft.fillRect(200, 0, 120, 20, FARBE_HINTERGRUND);
        tft.setTextColor(TFT_ORANGE, FARBE_HINTERGRUND);
        tft.setFreeFont(&FreeSansBold9pt7b);
        tft.setTextDatum(TR_DATUM);
        tft.drawString("Testmode", 315, 3);
        tft.setTextDatum(TL_DATUM);
    }
    else
    {
        tft.fillRect(200, 0, 120, 20, FARBE_HINTERGRUND);
    }

    tft.drawLine(1, 20, 319, 20, FARBE_LINIEN);

    tft.setTextColor(FARBE_TEXT_WEISS);
    tft.setFreeFont(&FreeSerif9pt7b);
    tft.drawString("Session Dist", 20, 35);

    tft.setTextColor(FARBE_EINHEITEN);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("km", 70, 60);

    tft.setTextColor(FARBE_TEXT_WEISS);
    tft.drawString("Session Time", 180, 35);

    tft.drawLine(1, 95, 319, 95, FARBE_LINIEN);

    tft.setTextColor(FARBE_TEXT_WEISS);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("Avg Speed", 20, 110);

    tft.setTextColor(FARBE_EINHEITEN);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("km/h", 70, 135);

    tft.setTextColor(FARBE_TEXT_WEISS);
    tft.drawString("Max Speed", 180, 110);

    tft.setTextColor(FARBE_EINHEITEN);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("km/h", 230, 135);

    tft.drawLine(1, 165, 319, 165, FARBE_LINIEN);

    tft.fillRoundRect(80, BTN_Y, 160, BTN_HOEHE, BTN_RADIUS, FARBE_WERTE);

    tft.setTextColor(FARBE_HINTERGRUND);
    tft.setFreeFont(&FreeSansBold9pt7b);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("START", 160, BTN_Y + BTN_HOEHE / 2);
    tft.setTextDatum(TL_DATUM);
}
void updateAktivenScreen()
{
    switch (aktiverScreen)
    {
    case SCREEN_MAIN:
        aktualisiereWerte();
        break;

    case SCREEN_SESSION:
        aktualisiereSessionScreenWerte();
        break;
    }
}

void setNewScreen(Screen neuerScreen) // hier auch wieder den extra Datentyp nehemn
{
    aktiverScreen = neuerScreen;

    if (aktiverScreen == SCREEN_MAIN)
    {
        zeichneGrundLayout();
    }
    else if (aktiverScreen == SCREEN_SESSION)
    {
        zeichneSessionLayout();
    }
}

bool pruefeStartButton(uint16_t x, uint16_t y)
{
    return (x >= 80 && x <= 240 &&
            y >= BTN_Y && y <= (BTN_Y + BTN_HOEHE));
}

bool pruefeWeiterButton(uint16_t x, uint16_t y)
{
    return (x >= BTN_WEITER_X &&
            x <= (BTN_WEITER_X + BTN_WEITER_BREITE) &&
            y >= BTN_Y &&
            y <= (BTN_Y + BTN_HOEHE));
}

bool pruefeStoppButton(uint16_t x, uint16_t y)
{
    return (x >= BTN_STOPP_X &&
            x <= (BTN_STOPP_X + BTN_STOPP_BREITE) &&
            y >= BTN_Y &&
            y <= (BTN_Y + BTN_HOEHE));
}
