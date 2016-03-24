#ifndef __TISCHCONFIG_H__
#define __TISCHCONFIG_H__

#include "FastLED.h"
FASTLED_USING_NAMESPACE;

const bool kMatrixSerpentineLayout = true;
const uint8_t kMatrixWidth  = 12;
const uint8_t kMatrixHeight = 23;

#define MAX_DIMENSION ((kMatrixWidth > kMatrixHeight) ? kMatrixWidth : kMatrixHeight)
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)

#endif
