#include <Wire.h>
#include "bmp_manager.h"
#include "debug_helper.h"

Adafruit_BMP280 bmp;

bool bmpAktiv = false;
float currentTemperature = 0.0;
float currentLuftDruck = 0.0; // in hPa
float currentHoeheBaro = 0.0;

void initBmp()
{
    Wire.begin(27, 22);

    if (!bmp.begin(0x76))
    {
        Serial.println("BMP280 not found! Geht nun trotzdem weiter, ohne den BMP380");
        bmpAktiv = false;
    }
    else
    {
        Serial.println("BMP280 erflogreich Gestartet.");
        bmpAktiv = true;
    }
}

void verarbeiteBmp()
{
    if (!bmpAktiv)
        return;

    currentTemperature = bmp.readTemperature();
    currentLuftDruck = (bmp.readPressure() / 100.0);
    currentHoeheBaro = bmp.readAltitude(1013.25);

    showBmpData();
}