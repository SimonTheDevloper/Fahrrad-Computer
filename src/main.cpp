#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

float speedVal = 12.5; // float für Nachkommastellen, das die erlaubt sind
float heightVal = 123.0;
float longVal = 43.7843;
float latVal = 199.473;

void drawLabelValue(int y, const char *label, String value) // char* ist ein Pointer auf einen Text im Speicher (C-String), also keine Kopie des Textes sondern nur die Adresse davon
{                                                           // dadurch wird es speicherschonender
  tft.setTextColor(TFT_DARKGREY, TFT_BLACK);
  tft.setCursor(10, y);
  tft.print(label);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(140, y);
  tft.print(value);
}

void zeigeBildschirm()
{
  tft.fillScreen(TFT_BLACK);

  tft.setTextSize(2);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(10, 5);
  tft.print("Bike Computer");

  tft.drawFastHLine(0, 25, 320, TFT_DARKGREY);

  drawLabelValue(40, "Speed", String(speedVal, 1) + " km/h"); // die eins sagt wie viele Nachkommastellen kommen dürfen
  drawLabelValue(75, "Height", String(heightVal, 0) + " m");
  drawLabelValue(110, "Long", String(longVal, 6));
  drawLabelValue(145, "Lat", String(latVal, 6));

  tft.drawFastHLine(0, 180, 320, TFT_DARKGREY);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.setTextSize(1);
  tft.setCursor(291, 227);
  tft.print("v0.2");
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