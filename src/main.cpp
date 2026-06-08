#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <TinyGPS++.h>

HardwareSerial gpsSerial(2);
TinyGPSPlus gps;
TFT_eSPI tft = TFT_eSPI();

#define GPS_RX 32
#define GPS_TX 33

double latitude = 0.0;
double longitude = 0.0;
double altitude = 0.0;
double speed = 0.0;

int satellites = 0;
int day = 0;
int month = 0;
int year = 0;

void zeigeBildschirm();
void verarbeiteGPS();

void zeigeBildschirm()
{
}

void setup()
{
  Serial.begin(115200);

  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
  tft.init();
  tft.setRotation(3);

  uint16_t calData[5] = {275, 3620, 264, 3532, 1}; // fürs kalibrieren
  tft.setTouch(calData);
  zeigeBildschirm();
}

void loop()
{
  uint16_t x = 0, y = 0;               // kurzschreibweise wenn man mit , trennt
  bool beruert = tft.getTouch(&x, &y); // liest die Touch-Position und schreibt die X- und Y-Werte direkt in x und y
  {
    Serial.println("Beruerung entdeckt");
    Serial.print("X: ");
    Serial.print(x);

    Serial.print(" Y: ");
    Serial.println(y);
  }
}
