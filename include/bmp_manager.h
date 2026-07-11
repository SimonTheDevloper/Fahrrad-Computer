#ifndef BMP_MANAGER_H
#define BMP_MANAGER_H
#include <Arduino.h>
#include <Adafruit_BMP280.h>

extern Adafruit_BMP280 bmp;

void initBmp();
void verarbeiteBmp();

extern float currentTemperature;
extern float currentLuftDruck;
extern float currentHoeheBaro;
extern bool bmpAktiv;
#endif