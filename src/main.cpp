#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>

TFT_eSPI tft = TFT_eSPI();

bool tft_output(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t *bitmap)
{

    tft.pushImage(x, y, width, height, bitmap); // Zeichnet den aktuellen bitmap

    return true;
}

void setup()
{
    Serial.begin(115200);
    tft.init();

    if (!LittleFS.begin())
    {
        Serial.println("LittleFS konnte nicht gestartet werden");
        return;
    }

    tft.setRotation(3);

    TJpgDec.setCallback(tft_output); // damit weiß der Decoder wo hin mit dem bil

    TJpgDec.setJpgScale(1);
    TJpgDec.setSwapBytes(true);

    TJpgDec.drawFsJpg(0, 0, "/geralt-binary-code.jpg", LittleFS); // Zeichnet das Bild aus dem LittleFs und mit den Koordinaten
}

void loop()
{
}