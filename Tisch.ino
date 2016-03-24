#include "myTischConfig.h"
#include "myGameOfLife.h"
#include "myASCII.h"
#include "myNoise.h"
#include "myNoisePlusPalette.h"
#include "myUtils.h"
#include "myTimeDate.h"
#include "myRainbowCycle.h"

CRGB leds[NUM_LEDS];

uint8_t brightness = 20;
CRGB fg_color = CRGB(200,200,200);
CRGB bg_color = CRGB(0,0,0);

bool displayEnabled = true;

// functions to call via cloud:
int incBrightness(String command);
int decBrightness(String command);
int getBrightness(String command);
int setBrightness(String value);
int enableDisplay(String command);
int disableDisplay(String command);
int setDisplayMode(String command);
int getDisplayMode(String command);
int setFgColor(String command);
int setBgColor(String command);

#define DATA_PIN 7

#define ONE_DAY_MILLIS (24 * 60 * 60 * 1000)
unsigned long lastSync = millis();

// Display modes:
// 1: GameOfLife
// 2: Noise
// 3: Time and Date
// 4: RainbowCycle
// 5: NoisePlusPalette

int dispMode = 2;

int incBrightness(String command)
{
    brightness++;
    FastLED.setBrightness(brightness);

    saveSettings();
    return brightness;
}

int decBrightness(String command)
{
    brightness--;
    brightness = (brightness < 0) ? 0 : brightness;
    FastLED.setBrightness(brightness);

    saveSettings();
    return brightness;
}

int getBrightness(String command) { return brightness; }

int setBrightness(String value)
{
    brightness = atoi(value);
    FastLED.setBrightness(brightness);

    saveSettings();
    return brightness;
}

int enableDisplay(String command)
{
    displayEnabled = true;

    saveSettings();
    return 1;
}

int disableDisplay(String command)
{
    displayEnabled = false;

    saveSettings();
    return 1;
}

int setFgColor(String command)
{
  char *rgbstr = (char *)malloc(command.length()+1);

  rgbstr = strcpy(rgbstr, (const char *)command);

  if (command.length() == 11) {
    int r = atoi(strsep(&rgbstr,","));
    int g = atoi(strsep(&rgbstr,","));
    int b = atoi(strsep(&rgbstr,","));

    fg_color = CRGB(r,g,b);
  }

  free(rgbstr);

  saveSettings();
  return 1;
}

int setBgColor(String command)
{
  char *rgbstr = (char *)malloc(command.length()+1);

  rgbstr = strcpy(rgbstr, (const char *)command);

  if (command.length() == 11) {
    int r = atoi(strsep(&rgbstr,","));
    int g = atoi(strsep(&rgbstr,","));
    int b = atoi(strsep(&rgbstr,","));

    bg_color = CRGB(r,g,b);
  }

  free(rgbstr);

  saveSettings();
  return 1;
}

int getDisplayMode(String command) { return dispMode; }

int setDisplayMode(String command)
{
  dispMode = atoi(command);

  switch (dispMode) {
     case 1: setupGameOfLife();
         break;
     case 2: setupNoise();
        break;
     case 3: setupTimeDate();
        break;
     case 4: setupRainbowCycle();
        break;
     case 5: setupNoisePlusPalette();
        break;
     default:
        break;
  }

  saveSettings();
  return dispMode;
}

void loadSettings() {
  int address = 1;

  brightness = EEPROM.read(address++);
  dispMode = EEPROM.read(address++);
  fg_color.r = EEPROM.read(address++);
  fg_color.g = EEPROM.read(address++);
  fg_color.b = EEPROM.read(address++);
  bg_color.r = EEPROM.read(address++);
  bg_color.g = EEPROM.read(address++);
  bg_color.b = EEPROM.read(address++);
  displayEnabled = EEPROM.read(address++);

  for (int i=0; i++; i < NUM_LEDS) {
    leds[i] = EEPROM.read(address++);
  }
}

void saveSettings() {
  int address = 1;

  EEPROM.write(address++, brightness);
  EEPROM.write(address++, dispMode);
  EEPROM.write(address++, fg_color.r);
  EEPROM.write(address++, fg_color.g);
  EEPROM.write(address++, fg_color.b);
  EEPROM.write(address++, bg_color.r);
  EEPROM.write(address++, bg_color.g);
  EEPROM.write(address++, bg_color.b);
  EEPROM.write(address++, displayEnabled);

  for (int i=0; i++; i < NUM_LEDS) {
    EEPROM.write(address++, leds[i]);
  }
}

void setup() {

  // register the cloud function
  Particle.function("incBright", incBrightness);
  Particle.function("decBright", decBrightness);
  Particle.function("getBright", getBrightness);
  Particle.function("setBright", setBrightness);
  Particle.function("enaDisplay", enableDisplay);
  Particle.function("disDisplay", disableDisplay);
  Particle.function("getDisMode", getDisplayMode);
  Particle.function("setDisMode", setDisplayMode);
  Particle.variable("dispMode", dispMode);
  Particle.function("setFgColor", setFgColor);
  Particle.function("setBgColor", setBgColor);

  loadSettings();

dispMode = 2;

  switch (dispMode) {
      case 1: setupGameOfLife();
        break;
      case 2: setupNoise();
        break;
      case 3: setupTimeDate();
        break;
      case 4: setupRainbowCycle();
        break;
      case 5: setupNoisePlusPalette();
        break;
      default:
        break;
  }

  Time.zone(+1);
  FastLED.addLeds<WS2812B,DATA_PIN>(leds,NUM_LEDS);
  FastLED.setBrightness(brightness);

}

void loop() {

  // once a day sync time with cloud:
  if (millis() - lastSync > ONE_DAY_MILLIS) {
    // Request time synchronization from the Particle Cloud
    Particle.syncTime();
    lastSync = millis();
  }

  if (displayEnabled) {
      switch (dispMode) {
          case 1: loopGameOfLife();
            break;
          case 2: loopNoise();
            break;
          case 3: loopTimeDate();
            break;
          case 4: loopRainbowCycle();
            break;
          case 5: loopNoisePlusPalette();
            break;
          default:
            break;
      }
    } else {
      for(int i = 0; i < kMatrixWidth; i++) {
        for(int j = 0; j < kMatrixHeight; j++) {
            leds[XY(i,j)] = 0;
            }
        }
    }

  LEDS.show();
  delay(10);
}
