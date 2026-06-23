#include <Arduino.h>
#include <Wire.h> // Bibliothek für I²C-Kommunikation

#define SDA_PIN 25 // Datenleitung (Serial Data)
#define SCL_PIN 26 // Taktleitung (Serial Clock)

const uint8_t QMC_ADDR = 0x0D; // I²C-Adresse des QMC5883L

void setup()
{
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN); // I²C-Hardware im ESP32 starten

  Serial.println("I2C gestartet");

  Wire.beginTransmission(QMC_ADDR);

  Wire.write(0x09); // ein bestimmtes Register auswählen

  Wire.write(0x1D);

  Wire.endTransmission();
}

void loop()
{

  Wire.beginTransmission(QMC_ADDR);
  Wire.write(0x00); // damit soll der Sensor bei dem nächten Register starten

  Wire.endTransmission();

  Wire.requestFrom(QMC_ADDR, 6);
  // 6 Bytes vom Sensor anfordern
  // X Low
  // X High
  // Y Low
  // Y High
  // Z Low
  // Z High

  uint8_t xLow = Wire.read();
  uint8_t xHigh = Wire.read();

  uint8_t yLow = Wire.read();
  uint8_t yHigh = Wire.read();

  uint8_t zLow = Wire.read();
  uint8_t zHigh = Wire.read();

  // Zwei 8-Bit-Werte zu einem 16-Bit-Wert zusammensetzen

  int16_t x =
      (xHigh << 8) | xLow;

  int16_t y =
      (yHigh << 8) | yLow;

  int16_t z =
      (zHigh << 8) | zLow;

  Serial.print("X: ");
  Serial.println(x);

  Serial.print("Y: ");
  Serial.println(y);

  Serial.print("Z: ");
  Serial.println(z);

  float headingRadians = // Winkel des Magnetfeldvektors berechnen

      atan2(y, x);

  float headingDegrees = // und hier die Grad
      headingRadians * 180.0 / PI;

  if (headingDegrees < 0)
  {
    headingDegrees += 360;
  }

  Serial.print("Richtung: ");
  Serial.println(headingDegrees);

  delay(500);
}