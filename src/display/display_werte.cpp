#include <TFT_eSPI.h>
#include "display/display_ui.h"
#include "gps_manager.h"
#include "trip_computer.h"
#include "ride_session.h"
#include "Org_01.h"

void aktualisiereWerte()
{
    static String letzteUhrzeit = ""; // Wie eine globale Variable, die aber sicher verpackt nur innerhalb dieser Funktion existiert
    static int letztesSpeedInt = -1;
    static String letzteGesamtStrecke = "";
    static String letzteGesamtFahrzeit = "";
    static String letztesMaxSpeed = "";

    if (screenChanged) // damit sozusagen das Cashe zurüg gesetzt wird und werte korrekt beim Screen wechseln geupdated werden
    {
        letzteUhrzeit = "";
        letztesSpeedInt = -1;
        letzteGesamtStrecke = "";
        letzteGesamtFahrzeit = "";
        letztesMaxSpeed = "";
        screenChanged = false;
    }

    bekommeUhrzeit();

    tft.setFreeFont(NULL);
    tft.setTextSize(2);
    tft.setTextColor(FARBE_TEXT, FARBE_HINTERGRUND);
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

    if (screenChanged)
    {
        letzteDistanz = "";
        letzteZeit = "";
        letzterAvgSpeed = "";
        letzterMaxSpeed = "";
        letzterState = UNBEKANNT;
        screenChanged = false;
    }
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

void aktualisiereMenuWerteHighKontrast()
{
    static String letzteUhrzeit = "";

    if (screenChanged)
    {
        letzteUhrzeit = "";
        screenChanged = false;
    }

    bekommeUhrzeit();

    if (letzteUhrzeit != String(uhrzeit))
    {
        tft.fillRect(260, 5, 58, 25, 0x0000);

        tft.setTextColor(0xFFFF);
        tft.setTextSize(2);
        tft.setFreeFont(&Org_01);
        tft.drawString(uhrzeit, 264, 14);

        letzteUhrzeit = String(uhrzeit);
    }
}

void aktualisiereMenuWerte()
{
    static String letzteUhrzeit = "";

    if (screenChanged)
    {
        letzteUhrzeit = "";
        screenChanged = false;
    }

    bekommeUhrzeit();

    if (letzteUhrzeit != String(uhrzeit))
    {
        tft.fillRect(260, 5, 58, 25, 0x0000);
        tft.fillRect(260, 5, 58, 25, 0x0);

        tft.setTextColor(0xFD09);
        tft.setTextSize(2);
        tft.setFreeFont(&Org_01);
        tft.drawString(uhrzeit, 264, 14);

        letzteUhrzeit = String(uhrzeit);
    }
}
void aktualisiereSettingsWerte()
{
    static bool letzterHighContrast = false;
    if (screenChanged)
    {
        letzterHighContrast = !highContrastAktiv;
        screenChanged = false;
    }

    if (letzterHighContrast != highContrastAktiv)
    {
        zeichneToggleButton(250, 38, highContrastAktiv);
        letzterHighContrast = highContrastAktiv;
    }
}