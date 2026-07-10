#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup()
{
    Serial.begin(115200);

    if (!bmp.begin(0x76))
    {
        Serial.println("BMP280 not found");
        while (1)
            ;
    }
}
void loop()
{
    Serial.print("Temperatur: ");
    Serial.print(bmp.readTemperature());
    Serial.println(" °C");

    Serial.print("Druck: ");
    Serial.print(bmp.readPressure() / 100.0); // damit man hPascal bekommt
    Serial.println(" hPa");

    float hoehe = bmp.readAltitude(1013.25); // führ meereshöhe
    Serial.print(hoehe);
    Serial.println(" m");

    delay(1000);
}