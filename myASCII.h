#ifndef __MYASCII_H__
#define __MYASCII_H__

#include "application.h"
#include <string.h>

void zeile_loeschen(int zeile);
void Lauftext_von_oben(String txt, int x, int pause, CRGB fg_color, CRGB bg_color);
void Lauftext_von_unten(String txt, int x, int pause, CRGB fg_color, CRGB bg_color);
void Lauftext_von_rechts(String txt, int y, int bremse, CRGB fg_color, CRGB bg_color);
void Lauftext2(String txt, int x, int y, int bremse, CRGB fg_color, CRGB bg_color);
void Lauftext_blenden(String txt, int x, int y, int warten, CRGB fg_color, CRGB bg_color);
void zeichnenPos(byte zeichen[], int posx, int posy, CRGB fg_color, CRGB bg_color);
void ZeichneBuchstaben(char ch, int x, int y, CRGB fg_color, CRGB bg_color);
void ZeichneText(String txt, int x, int y, CRGB fg_color, CRGB bg_color);

#endif
