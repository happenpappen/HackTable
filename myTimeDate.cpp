#include "myTischConfig.h"
#include "myUtils.h"
#include "myASCII.h"

extern CRGB leds[NUM_LEDS];
extern CRGB fg_color;
extern CRGB bg_color;

void setupTimeDate()
{
    for (int i = 0; i < kMatrixHeight; i++) {
        for (int j = 0; j < kMatrixWidth; j++) {
            leds[XY(i, j)] = bg_color;
        }
    }

    LEDS.show();
}

void loopTimeDate()
{
    //Lauftext_von_rechts(Time.format(Time.now(),"%H:%M:%S"), 2, 40, 0, 200, 200);
    ZeichneText(Time.format(Time.now(), "%H%M"), 0, 2, fg_color, bg_color);
}
