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

void drawLabelValue(int y, const char *label, String value);
void zeigeBildschirm(); // hier schon definieren, dasmit ich funktionen auch weiter unter wo sie aufgerufen werden benutzen kann
void verarbeiteGPS();
void printGpsData();

void drawLabelValue(int y, const char *label, String value)
{
  tft.setTextColor(TFT_DARKGREY, TFT_BLACK);
  tft.setCursor(10, y);
  tft.print(label);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(140, y);
  tft.print(value);
}

void zeigeBildschirm()
{
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(10, 5);
  tft.print("Bike Computer");

  tft.drawFastHLine(0, 25, 320, TFT_DARKGREY);
  drawLabelValue(40, "Speed", String(speed, 1) + " km/h");
  drawLabelValue(75, "Height", String(altitude, 0) + " m");
  drawLabelValue(110, "Long", String(longitude, 6));
  drawLabelValue(145, "Lat", String(latitude, 6));

  tft.drawFastHLine(0, 180, 320, TFT_DARKGREY);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.setTextSize(1);
  tft.setCursor(291, 227);
  tft.print("v0.2");
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
    printGpsData();
    zeigeBildschirm();
  }
}

void printGpsData()
{
  Serial.println("<------ GPS Daten ------>");
  Serial.print("Satelliten: ");
  Serial.println(satellites);
  Serial.print("Lat: ");
  Serial.println(latitude, 6);
  Serial.print("Lng: ");
  Serial.println(longitude, 6);
  Serial.print("Hoehe: ");
  Serial.print(altitude);
  Serial.println(" m");
  Serial.print("Datum: ");
  Serial.print(day);
  Serial.print(".");
  Serial.print(month);
  Serial.print(".");
  Serial.println(year);
  Serial.print("Tempo: ");
  Serial.print(speed);
  Serial.println(" km/h");

  if (satellites >= 4)
  {
    Serial.println("GPS Signal good");
  }
  else
  {
    Serial.println("GPS Signal weak");
  }
}

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Fahrrad-Computer startet...");

  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  zeigeBildschirm();
  Serial.println("Initialisierung abgeschlossen!");
}

void loop()
{
  verarbeiteGPS();
}