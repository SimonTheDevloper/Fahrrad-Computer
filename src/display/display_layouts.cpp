#include <TFT_eSPI.h>
#include "display/display_ui.h"
#include "bitmaps.h"
#include "Org_01.h"

void zeichneLiveDataLayout()
{
    tft.fillScreen(FARBE_HINTERGRUND);

    tft.fillRoundRect(5, 1, 23, 18, 3, 0xE300);
    tft.drawBitmap(7, 3, image_Pin_arrow_left_bits, 18, 14, 0xFFFF);

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

    tft.drawBitmap(230, 4, image_Celsius__Streamline_Micro_bits, 12, 12, FARBE_EINHEITEN);

    tft.setTextColor(FARBE_TEXT);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.setTextSize(1);
    tft.drawString("Speed", 70, 34);

    tft.setTextColor(FARBE_EINHEITEN);
    tft.setFreeFont(&FreeSerif12pt7b);
    tft.drawString("km/h", 70, 195);

    tft.setTextColor(FARBE_TEXT);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("Mileage", 220, 34);

    tft.setTextColor(FARBE_EINHEITEN);
    tft.drawString("km", 265, 62);

    tft.setTextColor(FARBE_TEXT);
    tft.drawString("Total Time", 205, 105);

    tft.setTextColor(FARBE_TEXT);
    tft.setFreeFont(&FreeSerif9pt7b);
    tft.drawString("Max", 238, 176);

    tft.setTextColor(FARBE_EINHEITEN);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("km/h", 258, 205);

    tft.setTextColor(FARBE_LINIEN);
    tft.setFreeFont(NULL);
    tft.drawString("v0.4", 292, 229);
}

