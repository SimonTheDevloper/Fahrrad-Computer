#include <TFT_eSPI.h>
#include "display_ui.h"
#include "gps_manager.h"
#include "trip_computer.h"

const uint16_t FARBE_HINTERGRUND = 0x0000; // Schwarz
const uint16_t FARBE_TEXT_WEISS = 0xFFFF;  // Weiß
const uint16_t FARBE_LINIEN = 0x73AF;      // Grau
const uint16_t FARBE_SPEED = 0xFF8D;       // Orange
const uint16_t FARBE_EINHEITEN = 0xFDED;   // Helles Graublau
const uint16_t FARBE_WERTE = 0xE521;       // Goldgelb

extern double meterToKm(double meter);
extern String formatTime(unsigned long sek);

TFT_eSPI tft = TFT_eSPI();

void initDisplay()
{
    tft.init();
    tft.setRotation(3);
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

    tft.setTextColor(FARBE_TEXT_WEISS);
    tft.setFreeFont(NULL);
    tft.setTextSize(2);

    if (TEST_MODE)
    {
        tft.drawString("TEST MODE", 5, 5);
    }
    else
    {
        tft.drawString("Bike Computer", 5, 5);
    }

    tft.drawLine(1, 24, 319, 24, FARBE_LINIEN);
    tft.drawLine(195, 1, 195, 239, FARBE_LINIEN);
    tft.drawLine(195, 95, 319, 95, FARBE_LINIEN);
    tft.drawLine(195, 166, 319, 166, FARBE_LINIEN);

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

    int speedInt = (int)speed; // dadurch gehen die kommazahlen weg
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
