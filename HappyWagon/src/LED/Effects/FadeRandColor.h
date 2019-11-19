#ifndef FadeRandColor_h
#define FadeRandColor_h

#include "IEffect.h"

class FadeRandColor : public IEffect {
    private:
    bool isSet = false;
    bool destroyed = false;
    bool fadeReverse = false;
    public:
    FadeRandColor();
    bool isSetup() { return isSet; }
    void setup(CHSV leds[]);
    void loop(CHSV leds[]);
    void destroy(CHSV leds[]);
    bool isDestroyed() { return destroyed; }
};

#endif