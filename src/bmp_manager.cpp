#include "bmp_manager.h"
#include "debug_helper.h"

float currentTemperature = 0.0;
float currentLuftDruck = 0.0; // in hPa
float currentHoeheBaro = 0.0;

void initBmp()
{
    if (!bmp.begin(0x76))
    {
        Serial.println("BMP280 not found");
        while (1)
            ;
    }
}
void verarbeiteBmp()
{
    currentTemperature = bmp.readTemperature();
    currentLuftDruck = (bmp.readPressure() / 100.0);
    currentHoeheBaro = bmp.readAltitude(1013.25);

    showBmpData();
};