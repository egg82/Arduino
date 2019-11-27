#ifndef FadeRandColor_h
#define FadeRandColor_h

#include "IEffect.h"

class FadeRandColor : public IEffect {
    private:
    bool destroyed = false;
    bool fadeReverse = false;
    public:
    FadeRandColor();
    bool canLoop(unsigned long delta) { return delta >= 10; }
    void loop(CHSV leds[], uint8_t fht[], uint8_t max);
    void destroy(CHSV leds[], uint8_t fht[], uint8_t max);
    bool isDestroyed() { return destroyed; }
};

#endif