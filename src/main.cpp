#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h> // das ist die konfoigurierte Display-Bib
TFT_eSPI tft = TFT_eSPI();
void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Fahrrad-Computer startet...");

  // Manuelle Initialisierung der Pins (optional, aber sicher ist sicher)
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH); // Reset Pin auf HIGH

  Serial.println("Initialisiere TFT...");
  tft.init();
  tft.setRotation(1);

  Serial.println("Bildschirm blau machen");
  tft.fillScreen(TFT_BLUE);
  Serial.println("Initialisierung abgeschlossen!");
}

void loop()
{
}
