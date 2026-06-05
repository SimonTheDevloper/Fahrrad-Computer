#include <TFT_eSPI.h>
#include "display_ui.h"
#include "gps_manager.h"
#include "trip_computer.h"

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
    tft.fillScreen(0x0);
    // string 1
    tft.setTextColor(0xFFFF);
    tft.setTextSize(1);
    tft.setFreeFont(&FreeSerif9pt7b);
    tft.drawString("Bike Computer", 5, 2);
    // string 2
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("13:44", 266, 2);
    // line 3
    tft.drawLine(1, 20, 319, 20, 0x73AF);
    // line 4
    tft.drawLine(195, 1, 195, 239, 0x73AF);
    // line 5
    tft.drawLine(195, 80, 319, 80, 0x73AF);
    // line 6
    tft.drawLine(195, 160, 319, 160, 0x73AF);
    // string 7
    tft.drawString("Speed", 70, 34);
    // string 8
    tft.setTextColor(0xFF8D);
    tft.setTextSize(8);
    tft.setFreeFont(&FreeSansBold9pt7b);
    tft.drawString("23", 17, 60);
    // string 9
    tft.setTextColor(0xFDED);
    tft.setTextSize(1);
    tft.setFreeFont(&FreeSerif12pt7b);
    tft.drawString("km/h", 70, 189);
    // string 10
    tft.setTextColor(0xFFFF);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("Mileage", 220, 28);
    // string 11
    tft.setTextColor(0xE521);
    tft.setFreeFont(&FreeSansBold9pt7b);
    tft.drawString("322.1", 210, 55);
    // string 12
    tft.setTextColor(0xFDED);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("km", 255, 55);
    // string 13
    tft.setTextColor(0xFFFF);
    tft.drawString("Total Time", 205, 100);
    // string 14
    tft.setTextColor(0xE521);
    tft.drawString("04:59:01", 215, 130);
    // string 15
    tft.setTextColor(0xFFFF);
    tft.setFreeFont(&FreeSerif9pt7b);
    tft.drawString("Max", 238, 171);
    // string 16
    tft.setTextColor(0xE521);
    tft.setFreeFont(&FreeSansBold9pt7b);
    tft.drawString("35.2", 218, 200);
    // string 17
    tft.setTextColor(0xFDED);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("km/h", 258, 200);
    // string 18
    tft.setTextColor(0x73AF);
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