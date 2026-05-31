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

void drawLabel(int x, int y, const char *label, uint16_t color)
{
  tft.setTextColor(color, TFT_BLACK);
  tft.setCursor(x, y);
  tft.print(label);
}

void drawValue(int x, int y, String value, uint16_t color)
{
  tft.setTextColor(color, TFT_BLACK);
  tft.setCursor(x, y);
  tft.print(value);
}

uint16_t gpsColor() // uint16_t ist dafür da, da es einen 16 bit output also für farben zurück gibt
{
  if (satellites >= 6)
    return TFT_GREEN;
  if (satellites >= 3)
    return TFT_ORANGE;
  return TFT_RED;
}

void drawUI()
{
  tft.fillScreen(TFT_BLACK);

  tft.setTextSize(2);

  drawLabel(10, 5, "BIKE COMPUTER", TFT_WHITE);

  String satText = "Sats: " + String(satellites);
  drawValue(220, 5, satText, gpsColor());
  tft.drawFastHLine(0, 30, 320, TFT_DARKGREY);

  tft.setTextSize(4);
  drawLabel(10, 45, "SPEED", TFT_DARKGREY);

  drawValue(10, 85, String(speed, 1) + " km/h", TFT_CYAN);
  tft.setTextSize(2);

  drawLabel(10, 150, "ALT", TFT_DARKGREY);
  drawValue(80, 150, String(altitude, 0) + " m", TFT_WHITE);

  drawLabel(10, 175, "LAT", TFT_DARKGREY);
  drawValue(80, 175, String(latitude, 5), TFT_WHITE);

  drawLabel(10, 200, "LON", TFT_DARKGREY);
  drawValue(80, 200, String(longitude, 5), TFT_WHITE);

  tft.setTextSize(1);
  drawValue(270, 225, "v0.3", TFT_DARKGREY);
}

void verarbeiteGPS()
{
  while (gpsSerial.available() > 0)
  {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid() && gps.location.isUpdated())
  {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    altitude = gps.altitude.meters();
    speed = gps.speed.kmph();
    satellites = gps.satellites.value();
    day = gps.date.day();
    month = gps.date.month();
    year = gps.date.year();

    Serial.println("GPS Update");
    drawUI();
  }
}

void aendereTestGPSDaten()
{
  static float fakeSpeed = 0;
  fakeSpeed += 0.5;

  if (fakeSpeed > 30)
  {
    fakeSpeed = 0;
  }
  speed = fakeSpeed;
  altitude = 500 + fakeSpeed;
  int testSatellitesVal = 0;
  testSatellitesVal + 1;

  if (testSatellitesVal > 16)
  {
    testSatellitesVal = 0;
  }
  satellites = testSatellitesVal;

  latitude = 48.137154 + fakeSpeed * 0.00001;
  longitude = 11.576124 + fakeSpeed * 0.00001;
}

void setup()
{
  Serial.begin(115200);

  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);

  tft.init();
  tft.setRotation(3);

  drawUI();
}

void loop()
{
  aendereTestGPSDaten();
  drawUI();
  delay(200);
}