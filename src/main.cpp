#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

float speedVal = 12.5;
float heightVal = 532.0;
float longVal = 11.576;
float latVal = 48.137;

void zeigeBildschirm()
{
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  tft.setCursor(10, 20);
  tft.println("SPEED:");
  tft.setCursor(120, 20);
  tft.println(speedVal);

  tft.setCursor(10, 60);
  tft.println("HEIGHT:");
  tft.setCursor(120, 60);
  tft.println(heightVal);

  tft.setCursor(10, 100);
  tft.println("LONG:");
  tft.setCursor(120, 100);
  tft.println(longVal, 6);

  tft.setCursor(10, 140);
  tft.println("LAT:");
  tft.setCursor(120, 140);
  tft.println(latVal, 6);
}

void setup()
{
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  zeigeBildschirm();
}

void loop()
{
}