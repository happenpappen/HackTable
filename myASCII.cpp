#include "myTischConfig.h"
#include "myASCIIFont_6bit.h"

extern CRGB leds[NUM_LEDS];
extern uint8_t brightness;
extern CRGB fg_color;
extern CRGB bg_color;

void zeile_loeschen(int zeile)
{
    if (zeile >= 0) {
        for (int i = 0 ; i < kMatrixHeight ; i++) {
            leds[zeile + i * kMatrixWidth] = bg_color;
        }
    }
}

void zeichnenPos(byte zeichen[], int posx, int posy, CRGB fg_color, CRGB bg_color)
{
    for (int spalte = 0; spalte < FONT_WIDTH; spalte++) { // 6, 7 od. 8 pixel breite
        for (int zeile = 0; zeile < 8; zeile++) {    // 8 pixel höhe
            if ((spalte + posx >= 0) && (spalte + posx < kMatrixHeight)) {
                if (zeichen[7 - zeile] & (1 << (FONT_WIDTH - spalte))) {
                    if (((spalte + posx) <= kMatrixHeight) && ((spalte + posx) >= 0)) {
                        leds[posx + spalte + (posy + zeile)*kMatrixHeight - 1] = fg_color;
                    }
                } else {
                    if (((spalte + posx) <= kMatrixHeight) && ((spalte + posx) >= 0)) {
                        leds[posx + spalte + (posy + zeile)*kMatrixHeight - 1] = bg_color;
                    }
                }

            }
        }
    }
    LEDS.show();
}

void ZeichneBuchstaben(char ch, int x, int y, CRGB fg_color, CRGB bg_color)
{
    if (ch - 32 > 0) {
        zeichnenPos(ASCII[ch - 32], x, y, fg_color, bg_color);
    }
}

void ZeichneText(String txt, int x, int y, CRGB fg_color, CRGB bg_color)
{
    int anzahl = txt.length();                     // Anzahl der Zeichen im Text

    for (int i = 0; i <= anzahl; i++) {
        ZeichneBuchstaben(txt[i], x + i * FONT_WIDTH, y, fg_color, bg_color);
    }
}

void Lauftext_von_oben(String txt, int x, int pause, CRGB fg_color, CRGB bg_color)
{
    int anzahl = txt.length();                     // Anzahl der Zeichen im Text
    for (int i = 0 ; i < kMatrixWidth + 8 * anzahl - 6 ; i++) { // Textzeichen haben eine Höhe von 8 Pixel
        for (int ii = 0; ii <= anzahl; ii++) {
            zeile_loeschen(i - 9 - ii * 8);
            ZeichneBuchstaben(txt[anzahl - ii], x, i - ii * 8, fg_color, bg_color);
        }
        delay(pause);
    }
}

void Lauftext_von_unten(String txt, int x, int pause, CRGB fg_color, CRGB bg_color)
{
    int anzahl = txt.length();                     // Anzahl der Zeichen im Text
    for (int i = kMatrixWidth + 8 * anzahl ; i > 0 ; i--) { // Textzeichen haben eine Höhe von 8 Pixel
        for (int ii = 0; ii <= anzahl; ii++) {
            ZeichneBuchstaben(txt[anzahl - ii], x, i - ii * 8, fg_color, bg_color);
        }
        delay(pause);
    }
}


void Lauftext_von_rechts(String txt, int y, int bremse, CRGB fg_color, CRGB bg_color)
{
    int anzahl = txt.length();
    for (int i = 8 ; i > anzahl * -6 ; i--) {  //Länge des Lauftextes
        for (int ii = 0 - (i / 6) ; ii < 3 - (i / 6) ; ii++) { //Buchstaben durchlaufen
            ZeichneBuchstaben(txt[ii], i + ii * 6, y, fg_color, bg_color);
        }
        delay(bremse);
    }
}

void Lauftext2(String txt, int x, int y, int bremse, CRGB fg_color, CRGB bg_color) // Nacheinander anzeigen
{
    int anzahl = txt.length();
    for (int i = 0 ; i < anzahl ; i++) {
        ZeichneBuchstaben(txt[i], x, y, fg_color, bg_color);
        delay(bremse);
    }
}

void Lauftext_blenden(String txt, int x, int y, int warten, CRGB fg_color, CRGB bg_color) // Nacheinander einblenden
{
    LEDS.setBrightness(0);
    int anzahl = txt.length();
    for (int i = 0 ; i < anzahl ; i++) {

        ZeichneBuchstaben(txt[i], x, y, fg_color, bg_color);
        for (int ii = 0 ; ii < brightness ; ii++) {
            LEDS.setBrightness(ii);
            delay(warten);
            LEDS.show();
        }

        for (int ii = brightness ; ii > 0 ; ii--) {
            LEDS.setBrightness(ii);
            delay(warten);
            LEDS.show();
        }
    }
    LEDS.setBrightness(brightness);
}
