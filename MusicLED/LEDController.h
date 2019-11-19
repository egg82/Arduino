#ifndef LEDController_h
#define LEDController_h

#include <FastLED.h>

#define NUM_LEDS 30
#define PIN 3

class LEDController {
    public:
    LEDController();
    void setLED(int led, CRGB color);
    void setLED(int led, CHSV hue);
    void clear(CRGB color);
    void clear(CHSV hue);
};
#endif