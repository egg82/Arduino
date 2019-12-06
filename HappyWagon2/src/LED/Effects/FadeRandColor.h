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
    void loop(CHSV leds[], int16_t fft[], int16_t peak);
    void destroy(CHSV leds[], int16_t fft[], int16_t peak);
    bool isDestroyed() { return destroyed; }
};

#endif