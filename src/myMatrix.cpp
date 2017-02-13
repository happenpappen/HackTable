#include "myTischConfig.h"
#include "myUtils.h"

extern CRGB leds[NUM_LEDS];

void DrawOneFrame( byte startHue8, int8_t yHueDelta8, int8_t xHueDelta8)
{
  byte lineStartHue = startHue8;
  for( byte y = 0; y < kMatrixWidth; y++) {
    lineStartHue += yHueDelta8;
    byte pixelHue = lineStartHue;      
    for( byte x = 0; x < kMatrixHeight; x++) {
      pixelHue += xHueDelta8;
      leds[ XY(x, y)]  = CHSV( pixelHue, 255, 255);
    }
  }
}

void setupMatrix() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = 0;
    }
}

void loopMatrix()
{
    uint32_t ms = millis();
    int32_t yHueDelta32 = ((int32_t)cos16( ms * (27/1) ) * (350 / kMatrixWidth));
    int32_t xHueDelta32 = ((int32_t)cos16( ms * (39/1) ) * (310 / kMatrixHeight));
    DrawOneFrame( ms / 65536, yHueDelta32 / 32768, xHueDelta32 / 32768);
/*
    if( ms < 5000 ) {
      FastLED.setBrightness( scale8( 64, (ms * 256) / 5000));
    } else {
      FastLED.setBrightness(64);
    }
*/
}

