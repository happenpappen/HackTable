#include "myTischConfig.h"
#include "myUtils.h"

extern cLEDMatrix<kMatrixWidth, kMatrixHeight, HORIZONTAL_MATRIX> leds;
extern CRGB fg_color;
extern CRGB bg_color;

void setupCylon() { 
    for (int i = 0; i < kMatrixHeight; i++) {
        for (int j = 0; j < kMatrixWidth; j++) {
            leds(XY(i, j)) = bg_color;
        }
    }
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds(i).nscale8(250); } }

void loopCylon() { 
	static uint8_t hue = 0;

	for(int i = 0; i < kMatrixHeight; i++) {
        for(int j = 0; j < kMatrixWidth; j++) {
		    // Set the i'th led to red 
		    leds(XY(i,j)) = CHSV(hue, 255, 255);
	    }
		hue++;
        // Show the leds
		FastLED.show(); 
		// now that we've shown the leds, reset the i'th led to black
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(100);
    }
	// Now go in the other direction.  
	for(int i = (kMatrixHeight)-1; i >= 0; i--) {
        for(int j = 0; j < kMatrixWidth; j++) {
		    // Set the i'th led to red 
		    leds(XY(i,j)) = CHSV(hue, 255, 255);
	    }
        hue++;
		// Show the leds
		FastLED.show();
		// now that we've shown the leds, reset the i'th led to black
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(100);
	}
}
