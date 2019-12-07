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
    void loop(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    void destroy(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    bool isDestroyed() { return destroyed; }
};

#endif