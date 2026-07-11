#ifndef DISPLAY_LAYOUTS_H
#define DISPLAY_LAYOUTS_H

#include <Arduino.h>
#include <TFT_eSPI.h>

void zeichneLiveDataLayout();
void zeichneSessionLayout();
void zeichneMenuLayout();
void zeichneMenuLayoutHighKontrast();
void zeichneSettingsLayout();
void zeichneToggleButton(int x, int y, bool aktiv);
#endif
