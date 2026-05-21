#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>

void dateinSystemAnzeigen()
{
  Serial.println("Lese Dateisystem...");
  File ordner = LittleFS.open("/"); // damit der Esp32 den Hauptordner öffnet

  if (!ordner || !ordner.isDirectory())
  {
    Serial.println("Fehler beim Öffnen des Hauptverzeichnisses!");
    return;
  }

  File datei = ordner.openNextFile(); // damit wird die erste datei au dem orner geholt

  int dateiAnzahl = 0; // Anzahl der gefundenen Dateien

  while (datei) // die schleife geht so lange weiter, so lange es noch datein gibt
  {
    String name = datei.name();

    size_t groesse = datei.size(); // so wird es als Byte gespeichert
    Serial.printf(
        "Datei gefunden: %s (%d Bytes)\n",
        name.c_str(),
        groesse);

    dateiAnzahl++;

    datei = ordner.openNextFile(); // zur nächsten Datei
  }
  if (dateiAnzahl == 0)
  {
    Serial.println("Keine Dateien im LittleFS gefunden.");
  }
  else
  {
    Serial.printf(
        "Insgesamt %d Dateien gefunden.\n",
        dateiAnzahl);
  }
}

void setup()
{
  Serial.begin(115200);

  if (!LittleFS.begin(true)) // startet LittleFS
  {
    Serial.println("LittleFS konnte nicht gestartet werden");
    return;
  }

  Serial.println("ESP32 und LittleFS gestartet");

  dateinSystemAnzeigen();
}

void loop()
{
}
