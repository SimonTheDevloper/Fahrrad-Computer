#include <TFT_eSPI.h>
#include "display/display_ui.h"
#include "ride_session.h"

void zeigeZweiButtons()
{
    tft.fillRoundRect(BTN_WEITER_X, BTN_Y, BTN_WEITER_BREITE, BTN_HOEHE, BTN_RADIUS, TFT_GREEN);
    tft.setTextColor(FARBE_HINTERGRUND);
    tft.setFreeFont(&FreeSansBold9pt7b);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("Weiter", BTN_WEITER_X + BTN_WEITER_BREITE / 2, BTN_Y + BTN_HOEHE / 2);

    tft.fillRoundRect(BTN_STOPP_X, BTN_Y, BTN_STOPP_BREITE, BTN_HOEHE, BTN_RADIUS, TFT_RED);
    tft.drawString("STOPP", BTN_STOPP_X + BTN_STOPP_BREITE / 2, BTN_Y + BTN_HOEHE / 2);
    tft.setTextDatum(TL_DATUM);
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

bool pruefeNavigationButton(uint16_t x, uint16_t y)
{
    return (x >= 0 && x <= 110 &&
            y >= 0 && y <= 40);
}

void handleMenuTouch(uint16_t x, uint16_t y)
{
    int buttonID = 0;

    if (y >= 48 && y <= 134)
    {
        if (x >= 14 && x <= 106)
            buttonID = 1; // Session
        else if (x >= 114 && x <= 206)
            buttonID = 2; // Live Data
        else if (x >= 214 && x <= 306)
            buttonID = 3; // MENU 3
    }
    else if (y >= 142 && y <= 228)
    {
        if (x >= 14 && x <= 106)
            buttonID = 4; // Navigation
        else if (x >= 114 && x <= 206)
            buttonID = 5; // Settings
        else if (x >= 214 && x <= 306)
            buttonID = 6; // MENU 6
    }

    switch (buttonID)
    {
    case 1:
        setNewScreen(SCREEN_SESSION);
        break;

    case 2:
        setNewScreen(SCREEN_MAIN);
        break;

    case 3:
        break;

    case 4:
        break;

    case 5:
        setNewScreen(SCREEN_SETTINGS);
        break;

    case 6:
        break;

    default:
        break;
    }
}

void handleMainTouch(uint16_t x, uint16_t y)
{
    if (pruefeNavigationButton(x, y))
    {
        setNewScreen(SCREEN_MENU);
    }
}

void handleSessionTouch(uint16_t x, uint16_t y)
{
    verarbeiteSessionTouchInput(x, y);
    if (pruefeNavigationButton(x, y))
    {
        setNewScreen(SCREEN_MENU);
        return;
    }

    verarbeiteSessionTouchInput(x, y);
}

void handeSettingsTouch(uint16_t x, uint16_t y)
{
    if (pruefeNavigationButton(x, y))
    {
        setNewScreen(SCREEN_MENU);
        return;
    }
    if (x >= 240 && x <= 310 && y >= 28 && y <= 74)
    {
        highContrastAktiv = !highContrastAktiv;

        screenChanged = true; // damit hier auch der Kontrast auch im menu screen beachtete wurd wird
        zeichneSettingsLayout();
    }
}
bool darfTouchVerarbeitetWerden()
{
    static unsigned long letzterTouch = 0;

    if (millis() - letzterTouch < 500)
        return false;

    letzterTouch = millis();
    return true;
}

void verarbeiteGesamtenTouch(uint16_t x, uint16_t y)
{
    if (!darfTouchVerarbeitetWerden())
        return;

    switch (aktiverScreen)
    {
    case SCREEN_MENU:
        handleMenuTouch(x, y);
        break;

    case SCREEN_MAIN:
        handleMainTouch(x, y);
        break;

    case SCREEN_SESSION:
        handleSessionTouch(x, y);
        break;
    case SCREEN_SETTINGS:
        handeSettingsTouch(x, y);
        break;
    default:
        break;
    }
}