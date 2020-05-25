#include "myTischConfig.h"
#include "myUtils.h"

extern cLEDMatrix<kMatrixWidth, kMatrixHeight, HORIZONTAL_MATRIX> leds;
extern CRGB fg_color;
extern CRGB bg_color;

void setupSingleColor()
{
    uint16_t i = 0;

    for (i = 0; i < NUM_LEDS; i++) {
        leds(i) = fg_color;
    }
}

void loopSingleColor()
{
    uint16_t i = 0;

    for (i = 0; i < NUM_LEDS; i++) {
        leds(i) = fg_color;
    }
}
