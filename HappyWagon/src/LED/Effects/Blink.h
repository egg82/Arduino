#ifndef Blink_h
#define Blink_h

#include "IEffect.h"

class Blink : public IEffect {
    private:
    bool isSet = false;
    bool destroyed = false;
    public:
    Blink();
    bool canLoop(unsigned long delta) { return !isSet ? delta >= 10 : delta >= 500; }
    bool isSetup() { return isSet; }
    void setup(CHSV leds[]);
    void loop(CHSV leds[]);
    void destroy(CHSV leds[]);
    bool isDestroyed() { return destroyed; }
};

#endif