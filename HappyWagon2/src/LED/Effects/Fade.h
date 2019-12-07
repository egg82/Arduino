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
    void loop(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    void destroy(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    bool isDestroyed() { return destroyed; }
};

#endif