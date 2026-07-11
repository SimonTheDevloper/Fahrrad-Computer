#include <TFT_eSPI.h>
#include "display/display_ui.h"
#include "gps_manager.h"
#include "trip_computer.h"
#include "ride_session.h"

TFT_eSPI tft = TFT_eSPI();
Screen aktiverScreen = SCREEN_SESSION;
bool screenChanged = false;

extern const bool TEST_MODE;

void initDisplay()
{
    tft.init();
    tft.setRotation(3);

    uint16_t calData[5] = {275, 3620, 264, 3532, 1}; // fürs kalibrieren fürs TouchWWW
    tft.setTouch(calData);
}

uint16_t gpsColor()
{
    if (satellites >= 6)
        return TFT_GREEN;
    if (satellites >= 3)
        return TFT_ORANGE;
    return TFT_RED;
}

void updateAktivenScreen()
{
    switch (aktiverScreen)
    {
    case SCREEN_MAIN:
        aktualisiereLiveDataWerte();
        break;

    case SCREEN_SESSION:
        aktualisiereSessionScreenWerte();
        break;

    case SCREEN_MENU:
        aktualisiereMenuWerte();
        break;

    case SCREEN_SETTINGS:
        aktualisiereSettingsWerte();
        break;
    }
}

void setNewScreen(Screen neuerScreen)
{
    aktiverScreen = neuerScreen;
    screenChanged = true;

    if (aktiverScreen == SCREEN_MAIN)
    {
        zeichneLiveDataLayout();
    }
    else if (aktiverScreen == SCREEN_SESSION)
    {
        zeichneSessionLayout();
    }
    else if (aktiverScreen == SCREEN_MENU)
    {
        zeichneMenuLayout();
    }
    else if (aktiverScreen == SCREEN_SETTINGS)
    {
        zeichneSettingsLayout();
    }
}