void zeichneSessionLayout()
{
    tft.fillScreen(FARBE_HINTERGRUND);

    tft.fillRoundRect(5, 1, 23, 18, 3, 0xE300);
    tft.drawBitmap(7, 3, image_Pin_arrow_left_bits, 18, 14, 0xFFFF);
    tft.setTextSize(1);
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

    tft.setTextColor(FARBE_TEXT);
    tft.setFreeFont(&FreeSerif9pt7b);
    tft.drawString("Session Dist", 20, 35);

    tft.setTextColor(FARBE_EINHEITEN);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("km", 70, 60);

    tft.setTextColor(FARBE_TEXT);
    tft.drawString("Session Time", 180, 35);

    tft.drawLine(1, 95, 319, 95, FARBE_LINIEN);

    tft.setTextColor(FARBE_TEXT);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("Avg Speed", 20, 110);

    tft.setTextColor(FARBE_EINHEITEN);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("km/h", 70, 135);

    tft.setTextColor(FARBE_TEXT);
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

void zeichneMenuLayout()
{
    tft.fillScreen(FARBE_HINTERGRUND);

    tft.fillRoundRect(14, 48, 92, 86, 4, FARBE_KACHEL_AUSSEN);
    tft.drawRoundRect(114, 48, 92, 86, 4, FARBE_LINIEN);
    tft.drawRoundRect(214, 48, 92, 86, 4, FARBE_LINIEN);
    tft.fillRoundRect(16, 50, 88, 82, 4, FARBE_KACHEL_INNEN);
    tft.drawRoundRect(14, 142, 92, 86, 4, FARBE_LINIEN);
    tft.drawLine(14, 40, 306, 40, FARBE_LINIEN);
    tft.drawRoundRect(114, 142, 92, 86, 4, FARBE_LINIEN);
    tft.drawRoundRect(214, 142, 92, 86, 4, FARBE_LINIEN);

    tft.setTextColor(FARBE_SPEED);
    tft.setTextSize(1);
    tft.setFreeFont(&FreeMonoBold12pt7b);
    tft.drawString("BIKE Computer", 42, 11);

    tft.fillRoundRect(14, 48, 92, 86, 4, FARBE_KACHEL_AUSSEN);
    tft.fillRoundRect(16, 50, 88, 82, 4, FARBE_KACHEL_INNEN);
    tft.fillRoundRect(114, 48, 92, 86, 4, FARBE_KACHEL_AUSSEN);
    tft.fillRoundRect(116, 50, 88, 82, 4, FARBE_KACHEL_INNEN);
    tft.fillRoundRect(214, 48, 92, 86, 4, FARBE_KACHEL_AUSSEN);
    tft.fillRoundRect(216, 50, 88, 82, 4, FARBE_KACHEL_INNEN);

    tft.setTextColor(FARBE_TEXT);
    tft.setFreeFont(&Org_01);
    tft.drawString("MENU 3", 237, 91);

    tft.fillRoundRect(14, 142, 92, 86, 4, FARBE_KACHEL_AUSSEN);
    tft.fillRoundRect(16, 144, 88, 82, 4, FARBE_KACHEL_INNEN);
    tft.setFreeFont(&FreeSerif9pt7b);
    tft.drawString("Navigation", 20, 208);

    tft.fillRoundRect(114, 142, 92, 86, 4, FARBE_KACHEL_AUSSEN);
    tft.fillRoundRect(116, 144, 88, 82, 4, FARBE_KACHEL_INNEN);
    tft.fillRoundRect(214, 142, 92, 86, 4, FARBE_KACHEL_AUSSEN);
    tft.fillRoundRect(216, 144, 88, 82, 4, FARBE_KACHEL_INNEN);

    tft.setFreeFont(&Org_01);
    tft.drawString("MENU 6", 234, 181);

    tft.setFreeFont(&FreeSerif9pt7b);
    tft.drawString("Session-", 24, 102);
    tft.drawString("record", 53, 116);
    tft.drawString("Live Data", 123, 115);
    tft.drawString("Settings", 130, 208);

    tft.drawBitmap(46, 60, image_paint_3_bits, 28, 28, FARBE_ICON);
    tft.drawBitmap(146, 60, image_paint_3_bits, 28, 28, FARBE_ICON);
    tft.drawBitmap(246, 60, image_paint_3_bits, 28, 28, FARBE_ICON);
    tft.drawBitmap(46, 154, image_paint_3_bits, 28, 28, FARBE_ICON);
    tft.drawBitmap(146, 154, image_paint_3_bits, 28, 28, FARBE_LINIEN);
    tft.drawBitmap(236, 150, image_paint_21_bits, 16, 16, FARBE_LINIEN);
    tft.drawBitmap(46, 154, image_paint_3_bits, 28, 28, FARBE_ICON);
    tft.drawBitmap(252, 154, image_paint_21_bits, 16, 16, FARBE_LINIEN);

    tft.drawBitmap(28, 148, image_paint_42_bits, 60, 60, FARBE_TEXT);
    tft.drawBitmap(132, 52, image_speedometer_bits, 55, 55, FARBE_TEXT);
    tft.drawBitmap(35, 50, image_paint_45_bits, 50, 50, FARBE_TEXT);
    tft.drawBitmap(130, 147, image_settings_bits, 57, 57, FARBE_TEXT);
    tft.drawBitmap(10, 8, image_bike_bits, 24, 24, FARBE_TEXT);
}
void zeichneMenuLayoutHighKontrast()
{
    tft.fillScreen(0x0000);

    tft.drawLine(14, 40, 306, 40, 0x7BEF);

    tft.fillRoundRect(14, 48, 92, 86, 4, 0xFFFF);
    tft.drawRoundRect(114, 48, 92, 86, 4, 0xFFFF);
    tft.drawRoundRect(214, 48, 92, 86, 4, 0xFFFF);
    tft.fillRoundRect(16, 50, 88, 82, 4, 0x2104);

    tft.drawRoundRect(14, 142, 92, 86, 4, 0xFFFF);
    tft.drawLine(14, 40, 306, 40, 0x7BEF);
    tft.drawRoundRect(114, 142, 92, 86, 4, 0xFFFF);
    tft.drawRoundRect(214, 142, 92, 86, 4, 0xFFFF);

    tft.setTextColor(0xFFFF);
    tft.setTextSize(1);
    tft.setFreeFont(&FreeMonoBold12pt7b);
    tft.drawString("BIKE Computer", 42, 11);

    tft.fillRoundRect(14, 48, 92, 86, 4, 0xFFFF);
    tft.fillRoundRect(16, 50, 88, 82, 4, 0x2104);
    tft.fillRoundRect(114, 48, 92, 86, 4, 0xFFFF);
    tft.fillRoundRect(116, 50, 88, 82, 4, 0x2104);
    tft.fillRoundRect(214, 48, 92, 86, 4, 0xFFFF);
    tft.fillRoundRect(216, 50, 88, 82, 4, 0x2104);

    tft.setTextColor(0xFFFF);
    tft.setFreeFont(&Org_01);
    tft.drawString("MENU 3", 237, 91);

    tft.fillRoundRect(14, 142, 92, 86, 4, 0xFFFF);
    tft.fillRoundRect(16, 144, 88, 82, 4, 0x2104);
    tft.setFreeFont(&FreeSerif9pt7b);
    tft.drawString("Navigation", 20, 208);

    tft.fillRoundRect(114, 142, 92, 86, 4, 0xFFFF);
    tft.fillRoundRect(116, 144, 88, 82, 4, 0x2104);
    tft.fillRoundRect(214, 142, 92, 86, 4, 0xFFFF);
    tft.fillRoundRect(216, 144, 88, 82, 4, 0x2104);

    tft.setFreeFont(&Org_01);
    tft.drawString("MENU 6", 234, 181);

    tft.setFreeFont(&FreeSerif9pt7b);
    tft.drawString("Session-", 24, 102);
    tft.drawString("record", 53, 116);
    tft.drawString("Live Data", 123, 115);
    tft.drawString("Settings", 130, 208);

    tft.drawBitmap(46, 60, image_paint_3_bits, 28, 28, 0xFFFF);
    tft.drawBitmap(146, 60, image_paint_3_bits, 28, 28, 0xFFFF);
    tft.drawBitmap(246, 60, image_paint_3_bits, 28, 28, 0xFFFF);
    tft.drawBitmap(46, 154, image_paint_3_bits, 28, 28, 0xFFFF);
    tft.drawBitmap(146, 154, image_paint_3_bits, 28, 28, 0xFFFF);
    tft.drawBitmap(236, 150, image_paint_21_bits, 16, 16, 0xFFFF);
    tft.drawBitmap(46, 154, image_paint_3_bits, 28, 28, 0xFFFF);
    tft.drawBitmap(252, 154, image_paint_21_bits, 16, 16, 0xFFFF);

    tft.drawBitmap(28, 148, image_paint_42_bits, 60, 60, 0xFFFF);
    tft.drawBitmap(132, 52, image_speedometer_bits, 55, 55, 0xFFFF);
    tft.drawBitmap(35, 50, image_paint_45_bits, 50, 50, 0xFFFF);
    tft.drawBitmap(130, 147, image_settings_bits, 57, 57, 0xFFFF);
    tft.drawBitmap(10, 8, image_bike_bits, 24, 24, 0xFFFF);
}
void zeichneToggleButton(int x, int y, bool aktiv)
{
    const int trackBreite = 50;
    const int trackHoehe = 26;
    const int trackRadius = 13;
    const int thumbDurchmesser = 22;

    uint16_t trackFarbe = aktiv ? 0x07E0 : FARBE_LINIEN;
    uint16_t thumbFarbe = 0xFFFF;

    tft.fillRoundRect(x, y, trackBreite, trackHoehe, trackRadius, trackFarbe);
    tft.drawRoundRect(x, y, trackBreite, trackHoehe, trackRadius, TFT_WHITE);

    int thumbX = aktiv ? x + trackBreite - thumbDurchmesser - 2 : x + 2;
    int thumbY = y + (trackHoehe - thumbDurchmesser) / 2;
    tft.fillCircle(thumbX + thumbDurchmesser / 2, thumbY + thumbDurchmesser / 2,
                   thumbDurchmesser / 2, thumbFarbe);
}

void zeichneSettingsLayout()
{
    tft.fillScreen(FARBE_HINTERGRUND);

    tft.fillRoundRect(5, 1, 23, 18, 3, 0xE300);
    tft.drawBitmap(7, 3, image_Pin_arrow_left_bits, 18, 14, 0xFFFF);

    tft.setTextColor(FARBE_TEXT);
    tft.setFreeFont(&FreeSansBold9pt7b);
    tft.setTextSize(1);
    tft.setTextDatum(TC_DATUM);
    tft.drawString("Settings", 160, 8);
    tft.setTextDatum(TL_DATUM);

    tft.drawLine(1, 24, 319, 24, FARBE_LINIEN);

    tft.setTextColor(FARBE_TEXT);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("High Contrast", 20, 40);

    tft.drawLine(10, 68, 310, 68, FARBE_LINIEN);
}
