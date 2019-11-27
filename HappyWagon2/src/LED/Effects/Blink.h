#ifndef Blink_h
#define Blink_h

#include "IEffect.h"

class Blink : public IEffect {
    private:
    bool destroyed = false;
    public:
    Blink();
    bool canLoop(unsigned long delta) { return delta >= 500; }
    void loop(CHSV leds[], uint8_t fht[], uint8_t max);
    void destroy(CHSV leds[], uint8_t fht[], uint8_t max);
    bool isDestroyed() { return destroyed; }
};

#endif