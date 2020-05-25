#include "myTischConfig.h"
#include "myUtils.h"

extern cLEDMatrix<kMatrixWidth, kMatrixHeight, VERTICAL_MATRIX> leds;

#define SHAPE_WIDTH 10
#define SHAPE_HEIGHT 7
const uint8_t ShapeData[] =
{
    // Frame 1
    B8_1BIT(0010000100),
    B8_1BIT(0001001000),
    B8_1BIT(0011111100),
    B8_1BIT(0110110110),
    B8_1BIT(1111111111),
    B8_1BIT(1010000101),
    B8_1BIT(0001001000),
    // Frame 2
    B8_1BIT(0010000100),
    B8_1BIT(0001001000),
    B8_1BIT(1011111101),
    B8_1BIT(1110110111),
    B8_1BIT(0111111110),
    B8_1BIT(0010000100),
    B8_1BIT(0100000010),
};

struct CRGB ColTable[1] = { CRGB(64, 128, 255) };

cLEDSprites Sprites(&leds);
cSprite Shape(SHAPE_WIDTH, SHAPE_HEIGHT, ShapeData, 2, _1BIT, ColTable, ShapeData); 

void setupSpaceInvader() {
  Shape.SetPositionFrameMotionOptions(0/*X*/, 0/*Y*/, 0/*Frame*/, 0/*FrameRate*/, +1/*XChange*/, 1/*XRate*/, +1/*YChange*/, 1/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN
 | SPRITE_Y_KEEPIN);
  Sprites.AddSprite(&Shape);    
}

void loopSpaceInvader() {
  Sprites.UpdateSprites();
  Sprites.RenderSprites();
}
