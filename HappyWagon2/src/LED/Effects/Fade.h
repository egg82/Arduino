#ifndef Fade_h
#define Fade_h

#include "IEffect.h"

class Fade : public IEffect {
    private:
    bool isSet = false;
    bool destroyed = false;
    bool fadeReverse = false;
    public:
    Fade();
    bool canLoop(unsigned long delta) { return delta >= 10; }
    bool isSetup() { return isSet; }
    void setup(CHSV leds[]);
    void loop(CHSV leds[]);
    void destroy(CHSV leds[]);
    bool isDestroyed() { return destroyed; }
};

#endif