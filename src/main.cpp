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

  Serial.println("Bildschirm blau machen");
  tft.fillScreen(TFT_BLUE);
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
}
