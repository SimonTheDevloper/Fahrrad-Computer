#include <TFT_eSPI.h>
#include "display_ui.h"
#include "gps_manager.h"
#include "trip_computer.h"

const uint16_t FARBE_HINTERGRUND = 0x0000; // Schwarz
const uint16_t FARBE_TEXT_WEISS = 0xFFFF;  // Weiß
const uint16_t FARBE_LINIEN = 0x73AF;      // Grau
const uint16_t FARBE_SPEED = 0xFF8D;       // Orange
const uint16_t FARBE_EINHEITEN = 0xFDED;   // Helles Graublau
const uint16_t FARBE_WERTE = 0xE521;       // Gold-Gelb

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

void drawLabel(int x, int y, const char *label, uint16_t color)
{
    tft.setTextColor(color, TFT_BLACK);
    tft.setCursor(x, y);
    tft.print(label);
}

void drawValue(int x, int y, String value, uint16_t color)
{
    tft.setTextColor(color, TFT_BLACK);
    tft.setCursor(x, y);
    tft.print(value);
}

void zeichneGrundLayout(void)
{
    tft.fillScreen(FARBE_HINTERGRUND);

    // Statusbar
    tft.setTextColor(FARBE_TEXT_WEISS);
    tft.setTextSize(1);
    tft.setFreeFont(NULL); // Standard-Schriftart für die Statusbar
    tft.setTextSize(2);
    if (TEST_MODE)
    {
        tft.drawString("TEST MODE", 5, 5);
    }
    else
    {
        tft.drawString("Bike Computer", 5, 5);
    }

    // tft.drawString("13:44", 275, 5);

    // Trennlinie
    tft.drawLine(1, 16, 319, 16, FARBE_LINIEN);
    tft.drawLine(195, 1, 195, 239, FARBE_LINIEN);
    tft.drawLine(195, 80, 319, 80, FARBE_LINIEN);
    tft.drawLine(195, 160, 319, 160, FARBE_LINIEN);

    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("Speed", 70, 28);

    // Große Geschwindigkeits Zahl
    // tft.setTextColor(FARBE_SPEED);
    // tft.setTextSize(8);
    // tft.setFreeFont(&FreeSansBold9pt7b);
    // tft.drawString("23", 17, 60);

    // Einheit "km/h"
    tft.setTextColor(FARBE_EINHEITEN);
    tft.setTextSize(1);
    tft.setFreeFont(&FreeSerif12pt7b);
    tft.drawString("km/h", 70, 189);

    tft.setTextColor(FARBE_TEXT_WEISS);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("Mileage", 220, 25);

    // Wert für Kilometerstand
    // tft.setTextColor(FARBE_WERTE);
    // tft.setFreeFont(&FreeSansBold9pt7b);
    // tft.drawString("322.1", 210, 55);

    tft.setTextColor(FARBE_EINHEITEN);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("km", 255, 55);

    tft.setTextColor(FARBE_TEXT_WEISS);
    tft.drawString("Total Time", 205, 100);

    // tft.setTextColor(FARBE_WERTE);
    // tft.drawString("04:59:01", 215, 130);

    tft.setTextColor(FARBE_TEXT_WEISS);
    tft.setFreeFont(&FreeSerif9pt7b);
    tft.drawString("Max", 238, 171);

    // tft.setTextColor(FARBE_WERTE);
    // tft.setFreeFont(&FreeSansBold9pt7b);
    // tft.drawString("35.2", 218, 200);

    tft.setTextColor(FARBE_EINHEITEN);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("km/h", 258, 200);

    tft.setTextColor(FARBE_LINIEN);
    tft.setTextSize(1);
    tft.setFreeFont(NULL);
    tft.drawString("v0.4", 292, 229);
}

/*void zeichneGrundLayout()
{
    tft.fillScreen(TFT_BLACK);

    tft.setTextSize(2);
    if (TEST_MODE)
    {
        drawLabel(10, 5, "TEST MODE", TFT_ORANGE);
    }
    else
    {
        drawLabel(10, 5, "BIKE COMPUTER", TFT_WHITE);
    }
    drawLabel(10, 225, "TIME", TFT_DARKGREY);
    tft.drawFastHLine(0, 30, 320, TFT_DARKGREY);
    tft.setTextSize(4);
    drawLabel(10, 45, "SPEED", TFT_DARKGREY);

    tft.setTextSize(2);
    drawValue(10, 115, "MAX " + String(maxSpeed, 1) + " km/h   ", TFT_YELLOW);
    drawLabel(10, 150, "ALT", TFT_DARKGREY);
    drawLabel(10, 175, "LAT", TFT_DARKGREY);
    drawLabel(10, 200, "LON", TFT_DARKGREY);

    tft.setTextSize(1);
    drawLabel(270, 225, "v0.3", TFT_DARKGREY);
}
*/
void aktualisiereWerte()
{
    bekommeUhrzeit();
    tft.setTextSize(2);
    String satText = "Sats: " + String(satellites) + "   ";
    drawValue(220, 5, satText, gpsColor());

    tft.setTextSize(4);
    drawValue(10, 85, String(speed, 1) + " km/h   ", TFT_CYAN);

    tft.setTextSize(2);
    drawValue(10, 115, "MAX " + String(maxSpeed, 1) + " km/h   ", TFT_YELLOW);
    drawValue(80, 150, String(altitude, 0) + " m    ", TFT_WHITE);
    drawValue(80, 175, String(latitude, 5) + "    ", TFT_WHITE);
    drawValue(80, 200, String(longitude, 5) + "    ", TFT_WHITE);

    drawValue(120, 225, uhrzeit, TFT_GREEN);
}