#ifndef IEffect_h
#define IEffect_h

#include <FastLED.h>

class IEffect {
    public:
    virtual ~IEffect(){};
    virtual bool canLoop(unsigned long delta) { return true; }
    virtual void loop(CHSV leds[], uint8_t fht[], uint8_t max) = 0;
    virtual void destroy(CHSV leds[], uint8_t fht[], uint8_t max) = 0;
    virtual bool isDestroyed() { return true; }
};

#endif