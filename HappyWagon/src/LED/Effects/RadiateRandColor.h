#ifndef RadiateRandColor_h
#define RadiateRandColor_h

#include "IEffect.h"

class RadiateRandColor : public IEffect {
    private:
    bool isSet = false;
    bool destroyed = false;
    int currentLED = 0;
    int middleLED = 0;
    public:
    RadiateRandColor();
    bool isSetup() { return isSet; }
    void setup(CHSV leds[]);
    void loop(CHSV leds[]);
    void destroy(CHSV leds[]);
    bool isDestroyed() { return destroyed; }
};

#endif