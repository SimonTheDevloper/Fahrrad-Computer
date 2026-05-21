#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h> // das ist die konfoigurierte Display-Bib
TFT_eSPI tft = TFT_eSPI();
void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Fahrrad-Computer startet...");
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  Serial.println("Initialisiere TFT...");
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  Serial.println("Initialisierung abgeschlossen!");
}

void loop()
{
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString("Hello World", 50, 10); // aufbau: text dann x und y

  tft.setTextColor(TFT_BROWN);
  tft.setTextSize(3);
  tft.drawString("Helllooo World", 50, 25);

  tft.setTextColor(TFT_DARKGREY, TFT_CYAN);
  tft.setTextSize(1);
  tft.drawString("Hey World", 50, 50);

  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.drawString("Test #" + String(2), 70, 60); // man kann leider nicht einfach Ziffern normal anzeigen

  tft.drawRect(60, 200, 80, 300, TFT_DARKCYAN); // so ist der aufbau tft.drawRect(x, y, breite, hoehe, farbe);
  tft.fillRect(10, 10, 10, 10, TFT_CASET);
  tft.drawRoundRect(20, 20, 20, 20, 40, TFT_YELLOW);

  tft.fillCircle(160, 120, 30, TFT_BLUE); // tft.fillCircle(x_mitte, y_mitte, radius, farbe); oder drawCircle
  tft.drawCircle(200, 40, 70, TFT_DARKGREY);

  tft.drawLine(0, 50, 320, 50, TFT_WHITE); // tft.drawLine(x_start, y_start, x_ende, y_ende, farbe);gfggfgffgfgfghfghhfghhghg
}
