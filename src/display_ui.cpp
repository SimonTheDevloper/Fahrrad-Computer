#include "display_ui.h"
#include "gps_manager.h"
#include "trip_computer.h"

TFT_eSPI tft = TFT_eSPI();
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
void zeichneGrundLayout()
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