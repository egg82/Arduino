#ifndef IEffect_h
#define IEffect_h

#include <FastLED.h>

class IEffect {
    public:
    virtual ~IEffect(){};
    virtual bool isSetup() { return true; }
    virtual void setup(CHSV leds[]) = 0;
    virtual void loop(CHSV leds[]) = 0;
    virtual void destroy(CHSV leds[]) = 0;
    virtual bool isDestroyed() { return true; }
};

#endif