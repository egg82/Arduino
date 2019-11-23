#ifndef RadiateRandColor_h
#define RadiateRandColor_h

#include "IEffect.h"
#include "../LEDController.h"

class RadiateRandColor : public IEffect {
    private:
    bool isSet = false;
    bool destroyed = false;
    int currentLED = 0;
    int middleLED = 0;
    int tailLength = NUM_LEDS / 5;
    public:
    RadiateRandColor();
    bool canLoop(unsigned long delta) { return !isSet ? delta >= 10 : delta >= 50; }
    bool isSetup() { return isSet; }
    void setup(CHSV leds[]);
    void loop(CHSV leds[]);
    void destroy(CHSV leds[]);
    bool isDestroyed() { return destroyed; }
};

#endif