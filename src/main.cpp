#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <TinyGPS++.h>

HardwareSerial gpsSerial(2);
TinyGPSPlus gps;
TFT_eSPI tft = TFT_eSPI();

#define TEST_MODE true

#define GPS_RX 32
#define GPS_TX 33

double latitude = 0.0;
double longitude = 0.0;
double altitude = 0.0;
double speed = 0.0;
double maxSpeed = 0.0;

float speedSum;
int speedCount;
float durchschnittSpeed;

int satellites = 0;
int day = 0;
int month = 0;
int year = 0;
int hour = 0;
int minute = 0;
int second = 0;

char uhrzeit[16];

double distanzInMetern;

double letzteLat = 0.0;
double letzteLong = 0.0;

unsigned long gesamtFahrtZeit = 0;
unsigned long letztesSekunde = 0;

void drawLabel(int x, int y, const char *label, uint16_t color);
void drawValue(int x, int y, String value, uint16_t color);
uint16_t gpsColor();
void zeichneGrundLayout();
void aktualisiereWerte();
void verarbeiteGPS();
void aendereTestGPSDaten();

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

uint16_t gpsColor()
{
  if (satellites >= 6)
    return TFT_GREEN;
  if (satellites >= 3)
    return TFT_ORANGE;
  return TFT_RED;
}

void zeichneGrundLayout()
{
  tft.fillScreen(TFT_BLACK);

  tft.setTextSize(2);
  if (TEST_MODE)
  {
    drawLabel(10, 5, "TEST MODE", TFT_ORANGE);
  }
  else
  {
    drawLabel(10, 5, "BIKE COMPUTER", TFT_WHITE);
  }
  drawLabel(10, 225, "TIME", TFT_DARKGREY);
  tft.drawFastHLine(0, 30, 320, TFT_DARKGREY);
  tft.setTextSize(4);
  drawLabel(10, 45, "SPEED", TFT_DARKGREY);

  tft.setTextSize(2);
  drawValue(10, 115, "MAX " + String(maxSpeed, 1) + " km/h   ", TFT_YELLOW);
  drawLabel(10, 150, "ALT", TFT_DARKGREY);
  drawLabel(10, 175, "LAT", TFT_DARKGREY);
  drawLabel(10, 200, "LON", TFT_DARKGREY);

  tft.setTextSize(1);
  drawLabel(270, 225, "v0.3", TFT_DARKGREY);
}

void bekommeUhrzeit()
{
  sprintf(uhrzeit,          // sprintf() baut aus Variablen einen Text zusammen.
          "%02d:%02d:%02d", // das macht das es auch 04 statt einfach 4 sein kann und ist natührlich ein platzhalter
          hour,
          minute,
          second);
}
void aktualisiereWerte()
{
  bekommeUhrzeit();
  tft.setTextSize(2);
  String satText = "Sats: " + String(satellites) + "   ";
  drawValue(220, 5, satText, gpsColor());

  tft.setTextSize(4);
  drawValue(10, 85, String(speed, 1) + " km/h   ", TFT_CYAN);

  tft.setTextSize(2);
  drawValue(10, 115, "MAX " + String(maxSpeed, 1) + " km/h   ", TFT_YELLOW);
  drawValue(80, 150, String(altitude, 0) + " m    ", TFT_WHITE);
  drawValue(80, 175, String(latitude, 5) + "    ", TFT_WHITE);
  drawValue(80, 200, String(longitude, 5) + "    ", TFT_WHITE);

  drawValue(120, 225, uhrzeit, TFT_GREEN);
}

void berechneDurschnittsSpeed(float currentspeed)
{
  speedSum += currentspeed;
  speedCount++;

  if (speedCount > 1)
  {
    durchschnittSpeed = speedSum / speedCount;
    // Serial.println(durchschnittSpeed);
  }
}

void berechneDistanz()
{
  if (letzteLat == 0.0 && letzteLong == 0.0)
  {
    letzteLat = latitude;
    letzteLong = longitude;
    return;
  }
  double distanzInMetern = TinyGPSPlus::distanceBetween( // das berechnet es einfach schon
      letzteLat, letzteLong,
      latitude, longitude);

  Serial.print("Distanz in m:");
  Serial.println(distanzInMetern);
  letzteLat = latitude;
  letzteLong = longitude;
}
void berechneGesamtfahrzeit()
{
  if (speed > 1.5)
  {
    gesamtFahrtZeit++;
    Serial.print("Gesmatfahrzeit in s:");
    Serial.println(gesamtFahrtZeit);
  }
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

    berechneDurschnittsSpeed(speed);

    if (speed > maxSpeed)
      maxSpeed = speed;

    satellites = gps.satellites.value();
    day = gps.date.day();
    month = gps.date.month();
    year = gps.date.year();

    hour = gps.time.hour();
    minute = gps.time.minute();
    second = gps.time.second();

    aktualisiereWerte();
  }
}

void aendereTestGPSDaten()
{
  static float fakeSpeed = 0;
  fakeSpeed += 0.5;

  if (fakeSpeed > 30)
    fakeSpeed = 0;

  speed = fakeSpeed;

  berechneDurschnittsSpeed(speed);
  if (speed > maxSpeed)
    maxSpeed = speed;
  altitude = 500 + fakeSpeed;

  static int testSatellitesVal = 0;
  testSatellitesVal += 1;

  if (testSatellitesVal > 16)
    testSatellitesVal = 0;
  satellites = testSatellitesVal;

  latitude = 22.34556 + fakeSpeed * 0.00001;
  longitude = 32.5654 + fakeSpeed * 0.00001;
}

void updateData()
{
  if (TEST_MODE)
  {
    aendereTestGPSDaten();
  }
  else
  {
    verarbeiteGPS();
  }
}
void setup()
{
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);

  tft.init();
  tft.setRotation(3);

  zeichneGrundLayout();
}

void loop()
{
  updateData();
  if (TEST_MODE)
  {
    aktualisiereWerte();
    delay(500);
  }

  if (millis() - letztesSekunde >= 1000)
  {
    letztesSekunde = millis();
    berechneGesamtfahrzeit();
    berechneDistanz();
  }
}
