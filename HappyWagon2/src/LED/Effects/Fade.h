#ifndef Fade_h
#define Fade_h

#include "IEffect.h"

class Fade : public IEffect {
    private:
    bool destroyed = false;
    bool fadeReverse = false;
    public:
    Fade();
    bool canLoop(unsigned long delta) { return delta >= 10; }
    void loop(CHSV leds[], uint8_t fht[], uint8_t max);
    void destroy(CHSV leds[], uint8_t fht[], uint8_t max);
    bool isDestroyed() { return destroyed; }
};

#endif