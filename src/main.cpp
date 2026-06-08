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

const int BTN_X = 50;
const int BTN_Y = 100;
const int BTN_BREITE = 100;
const int BTN_HOEHE = 50;

void zeigeBtn();

void zeigeBtn()
{

  tft.fillRoundRect(BTN_X, BTN_Y, BTN_BREITE, BTN_HOEHE, 8, TFT_BLUE);
}
bool gedruecktImBtn(uint16_t x, uint16_t y)
{
  return x >= 50 && x <= 150 &&
         y >= 100 && y <= 150;
}
void setup()
{
  Serial.begin(115200);

  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  uint16_t calData[5] = {275, 3620, 264, 3532, 1}; // fürs kalibrieren
  tft.setTouch(calData);
  zeigeBtn();
}

void loop()
{
  uint16_t x = 0, y = 0;               // kurzschreibweise wenn man mit , trennt
  bool beruert = tft.getTouch(&x, &y); // liest die Touch-Position und schreibt die X- und Y-Werte direkt in x und y
  if (beruert)
  {
    Serial.println("Touch detected");
    Serial.print("X: ");
    Serial.print(x);

    Serial.print(" Y: ");
    Serial.println(y);

    if (gedruecktImBtn(x, y))
    {
      Serial.println("Pressed on BTN!");
    }
  }
}
