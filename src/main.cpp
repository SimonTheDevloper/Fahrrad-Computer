#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup()
{
    disableCore0WDT();
    disableCore1WDT();
    
    Serial.begin(115200);
    delay(3000);

    Serial.println("\n==================================");
    Serial.println("   ESP32-S3 DISPLAY TEST START");
    Serial.println("==================================");

    Serial.println("Starte tft.init()...");
    tft.init();
    Serial.println("Display erfolgreich gestartet!");

    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.println("ESP32-S3 Nano");

    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(3);
    tft.setCursor(10, 50);
    tft.println("ES LEBT!!!");

    Serial.println("Setup abgeschlossen!");
}

int counter = 0;

void loop()
{
    Serial.print("Sekunden seit Start: ");
    Serial.println(counter);

    tft.fillRect(10, 120, 200, 40, TFT_BLACK);

    tft.setTextColor(TFT_YELLOW);
    tft.setTextSize(3);
    tft.setCursor(10, 120);
    tft.print("Zeit: ");
    tft.print(counter);
    tft.print(" s");

    counter++;
    delay(1000);
}