#ifndef MOCK_DATEN
#define MOCK_DATEN

#include <Arduino.h>
struct GpsKoordinate // hier sage ich wie der Neue Typ aufgebaut ist
{
    double lat;
    double lon;
};

extern const GpsKoordinate MOCK_ROUTE[];
extern const int MOCK_ROUTE_LAENGE;

#endif