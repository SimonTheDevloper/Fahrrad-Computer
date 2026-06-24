#include <Arduino.h>
#include <Wire.h> // Bibliothek für I²C-Kommunikation

#define SDA_PIN 25 // Datenleitung (Serial Data)
#define SCL_PIN 26 // Taktleitung (Serial Clock)

const uint8_t QMC_ADDR = 0x0D; // I²C-Adresse des QMC5883L

void writeRegister(uint8_t reg, u_int8_t wert)
{
    Wire.beginTransmission(QMC_ADDR);

    Wire.write(reg); // ein bestimmtes Register auswählen

    Wire.write(wert);

    Wire.endTransmission();
}

u_int8_t readRegister(u_int8_t reg)
{
    Wire.beginTransmission(QMC_ADDR);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(QMC_ADDR, 1);

    return Wire.read();
}

void readXYZ(int16_t &x, int16_t &y, int16_t &z)
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

    x = (xHigh << 8) | xLow;
    y = (yHigh << 8) | yLow;
    z = (zHigh << 8) | zLow;
}

void showXYZSerial(int16_t x, int16_t y, int16_t z) // &damit werden die Werte in die Variable geschrieben
{
    Serial.print("X: ");
    Serial.println(x);

    Serial.print("Y: ");
    Serial.println(y);

    Serial.print("Z: ");
    Serial.println(z);
}

float berechneInGrad(int16_t &x, int16_t &y)
{
    float headingRadians = // Winkel des Magnetfeldvektors berechnen

        atan2(y, x);

    float headingDegrees = // und hier die Grad
        headingRadians * 180.0 / PI;

    if (headingDegrees < 0)
    {
        headingDegrees += 360;
    }
    return headingDegrees;
}
void setup()
{
    Serial.begin(115200);

    Wire.begin(SDA_PIN, SCL_PIN); // I²C-Hardware im ESP32 starten

    writeRegister(0x09, 0x1D);
    Serial.println("Der Kompass ist gestartet");
}

void loop()
{
    int16_t x, y, z;

    readXYZ(x, y, z);

    showXYZSerial(x, y, z);

    float headingDegrees =
        berechneInGrad(x, y);

    Serial.print("Richtung: ");
    Serial.println(headingDegrees);

    delay(500);
}